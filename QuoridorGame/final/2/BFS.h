#ifndef BFS_H
#define BFS_H

#include "Board.h"

bool is_path_to_end_BFS(std::pair<int,int> start, int end_row, std::vector<std::vector<int>>& walls);

#endif