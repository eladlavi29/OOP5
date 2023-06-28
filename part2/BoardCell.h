//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_BOARDCELL_H
#define OOP5_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"

template<CellType T, Direction D, int L>
struct BoardCell{
    enum {
        type = T,
        direction = D,
        length = L
    };
};

#endif //OOP5_BOARDCELL_H
