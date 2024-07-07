#include "BFS.h"


bool is_path_to_end_BFS(std::pair<int,int> start, int end_row, std::vector<std::vector<int>>& walls){
    std::queue<std::pair<int,int>> q;
    q.push(start);

    // Set to keep track of visited points
    std::set<std::pair<int, int>> visited;
    visited.insert({start.first, start.second});

    while (!q.empty()) {
        std::pair<int,int> current = q.front();
        q.pop();
        
        // Check if we've reached the end row
        if (current.first == end_row) {
            return true;
        }
        
        // Get possible moves from the current point
        int directions = validMove(current.first, current.second, walls);
        std::vector<std::pair<int,int>> moves = dirction2position(directions, current.first, current.second);
        
        // Process each move
        for (const auto& move : moves) {
            if (is_valid_point(move.first, move.second, 9) && visited.find({move.first, move.second}) == visited.end()) {
                q.push(move);
                visited.insert({move.first, move.second});
            }
        }
    }
    return false;
}