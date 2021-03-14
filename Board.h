//
// Created by Darshan on 3/11/2021.
//

#ifndef SRC_BOARD_H
#define SRC_BOARD_H
#include "Square.h"
#include <string>
#include <iostream>

typedef struct {
    int* moves;
    int numMoves;
}moves;


class Board {
public:
    void init(int, int);
    void printBoard();
    void setN(int);
    Square* getSquare(int, int);
    void move();
    moves getMoves();
    void cpuMove();
    void playerMove(const std::string&);

    bool checkValidCPUMove(int n1, int n2, int n3, int n4);

private:
    int n;
    int turn;
    Square* board;
};


#endif //SRC_BOARD_H
