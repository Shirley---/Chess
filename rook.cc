#include "piece.h"
#include "board.h"
#include "textdisplay.h"
#include "player.h"
#include <cstdlib>

using namespace std;

Rook::Rook(char type, int row, int col, Player* p, Board *theBoard)
	:Piece(type, row, col, p, theBoard), moved(false) {}


bool Rook::validMove(int row, int col) {
	if ((this->col == col && this->row == row) || (col > GRID_SIZE) || col < 0) return false;
	if ((this->col == col && this->row == row) || (row > GRID_SIZE) || row < 0) return false;
	//if the move is not done according to the rule, it's false
	if (! ((this->row == row && this->col != col) ||
			(this->col == col && this->row != row))) return false;
	
	//check if anything blocking the way
	//since it doesn't matter the final destination is placed or not.
	//go till -1 of the displacement
	//DOWN
	if (row > this->row) {
		for (int i = 1; i < row - this->row; i ++) {
			if(theBoard->isPlaced(this->row + i, this->col)) return false;
		}
	}
	//UP
	else if (row < this->row) {
		for (int i = 1; i < this->row - row; i ++) {
			if(theBoard->isPlaced(this->row - i, this->col)) return false;
		}
	}
	//R up
	else if (col > this->col) {
		for (int i = 1; i < col - this->col; i ++) {
			if(theBoard->isPlaced(this->row, this->col + i)) return false;
		}
	}
	//R down
	else if (col < this->col) {
		for (int i = 1; i < this->col - col; i ++) {
			if(theBoard->isPlaced(this->row, this->col - i)) return false;
		}
	}
	//if the final destination is my own piece, return false
	if (thePlayer->isPlaced(row,col)) return false;
	return true;
	/*
	//notify the king
	//temperately modify the Board, and see if king disagree with it
	theBoard->setPlaced(row, col, true);
	theBoard->setPlaced(this->row, this->col, false);
	notifyNeighbours();
	//reset the board after notifying neighbours
	theBoard->setPlaced(row, col, false);
	theBoard->setPlaced(this->row, this->col, true);

	if(notifyKing()) {
		notifyNeighbours();
		return true;
	} else {
		//if the king says no, undo the notify
		notifyNeighbours();
		return false;
	}*/
	
}


bool Rook::tryToMove(){
	for (int i = col+1; i < GRID_SIZE; i++){
		if(validMove(row, i)) return true;
	}

	for (int i = 0; i < col; i++){
		if(validMove(row, i)) return true;
	}

	for (int i = row +1; i < GRID_SIZE; i++){
		if(validMove(i, col)) return true;
	}

	for (int i = 0; i < row; i++){
		if(validMove(i, col)) return true;
	}
	return false;
}


void Rook::check(Player* opp){
	for (int i = col+1; i < GRID_SIZE; i++){
		if (theBoard->isPlaced(row, i)){
			opp->check(row,i);
			break;
		}
		opp->check(row,i);
	}

	for (int i = 0; i < col; i++){
		if (theBoard->isPlaced(row, i)){
			opp->check(row,i);
			break;
		}
		opp->check(row,i);
	}

	for (int i = row +1; i < GRID_SIZE; i++){
		if (theBoard->isPlaced(i,col)){
			opp->check(i,col);
			break;
		}
		opp->check(row,i);
	}

	for (int i = 0; i < row; i++){
		if (theBoard->isPlaced(i,col)){
			opp->check(i,col);
			break;
		}
		opp->check(row,i);
	}
}

void Rook::uncheck(Player* opp, int row, int col) {
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
}

void Rook::notifyDisplay(TextDisplay& t){}

void Rook::upgrade(){}
/*
void Rook::draw(int colour){
	w->drawBigString(x*10,y*10,"R",colour);
}
*/