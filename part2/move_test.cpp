//
// Created by amirb on 28/06/2023.
//

#include <iostream>
using namespace std;
#include "MoveVehicle.h"
#include "BoardCell.h"
#include "List.h"
#include "GameBoard.h"
#include "Printer.h"

int main() {
    typedef BoardCell<A, RIGHT, 2> Cell1;
    typedef BoardCell<A, RIGHT, 2> Cell2;
    typedef BoardCell<EMPTY, DOWN, 3> Cell3;
    typedef BoardCell<EMPTY, LEFT, 8> Cell4;
    typedef BoardCell<B, LEFT, 1> Cell5;

    typedef List<Cell1, Cell2, Cell3, Cell4, Cell5> Raw1;

    typedef List<Raw1> board;

    typedef GameBoard<board> gameboard1;
    Printer<gameboard1>::print(std::cout);

    typedef MoveVehicleAux<2, 0, 0, 2, RIGHT, gameboard1>::gameboard gameboard2;
    Printer<gameboard2>::print(std::cout);
}