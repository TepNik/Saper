#pragma once
#include "language.h"
void unflag(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat)
{
	if ((x <= 0) || (y <= 0) || (x > SIZEX) || (y > SIZEY))
	{
		std::cout << phrases[15];
		stat = false;
		return;
	}
	switch (status[x - 1][y - 1])
	case -2:
		status[x - 1][y - 1] = -1;
}