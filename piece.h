#ifndef __PIECE_H__
#define __PIECE_H__

//#include "Player.h"
#include "textdisplay.h"
#include "window-v2.h"

class Player;
class Board;

const int MAX_NEIGHBOURS = 8;
const int GRID_SIZE = 8;

class Piece{
protected:
	char type;
	int row, col;
	int index;
	static Piece* pawnJustMoved;
	Player* thePlayer;
	Piece** neighbour;
	Board* theBoard;
	Xwindow *w;
public:
	Piece(char type, int row, int col, Player* p, Board *theBoard);
	//void setCoor(int row, int col);
	virtual bool validMove(int row, int col) = 0;
	//try the next possible move return true if there exist a possible next move
	virtual bool tryToMove() = 0;
	virtual void check(Player* opp) = 0;
	virtual void uncheck(Player* opp, int row, int col) = 0;
	virtual void notifyDisplay(TextDisplay& t) = 0;
	bool move(int fRow, int fCol);
	bool notifyKing();
	void addNeighbours();
	void addNeighbour(Piece* neighbour);
	void notifyNeighboursMoved();
	void notifyNeighboursPlaced();
	void notify(Player* opp, int row, int col);
	virtual void upgrade() = 0;
	int getRow() ;
	int getCol();
	char getType();
	//void undraw();
	~Piece();
};

class Pawn : public Piece{
	int front;
	bool firstTime;
public:
	Pawn(char type, int row, int coloum, Player* p, Board *theBoard, int front);
	bool validMove(int row, int col);
	//try the next possible move return true if there exist a possible next move
	bool tryToMove();
	void check(Player* opp);
	void uncheck(Player* opp, int row, int col);
	void notifyDisplay(TextDisplay& t);
	void upgrade();
	int getFront();
	//void draw(int colour);

};

class Rook : public Piece{
	bool moved;
public:
	Rook(char type,int row, int coloum, Player* p, Board *theBoard);
	bool validMove(int row, int col);
	//try the next possible move return true if there exist a possible next move
	bool tryToMove();
	void check(Player* opp);
	void uncheck(Player* opp, int row, int col);
	void notifyDisplay(TextDisplay& t);
	void upgrade();
	//void draw(int colour);
};

class Knight : public Piece{
public:
	Knight(char type, int row, int coloum, Player* p, Board *theBoard);
	bool validMove(int row, int col);
	//try the next possible move return true if there exist a possible next move
	bool tryToMove();
	void check(Player* opp);
	void uncheck(Player* opp, int row, int col);
	void notifyDisplay(TextDisplay& t);
	void upgrade();
	//void draw(int colour);
};

class Bishop : public Piece{
public:
	Bishop(char type, int row, int coloum, Player* p, Board *theBoard);
	bool validMove(int row, int col);
	//try the next possible move return true if there exist a possible next move
	bool tryToMove();
	void check(Player* opp);
	void uncheck(Player* opp, int row, int col);
	void notifyDisplay(TextDisplay& t);
	void upgrade();
	//void draw(int colour);
};


class King : public Piece{
public:
	King(char type, int row, int coloum, Player* p, Board *theBoard);
	bool validMove(int row, int col);
	//try the next possible move return true if there exist a possible next move
	bool tryToMove();
	void check(Player* opp);
	void uncheck(Player* opp, int row, int col);
	void notifyDisplay(TextDisplay& t);
	void upgrade();
	void castling();
	//void draw(int colour);
};

class Queen : public Piece{
public:
	Queen(char type, int row, int coloum, Player* p, Board *theBoard);
	bool validMove(int row, int col);
	//try the next possible move return true if there exist a possible next move
	bool tryToMove();
	void check(Player* opp);
	void uncheck(Player* opp, int row, int col);
	void notifyDisplay(TextDisplay& t);
	void upgrade();
	//void draw(int colour);
};
#endif