//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

//todo: solve problem

template<List<List<BoardCell>> B, int W, int L>
struct GameBoard{
    enum {
        board = B,
        width = W,
        length = L
    };
};

#endif //OOP5_GAMEBOARD_H
