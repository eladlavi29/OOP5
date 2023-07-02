cmake_minimum_required(VERSION 3.21)
project(OOP5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOP5
        part2/BoardCell.h
        part2/CellType.h
        part2/Direction.h
        part2/GameBoard.h
        part2/Int.h
        part2/List.h
        part2/MoveVehicle.h
        part2/Printer.h
        part2/TransposeList.h
        part2/Utilities.h
        part2/RushHour.h

        part2/Part2Examples.cpp)
