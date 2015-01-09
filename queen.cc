#include "piece.h"
#include "board.h"
#include "textdisplay.h"
#include "player.h"
#include <cstdlib>

using namespace std;

Queen::Queen(char type, int row, int col, Player* p, Board *theBoard)
	:Piece(type, row, col, p, theBoard) {}

bool Queen::validMove(int row, int col) {
	if ((this->col == col && this->row == row) || (col + 1> GRID_SIZE) || col < 0) return false;
	if ((this->col == col && this->row == row) || (row + 1> GRID_SIZE) || row < 0) return false;
	if(!(this->row - row == this->col - col) || 
		(this->row == row && this->col != col) ||
		(this->col == col && this->row != row)) return false;
	//moving like a rook
	//R-->
	if (row > this->row && this->col == col) {
		for (int i = this->row + 1; i < row - 1; i ++) {
			if(theBoard->isPlaced(i, this->col)) return false;
		}
	}
	//UP
	else if (row < this->row && this->col == col) {
		for (int i = this->row - 1; i > row - 1; i --) {
			if(theBoard->isPlaced(i, this->col)) return false;
		}
	}
	//R up
	else if (col > this->col && this->row == row) {
		for (int i = this->col + 1; i < col - 1; i ++) {
			if(theBoard->isPlaced(this->row, i)) return false;
		}
	}
	//R down
	else if (col < this->col && this->row == row) {
		for (int i = this->col - 1; i > col - 1; i --) {
			if(theBoard->isPlaced(this->row, i)) return false;
		}
	} else if (row > this->row && col > this->col) {
		for (int i = 1; i < row - this->row; i ++) {
			if(theBoard->isPlaced(this->row + i, this->col + i)) return false;
		}
	}
	//UP + LEFT
	else if (row > this->row && col < this->col) {
		for (int i = 1; i < row - this->row; i ++) {
			if(theBoard->isPlaced(this->row + i, this->col - i)) return false;
		}
	}
	//DOWN + RIGHT
	else if (row < this->row &&  col > this->col) {
		for (int i = 1; i < this->row - row; i ++) {
			if(theBoard->isPlaced(this->row - i, this->col + i)) return false;
		}
	}
	//DOWN + LEFT
	else if (row < this->row && col < this->col) {
		for (int i = 1; i < this->row - row; i ++) {
			if(theBoard->isPlaced(this->row - i, this->col - i)) return false;
		}
	}

	return true;
	/*
	//notify the king
	theBoard->setPlaced(row, col, true);
	theBoard->setPlaced(this->row, this->col, false);
	notifyNeighbours();
	theBoard->setPlaced(row, col, false);
	theBoard->setPlaced(this->row, this->col, true);

	if(notifyKing()) {
		notifyNeighbours();
		return true;
	} else {
		notifyNeighbours();
		return false;
	}
	*/
}

bool Queen::tryToMove(){

	//right
	for (int i = col + 1; i < GRID_SIZE; i ++) {
		if(validMove(row, i)) return true;
	}
	//<--R
	for (int i = col - 1; i >= 0; i --) {
		if(validMove(row, i)) return true;
	}
	//R up
	for (int i = row + 1; i < GRID_SIZE; i ++) {
		if(validMove(i, col)) return true;
	}
	//R down
	for (int i = row - 1; i >= 0; i --) {
		if(validMove(i, col)) return true;
	}
	for(int i = 1; i < GRID_SIZE; i ++) {
		//check for over board
		if(this->row + i >= GRID_SIZE || this->col + i >=GRID_SIZE) break;
		//check for placement
		if(thePlayer->isPlaced(row + i, col + i)) break;
		if(validMove(row + i, col + i)) return true;
	}
	//UP LEFT
	for(int i = 1; i < GRID_SIZE; i ++) {

		if(this->row + i >= GRID_SIZE || this->col - i < 0) break;
		if(thePlayer->isPlaced(row + i, col - i)) break;
		if(validMove(row + i, col - i)) return true;
	}
	for(int i = 1; i < GRID_SIZE; i ++) {

		if(this->row - i < 0 || this->col + i >=GRID_SIZE) break;
		if(thePlayer->isPlaced(row - i, col + i)) break;
		if(validMove(row - i, col + i)) return true;
	}
	for(int i = 1; i < GRID_SIZE; i ++) {

		if(this->row - i < 0 || this->col - i < 0) break;
		if(thePlayer->isPlaced(row - i, col - i)) break;
		if(validMove(row - i, col - i)) return true;
	}
	return false;
}

void Queen::check(Player* opp){
	
	//right
	for (int i = col + 1; i < GRID_SIZE; i ++) {
		if(theBoard->isPlaced(row, i)) {
			opp->check(row, i);
			break;
		}
		opp->check(row, i);
	}
	//<--R
	for (int i = col - 1; i >= 0; i --) {
		if(theBoard->isPlaced(row, i)) {
			opp->check(row, i);
			break;
		}
		opp->check(row, i);
	}
	//R up
	for (int i = row + 1; i < GRID_SIZE; i ++) {
		if(theBoard->isPlaced(i, col)) {
			opp->check(i, col);
			break;
		}
		opp->check(i, col);
	}
	//R down
	for (int i = row - 1; i >= 0; i --) {
		if(theBoard->isPlaced(i, col)) {
			opp->check(i, col);
			break;
		}
		opp->check(i, col);
	}
	//up right
	for (int i = 0; i < GRID_SIZE; i ++) {
		if(row + i > GRID_SIZE || col + i > GRID_SIZE) break;
		if(theBoard->isPlaced(row + i, col + i)) {
			opp->check(row + i, col + i);
			break;
		}
		opp->check(row + i, col + i);
	}
	//UP + LEFT
	for (int i = 0; i < GRID_SIZE; i ++) {
		if(row + i > GRID_SIZE || col - i < 0) break;
		if(theBoard->isPlaced(row + i, col - i)) {
			opp->check(row + i, col - i);
			break;
		}
		opp->check(row + i, col - i);
	}
	//DOWN + RIGHT
	for (int i = 0; i < GRID_SIZE; i ++) {
		if(row - i < 0 || col + i > GRID_SIZE) break;
		if(theBoard->isPlaced(row - i, col + i)) {
			opp->check(row - i, col + i);
			break;
		}
		opp->check(row - i, col + i);
	}
	//DOWN + LEFT
	for (int i = 0; i < GRID_SIZE; i ++) {
		if(row - i < 0 || col - i < 0) break;
		if(theBoard->isPlaced(row - i, col - i)) {
			opp->check(row - i, col - i);
			break;
		}
		opp->check(row - i, col - i);
	}
}

void Queen::uncheck(Player* opp, int row, int col) {
//R-->
	for(int j = this->col + 1; j < GRID_SIZE; j ++) {
		if(theBoard->isPlaced(this->row,j) || (this->row == row && j == col)) {
			opp->uncheck(this->row,j);
			break;
		}
		opp->uncheck(this->row,j);
	}
	//<--R
	for(int j = this->col - 1; j >= 0; j --) {
		if(theBoard->isPlaced(this->row,j) || (this->row == row && j == col)) {
			opp->uncheck(this->row,j);
			break;
		}
		opp->uncheck(this->row,j);
	}
	//up
	for(int j = this->row + 1; j < GRID_SIZE; j ++) {
		
		if(theBoard->isPlaced(j,this->col) || (j == row && this->col == col)) {
			opp->uncheck(j, this->col);
			break;
		}
		opp->uncheck(j, this->col);
	}
	//down
	for(int j = this->row - 1; j >= 0; j --) {
		if(theBoard->isPlaced(j,this->col) || (j == row && this->col == col)) {
			opp->uncheck(j, this->col);
			break;
		}
		opp->uncheck(j, this->col);
	}	
	//UP RIGHT
	for(int i = 1; i < GRID_SIZE - 1; i ++) {
		//check for over board
		if(this->row + i >= GRID_SIZE || this->col + i >=GRID_SIZE) break;
		//check for placement
		if(theBoard->isPlaced(this->row + i, this->col + i) ||
			(this->row + i == row && this->col + i == col)) {
			opp->uncheck(this->row + i, this->col + i);
			break;
		}
		opp->uncheck(this->row + i, this->col + i);
	}
	//UP LEFT
	for(int i = 1; i < GRID_SIZE - 1; i ++) {

		if(this->row + i >= GRID_SIZE || this->col - i < 0) break;

		if(theBoard->isPlaced(this->row + i, this->col - i) ||
			(this->row + i == row && this->col - i == col)) {
			opp->uncheck(this->row + i, this->col - i);
			break;
		}
		opp->uncheck(this->row + i, this->col + i);
	}
	for(int i = 1; i < GRID_SIZE - 1; i ++) {

		if(this->row - i < 0 || this->col + i >=GRID_SIZE) break;

		if(theBoard->isPlaced(this->row - i, this->col + i) ||
			(this->row - i == row && this->col + i == col)) {
			opp->uncheck(this->row - i, this->col + i);
			break;
		}
		opp->uncheck(this->row - i, this->col + i);
	}
	for(int i = 1; i < GRID_SIZE - 1; i ++) {

		if(this->row - i < 0 || this->col - i < 0) break;

		if(theBoard->isPlaced(this->row - i, this->col - i) ||
			(this->row - i == row && this->col - i == col)) {
			opp->uncheck(this->row - i, this->col - i);
			break;
		}
		opp->uncheck(this->row - i, this->col - i);
	}
}

void Queen::upgrade() {}

void Queen::notifyDisplay(TextDisplay& t) {}
/*
void Queen::draw(int colour){
	w->drawBigString(x*10,y*10,"Q",colour);
}
*/