//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "List.h"
#include "Utilities.h"
#include "CellType.h"
#include "Direction.h"

template<CellType T, Direction D, int A>
struct Move{
    static_assert(T != EMPTY, "Can't move EMPTY cells!");
    enum {
        type = T,
        direction = D,
        amount = A
    };
};


#endif //OOP5_MOVEVEHICLE_H














