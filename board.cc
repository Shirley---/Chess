#include "board.h"
#include "textdisplay.h"
#include "trashbin.h"
#include "player.h"
#include "piece.h"
#include <stdlib.h>

#include <iostream>

using namespace std;

const int BOARD_SIZE = 8;
const int MAX_PIECE = 32;

Board::Board(int maxPlayer): maxPlayer(maxPlayer), numPlayer(0), currentPlayer(0) {
		
	theBoard = new Piece **[BOARD_SIZE];
	theDisplay = new TextDisplay(BOARD_SIZE);
	placed = new bool *[BOARD_SIZE];
	players = new Player *[maxPlayer];
	theBin = new TrashBin(MAX_PIECE);
	scores = new int(2);
	scores[0] = 0;
	scores[1] = 0;
	for (int i = 0; i < BOARD_SIZE; i ++) {
			
		theBoard[i] = new Piece *[BOARD_SIZE];
		placed[i] = new bool [BOARD_SIZE];
		players[i] = NULL;

		for (int j = 0; j < BOARD_SIZE; j ++) {
			theBoard[i][j] = NULL;
			placed[i][j] = false;
		}

	}
}

//default is two players

void Board::defaultInit(Player *p1, Player *p2) {
	theDisplay->resetDisplay();
	players[0] = p1;
	players[1] = p2;
	numPlayer = 2;
	p1->addOpp(p2);
	p2->addOpp(p1);
	theBoard = new Piece **[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i ++) {
			
		theBoard[i] = new Piece *[BOARD_SIZE];

		for (int j = 0; j < BOARD_SIZE; j ++) {
			theBoard[i][j] = NULL;
			placed[i][j] = false;
		}

	}
	//initializing black
	setPiece('r', 0, 0);
	setPiece('n', 0, 1);
	setPiece('b', 0, 2);
	setPiece('q', 0, 3);
	setPiece('k', 0, 4);
	setPiece('b', 0, 5);
	setPiece('n', 0, 6);
	setPiece('r', 0, 7);
	for (int i = 0; i < BOARD_SIZE; i ++) {
		setPiece('p', 1, i);
	}

	//initializing white
	setPiece('R', BOARD_SIZE - 1, 0);
	setPiece('N', BOARD_SIZE - 1, 1);
	setPiece('B', BOARD_SIZE - 1, 2);
	setPiece('Q', BOARD_SIZE - 1, 3);
	setPiece('K', BOARD_SIZE - 1, 4);
	setPiece('B', BOARD_SIZE - 1, 5);
	setPiece('N', BOARD_SIZE - 1, 6);
	setPiece('R', BOARD_SIZE - 1, 7);
	for (int i = 0; i < BOARD_SIZE; i ++) {
		setPiece('P', BOARD_SIZE - 2, i);
	}
}

void Board::addPlayer(Player* p) {
	players[numPlayer] = p;
	numPlayer ++;
}

void Board::setPiece(char type, int row, int col) {
	Piece* temp = NULL;
	if (placed[row][col]){
		//if there is a piece, delete the original piece
		delPiece(row, col);
	}
	switch (type) {
	
	case 'R':
		temp = new Rook(type, row, col, players[0], this);
		players[0]->addPiece(temp, row, col);
		break;
	case 'r':
		temp = new Rook(type, row, col, players[1], this);
		players[1]->addPiece(temp, row, col);
		break;
	case 'N':
		temp = new Knight(type, row, col, players[0], this);
		players[0]->addPiece(temp, row, col);
		break;
	case 'n':
		temp = new Knight(type, row, col, players[1], this);
		players[1]->addPiece(temp, row, col);
		break;
	case 'B':
		temp = new Bishop(type, row, col, players[0], this);
		players[0]->addPiece(temp, row, col);
		break;
	case 'b':
		temp = new Bishop(type, row, col, players[1], this);
		players[1]->addPiece(temp, row, col);
		break;
	case 'Q':
		temp = new Queen(type, row, col, players[0], this);
		players[0]->addPiece(temp, row, col);
		break;
	case 'q':
		temp = new Queen(type, row, col, players[1], this);
		players[1]->addPiece(temp, row, col);
		break;
	case 'K':
		temp = new King(type, row, col, players[0], this);
		players[0]->addPiece(temp, row, col);
		break;
	case 'k':
		temp = new King(type, row, col, players[1], this);
		players[1]->addPiece(temp, row, col);
		break;
	case 'P':
		temp = new Pawn(type, row, col, players[0], this, -1);
		players[0]->addPiece(temp, row, col);
		break;
	case 'p':
		temp = new Pawn(type, row, col, players[1], this, 1);
		players[1]->addPiece(temp, row, col);
		break;
	default:
		break;
	}
	temp->addNeighbours();
	//cout << "set: " << row << col << endl;
	theBoard[row][col] = temp;
	theDisplay->notify(-1, -1, row, col, type);
	placed[row][col] = true;
}

void Board::delPiece(int row, int col) {

	if (theBoard[row][col] != NULL) {
		//notify all players that this piece is removed
		notifyPlayer(row, col);
		//trash it to the bin, and do the recycle thingy
		theBin->dump(theBoard[row][col]);
		theBoard[row][col] = NULL;
		placed[row][col] = false;
		theDisplay->notify(row, col, -1, -1, 'a');
	}

}

bool Board::isPlaced(int row, int col) {
	return placed[row][col];
}

void Board::setPlaced(int row, int col, bool value) {
	placed[row][col] = value;
}

void Board::notifyPlayer(int row, int col) {
	for(int i = 0; i < numPlayer; i ++) {
		players[i]->removePiece(row, col);
	}
}

//board has been notified iff there is a move of a piece on the board
//that is, a player has done the move
void Board::notify(int iRow, int iCol, int fRow, int fCol) {
	//if there is a piece there, delete it
	delPiece(fRow, fCol);
	//move the required piece
	theBoard[fRow][fCol] = theBoard[iRow][iCol];
	theBoard[iRow][iCol] = NULL;
	//theBoard[fRow][fCol]->setCoor(fRow, fCol);
	theDisplay->notify(iRow,iCol,fRow,fCol,theBoard[fRow][fCol]->getType());
	
}

int Board::getTurn() {
	return currentPlayer;
}

Piece* Board::getPiece(int row, int col) {
	return theBoard[row][col];
}

Player* Board::getPlayer() {
	return players[currentPlayer];
}

void Board::nextTurn() {
	currentPlayer = (currentPlayer + 1) % numPlayer;
}

bool Board::checkForStart() {
	
	for (int i = 0; i < numPlayer; i ++) {
		//check for one King each player
		if (players[i]->getKing() == NULL) {
			return false;
		} 
		//check for bottom line pawns
		if (players[i]->bottomLinePawn()) {
			return false;
		}
		//a player cannot be checked
		if (players[i]->getChecked()) {
			return false;
		}
	}

	return true;
}

void Board::printScore() {
	for (int i = 0; i < numPlayer; i ++) {
		cout << "Player " << i + 1 << ": " << scores[i] << endl;
	}
}

void Board::addScore() {
	//everyone except current player get a point
	for (int i = 0; i < numPlayer; i ++) {
		if (i != currentPlayer) {
			scores[i] ++;
		}
	}
}

ostream &operator<<(ostream &out, const Board &b) {
	out << *(b.theDisplay);
	return out;
}

Board::~Board() {
	theBin->emptyBin();
	for (int i = 0; i < BOARD_SIZE; i ++) {
		for (int j = 0; j < BOARD_SIZE; j ++) {
			delete theBoard[i][j];
		}
		//delete [] theBoard[i];
	}
	//delete[] theBoard;
}

void Board::setTurn(int tNum) {
	currentPlayer = tNum;
}
