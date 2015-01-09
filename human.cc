#include "player.h"
#include "piece.h"
#include "board.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Human::Human(Board *theBoard, int numOpp, int bottomLine, int playerNum):
	Player(theBoard, numOpp, bottomLine, playerNum){}

void Human::addPiece(Piece* p, int row, int col) {
	myPiece[row][col] = p;
	
	if (p->getType() == 'K' || p->getType() == 'k') {
		theKing = p;
	}
	char type = p->getType();
	//using negative number to repersent whtie pieces, and positive to repersent black
	switch (type)
	{
	case 'P':
		values[row][col] = 1;
		break;
	case 'p':
		values[row][col] = 1;
		break;
	case 'N':
		values[row][col] = 2;
		break;
	case 'n':
		values[row][col] = 2;
		break;
	case 'B':
		values[row][col] = 3;
		break;
	case 'b':
		values[row][col] = 3;
		break;
	case 'R':
		values[row][col] = 3;
		break;
	case 'r':	
		values[row][col] = 3;
		break;
	case 'Q':
		values[row][col] = 5;
		break;
	case 'q':
		values[row][col] = 5;
		break;
	case 'K':
		values[row][col] = 10;
		break;
	case 'k':
		values[row][col] = 10;
	default:
		break;
	}
	//setting a piece causes checking opponents
	for (int i = 0; i < numOpp; i ++) {
		if (i != this->playerNum) {
			myPiece[row][col]->check(Opps[i]);
		}
	}

}

void Human::removePiece(int row, int col) {
	if (myPiece[row][col] != NULL) {
		myPiece[row][col]->notifyNeighboursMoved();
		myPiece[row][col] = NULL;
		values[row][col] = 0;
	}
}

bool Human::move() {
	char iColC;
	int iRow;
	char fColC;
	int fRow;
	
	cin >> iColC >> iRow;
	cin >> fColC >> fRow;

	int iCol = iColC - 'a';
	int fCol = fColC - 'a';

	iRow = GRID_SIZE - iRow;
	fRow = GRID_SIZE - fRow;

	if (myPiece[iRow][iCol] == NULL) return false;
	if (myPiece[iRow][iCol]->move(fRow, fCol)) {
		myPiece[fRow][fCol] = myPiece[iRow][iCol];
		myPiece[iRow][iCol] = NULL;
		theBoard->notify(iRow, iCol, fRow, fCol);
		return true;
	}
	//either it should be a valid move, and there is no piece at final
	//coor that is mine
}