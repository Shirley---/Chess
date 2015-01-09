#ifndef __BOARD_H__
#define __BOARD_H__
//#include "Piece.h"

//#include "Player.h"
#include "textdisplay.h"
#include "trashbin.h"
#include <iostream>
#include "window-v2.h"

class Player;
class Piece;

class Board {
	int maxPlayer;
	int numPlayer;
	int currentPlayer;
	int* scores;
	Piece*** theBoard;
	bool** placed;
	TextDisplay* theDisplay;
	Player** players;
	TrashBin* theBin;
public:
	Board(int maxPlayer);
	//default initializing two players
	void defaultInit(Player *p1, Player *p2);
	void notify(int iRow, int iCol, int fRow, int fCol);
	void addPlayer(Player* p);
	void setPiece(char type, int row, int col);
	Piece* getPiece(int row, int col);
	void delPiece(int row, int col);
	bool isPlaced(int row, int col);
	void setPlaced(int row, int col, bool value);
	void notifyPlayer(int row, int col);
	Player* getPlayer();
	int getTurn();
	bool checkForStart();						//return true if each player has a king
	void nextTurn();
	void setTurn(int tNum);
	void addScore();
	void printScore();

	~Board();

	friend std::ostream &operator<<(std::ostream &out, const Board &d);

};

#endif