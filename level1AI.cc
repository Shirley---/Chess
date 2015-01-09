#include "player.h"
#include "piece.h"
#include <math.h>
#include <iostream>
#include <cstdlib>

using namespace std;

Level1AI::Level1AI(Board* theBoard, int numOpp, int bottomLine, int playerNum)
	:Computer(theBoard, numOpp, bottomLine, playerNum){}

bool Level1AI::move() {
	//randomly select a piece
	bool done = false;
	int i = rand() % numPiece;
	while (! pList[i]->tryToMove()) {
		
		i = (i + 1) % numPiece;
	//	cout << pList[i]->tryToMove() << " " << i << endl;;
	}
	int iRow = pList[i]->getRow();
	int iCol = pList[i]->getCol();

	//cout << "try " << (char)('a' + iCol) << GRID_SIZE - iRow << endl;
	for (int fRow = 0; fRow < GRID_SIZE; fRow ++) {
		for (int fCol = 0; fCol < GRID_SIZE; fCol ++) {
			if (myPiece[iRow][iCol]->move(fRow, fCol)) {
				theBoard->notify(iRow, iCol, fRow, fCol);
				myPiece[fRow][fCol] = myPiece[iRow][iCol];
				myPiece[iRow][iCol] = NULL;
				cout << "Computer moves " << (char)('a' + iCol) << GRID_SIZE - iRow << " " << (char)('a' + fCol) << GRID_SIZE - fRow << endl;

				return true;
			}
			/*if (myPiece[iRow][iCol]->validMove(fRow, fCol) &&
				myPiece[fRow][fCol] == NULL) {

				cout << "Computer moves " << (char)('a' + iCol) << GRID_SIZE - iRow << " " << (char)('a' + fCol) << GRID_SIZE - fRow << endl;

				//open up a upgrade possibility
				if (fRow == bottomLine && 
					(myPiece[iRow][iCol]->getType()== 'P' ||
					myPiece[iRow][iCol]->getType() == 'p')) {
					myPiece[iRow][iCol]->upgrade();
				}
				notifyBoard(iRow, iCol, fRow, fCol);
				myPiece[iRow][iCol]->setCoor(fRow, fCol);
				//move the piece on my board
				myPiece[fRow][fCol] = myPiece[iRow][iCol];
				myPiece[iRow][iCol] = NULL;

				//register to the board

				return true;
			}*/
		}
	}
	return true;
}