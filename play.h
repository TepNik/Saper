#pragma once
void play(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat)
{
	if ((x <= 0) || (y <= 0) || (x > SIZEX) || (y > SIZEY))
	{
		std::cout << "Наберите нормальные координаты.\n";
		stat = false;
		return;
	}
	if (mines[x - 1][y - 1] == true)
	{
		std::cout << "Вы проиграли!\n";
		system("pause");
		exit(0);
	}
	int count = 0;
	if ((x > 1) && (y > 1) && (mines[x - 2][y - 2]))
		++count;

	if ((y > 1) && (mines[x - 1][y - 2]))
		++count;

	if ((x < SIZEX) && (y > 1) && (mines[x][y - 2]))
		++count;

	if ((x > 1) && (mines[x - 2][y - 1]))
		++count;

	if ((x < SIZEX) && (mines[x][y - 1]))
		++count;

	if ((x > 1) && (y < SIZEY) && (mines[x - 2][y]))
		++count;

	if ((y < SIZEX) && (mines[x - 1][y]))
		++count;

	if ((x < SIZEX) && (y < SIZEY) && (mines[x][y]))
		++count;

	status[x - 1][y - 1] = count;

	if ((x > 1) && (y > 1) && (!mines[x - 2][y - 2]) && (status[x - 2][y - 2] == -1))
		play(x - 1, y - 1, status, mines, SIZEX, SIZEY, stat);

	if ((y > 1) && (!mines[x - 1][y - 2]) && (status[x - 1][y - 2] == -1))
		play(x, y - 1, status, mines, SIZEX, SIZEY, stat);

	if ((x < SIZEX) && (y > 1) && (!mines[x][y - 2]) && (status[x][y - 2] == -1))
		play(x + 1, y - 1, status, mines, SIZEX, SIZEY, stat);

	if ((x > 1) && (!mines[x - 2][y - 1]) && (status[x - 2][y - 1] == -1))
		play(x - 1, y, status, mines, SIZEX, SIZEY, stat);

	if ((x < SIZEX) && (!mines[x][y - 1]) && (status[x][y - 1] == -1))
		play(x + 1, y, status, mines, SIZEX, SIZEY, stat);

	if ((x > 1) && (y < SIZEY) && (!mines[x - 2][y]) && (status[x - 2][y] == -1))
		play(x - 1, y + 1, status, mines, SIZEX, SIZEY, stat);

	if ((y < SIZEX) && (!mines[x - 1][y]) && (status[x - 1][y] == -1))
		play(x, y + 1, status, mines, SIZEX, SIZEY, stat);

	if ((x < SIZEX) && (y < SIZEY) && (!mines[x][y]) && (status[x][y] == -1))
		play(x + 1, y + 1, status, mines, SIZEX, SIZEY, stat);
}