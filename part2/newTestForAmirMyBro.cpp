//
// Created by Elad on 28/06/2023.
//

#include <iostream>
using namespace std;
#include "MoveVehicle.h"
#include "BoardCell.h"
#include "List.h"
#include "GameBoard.h"
#include "Printer.h"
int main(){
    typedef BoardCell<EMPTY, RIGHT, 2> Cell1;
    typedef BoardCell<X, LEFT, 2> Cell2;
    typedef BoardCell<X, LEFT, 2> Cell3;
    typedef BoardCell<A, UP, 2> Cell4;
    typedef BoardCell<EMPTY, RIGHT, 2> Cell5;
    typedef BoardCell<EMPTY, RIGHT, 2> Cell6;
    typedef BoardCell<A, UP, 2> Cell7;
    typedef BoardCell<P, RIGHT, 1> Cell8;
    typedef BoardCell<EMPTY, RIGHT, 2> Cell9;

    typedef List<Cell1, Cell2, Cell3> List1;
    typedef List<Cell4, Cell5, Cell6> List2;
    typedef List<Cell7, Cell8, Cell9> List3;

    typedef List<List1, List2, List3> List4;
    typedef GameBoard<List4> Board;

//    typedef typename AlterMat<List4, List4::size>::AlteredMat altered_mat;
//    typedef GetAtIndex<0,altered_mat>::value Row1;
//    typedef GetAtIndex<1,altered_mat>::value Row2;
//    typedef GetAtIndex<2,altered_mat>::value Row3;
//
//    typedef GetAtIndex<0,Row1>::value Res1;
//    typedef GetAtIndex<1,Row1>::value Res2;
//    typedef GetAtIndex<2,Row1>::value Res3;
//
//    cout << Res1::direction << endl;
//    cout << Res2::direction << endl;
//    cout << Res3::direction << endl;
//
//    typedef GetAtIndex<0,Row2>::value Res4;
//    typedef GetAtIndex<1,Row2>::value Res5;
//    typedef GetAtIndex<2,Row2>::value Res6;
//
//    cout << Res4::direction << endl;
//    cout << Res5::direction << endl;
//    cout << Res6::direction << endl;
//
//    typedef GetAtIndex<0,Row3>::value Res7;
//    typedef GetAtIndex<1,Row3>::value Res8;
//    typedef GetAtIndex<2,Row3>::value Res9;
//
//    cout << Res7::direction << endl;
//    cout << Res8::direction << endl;
//    cout << Res9::direction << endl;
//    typedef TransposeData<Board, 1, 0, RIGHT, 2> transposed_data;
//    cout<<  transposed_data::transpoded_C<< endl;
//    cout<<  transposed_data::transpoded_R<< endl;
//    cout<<  transposed_data::transpoded_D<< endl;
//    Printer<Board>::print(std::cout);
//    Printer<GameBoard<transposed_data::transposed_mat>>::print(std::cout);

    typedef TransposeData<Board, 1, 0, DOWN, 1> transposed_data;
    cout<<  transposed_data::transpoded_C<< endl;
    cout<<  transposed_data::transpoded_R<< endl;
    cout<<  transposed_data::transpoded_D<< endl;
    Printer<Board>::print(std::cout);
    Printer<GameBoard<transposed_data::transposed_mat>>::print(std::cout);

    Printer<Board>::print(std::cout);
    typedef MoveVehicle<Board, 1, 0, UP, 1>::board gameboard2;
    Printer<gameboard2>::print(std::cout);

    typedef MoveVehicle<gameboard2, 1, 0, DOWN, 1>::board gameboard3;
    Printer<gameboard3>::print(std::cout);
}
