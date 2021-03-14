//
// Created by Darshan on 3/13/2021.
//

#include "King.h"

King::King(Piece* p) {
    this->piece = p->piece;
    this->type = 'k';
    this->side = p->side;
    this->xCoord = p->xCoord;
    this->yCoord = p->yCoord;
}
