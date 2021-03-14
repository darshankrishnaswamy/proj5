//
// Created by Darshan on 3/11/2021.
//

#ifndef SRC_PIECE_H
#define SRC_PIECE_H


class Piece {
public:
    Piece(bool piece, char type, char side, int xCoord, int yCoord);

    Piece();

    bool piece;
    char type;
    char side;
    int xCoord;
    int yCoord;
};


#endif //SRC_PIECE_H
