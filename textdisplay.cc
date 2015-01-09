#include "textdisplay.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

TextDisplay::TextDisplay(int n):boardSize(n + 2) {
	//leaving a 2 x 2 margin for number and letter around the board
	w = new Xwindow(800,800);
	theDisplay = new char *[boardSize];
	for (int i = 0; i < boardSize; i ++) {
		theDisplay[i] = new char [boardSize];
		for(int j = 0; j < boardSize; j ++) {
			theDisplay[i][j] = ' ';
			w->fillRectangle(i*10,j*10,10,10,0);
		}
	}
	for (int i = 0; i < n; i ++) {
		theDisplay[i][0] = '8' - i;
		theDisplay[boardSize - 1][i + 2] = 'a' + i;
	}
	//shifiting the board 2 units to the left
	for (int i = 0; i < n; i ++) {
		for (int j = 2; j < boardSize; j ++) {
			if((i + j) % 2 == 0) {
				theDisplay[i][j] = ' ';
				w->fillRectangle(i*10,j*10,10,10,0);
			} else {
				theDisplay[i][j] = '_';
				w->fillRectangle(i*10,j*10,10,10,1);
			}
		}
	}
}

void TextDisplay::resetDisplay() {
	for (int i = 0; i < boardSize - 2; i ++) {
		theDisplay[i][0] = '8' - i;
		theDisplay[boardSize - 1][i + 2] = 'a' + i;
	}
	for (int i = 0; i < boardSize - 2; i ++) {
		for (int j = 2; j < boardSize; j ++) {
			if((i + j) % 2 == 0) {
				theDisplay[i][j] = ' ';
				w->fillRectangle(i*10,j*10,10,10,0);
			} else {
				theDisplay[i][j] = '_';
				w->fillRectangle(i*10,j*10,10,10,1);
			}
		}
	}
}

//iRow = -1 and iCol = -1 implies it's placing a piece only
//fRow = -1 and fCol = -1 implies it's removing a piece
void TextDisplay::notify(int iRow, int iCol, int fRow, int fCol, char type) {
	if (iRow == -1) {
		theDisplay[fRow][fCol + 2] = type;	
	} else if (fRow == -1) {
		if ((iRow + iCol + 2) % 2 == 0) {
			theDisplay[iRow][iCol + 2] = ' ';
			w->fillRectangle(iRow*10,iCol*10+2,10,10,0);
		} else {
			theDisplay[iRow][iCol + 2] = '_';
			w->fillRectangle(iRow*10,iCol*10+2,10,10,1);
		}
	} else {
		if ((iRow + iCol + 2) % 2 == 0) {
			theDisplay[iRow][iCol + 2] = ' ';
			w->fillRectangle(iRow*10,iCol*10+2,10,10,0);
		} else {
			theDisplay[iRow][iCol + 2] = '_';
			w->fillRectangle(iRow*10,iCol*10+2,10,10,1);
		}
		theDisplay[fRow][fCol + 2] = type;	
		stringstream ss;
		string s;
		ss << type;
		ss >> s;
		if (isupper(type)){
			w->drawBigString(fRow*10,fCol*10+2,s,3);
		} else{
			w->drawBigString(fRow*10,fCol*10+2,s,1);
		}
	}
	
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for(int i = 0; i < td.boardSize; i ++) {
		for (int j = 0; j < td.boardSize; j ++) {
			out << td.theDisplay[i][j];
		}
		out << endl;
	}
	return out;
}