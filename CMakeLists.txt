cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        hw5.cpp
        Production.cpp
        Production.h
        Room.h
        Tests.cpp
        Tests.h Board.cpp Board.h Piece.cpp Piece.h Square.cpp Square.h King.cpp King.h)
