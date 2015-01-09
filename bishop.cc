#include "piece.h"
#include "board.h"
#include "textdisplay.h"
#include "player.h"
#include <cstdlib>

using namespace std;

Bishop::Bishop(char type, int row, int col, Player* p, Board *theBoard):Piece(type, row, col, p, theBoard) {}

bool Bishop::validMove(int row, int col) {
	if ((this->col == col && this->row == row) || (col + 1> GRID_SIZE) || col < 0) return false;
	if ((this->col == col && this->row == row) || (row + 1> GRID_SIZE) || row < 0) return false;

	if(!(this->row - row == this->col - col)) return false;
	//check for blocking
	//UP + RIGHT
	if (row > this->row && col > this->col) {
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

bool Bishop::tryToMove(){
	//UP RIGHT
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

void Bishop::check(Player* opp){
	//UP RIGHT
	for(int i = 1; i < GRID_SIZE - 1; i ++) {
		//check for over board
		if(this->row + i >= GRID_SIZE || this->col + i >=GRID_SIZE) break;
		//check for placement
		if(theBoard->isPlaced(this->row + i, this->col + i)) {
			opp->check(this->row + i, this->col + i);
			break;
		}
		opp->check(this->row + i, this->col + i);
	}
	//UP LEFT
	for(int i = 1; i < GRID_SIZE - 1; i ++) {

		if(this->row + i >= GRID_SIZE || this->col - i < 0) break;

		if(theBoard->isPlaced(this->row + i, this->col - i)) {
			opp->check(this->row + i, this->col - i);
			break;
		}
		opp->check(this->row + i, this->col + i);
	}
	for(int i = 1; i < GRID_SIZE - 1; i ++) {

		if(this->row - i < 0 || this->col + i >=GRID_SIZE) break;

		if(theBoard->isPlaced(this->row - i, this->col + i)) {
			opp->check(this->row - i, this->col + i);
			break;
		}
		opp->check(this->row - i, this->col + i);
	}
	for(int i = 1; i < GRID_SIZE - 1; i ++) {

		if(this->row - i < 0 || this->col - i < 0) break;

		if(theBoard->isPlaced(this->row - i, this->col - i)) {
			opp->check(this->row - i, this->col - i);
			break;
		}
		opp->check(this->row - i, this->col - i);
	}
}

void Bishop::uncheck(Player* opp, int row, int col) {
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

void Bishop::upgrade(){}
/*
void Bishop::draw(int colour){
	w->drawBigString(x*10,y*10,"B",colour);
}
*/

void Bishop::notifyDisplay(TextDisplay& t) {}