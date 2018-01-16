#pragma once
#include "language.h"
void flag(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat, int NOFFLAGS, int NOFMINES)
{
	if ((x <= 0) || (y <= 0) || (x > SIZEX) || (y > SIZEY))
	{
		std::cout << phrases[15];
		stat = false;
		return;
	}
	if (NOFFLAGS == NOFMINES) //we can't put flags more than number of mines
	{
		std::cout << phrases[17];
		stat = false;
		return;
	}
	if (status[x - 1][y - 1] >= 0)
	{
		std::cout << phrases[18];
		stat = false;
		return;
	}
	if ((status[x - 1][y - 1] < 0) && (NOFFLAGS < NOFMINES))
		status[x - 1][y - 1] = -2;
}