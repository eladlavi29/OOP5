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
#include "TransposeList.h"

template<CellType T, Direction D, int A>
struct Move{
    static_assert(T != EMPTY, "Can't move EMPTY cells!");
    static const CellType type = T;
    static const Direction direction = D;
    static const int amount = A;
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
    static const int tmp1 = ConditionalInteger<(N>0), N-1,N+1>::value;
    static const int res = ConditionalInteger<(N==0), 0,tmp1>::value;
};

template<int C, CellType TYPE, int MAX,typename T>
struct getStart{};

//MAX is the len of the car at the beginning (could be either pos or neg)
template<int C, CellType TYPE, int MAX, typename... TT>
struct getStart<C,TYPE,MAX,List<TT...>>{
    static const int Eff_Max_tmp = ConditionalInteger<(C+MAX<0), 0, C+MAX>::value;
    static const int Eff_Max = ConditionalInteger<(Eff_Max_tmp>=List<TT...>::size), List<TT...>::size-1, Eff_Max_tmp>::value;
    typedef typename GetAtIndex<Eff_Max,List<TT...>>::value Cell;
    static const int res = ConditionalInteger<Cell::type==TYPE, Eff_Max, getStart<C,TYPE,dec_abs<Eff_Max-C>::res,List<TT...>>::res>::value;
};

//speciaization
template<int C, CellType TYPE, typename... TT>
struct getStart<C,TYPE,0,List<TT...>>{
    static const int res = C;
};

template<typename, int, int, Direction>
struct find_edges_horiz{};

template<int R, int C, Direction D, typename... TT>
struct find_edges_horiz<GameBoard<List<TT...>>, R, C, D>{
    typedef typename GetCell<List<TT...>,R,C>::cell Cell;
    typedef typename GetAtIndex<R,List<TT...>>::value Row;

    static const int temp = ConditionalInteger<D==LEFT,Cell::length,-1*Cell::length>::value;
    static const int start = getStart<C,Cell::type,temp,Row>::res;
    static const int end = ConditionalInteger<D==LEFT,(getStart<C,Cell::type,-1*temp,Row>::res)-1,(getStart<C,Cell::type,-1*temp,Row>::res)+1>::value;
};

template<Direction D>
struct TransposeDirection{
    static const int temp1 = ConditionalInteger<D==DOWN,RIGHT,LEFT>::value;
    static const int temp2 = ConditionalInteger<D==RIGHT,DOWN,UP>::value;
    static const int transposed = ConditionalInteger<(D==DOWN||D==UP),temp1,temp2>::value;
};

template<typename GB, int, int, Direction, int, typename... TT>
struct TransposeData{};

template<typename, int>
struct AlterRow{};

template<int N, typename T, typename... TT>
struct AlterRow<List<T,TT...>,N>{
    static const CellType Temp_type = T::type;
    static const Direction Temp_direction = T::direction;
    static const int Temp_length = T::length;
    static const int transposed_direction_tmp = TransposeDirection<Temp_direction>::transposed;
    static const Direction transposed_direction = static_cast<Direction>(transposed_direction_tmp);
    typedef BoardCell<Temp_type, transposed_direction, Temp_length> Temp;
    typedef typename AlterRow<List<TT...>, N-1>::AlteredRow Temp_Row;
    typedef typename PrependList<Temp,Temp_Row>::list AlteredRow;
};

template<typename... TT>
struct AlterRow<List<TT...>,0>{
    typedef List<TT...> AlteredRow;
};

template<typename, int>
struct AlterMat{};

//N=SIZE OF LIST
template<int N,typename T, typename... TT>
struct AlterMat<List<T,TT...>, N>{
    typedef typename AlterRow<T, T::size>::AlteredRow Temp;
    typedef typename AlterMat<List<TT...>, N-1>::AlteredMat TempMat;
    typedef typename PrependList<Temp,TempMat>::list AlteredMat;
};

template<typename... TT>
struct AlterMat<List<TT...>, 0>{
    typedef List<TT...> AlteredMat;
};

template<int R, int C, Direction D, int A, typename... TT>
struct TransposeData<GameBoard<List<TT...>>, R, C, D, A>{
    static const int transpoded_C = R;
    static const int transpoded_R = C;
    static const Direction transpoded_D = static_cast<Direction>(TransposeDirection<D>::transposed);
    typedef typename Transpose<List<TT...>>::matrix Temp_mat;
    typedef typename AlterMat<Temp_mat,sizeof...(TT)>::AlteredMat  transposed_mat;
};

template<int, int, int, int, Direction, typename>
struct MoveVehicleAux{};

template<int A, int R, int CS, int CE, Direction D, typename... TT>
struct MoveVehicleAux<A, R, CS, CE, D, GameBoard<List<TT...>>>{
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
    typedef typename GetCell<List<TT...>,R,C>::cell Cell;
    static_assert((R>=0 && R<initial_Board::length), "Row is not in Range!");
    static_assert((C>=0 && C<initial_Board::width), "Column is not in Range!");
    static_assert((R>=0 && R<initial_Board::length), "Row is not in Range!");
    static_assert(Cell::type!=EMPTY,"The Selected Cell is EMPTY");
    static_assert(Comp_Directions<Cell::direction,D>::value, "Directions of car and movement are Not Compatible!");
    typedef find_edges_horiz<GameBoard<List<TT...>>, R, C, D> Temp;
    typedef typename MoveVehicleAux<A, R, Temp::start,Temp::end, D, GameBoard<List<TT...>>>::gameboard board;
};

template<int R, int C, int A, typename... TT>
struct MoveVehicle_Horiz<GameBoard<List<TT...>>, R, C, UP, A>{
    typedef GameBoard<List<TT...>> board;
};

template<int R, int C, int A, typename... TT>
struct MoveVehicle_Horiz<GameBoard<List<TT...>>, R, C, DOWN, A>{
    typedef GameBoard<List<TT...>> board;
};

template<typename GB, int, int, Direction, int, typename... TT>
struct MoveVehicle_Vert{};

template<int R, int C, Direction D, int A, typename... TT>
struct MoveVehicle_Vert<GameBoard<List<TT...>>, R, C, D, A>{
    typedef TransposeData<GameBoard<List<TT...>>, R, C, D, A> transposed_data;
    typedef typename transposed_data::transposed_mat temp;
    typedef typename MoveVehicle_Horiz<GameBoard<temp>,
            transposed_data::transpoded_R,
            transposed_data::transpoded_C, transposed_data::transpoded_D, A>::board temp_board1;
    typedef TransposeData<temp_board1, transposed_data::transpoded_R,
            transposed_data::transpoded_C, transposed_data::transpoded_D, A> transposed_data2;
    typedef typename transposed_data2::transposed_mat temp_board3;
    typedef GameBoard<temp_board3> board;
};

template<int R, int C, int A, typename... TT>
struct MoveVehicle_Vert<GameBoard<List<TT...>>, R, C, LEFT, A>{
    typedef GameBoard<List<TT...>> board;
};

template<int R, int C, int A, typename... TT>
struct MoveVehicle_Vert<GameBoard<List<TT...>>, R, C, RIGHT, A>{
    typedef GameBoard<List<TT...>> board;
};

template<typename GB, int, int, Direction, int, typename... TT>
struct MoveVehicle{};

template<int R, int C, Direction D, int A, typename... TT>
struct MoveVehicle<GameBoard<List<TT...>>, R, C, D, A>{
    typedef typename MoveVehicle_Horiz<GameBoard<List<TT...>>, R, C, D, A>::board tmp1;
    typedef typename MoveVehicle_Vert<GameBoard<List<TT...>>, R, C, D, A>::board tmp2;
    typedef typename Conditional<(D==LEFT||D==RIGHT), tmp1, tmp2>::value board;
};



#endif //OOP5_MOVEVEHICLE_H













