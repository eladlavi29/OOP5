cmake_minimum_required(VERSION 3.21)
project(OOP5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOP5
        Observer.h
        OOP5EventException.h
        Part1Examples.cpp
        Subject.h)
