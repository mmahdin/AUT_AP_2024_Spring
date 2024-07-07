#include "AStar.h"

// Heuristic function: Manhattan distance
int heuristic(int x1, int x2) {
    return abs(x1 - x2);
}

// A* algorithm function
bool is_path_to_end_AS(std::pair<int,int> start, int goalX, std::vector<std::vector<int>>& walls) {
    std::priority_queue<Node, std::vector<Node>, CompareNode> openSet;
    std::unordered_set<int> closedSet;
    auto hash = [&](int x, int y) { return x * 9 + y; };
    int startX = start.first;
    int startY = start.second;
    openSet.emplace(Node(startX, startY, 0, heuristic(startX, goalX)));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();
        
        if (current.x == goalX) {
            return true;
        }

        closedSet.insert(hash(current.x, current.y));

        // Get possible moves from the current point
        int directions = validMove(current.x, current.y, walls);
        std::vector<std::pair<int,int>> moves = dirction2position(directions, current.x, current.y);

        for (auto& neighbor : moves) {
            int nx = neighbor.first, ny = neighbor.second;
            if (is_valid_point(nx, ny, 9)){
                if (closedSet.count(hash(nx, ny))) continue;
                int tentativeG = current.g + 1;
                openSet.emplace( Node(nx, ny, tentativeG, heuristic(nx, goalX)));
            }
        }
    }

    return false; 
}