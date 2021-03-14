//
// Created by Darshan on 3/11/2021.
//

#include "Piece.h"

Piece::Piece(bool piece, char type, char side, int xCoord, int yCoord){
    this->piece = piece;
    this->type = type;
    this->side = side;
    this->xCoord = xCoord;
    this->yCoord = yCoord;
}

Piece::Piece() = default;

