//
// Created by Darshan on 3/11/2021.
//

#include "Board.h"
#include "King.h"
#include <cstdio>
#include <cstdlib>

void Board::init(int num, int whoseTurn){
    setN(num);
    this->turn = whoseTurn;
    board = (Square*) malloc(n * n * sizeof(Square));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if((i == 0 || i == 2) && j % 2 == 1 || i == 1 && j % 2 == 0)
                (board + n*i + j)->p = new Piece(true, 'p', 'W', i, j);
            else if((i == n-3 || i == n-1) && j%2 == 0 || i == n-2 && j % 2 == 1)
                (board + n*i + j)->p = new Piece(true, 'p', 'B', i, j);
            else
                (board + n*i + j)->p = nullptr;
        }
    }
}

void Board::printBoard() {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if((board+n*i+j)->p){
                bool king = (board+n*i+j)->p->type == 'k';
                printf("|%c", (board+n*i+j)->p->side + 32 * !king);
            }
            else
                printf("| ");
        }
        puts("|");
    }
}

void Board::setN(int set){
    n = set;
}

Square* Board::getSquare(int x, int y){
    return board + n*x + y;
}

void Board::move()
{
    if(this->turn)
    {
        cpuMove();
        this->turn = !this->turn;
    }
    else
    {
        std::string move;
        std::cout << "Enter your move" << std::endl;
        std::getline(std::cin, move);
        this->playerMove(move);
        this->turn = !this->turn;
    }
}

bool Board::checkValidCPUMove(int n1, int n2, int n3, int n4)
{
    bool valid = true;
    if(n1 < 0 || n1 > n-1 || n2 < 0 || n2 > n-1 || n3 < 0 || n3 > n-1 || n4 < 0 || n4 > n-1) {
        valid = false;
    }
    else if(!(board + n1 * n + n2)->p){
        valid = false;
    }
    else if ((board + n1 * n + n2)->p->side != 'W') {
        valid = false;
    }
    else if((board + n3 * n + n4)->p) {
        valid = false;
    }
    else if((board+n1*n+n2)->p->type == 'p')
    {
        if(n3 - n1 < 1)
            valid = false;
        else if(n3 - n1 == 1){
            if(n4 - n2 != 1 && n4 - n2 != -1)
                valid = false;
        }
        else if(n3 - n1 == 2){
            if(n4 - n2 != 2 && n4 - n2 != -2)
                valid = false;
            else {
                Square *midSq = board + n * (n3 + n1) / 2 + (n4 + n2) / 2;
                if (!midSq->p || midSq->p->side == 'W')
                    valid = false;
            }
        }
    }
    else if ((board+n1*n+n2)->p->type == 'k'){
        // TODO
        if(n3 - n1 == 1 || n3 - n1 == -1){
            if(n4 - n2 != 1 && n4 - n2 != -1)
                valid = false;
        }
        else if(n3 - n1 == 2 || n3 - n1 == -2){
            if(n4 - n2 != 2 && n4 - n2 != -2)
                valid = false;
            else{
                Square* midSq = board + n * (n3 + n1)/2 + (n4 + n2)/2;
                if(!midSq->p || midSq->p->side == 'W')
                    valid = false;
            }
        }
    }


    return valid;
}

moves Board::getMoves(){
    int locations[12];

    int numLocations = 0;
    for(int i = 1; i < n*n; i++){
        if((board+i)->p && (board+i)->p->side == 'W'){
            locations[numLocations] = i;
            numLocations++;
        }
    }
    int numMoves = 0;
    // max 12 locations, each location can have at most 8 moves, and each move requires 4 numbers to describe it
    int* moves = (int*) malloc(12*8*4*sizeof(int));
    int index = 0;
    for(int i = 0; i < numLocations; i++){
        Piece* p = (board + locations[i])->p;
        int x1 = p->xCoord;
        int y1 = p->yCoord;
        int dirs1[] = {-1, 1};
        int dirs2[] = {-2, 2};
        for(int xdiff : dirs1){
            for(int ydiff : dirs1){
                if(checkValidCPUMove(x1, y1, x1+xdiff, y1+ydiff)){
                    numMoves ++;
                    moves[index] = x1;
                    moves[index+1] = y1;
                    moves[index+2] = x1+xdiff;
                    moves[index+3] = y1+ydiff;
                    index += 4;
                }
            }
        }
        for(int xdiff : dirs2){
            for(int ydiff : dirs2){
                if(checkValidCPUMove(x1, y1, x1+xdiff, y1+ydiff)){
                    numMoves ++;
                    moves[index] = x1;
                    moves[index+1] = y1;
                    moves[index+2] = x1+xdiff;
                    moves[index+3] = y1+ydiff;
                    index += 4;
                }
            }
        }
    }
    return {moves, numMoves};
}

void Board::cpuMove() {
    moves m = this->getMoves();
    int numMoves = m.numMoves;
    int index = rand() % numMoves;
    int x1 = m.moves[4*index];
    int y1 = m.moves[4*index+1];
    int x2 = m.moves[4*index+2];
    int y2 = m.moves[4*index+3];
    if(x2 - x1 == 1 || x2 - x1 == -1){
        Square* start = board + n*x1 + y1;
        Square* end = board + n*x2 + y2;
        Piece* piece = start->p;
        piece->xCoord = x2;
        piece->yCoord = y2;
        start->p = nullptr;
        end->p = piece;
        if(x2 == n-1)
            end->p = new King(piece);
    }
    else{
        Square* mid = board + n*(x1+x2)/2 + (y1 + y2)/2;
        Piece* jumped = mid->p;
        mid->p = nullptr;
        delete jumped;
        Square* start = board + n*x1 + y1;
        Square* end = board + n*x2 + y2;
        Piece* piece = start->p;
        piece->xCoord = x2;
        piece->yCoord = y2;
        start->p = nullptr;
        end->p = piece;
        if(x2 == n-1)
            end->p = new King(piece);
    }


}

void Board::playerMove(const std::string& move) {
    // Player is Black, CPU is White
    int n1 = move[0] - '0';
    int n2 = move[2] - '0';
    int n3 = move[4] - '0';
    int n4 = move[6] - '0';
    Square* start = board + n1 * n + n2;
    Square* end = board + n3 * n + n4;
    if(n1 < 0 || n1 >= n || n2 < 0 || n2 >= n || n3 < 0 || n3 >= n || n4 < 0 || n4 >= n){
        std::cout << "Invalid position, must be between 0 and " << n-1 << std::endl;
        std::cout << "Enter your move" << std::endl;
        std::string newMove;
        std::getline(std::cin, newMove);
        this->playerMove(newMove);
    }
    else if(!start->p || start->p->side == 'W'){
        std::cout << "Invalid move, none of your pieces is located at your start position" << std::endl;
        std::cout << "Enter your move" << std::endl;
        std::string newMove;
        std::getline(std::cin, newMove);
        this->playerMove(newMove);
    }
    else if(end->p)
    {
        std::cout << "Invalid move, there is a piece at your end position" << std::endl;
        std::cout << "Enter your move" << std::endl;
        std::string newMove;
        std::getline(std::cin, newMove);
        this->playerMove(newMove);
    }
    else if(start->p->type == 'p')
    {
        //TODO: check direction here but I think it's good
        if(n3 - n1 == -2 && (n4 - n2 == -2 || n4 - n2 == 2))
        {
            Square* jumpSq = (board + n*(n3 + n1)/2 + (n4+n2)/2);
            Piece* jump = jumpSq->p;
            if(jump && jump->side == 'W')
            {
                jumpSq->p = nullptr;
                delete jump;
                Piece* piece = start->p;
                piece->xCoord = n4;
                piece->yCoord = n3;
                start->p = nullptr;
                end->p = piece;
                if(n3 == 0)
                    piece->type = 'k';
            }
            else{
                std::cout << "Invalid move, you cannot jump a player there" << std::endl;
                std::cout << "Enter your move" << std::endl;
                std::string newMove;
                std::getline(std::cin, newMove);
                this->playerMove(newMove);
            }
        }
        else if(n3 - n1 != -1 || (n4 - n2 != 1 && n4 - n2 != -1)) {
            std::cout << "A pawn cannot move there" << std::endl;
            std::cout << "Enter your move" << std::endl;
            std::string newMove;
            std::getline(std::cin, newMove);
            this->playerMove(newMove);
        }
        else{
            Piece* piece = start->p;
            piece->xCoord = n4;
            piece->yCoord = n3;
            start->p = nullptr;
            end->p = piece;
            if(n3 == 0)
                piece->type = 'k';
        }
    }
    else
    {
        if((n3 - n1 == -2 || n3 - n1 == 2) && (n4 - n2 == -2 || n4 - n2 == 2))
        {
            Square* jumpSq = (board + n*(n3 + n1)/2 + (n4 + n2)/2);
            Piece* jump = jumpSq->p;
            if(jump && jump->side == 'W')
            {
                jumpSq->p = nullptr;
                delete jump;
                Piece* piece = start->p;
                piece->xCoord = n4;
                piece->yCoord = n3;
                start->p = nullptr;
                end->p = piece;
            }
            else{
                std::cout << "Invalid move, you cannot jump a player there" << std::endl;
                std::cout << "Enter your move" << std::endl;
                std::string newMove;
                std::getline(std::cin, newMove);
                this->playerMove(newMove);
            }
        }
        else if((n4 - n2 != 1 && n4 - n2 != -1) || (n3 - n1 != 1 && n3 - n1 != -1)) {
            std::cout << "A king cannot move there" << std::endl;
            std::cout << "Enter your move" << std::endl;
            std::string newMove;
            std::getline(std::cin, newMove);
            this->playerMove(newMove);
        }
        else{
            Piece* piece = start->p;
            piece->xCoord = n4;
            piece->yCoord = n3;
            start->p = nullptr;
            end->p = piece;
        }
    }
}


// STUFF I PROBABLY DONT NEED:wqL::w:

//    std::cout << "CPU Move" << std::endl;
//    int locations[12];
//
//    int index = 0;
//    for(int i = 1; i < n*n; i++){
//        if((board+i)->p && (board+i)->p->side == 'W'){
//            locations[index] = i;
//            index ++;
//        }
//    }
//    bool valid = false;
//    int count = 0;
//    while(!valid){
//        count ++;
//        int i = rand() % index;
//        Square* s = board + locations[i];
//        Piece* p = s->p;
//        int x1 = p->xCoord;
//        int y1 = p->yCoord;
//        if(p->type == 'p'){
//            int x2 = x1 + 2;
//            int y2 = y1 - 2;
//            if(checkValidCPUMove(x1, y1, x2, y2)){
//                valid = true;
//                Square* mid = board + n*(x1+x2)/2 + (y1 + y2)/2;
//                Piece* jumped = mid->p;
//                mid->p = nullptr;
//                delete jumped;
//                Square* start = board + n*x1 + y1;
//                Square* end = board + n*x2 + y2;
//                Piece* piece = start->p;
//                piece->xCoord = x2;
//                piece->yCoord = y2;
//                start->p = nullptr;
//                end->p = piece;
//                if(x2 == n-1)
//                    end->p = new King(piece);
//            }
//            else if(checkValidCPUMove(x1, y1, x2, y1+2)){
//                y2 = y1 + 1;
//                valid = true;
//                Square* mid = board + n*(x1+x2)/2 + (y1 + y2)/2;
//                Piece* jumped = mid->p;
//                mid->p = nullptr;
//                delete jumped;
//                Square* start = board + n*x1 + y1;
//                Square* end = board + n*x2 + y2;
//                Piece* piece = start->p;
//                piece->xCoord = x2;
//                piece->yCoord = y2;
//                start->p = nullptr;
//                end->p = piece;
//                if(x2 == n-1)
//                    end->p = new King(piece);
//            }
//            else{
//                x2 = x1 + 1;
//                y2 = y1 - 1;
//                if(checkValidCPUMove(x1, y1, x2, y2))
//                {
//                    valid = true;
//                    Square* start = board + n*x1 + y1;
//                    Square* end = board + n*x2 + y2;
//                    Piece* piece = start->p;
//                    piece->xCoord = x2;
//                    piece->yCoord = y2;
//                    start->p = nullptr;
//                    end->p = piece;
//                    if(x2 == n-1)
//                        end->p = new King(piece);
//
//                }
//                else if(checkValidCPUMove(x1, y1, x2, y1+1)){
//                    y2 = y1 + 1;
//                    valid = true;
//                    Square* start = board + n*x1 + y1;
//                    Square* end = board + n*x2 + y2;
//                    Piece* piece = start->p;
//                    piece->xCoord = x2;
//                    piece->yCoord = y2;
//                    start->p = nullptr;
//                    end->p = piece;
//                    if(x2 == n-1)
//                        end->p = new King(piece);
//                }
//                // if none of these moves are valid, then this piece cannot move anywhere, so valid stays false
//            }
//        }
//        else if(p->type == 'k'){
//        }
//        else{
//        }
//    }