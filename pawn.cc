#include "piece.h"
#include "board.h"
#include "textdisplay.h"
#include "player.h"
#include <cstdlib>

using namespace std;

Pawn::Pawn(char type, int row, int col, Player* p, Board *theBoard, int front)
	:Piece(type, row, col, p, theBoard), front(front), firstTime(true) {}


bool Pawn::validMove(int row, int col) {
	bool result = false;
	if ((this->col == col && this->row == row) || (col > GRID_SIZE) || col < 0) return false;
	if ((this->col == col && this->row == row) || (row > GRID_SIZE) || row < 0) return false;
	//check en passant a valid move
	if (pawnJustMoved != NULL) {
		int pRow = pawnJustMoved->getRow();
		int pCol = pawnJustMoved->getCol();
		//-x-
		//Pp-
		//---
		if ((pRow - front == row && pCol == col) &&
			(this->row + front == row && this->col+ front == col)) {
			result = true;
		}
	}
	//check for capturing
	//-x-
	//P--
	if (theBoard->isPlaced(row, col) &&
		this->row + front == row && (this->col + 1 == col || this->col - 1 == col)) {
		result = true;
	}
	//if it's just moving forward one blog, then it's good
	if (this->row + front == row && this->col == col) {
		//cout << theBoard->isPlaced(row, col);
		if (theBoard->isPlaced(row, col)) return false;
		if (firstTime) {
			firstTime = false;
			pawnJustMoved = this;
		}
		result = true;
	}
	//check for first time movement
	if (this->row + front * 2 == row && this->col == col && firstTime) {
		firstTime = false;
		//register the pawn just moved to everyone
		pawnJustMoved = this;
		result = true;
	}
	if(thePlayer->isPlaced(row, col)) return false;

	return result;
}

bool Pawn::tryToMove(){
	return (validMove(row + front, col) ||
		validMove(row + front, col + front) ||
		validMove(row + front, col - front));
}

void Pawn::check(Player* opp){
	if (this->row + front < GRID_SIZE  && this->col + 1 < GRID_SIZE)
		opp->check(this->row + front, this->col + 1);
	if (this->row + front < GRID_SIZE && this->col - 1 > 0)
		opp->check(this->row + front, this->col - 1);
}

void Pawn::uncheck(Player* opp, int row, int col){
	if (this->row + front < GRID_SIZE  && this->col + 1 < GRID_SIZE)
		opp->uncheck(this->row + front, this->col + 1);
	if (this->row + front < GRID_SIZE && this->col - 1 > 0)
		opp->uncheck(this->row + front, this->col - 1);
}

void Pawn::notifyDisplay(TextDisplay& t){
	t.notify(-1,-1,row,this->col,type);
}

int Pawn::getFront() {
	return front;
}

void Pawn::upgrade(){
	char c;
	cin >> c;
	theBoard->setPiece(c, row, col);
	
}

/*
void Pawn::draw(int colour){
	w->drawBigString(x*10,y*10,"P",colour);
}
*/