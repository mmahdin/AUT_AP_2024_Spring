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

void Board::move(int piece, size_t x, size_t y){
    if()
}