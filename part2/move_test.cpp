//
// Created by amirb on 28/06/2023.
//

#include <iostream>
using namespace std;
#include "MoveVehicle.h"
#include "BoardCell.h"
#include "List.h"
#include "GameBoard.h"

int main(){
    typedef BoardCell<EMPTY, DOWN, 1> Cell1;
    typedef BoardCell<X, UP, 2> Cell2;
    typedef BoardCell<EMPTY, DOWN, 3> Cell3;
    typedef BoardCell<X, UP, 4> Cell4;
    typedef BoardCell<EMPTY, DOWN, 5> Cell5;
    typedef BoardCell<X, UP, 6> Cell6;
    typedef BoardCell<EMPTY, DOWN, 7> Cell7;
    typedef BoardCell<X, UP, 8> Cell8;
    typedef BoardCell<EMPTY, DOWN, 9> Cell9;

    cout << (Cell1::direction == DOWN) << endl;
    cout << (Cell1::type == EMPTY) << endl;
    cout << (Cell1::length == 1) << endl;

    typedef List<Cell1, Cell2, Cell3> List1;
    typedef List<Cell4, Cell5, Cell6> List2;
    typedef List<Cell7, Cell8, Cell9> List3;

    typedef List<List1, List2, List3> List4;

    typedef GameBoard<List4> gameBoard;
    cout << (gameBoard::width == 3) << endl;
    cout << (gameBoard::length == 3) << endl;
    cout << std::is_same<gameBoard::board ,List4>::value << endl;
}