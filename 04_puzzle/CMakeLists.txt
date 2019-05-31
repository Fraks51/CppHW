cmake_minimum_required(VERSION 3.13)
project(04_8_puzzle_Fraks51)

set(CMAKE_CXX_STANDARD 14)

add_executable(04_8_puzzle_Fraks51
        main.cpp board.h board.cpp solver.cpp solver.h)
