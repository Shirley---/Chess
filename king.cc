#include "piece.h"
#include "board.h"
#include "textdisplay.h"
#include "player.h"
#include <cstdlib>

using namespace std;

int abs(int a) {
	if (a < 0) return -a;
	return a;
}

King::King(char type, int row, int col, Player* p, Board *theBoard):Piece(type, row, col, p, theBoard) {
	if (thePlayer->getPNum() == 0) type = 'K';
	else type = 'k';
}

bool King::validMove(int row, int col) {
	if ((this->col == col && this->row == row) || (col + 1> GRID_SIZE) || col < 0) return false;
	if ((this->col == col && this->row == row) || (row + 1> GRID_SIZE) || row < 0) return false;

	//moving according to the rule
	if (! (abs(this->row - row) == 1 && abs(this->col - col) == 1)||
		(abs(this->row - row) == 1 && this->col == col)||
		(this->row == row && abs(this->col - col) == 1))
		return false;
	if (thePlayer->isPlaced(row, col)) return false;
	if (thePlayer->isChecked(row, col)) return false;
	return true;
}

void King::castling() {
	
}

bool King::tryToMove(void) {
	return 
		(validMove(row + 1, col + 1) ||
		validMove(row + 1, col) ||
		validMove(row + 1, col - 1) ||
		validMove(row, col + 1) ||
		validMove(row, col - 1) ||
		validMove(row - 1, col + 1) ||
		validMove(row - 1, col) ||
		validMove(row - 1, col - 1));
}

void King::check(Player *p) {
	if (row + 1 < GRID_SIZE && col + 1 < GRID_SIZE)
		p->check(row + 1, col + 1);
	if (row + 1 < GRID_SIZE)
		p->check(row + 1, col);
	if (row + 1 < GRID_SIZE && col - 1 > 0)
		p->check(row + 1, col - 1);
	if (col + 1 < GRID_SIZE)
		p->check(row, col + 1);
	if (col - 1 > 0)
		p->check(row, col - 1);
	if (row - 1 > 0 && col + 1 < GRID_SIZE)
		p->check(row - 1, col + 1);
	if (row - 1 > 0)
		p->check(row - 1, col);
	if (row - 1 > 0 && col - 1 > 0)
		p->check(row - 1, col - 1);
}

void King::uncheck(Player* p, int row, int col) {
	
	if (row + 1 < GRID_SIZE && col + 1 < GRID_SIZE)
		p->uncheck(row + 1, col + 1);
	if (row + 1 < GRID_SIZE)
		p->uncheck(row + 1, col);
	if (row + 1 < GRID_SIZE && col - 1 > 0)
		p->uncheck(row + 1, col - 1);
	if (col + 1 < GRID_SIZE)
		p->uncheck(row, col + 1);
	if (col - 1 > 0)
		p->uncheck(row, col - 1);
	if (row - 1 > 0 && col + 1 < GRID_SIZE)
		p->uncheck(row - 1, col + 1);
	if (row - 1 > 0)
		p->uncheck(row - 1, col);
	if (row - 1 > 0 && col - 1 > 0)
		p->uncheck(row - 1, col - 1);
}

void King::notifyDisplay(TextDisplay &t) {}

void King::upgrade(){}

/*
void King::draw(int colour){
	w->drawBigString(x*10,y*10,"K",colour);
}
*/