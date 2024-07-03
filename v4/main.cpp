#include <boost/asio.hpp>
#include <boost/json.hpp>
#include "Board.h" // Include your Board header
#include "Logger.h"
#include "Minimax.h"
#include "Move.h"
#include "hand_play.h"
using boost::asio::ip::tcp;
namespace json = boost::json;

// Function to convert game state to JSON
json::value serialize_game_state(const std::shared_ptr<Board>& board, const std::vector<Move>& turnHistory) {
    json::value game_state = {
        {"gameInfo", {
            {"gameId", "unique_game_identifier"},
            {"gameStatus", board->is_finished() ? (board->who_is_winner() == '1' ? "player1wins" : "player2wins") : "ongoing"},
            {"currentTurn", (turnHistory.size() % 2 == 0) ? "player1" : "player2"}
        }},
        {"settings", {
            {"playerCount", 2},
            {"timePerMove", 30},
            {"totalWalls", 20},
            {"boardSize", 9}
        }},
        {"players", json::array({
            {
                {"id", "player1"},
                {"type", "human"},
                {"position", {{"x", board->getPlayer(1).getX()}, {"y", board->getPlayer(1).getY()}}},
                {"wallsLeft", board->getPlayer(1).get_wall_left()},
                {"color", "black"}
            },
            {
                {"id", "player2"},
                {"type", "human"},
                {"position", {{"x", board->getPlayer(2).getX()}, {"y", board->getPlayer(2).getY()}}},
                {"wallsLeft", board->getPlayer(2).get_wall_left()},
                {"color", "white"}
            }
        })},
        {"walls", {
            {"horizontal", json::array({})},
            {"vertical", json::array({})}
        }},
        {"turnHistory", json::array()}
    };

    // Serialize walls
    for (const auto& wall : board->get_H_walls()) {
        game_state.at("walls").at("horizontal").as_array().emplace_back(json::object({{"start", {{"x", wall.startX}, {"y", wall.startY}}}, {"end", {{"x", wall.startX}, {"y", wall.startY+2}}}}));
    }
    for (const auto& wall : board->get_V_walls()) {
        game_state.at("walls").at("vertical").as_array().emplace_back(json::object({{"start", {{"x", wall.startX}, {"y", wall.startY}}}, {"end", {{"x", wall.startX+2}, {"y", wall.startY}}}}));
    }

    // Serialize turn history
    int moveCount = 1;
    for (const auto& move : turnHistory) {
        game_state.at("turnHistory").as_array().emplace_back(json::object({
            {"moveCount", moveCount++},
            {"playerId", move.wall_or_piece == 0 ? "player1" : "player2"},
            {"action", move.wall_or_piece == 0 ? "placeWall" : "move"},
            {"details", move.wall_or_piece == 0 ? json::object({{"start", {{"x", move.newX}, {"y", move.newY}}}, {"end", {{"x", move.newX + (move.hv == 0 ? 1 : 0)}, {"y", move.newY + (move.hv == 1 ? 1 : 0)}}}}) : json::object({{"from", {{"x", move.newX}, {"y", move.newY}}}, {"to", {{"x", move.newX}, {"y", move.newY}}}})
        }}));
    }

    return game_state;
}

std::string dummy_function(const std::shared_ptr<Board>& board, const std::vector<Move>& turnHistory) {
    json::value game_state = serialize_game_state(board, turnHistory);
    return json::serialize(game_state);
}


void handle_connection(tcp::socket& socket, const std::shared_ptr<Board>& board, const std::vector<Move>& turnHistory) {
    try {
        boost::asio::streambuf buffer;
        boost::system::error_code error;

        // Read data until newline
        boost::asio::read_until(socket, buffer, "\n", error);

        if (error && error != boost::asio::error::eof) {
            throw boost::system::system_error(error);
        }

        std::istream stream(&buffer);
        std::string received_data((std::istreambuf_iterator<char>(stream)),
                      std::istreambuf_iterator<char>());
        std::cout << "Received JSON: " << received_data << std::endl;

        // Parse the JSON
        json::value parsed_data = json::parse(received_data);
// Perform dummy function and send response
        std::string response = dummy_function(board, turnHistory);
        boost::asio::write(socket, boost::asio::buffer(response + "\n"), error);

        if (error) {
            throw boost::system::system_error(error);
        }

        std::cout << "Sent JSON: " << response << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 6668));

        std::cout << "Server listening on port 12345" << std::endl;

        // Initialize game
        Logger logger("game.log");
        logger.log("Game started", Logger::INFO);

        Player player1(0, 4, '1');
        Player player2(8, 4, '2');
        std::shared_ptr<Board> board = std::make_shared<Board>(player1, player2, logger);
        board->display();

        std::vector<Move> turnHistory;
        M_Node rootNode{board, Move{}};
        Minimax minimax(4, rootNode, true, 0);

        Move bestMove;
        int i = 0;
        while (!board->is_finished()) {
            if (i % 2 == 0) {
                auto start = std::chrono::high_resolution_clock::now(); // Start time
                bestMove = minimax();
                auto end = std::chrono::high_resolution_clock::now(); // End time
                std::chrono::duration<double> duration = end - start;
                std::cout << "Time taken for minimax(): " << duration.count() << " seconds" << std::endl;
            } else {
                bestMove = hand_play();
            }

            if (bestMove.wall_or_piece == 0) {
                board->addWall(bestMove.newX, bestMove.newY, bestMove.hv);
                board->use_wall(i % 2 + 1);
            } else {
                board->movePlayer(i % 2 + 1, bestMove.newX, bestMove.newY);
            }

            i++;
            turnHistory.push_back(bestMove);
            board->display();
        }

        char winner = board->who_is_winner();
        std::cout << "Player " << winner << " wins!" << std::endl;
        logger.log("Game ended", Logger::INFO);

        // Accept connections and handle them
        while (true) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            handle_connection(socket, board, turnHistory);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}