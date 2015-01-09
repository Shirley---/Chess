#include "piece.h"
#include "board.h"
#include "player.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Piece* Piece::pawnJustMoved = NULL;

Piece::Piece(char type, int row, int col, Player* p, Board *theBoard):
type(type),row(row), col(col), thePlayer(p), theBoard(theBoard){
	type = 0;
	neighbour = new Piece* [MAX_NEIGHBOURS];
	index = 0;
}

bool Piece::move(int fRow, int fCol) {
	//check if it is a valid move
	if (validMove(fRow, fCol) && (! thePlayer->isPlaced(fRow, fCol))) {
		
		theBoard->setPlaced(row, col, false);
		theBoard->setPlaced(fRow, fCol, true);
		//notifyNeighboursMoved();
		int iRow = row;
		int iCol = col;
		row = fRow;
		col = fCol;
		thePlayer->getOpp(0)->reCalc();
		//then, i have to notify my neighbours that i moved
		//set my coordinates, add new neighbours, and notify those neighbours that i placed
		//addNeighbours();
		//theBoard->setPlaced(fRow, fCol, true);
		//notifyNeighboursPlaced();
		
		//see what does the king says
		if(notifyKing()) {
			//if it is a bottom line pawn, then upgrade it
			if (thePlayer->bottomLinePawn()) {
				upgrade();
			}
			return true;
		} else {
			//if king will be checked after this move, reverse the move
			theBoard->setPlaced(iRow, iCol, true);
			theBoard->setPlaced(fRow, fCol, false);
			//notifyNeighboursMoved();
			row = iRow;
			col = iCol;
			//addNeighbours();
			thePlayer->getOpp(0)->reCalc();
			//notifyNeighboursPlaced();
			return false;
		}
	} else {
		//if it is not a valid move, then return false
		return false;
	}
	
}

//recalculate
void Piece::notifyNeighboursMoved() {
	//thePlayer->getOpp(0)->reCalc(row, col);
	for(int i = 0; i < index; i ++) {
		neighbour[i]->uncheck(thePlayer, row, col);
		neighbour[i]->addNeighbours();
		neighbour[i]->check(thePlayer);
	}
}

void Piece::notifyNeighboursPlaced() {
	//assume that iam not there, and do the recalculation
	theBoard->setPlaced(row, col, false);
	for(int i = 0; i < index; i++) {
		neighbour[i]->uncheck(thePlayer, -1, -1);
		neighbour[i]->check(thePlayer);
	}
	theBoard->setPlaced(row, col, true);
}

/*
void Piece:: setCoor(int row, int col){
	theBoard->setPlaced(this->row, this->col, false);
	theBoard->setPlaced(row, col, true);
	notifyNeighbours();
	this->row = row;
	this->col = col;
	thePlayer->uncheckOpps(this);
	thePlayer->checkOpps(this);
	addNeighbours();
	notifyNeighbours();
}
*/
void Piece::addNeighbours() {
	index = 0;
	for(int j = col + 1; j < GRID_SIZE; j ++) {
		if(theBoard->isPlaced(row,j)) {
			Piece *p = theBoard->getPiece(row,j);
			if (p != NULL) {
				neighbour[index] = p;
				p->addNeighbour(this);
				index ++;
				break;
			}
		}
	}
	//<--R
	for(int j = col - 1; j >= 0; j --) {
		if(theBoard->isPlaced(row,j)) {
			
			Piece *p = theBoard->getPiece(row,j);
			if (p != NULL) {
				neighbour[index] = p;
				p->addNeighbour(this);
				index ++;
				break;
			}
		}
	}
	//up
	for(int j = this->row + 1; j < GRID_SIZE; j ++) {
		if(theBoard->isPlaced(j,col)) {

			Piece *p = theBoard->getPiece(j, col);
			if (p != NULL) {
				neighbour[index] = p;
				p->addNeighbour(this);
				index ++;
				break;
			}
		}
	}
	//down
	for(int j = this->row - 1; j >= 0; j --) {
		if(theBoard->isPlaced(j,col)) {
			Piece *p = theBoard->getPiece(j, col);
			if (p != NULL) {
				neighbour[index] = p;
				p->addNeighbour(this);
				index ++;
				break;
			}
		}
	}	
	//UP RIGHT
	for(int i = 1; i < GRID_SIZE - 1; i ++) {
		//check for over board
		if(this->row + i >= GRID_SIZE || this->col + i >=GRID_SIZE) break;
		//check for placement

		if(theBoard->isPlaced(this->row + i, this->col + i)) {
			Piece *p = theBoard->getPiece(this->row + i, this->col + i);
			if (p != NULL) {
				neighbour[index] = p;
				p->addNeighbour(this);
				index ++;
				break;
			}
		}
	}
	//UP LEFT
	for(int i = 1; i < GRID_SIZE - 1; i ++) {

		if(this->row + i >= GRID_SIZE || this->col - i < 0) break;
		//check for placement
		if(theBoard->isPlaced(this->row + i, this->col - i)) {
			Piece *p = theBoard->getPiece(this->row + i, this->col - i);
			if (p != NULL) {
				neighbour[index] = p;
				p->addNeighbour(this);
				index ++;
				break;
			}
		}
	}
	//down right
	for(int i = 1; i < GRID_SIZE - 1; i ++) {

		if(this->row - i < 0 || this->col + i >= GRID_SIZE) break;
		//check for placement
		if(theBoard->isPlaced(this->row - i, this->col + i)) {
			Piece *p = theBoard->getPiece(this->row - i, this->col + i);
			if (p != NULL) {
				neighbour[index] = p;
				p->addNeighbour(this);
				index ++;
				break;
			}
		}
	}
	//down left
	for(int i = 1; i < GRID_SIZE - 1; i ++) {
		if(this->row - i < 0 || this->col - i < 0) break;
		//check for placement
		if(theBoard->isPlaced(this->row - i, this->col - i)) {
			Piece *p = theBoard->getPiece(this->row - i, this->col - i);
			if (p != NULL) {
				neighbour[index] = p;
				p->addNeighbour(this);
				index ++;
				break;
			}
		}
	}
}

bool Piece::notifyKing(){
	Piece *king = thePlayer->getKing();
	return ! thePlayer->isChecked(king->getRow(), king->getCol());
}

void Piece::addNeighbour(Piece* p){
	bool in = false;
	for (int i = 0; i < index; i ++){
		if (neighbour[i] == p) in = true;
	}
	if (!in){
		uncheck(thePlayer->getOpp(0), p->getRow(), p->getRow());
		check(thePlayer->getOpp(0));
		neighbour[index] = p;
		index ++;
	}
}
void Piece::notify(Player* opp, int row, int col){
	uncheck(thePlayer->getOpp(0), row, col);
	//addNeighbours();
	check(thePlayer->getOpp(0));
}

int Piece::getRow(){
	return row;
}

int Piece::getCol(){
	return col;
}

char Piece::getType(){
	return type;
}

/*
void Piece::undraw(){
	w->fillRectangle(row, col,10,10,0);
}
*/

Piece::~Piece(){}

