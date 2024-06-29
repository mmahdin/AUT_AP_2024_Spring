#ifndef ASTAR_H
#define ASTAR_H

#include "Board.h"
#include <unordered_set>

// Define a structure for the nodes in the priority queue
struct Node {
    int x, y;
    int g, h; // g is the cost from start to current node, h is the heuristic cost to the goal
    Node(int x, int y, int g, int h) : x(x), y(y), g(g), h(h) {}
    int f() const { return g + h; }
};

struct CompareNode {
    bool operator()(const Node a, const Node b) {
        return a.f() > b.f();
    }
};

bool is_path_to_end_AS(std::pair<int,int> start, int goalX, std::vector<std::vector<int>>& walls);
std::vector<std::pair<int, int>> way_to_win(std::pair<int,int> start, int goalX, std::vector<std::vector<int>>& walls);

int heuristic(int x1, int x2);


#endif