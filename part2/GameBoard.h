//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_GAMEBOARD_H
#define OOP5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

template<typename>
struct GameBoard;

template<typename T, typename... TT>
struct GameBoard<List<T,TT...>>{
    typedef List<T,TT...> board;
    enum {
        width = T::size,
        length = List<T,TT...>::size
    };
};

#endif //OOP5_GAMEBOARD_H
