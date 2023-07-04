//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"

template<CellType T, Direction D, int L>
struct BoardCell{
    static const CellType type = T;
    static const Direction direction = D;
    static const int length = L;
};

#endif //OOP5_BOARDCELL_H
