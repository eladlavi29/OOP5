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
    static const int width = T::size;
    static const int length =  List<T,TT...>::size;
};

#endif //OOP5_GAMEBOARD_H
