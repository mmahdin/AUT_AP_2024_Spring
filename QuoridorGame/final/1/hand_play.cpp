#include "hand_play.h"
#include <iostream>

Move hand_play() {
    int wall_or_piece;
    std::cout << "Wall or piece(0 for wall, 1 for piece): " << std::endl;
    std::cin >> wall_or_piece;
    if (wall_or_piece == 0) {
        std::cout << "Give the wall position x, y, hv (horizontal=1, vertical=0): " << std::endl;
        int x, y, hv;
        std::cin >> x >> y >> hv;
        Move move{wall_or_piece, x, y, 0, hv};
        return move;
    } else {
        std::cout << "Give the piece position x, y: " << std::endl;
        int x, y;
        std::cin >> x >> y;
        std::cout<<"x, y: "<<x<<" "<<y<<std::endl;
        Move move{wall_or_piece, x, y, 0};
        return move;
    }
}
