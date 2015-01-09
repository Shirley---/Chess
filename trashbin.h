#ifndef __TRASHBIN_H__
#define __TRASHBIN_H__

class Piece;

class TrashBin{
	Piece** theBin;
	int numTrash;
	int capacity;
public:
	TrashBin(int capacity);
	void dump(Piece* garbage);
	void emptyBin();
	Piece* recover(Piece* p);
};

#endif