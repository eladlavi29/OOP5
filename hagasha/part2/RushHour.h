//
// Created by Elad on 28/06/2023.
//

#ifndef OOP5_RUSHHOUR_H
#define OOP5_RUSHHOUR_H

#include "MoveVehicle.h"

//Start search from the downward right corner of the board
#define NOT_FOUND (-1)
template<int R, int C, CellType, typename>
struct findCarRaw{};

template<int R, int C, CellType CT, typename... TT>
struct findCarRaw<R, C, CT, GameBoard<List<TT...>>>{
    static const int Rs =
        ConditionalInteger<(CT == GetCell<List<TT...>, R, C>::cell::type), R,
        findCarRaw<R - 1, C, CT, GameBoard<List<TT...>>>::Rs>::value;
};

template<int C, CellType CT, typename... TT>
struct findCarRaw<-1, C, CT, GameBoard<List<TT...>>>{
    static const int Rs = NOT_FOUND;
};

template<int C, CellType CT, typename>
struct findCarCol{};

template<int C, CellType CT, typename... TT>
struct findCarCol<C, CT, GameBoard<List<TT...>>>{
    static const int temp = findCarRaw<GameBoard<List<TT...>>::length - 1,
        C, CT, GameBoard<List<TT...>>>::Rs;
    static const int Cs =
        ConditionalInteger<(temp != NOT_FOUND), C,
        findCarCol<C - 1, CT, GameBoard<List<TT...>>>::Cs>::value;
};

template<CellType CT, typename... TT>
struct findCarCol<-1, CT, GameBoard<List<TT...>>>{
    static const int Rs = NOT_FOUND;
    static const int Cs = NOT_FOUND;
};

//Return a point on the car (not its beginning necessarily)
template<CellType, typename>
struct findCar{};

template<CellType CT, typename... TT>
struct findCar<CT, GameBoard<List<TT...>>>{
    static const int Cs = findCarCol<GameBoard<List<TT...>>::width - 1,
            CT, GameBoard<List<TT...>>>::Cs;
    static const int Rs = findCarRaw<GameBoard<List<TT...>>::length - 1, Cs,
            CT, GameBoard<List<TT...>>>::Rs;
};

template<int, int, typename>
struct canRedMoveOut{};

template<int R, int C, typename... TT>
struct canRedMoveOut<R, C, GameBoard<List<TT...>>>{
    typedef typename GetCell<List<TT...>,R,C>::cell Cell;

    const static bool value =
        ConditionalInteger<(Cell::type == X), 1,
        ConditionalInteger<(Cell::type != EMPTY), 0,
        canRedMoveOut<R, C - 1, GameBoard<List<TT...>>>::value>::value>::value;
};

template<int R, typename... TT>
struct canRedMoveOut<R, -1, GameBoard<List<TT...>>>{
    const static bool value = false;
};

template<typename>
struct CheckWin{};

template<typename... TT>
struct CheckWin<GameBoard<List<TT...>>>{
    static const int Rtemp = findCar<X, GameBoard<List<TT...>>>::Rs;
    static const bool result = canRedMoveOut<Rtemp,
        GameBoard<List<TT...>>::width - 1, GameBoard<List<TT...>>>::value;
};


template<int, typename, typename>
struct CheckSolutionAux{};

template<int N, typename... TT1, typename... TT2>
struct CheckSolutionAux<N, List<TT1...>, GameBoard<List<TT2...>>>{
    typedef typename GetAtIndex<List<TT1...>::size - N, List<TT1...>>::value move;

    static const int Rs = findCar<move::type, GameBoard<List<TT2...>>>::Rs;
    static const int Cs = findCar<move::type, GameBoard<List<TT2...>>>::Cs;;

    typedef typename MoveVehicle<GameBoard<List<TT2...>>,
        Rs, Cs, move::direction, move::amount>::board temp;
    typedef typename CheckSolutionAux<N - 1, List<TT1...>, temp>::board board;
};

template<typename... TT1, typename... TT2>
struct CheckSolutionAux<0, List<TT1...>, GameBoard<List<TT2...>>>{
    typedef GameBoard<List<TT2...>> board;
};

template<typename, typename>
struct CheckSolution{};

template<typename... TT1, typename... TT2>
struct CheckSolution<GameBoard<List<TT1...>>, List<TT2...>>{
    typedef typename CheckSolutionAux<List<TT2...>::size,
        List<TT2...>, GameBoard<List<TT1...>>>::board board;

    static const bool result = CheckWin<board>::result;
};

#endif //OOP5_RUSHHOUR_H
