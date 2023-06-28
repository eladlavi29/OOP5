//
// Created by amirb on 28/06/2023.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "List.h"
#include "Utilities.h"
#include "CellType.h"
#include "Direction.h"
#include "BoardCell.h"
#include "GameBoard.h"

template<CellType T, Direction D, int A>
struct Move{
    static_assert(T != EMPTY, "Can't move EMPTY cells!");
    enum {
        type = T,
        direction = D,
        amount = A
    };
};

template<typename, int, int>
struct GetCell{};

template<int R, int C, typename... TT>
struct GetCell<List<TT...>,R,C>{
    typedef typename GetAtIndex<R,List<TT...>>::value temp;
    typedef typename GetAtIndex<C,temp>::value cell;
};

template<typename, int, int, typename >
struct SetCell{};

template<int R, int C, typename S, typename... TT>
struct SetCell<List<TT...>,R,C,S>{
    typedef typename GetAtIndex<R,List<TT...>>::value temp1;
    typedef typename SetAtIndex<C,S,temp1>::list temp2;

    typedef typename SetAtIndex<R,temp2, List<TT...>>::list value;
};

template<Direction, Direction>
struct Comp_Directions{
    enum{
        value = false
    };
};
template<>
struct Comp_Directions<UP, UP>{
    enum{
        value = true
    };
};
template<>
struct Comp_Directions<DOWN, UP>{
    enum{
        value = true
    };
};
template<>
struct Comp_Directions<UP, DOWN>{
    enum{
        value = true
    };
};
template<>
struct Comp_Directions<DOWN, DOWN>{
    enum{
        value = true
    };
};
template<>
struct Comp_Directions<RIGHT, RIGHT>{
    enum{
        value = true
    };
};
template<>
struct Comp_Directions<RIGHT, LEFT>{
    enum{
        value = true
    };
};
template<>
struct Comp_Directions<LEFT, RIGHT>{
    enum{
        value = true
    };
};
template<>
struct Comp_Directions<LEFT, LEFT>{
    enum{
        value = true
    };
};

template <int N>
struct dec_abs{
    enum{
        res = ConditionalInteger<(N>0), N-1,N+1>::value
    };
};



template<int,CellType,int,typename... TT>
struct getStart{};

//MAX is the len of the car at the beginning (could be either pos or neg)
template<int C, CellType TYPE, int MAX, typename... TT>
struct getStart<C,TYPE,MAX,List<TT...>>{
    enum{
        res = ConditionalInteger<GetAtIndex<C+MAX,List<TT...>>::value::type==TYPE, C+MAX, getStart<C,TYPE,dec_abs<MAX>::res,List<TT...>>::res>::value
    };
};

template<typename, int, int, Direction, int>
struct find_edges_horiz{};

template<int R, int C, Direction D, int A, typename... TT>
struct find_edges_horiz<GameBoard<List<TT...>>, R, C, D, A>{
    typedef typename GetCell<List<TT...>,R,C>::cell Cell;
    typedef typename GetAtIndex<R,List<TT...>>::value Row;
    enum{
        temp = ConditionalInteger<D==LEFT,Cell::length,-1*Cell::length>::value,
        start = getStart<C,Cell::type,temp,Row>::res,
        end = ConditionalInteger<D==LEFT,getStart<C,Cell::type,-1*temp,Row>::res-1,getStart<C,Cell::type,-1*temp,Row>::res+1>::value
    };
};

template<int, int, int, int, Direction, typename>
struct MoveVehicleAux{};

template<int A, int R, int CS, int CE, Direction D, typename... TT>
struct MoveVehicleAux<A, R, CS, CE, D, GameBoard<List<TT...>>>{
    static_assert(C >= 0 && C < GameBoard<List<TT...>>::width, "Car moved outside of the board!\n");

    typedef typename GetCell<List<TT...>,R,CS>::cell moveFrom;
    typedef typename GetCell<List<TT...>,R,CE>::cell moveTo;
    static_assert(moveTo::type == EMPTY, "Car moved to an occupied board cell!\n");

    typedef typename SetCell<List<TT...>, R, CS,
        BoardCell<EMPTY, moveFrom::direction, moveFrom::length>>::value boardUpdate1;

    typedef typename SetCell<boardUpdate1 , R, CE,
            BoardCell<moveFrom::type, moveFrom::direction, moveFrom::length>>::value boardUpdate2;

    enum{
        fromMovement = ConditionalInteger<(D == RIGHT), CS + 1, CS - 1>::value,
        toMovement = ConditionalInteger<(D == RIGHT), CE + 1, CE - 1>::value
    };

    typedef typename MoveVehicleAux<A - 1, R, fromMovement, toMovement, D,
        GameBoard<boardUpdate2>>::gameboard gameboard;
};

template<int R, int CS, int CE, Direction D, typename... TT>
struct MoveVehicleAux<0, R, CS, CE, D, GameBoard<List<TT...>>>{
    typedef GameBoard<List<TT...>> gameboard;
};

template<typename GB, int, int, Direction, int, typename... TT>
struct MoveVehicle_Horiz{};

template<int R, int C, Direction D, int A, typename... TT>
struct MoveVehicle_Horiz<GameBoard<List<TT...>>, R, C, D, A>{
    typedef GameBoard<List<TT...>> initial_Board;
    typedef typename  GetCell<List<TT...>,R,C>::cell Cell;
    static_assert((R>=0 && R<initial_Board::length), "Row is not in Range!");
    static_assert((C>=0 && C<initial_Board::width), "Column is not in Range!");
    static_assert((R>=0 && R<initial_Board::length), "Row is not in Range!");
    static_assert(Cell::type!=EMPTY,"The Selected Cell is EMPTY");
    static_assert(Comp_Directions<Cell::direction,D>::value, "Directions of car and movement are Not Compatible!");
    typedef find_edges_horiz<GameBoard<List<TT...>>, R, C, D, A> Temp;
    //typedef typename MoveVehicleAux<GameBoard<List<TT...>>, R, Temp::start, Temp::end, D, A>::gameboard board;
};



#endif //OOP5_MOVEVEHICLE_H














