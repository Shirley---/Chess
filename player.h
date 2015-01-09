#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "board.h"

//#include "Piece.h"
class Piece;

//pure abstract class
class Player {
protected:
	int playerNum;		//to indicate which player i am
	static int numKing;
	int **values;
	int bottomLine;
	int maxOpp;
	int numOpp;
	int numPiece;
	Player** Opps;		//oops will include this
	Piece*** myPiece;
	Piece** pList;
	Piece* theKing;
	Board* theBoard;
	
public:
	int** Checked;
	Player(Board* theBoard, int maxOpp, int bottomLine, int playerNum);
	virtual bool move() = 0;
	virtual void addPiece(Piece* p, int row, int col) = 0;
	virtual void removePiece(int row, int col) = 0;
	int getPNum();
	void reCalc();
	void clearChecked();
	int getScore(int row, int col);
	//virtual bool move(int iRow, int iCol, int fRow, int fCol) = 0;
	void check(int row, int col) ;
	void uncheck(int row, int col);
	bool getChecked();
	//a board is notified when a change of pieces is made
	void notifyBoard(int iRow, int iCol, int fRow, int fCol);
	void addOpp(Player* opp);
	bool isChecked(int row, int col);
	bool isPlaced(int row, int col);
	Player* getOpp(int pNum) ;
	Piece* getKing();
	//return true when there is a pawn at bottom line
	bool bottomLinePawn();
	void checkOpps(Piece* p) ;			//checking all the opponents using this piece
	void uncheckOpps(Piece* p);
	~Player();
};

class Human: public Player {
public:
	Human(Board* theBoard, int numOpp, int bottomLine, int playerNum);
	void addPiece(Piece* p, int row, int col);
	void removePiece(int row, int col);
	bool move();
};

class Computer: public Player {
protected:
	int** values;
	int numPiece;
	Piece** pList;
public:
	Computer(Board *theBoard, int numOpp, int bottomLine, int playerNum);
	virtual bool move() = 0;
	void addPiece(Piece* p, int row, int col);
	void removePiece(int row, int col);
	
};

class Level1AI: public Computer {
public:
	Level1AI(Board* theBoard, int numOpp, int bottomLine, int playerNum);
	bool move();
};

class Level2AI: public Computer {
public:
	Level2AI(Board* theBoard, int numOpp, int bottomLine, int playerNum);
	bool move();
};

class Level3AI: public Computer {
public:
	Level3AI(Board* theBoard, int numOpp, int bottomLine, int playerNum);
	bool move();
};

class Level4AI: public Computer {
public:
	Level4AI(Board* theBoard, int numOpp, int bottomLine, int playerNum);
	bool move();
};

#endif