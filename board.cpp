#include "board.h"

#include <iostream>

void Board::show_board(){
    for(size_t i=0; i<19; i++){
        for(size_t j=0; j<19; j++){
            if(positions[i][j]==0)
                std::cout<<" ";
            else if(positions[i][j]==1)
                std::cout<<"1";
            else if(positions[i][j]==6)
                std::cout<<"6";
            else if(positions[i][j]==2)
                std::cout<<"__";
            else if(positions[i][j]==-2)
                std::cout<<"| ";
            else if(positions[i][j]==3)
                std::cout<<"__";
            else if(positions[i][j]==-3)
                std::cout<<"| ";
            else if(positions[i][j]==4)
                std::cout<<"VV";
            else if(positions[i][j]==-4)
                std::cout<<"H ";
            else
                std::cout<<".";
        }
        std::cout<<std::endl;
    }
}

bool Board::is_finished(){
    if(blue_piece_pos[1]==17){
        std::cout<<"Game is finished, player blue is winner";
        return true;
    }
    else if(red_piece_pos[1]==1){
        std::cout<<"Game is finished, player blue is winner";
        return true;
    }
    else
        return false;
}

bool in_range(size_t pos, size_t dir){
    if(pos!=dir+2 || pos!=dir-2)
        return true;
    else
        return false;
}
bool Board::piece_move_is_valid(size_t piece_pos[2], size_t x, size_t y){
    x = 2*x-1;
    y = 2*y-1;

    if(!in_range(piece_pos[0], x)||!in_range(piece_pos[1], y))
        return false;
    if(x>piece_pos[0]){
        if(positions[x-1][y]==-2 || positions[x-1][y]==-3){
            std::cout<<"your way is vertically blocked";
            return false;
        }
    }
    else{
        if(positions[x+1][y]==-4 || positions[x+1][y]==-3){
            std::cout<<"your way is vertically blocked";
            return false;
        }
    }
    if(y>piece_pos[1]){
        if(positions[x][y-1]==4 || positions[x][y-1]==3){
            std::cout<<"your way is horizontally blocked";
            return false;
        }
    }
    else{
        if(positions[x][y+1]==4 || positions[x][y+1]==3){
            std::cout<<"your way is horizontally blocked";
            return false;
        }
    }
    return true;
}

bool wall_put_is_valid(int wall_num, int hor_ver, size_t x, size_t y){
    if(wall_num<=0)
        return false;
    x = x+(x-1)-1;
    y = y+(y-1)-1;
    if(hor_ver==0){         // 0 = horizontal
        if(y==0 || y==9)
            return false;
    } 
    else{         // vertical
        if(x==0 || x==9)
            return false;
    } 
}
