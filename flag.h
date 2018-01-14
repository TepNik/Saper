#pragma once
void flag(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat, int NOFFLAGS, int NOFMINES)
{
	if ((x <= 0) || (y <= 0) || (x > SIZEX) || (y > SIZEY))
	{
		std::cout << "Ќаберите нормальные координаты.\n";
		stat = false;
		return;
	}
	if (NOFFLAGS == NOFMINES)
	{
		std::cout << "Ќа карте уже стоит максимальное количество флагов.\n";
		stat = false;
		return;
	}
	if (status[x - 1][y - 1] >= 0)
	{
		std::cout << "Ёта точка уже открыта.\n";
		stat = false;
		return;
	}
	if ((status[x - 1][y - 1] < 0) && (NOFFLAGS < NOFMINES))
		status[x - 1][y - 1] = -2;
}