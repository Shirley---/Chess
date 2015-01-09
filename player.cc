#include "player.h"
#include "piece.h"
#include "board.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int Player::numKing = 0;

Player::Player(Board *theBoard, int maxOpp, int bottomLine,int playerNum):
	theBoard(theBoard), maxOpp(maxOpp), bottomLine(bottomLine), theKing(NULL), numOpp(0), playerNum(playerNum) {
		//initializing Player's myPiece, Opponents, checked
		
		Checked = new int *[GRID_SIZE];
		Opps = new Player *[maxOpp];
		myPiece = new Piece **[GRID_SIZE];
		values = new int *[GRID_SIZE];
		//pList = new Piece*[GRID_SIZE * GRID_SIZE];

		for(int i = 0; i < GRID_SIZE; i ++) {
			Checked[i] = new int [GRID_SIZE];
			myPiece[i] = new Piece *[GRID_SIZE];
			Opps[i] = NULL;
			values[i] = new int [GRID_SIZE];
			//setting initial value of pointer to 0
			for (int j = 0; j < GRID_SIZE; j ++) {
				Checked[i][j] = 0;
				myPiece[i][j] = NULL;
				values[i][j] = 0;
			}
		}
}

bool Player::getChecked() {
	//if the king is not checked, or can move, then it's good
	if (Checked[theKing->getRow()][theKing->getCol()] == 0 || theKing->tryToMove()) 
		return false;

	//search for myPiece, try to move it
	for (int i = 0; i < GRID_SIZE; i ++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			//if found a piece, try to move it
			if (myPiece[i][j] != NULL) {
				if(myPiece[i][j]->tryToMove()) 
					return false;
			}
		}
	}
	return true;
}

int Player::getScore(int row, int col) {
	return values[row][col];
}

void Player::check(int row, int col){
	if (row < 0 || row > GRID_SIZE || col < 0 || col > GRID_SIZE) return;
	Checked[row][col] ++;
}

void Player::uncheck(int row, int col){
	if (row < 0 || row > GRID_SIZE || col < 0 || col > GRID_SIZE) return;
	Checked[row][col] --;
}

void Player::notifyBoard(int iRow, int iCol, int fRow, int fCol){
	theBoard->notify(iRow, iCol, fRow, fCol);
}

void Player::addOpp(Player* opp){
	Opps[numOpp] = opp;
	numOpp ++;
}

bool Player::isChecked(int row, int col) {
	return Checked[row][col] != 0;
}

bool Player::isPlaced(int row, int col) {

	return myPiece[row][col] != NULL;
}

Player* Player::getOpp(int pNum) {
	return Opps[pNum];
}

Piece* Player::getKing() {
	return theKing;
}

bool Player::bottomLinePawn() {
	for (int i = 0; i < GRID_SIZE; i ++) {
		if(myPiece[bottomLine][i] != NULL && (myPiece[bottomLine][i]->getType() == 'P' ||
			myPiece[bottomLine][i]->getType() == 'p')) {
			return true;
		}
	}
	return false;
}

void Player::checkOpps(Piece* p) {
	p->check(Opps[0]);
}

void Player::uncheckOpps(Piece* p) {
	p->uncheck(Opps[0], p->getRow(), p->getCol());
}

void Player::clearChecked() {
	for (int i = 0; i < GRID_SIZE; i ++) {
		for (int j = 0; j < GRID_SIZE; j ++) {
			Checked[i][j] = 0;
		}
	}
}

void Player::reCalc() {
	Opps[0]->clearChecked();
	for(int i = 0; i < GRID_SIZE; i ++) {
		for(int j = 0; j < GRID_SIZE; j ++) {
			if(myPiece[i][j] != NULL) {
				//myPiece[i][j]->uncheck(Opps[0], row, col);
				myPiece[i][j]->check(Opps[0]);
			}
		}
	}
}

int Player::getPNum() {
	return playerNum;
}

Player::~Player(){}