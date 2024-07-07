#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include "Board.h"	// Include your Board header
#include "Logger.h"
#include "Minimax.h"
#include "Move.h"
#include "hand_play.h"

using boost::asio::ip::tcp;
namespace json = boost::json;
// Function to convert game state to JSON
json::value serialize_game_state(const std::shared_ptr<Board>& board,
								 const std::vector<Move>& turnHistory) {
	json::value game_state = {
		{"gameInfo",
		 {{"gameId", "unique_game_identifier"},
		  {"gameStatus",
		   board->is_finished()
			   ? (board->who_is_winner() == '1' ? "player1wins" : "player2wins")
			   : "ongoing"},
		  {"currentTurn",
		   (turnHistory.size() % 2 == 0) ? "player1" : "player2"}}},
		{"settings",
		 {{"playerCount", 2},
		  {"timePerMove", 30},
		  {"totalWalls", 20},
		  {"boardSize", 9}}},
		{"players",
		 json::array({{{"id", "player1"},
					   {"type", "human"},
					   {"position",
						{{"x", board->getPlayer(1).getX()/2},
						 {"y", board->getPlayer(1).getY()/2}}},
					   {"wallsLeft", board->getPlayer(1).get_wall_left()},
					   {"color", "black"}},
					  {{"id", "player2"},
					   {"type", "human"},
					   {"position",
						{{"x", board->getPlayer(2).getX()/2},
						 {"y", board->getPlayer(2).getY()/2}}},
					   {"wallsLeft", board->getPlayer(2).get_wall_left()},
					   {"color", "white"}}})},
		{"walls",
		 {{"horizontal", json::array({})}, {"vertical", json::array({})}}},
		{"turnHistory", json::array()}};

	// Serialize walls
	for (const auto& wall : board->get_H_walls()) {
		game_state.at("walls")
			.at("horizontal")
			.as_array()
			.emplace_back(json::object(
				{{"start", {{"x", wall.startX/2}, {"y", wall.startY/2}}},
				 {"end", {{"x", wall.startX/2}, {"y", wall.startY/2 + 2}}}}));
	}
	for (const auto& wall : board->get_V_walls()) {
		game_state.at("walls")
			.at("vertical")
			.as_array()
			.emplace_back(json::object(
				{{"start", {{"x", wall.startX/2}, {"y", wall.startY/2}}},
				 {"end", {{"x", wall.startX/2 + 2}, {"y", wall.startY/2}}}}));
	}

	// Serialize turn history
	int moveCount = 1;
	for (const auto& move : turnHistory) {
		game_state.at("turnHistory")
			.as_array()
			.emplace_back(json::object(
				{{"moveCount", moveCount++},
				 {"playerId", move.wall_or_piece == 0 ? "player1" : "player2"},
				 {"action", move.wall_or_piece == 0 ? "placeWall" : "move"},
				 {"details",
				  move.wall_or_piece == 0
					  ? json::object(
							{{"start", {{"x", move.newX}, {"y", move.newY}}},
							 {"end",
							  {{"x", move.newX + (move.hv == 0 ? 1 : 0)},
							   {"y", move.newY + (move.hv == 1 ? 1 : 0)}}}})
					  : json::object(
							{{"from", {{"x", move.newX}, {"y", move.newY}}},
							 {"to", {{"x", move.newX}, {"y", move.newY}}}})}}));
	}

	return game_state;
}

// Function to update game state from JSON
void deserialize_game_state(const json::value& game_state,
							std::shared_ptr<Board>& board,
							std::vector<Move>& turnHistory) {
	const auto& players = game_state.at("players").as_array();
	board->movePlayer(1, players[0].at("position").at("x").as_int64(), players[0].at("position").at("y").as_int64());
	board->getPlayer(1).set_wall_left(players[0].at("wallsLeft").as_int64());

	board->movePlayer(2, players[0].at("position").at("x").as_int64(), players[0].at("position").at("y").as_int64());
	board->getPlayer(2).set_wall_left(players[1].at("wallsLeft").as_int64());

	board->clear_walls();
	for (const auto& wall :
		 game_state.at("walls").at("horizontal").as_array()) {
		board->addWall(wall.at("start").at("x").as_int64(),
					   wall.at("start").at("y").as_int64(), 1);
	}
	for (const auto& wall : game_state.at("walls").at("vertical").as_array()) {
		board->addWall(wall.at("start").at("x").as_int64(),
					   wall.at("start").at("y").as_int64(), 0);
	}

	turnHistory.clear();
	for (const auto& move : game_state.at("turnHistory").as_array()) {
		Move m;
		if (move.at("action").as_string() == "placeWall") {
			m.wall_or_piece = 0;
			m.newX = move.at("details").at("start").at("x").as_int64();
			m.newY = move.at("details").at("start").at("y").as_int64();
			m.hv = move.at("details").at("end").at("y").as_int64() == m.newY
					   ? 1
					   : 0;
		} else {
			m.wall_or_piece = 1;
			m.newX = move.at("details").at("to").at("x").as_int64();
			m.newY = move.at("details").at("to").at("y").as_int64();
		}
		turnHistory.push_back(m);
	}
}


void send_json(tcp::socket& socket, const std::string& json_str) {
    boost::asio::write(socket, boost::asio::buffer(json_str + "\n"));
}


json::value receive_json(tcp::socket& socket) {
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\n");

    std::istream response_stream(&response);
    std::string response_str;
    std::getline(response_stream, response_str);

    json::value json_response = json::parse(response_str);
    return json_response;
}

int main() {
	Logger logger("game.log");
    logger.log("Game started", Logger::INFO);

    Player player1(0, 4, '1');
    Player player2(8, 4, '2');
    std::shared_ptr<Board> board = std::make_shared<Board>(player1, player2, logger);
    board->display();

    M_Node rootNode{board, Move{}};
    Minimax minimax(4, rootNode, true, 1);

    Move bestMove;

	std::vector<Move> turnHistory;

    try {
        boost::asio::io_service io_service;
        tcp::socket socket(io_service);
        tcp::resolver resolver(io_service);
        boost::asio::connect(socket, resolver.resolve({"localhost", "60011"}));

        json::value json_data = {
            {"message", "Hello from C++ client 1"}
        };

        std::string json_str = json::serialize(json_data);

        while (!board->is_finished()) {
			json::value res = receive_json(socket);
			deserialize_game_state(res, board, turnHistory);
			std::cout<< "**************************************" << std::endl;
			std::cout << "Player1:  " << std::endl;
			board->display();

			auto start = std::chrono::high_resolution_clock::now(); // Start time

			bestMove = minimax();

			auto end = std::chrono::high_resolution_clock::now(); // End time
			std::chrono::duration<double> duration = end - start;
			std::cout << "Time taken for minimax(): " << duration.count() << " seconds" << std::endl;

			
			if (bestMove.wall_or_piece == 0) {
				board->addWall(bestMove.newX, bestMove.newY, bestMove.hv);
				std::cout << "Player 2 Place " << bestMove.hv << " Wall at " << bestMove.newX << " " << bestMove.newY << std::endl;
			} else {
				board->movePlayer(2, bestMove.newX, bestMove.newY);
				board->use_wall(2);
				std::cout<< "Player 2 Move to " << bestMove.newX << " " << bestMove.newY << std::endl;
			}

			turnHistory.push_back(bestMove);
			json_data = serialize_game_state(board, turnHistory);
			std::string json_str = json::serialize(json_data);

			std::cout << "Player2: " << std::endl;
			board->display();
			std::cout<< "**************************************" << std::endl;
            send_json(socket, json_str);
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
