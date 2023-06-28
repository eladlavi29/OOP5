//
// Created by Elad on 28/06/2023.
//

#include <iostream>
using namespace std;
#include "MoveVehicle.h"
#include "BoardCell.h"
#include "List.h"
#include "GameBoard.h"

int main(){
    typedef BoardCell<A, RIGHT, 2> Cell1;
    typedef BoardCell<A, RIGHT, 2> Cell2;
    typedef BoardCell<EMPTY, DOWN, 3> Cell3;
    typedef BoardCell<EMPTY, LEFT, 4> Cell4;
    typedef BoardCell<EMPTY, RIGHT, 2> Cell5;
    typedef BoardCell<EMPTY, RIGHT, 2> Cell6;
    typedef BoardCell<EMPTY, DOWN, 3> Cell7;
    typedef BoardCell<EMPTY, LEFT, 4> Cell8;
    typedef BoardCell<EMPTY, RIGHT, 2> Cell9;

    typedef List<Cell1, Cell2, Cell3> List1;
    typedef List<Cell4, Cell5, Cell6> List2;
    typedef List<Cell7, Cell8, Cell9> List3;

    typedef List<List1, List2, List3> List4;
    typedef GameBoard<List4> Board;
    typedef find_edges_horiz<Board, 0, 0, RIGHT, 1> Temp;
    typedef GetCell<List4,0,0>::cell Cell;
    cout<<"CELL::TYPE: "<< Cell::type <<endl;
    cout<<"CELL::len: "<< Cell::length <<endl;
    cout<<"CELL::direction: "<< Cell::direction <<endl;

//    cout<<"START: "<< Temp::start <<endl;
//    cout<<"END: "<< Temp::end <<endl;
}
