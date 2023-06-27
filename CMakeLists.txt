cmake_minimum_required(VERSION 3.21)
project(OOP5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOP5
        part1/Observer.h
        part1/OOP5EventException.h
        part1/Part1Examples.cpp
        part1/Subject.h)
