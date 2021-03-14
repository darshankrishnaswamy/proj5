/*
 * Production.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Production.h"
#include <stdbool.h>
#include "Room.h"
#include <string>
#include <iostream>
#include "Board.h"

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[])
{
	printf("Starting Production\n");
	bool answer = false;

	if(argc <=1) //no interesting information
	{
		puts("Didn't find any arguments.");
		fflush(stdout);
		answer = false;
	}
	else //there is interesting information
	{
		printf("Found %d interesting arguments.\n", argc-1);
		fflush(stdout);
		int boardSize;
		int whoseTurn;
		int numMoves;

		for(int i = 1; i<argc; i++) //don't want to read argv[0]
				{//argv[i] is a string

					switch(i)
					{
                    case 1:
                        try{
                            whoseTurn = std::stoi(argv[i]);
                            printf("The turn is %s.\n", argv[i]);
                        }
                        catch(...){
                            std::cout << "Turn must be an int" << std::endl;
                            answer = false;
                        }

                        break;
					case 2:
						try{
						    boardSize = std::stoi(argv[i]);
                            printf("The size of the board is %s.\n", argv[i]);
						}
						catch(...) {
                            std::cout << "Size of board must be an int" << std::endl;
                            answer = false;
                        }
						break;
					case 3:
                        try{
                            numMoves = std::stoi(argv[i]);
                            printf("Number of moves is %s.\n", argv[i]);
                        }
                        catch(...){
                            std::cout << "Number of moves must be an int" << std::endl;
                            answer = false;
                        }
                        break;
					default:
						puts("Unexpected argument count."); fflush(stdout);
						answer = false;
						break;
					}//end of switch
				}//end of for loop on argument count
				puts("after reading arguments"); fflush(stdout);

		//we'll want to read the file
		printf("SIZE OF BOARD: %d\n", boardSize);
		printf("NUMBER OF MOVES: %d\n", numMoves);

		auto* b = new Board();
		b->init(boardSize, whoseTurn);
		b->printBoard();
		printf("MOVES: %d\n", b->getMoves().numMoves);
		for(int i = 0; i < numMoves; i++) {
		    b->move();
            b->printBoard();
        }

	}
	return answer;
}


