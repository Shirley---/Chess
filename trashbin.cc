#include "trashbin.h"
#include <stdlib.h>

class Piece;

TrashBin::TrashBin(int capacity):capacity(capacity), numTrash(0) {
	theBin = new Piece *[capacity];
}

void TrashBin::dump(Piece* garbage) {
	if (numTrash + 1 >= capacity) {
		emptyBin();
	}
	theBin[numTrash] = garbage;
	numTrash ++;
}

void TrashBin::emptyBin() {
	for (int i = 0; i < numTrash; i ++) {
		delete theBin[i];
	}
	numTrash = 0;
}

Piece* TrashBin::recover(Piece* p) {
	for (int i = 0; i < numTrash; i ++) {
		if (theBin[i] == p) {
			theBin[i] = NULL;
			numTrash --;
			for (int j = i; j < numTrash; j ++) {
				theBin[j] = theBin[j + 1];
			}
			return p;
		}
	}
	//if nothing is found, return a NULL pointers
	return NULL;
}