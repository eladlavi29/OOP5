//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"

struct BoardCell{
    CellType type;
    Direction direction;
    int length;
};

#endif //OOP5_BOARDCELL_H
