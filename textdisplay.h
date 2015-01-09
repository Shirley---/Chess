#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>
#include "window-v2.h"

class TextDisplay {
  char **theDisplay;
  const int boardSize;
  Xwindow *w;
public:
	TextDisplay(int n);
	//resets the display
	void resetDisplay();
	void notify(int iRow, int iCol, int fRow, int fCol, char type);

	~TextDisplay();

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
