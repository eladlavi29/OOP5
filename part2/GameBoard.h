//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

struct GameBoard{
    List<List<BoardCell>> board;
    int width;
    int length;
};

#endif //OOP5_GAMEBOARD_H
