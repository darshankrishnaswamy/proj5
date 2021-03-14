//============================================================================
// Name        : 2020HW4starter.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Tests.h"
#include "Production.h"
#include "Board.h"

int main(int argc, char* argv[]) {
	cout << "!!!Hello World,  we are on HW4!!!" << endl; // prints !!!Hello World!!!
	Production* pP = new Production();
	pP->prod(argc, argv);
//	Tests* tsP = new Tests();
//	if(tsP->tests())
//	{
//        Production* pP = new Production();
//        if(pP->prod(argc, argv))
//        {
//        	cout <<"Production passed." << endl;
//        }
//        delete(pP);
//	}
//	else
//	{
//		cout <<"Not all tests passed." << endl;
//	}
//	delete(tsP);
//	return 0;
}
