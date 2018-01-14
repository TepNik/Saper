#include <iostream>
#include <ctime>
#include <cstdlib>

void print_field(int x, int y, int **status, bool **mines);
bool is_end(int SIZEX, int SIZEY, int **status, bool **mines, int NOFMINES);
void play(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat);
void flag(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat, int NOFFLAGS, int NOFMINES);
void unflag(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat);

int main()
{
	int SIZEX, SIZEY, NOFMINES, NOFFLAGS = 0;
	setlocale(LC_ALL, "Russian");
	std::cout << "Сапер\n" << "Укажите размер x:";
	std::cin >> SIZEX;
	std::cout << "Укажите размер y:";
	std::cin >> SIZEY;
	std::cout << "Укажите количество мин:";
	std::cin >> NOFMINES;
	while (NOFMINES > SIZEX*SIZEY)
	{
		std::cout << "Слишком много мин. Укажите количество мин:";
		std::cin >> NOFMINES;
	}
	int **status = new int*[SIZEX];
	for (int i = 0; i < SIZEX; ++i)
	{
		status[i] = new int[SIZEY];
		for (int j = 0; j < SIZEY; ++j)
		{
			status[i][j] = -1;
		}
	}
	bool **mines = new bool*[SIZEX];
	for (int i = 0; i < SIZEX; ++i)
	{
		mines[i] = new bool[SIZEY];
		for (int j = 0; j < SIZEY; ++j)
		{
			mines[i][j] = false;
		}
	}
	for (int i = 0; i < NOFMINES; ++i)
	{
		int x, y;
		x = rand() % SIZEX;
		y = rand() % SIZEY;
		if (mines[x][y] == false)
			mines[x][y] = true;
		else
			--i;
	}
	bool stat = true;
	long long int begin = time(0), end;
	while (!is_end(SIZEX, SIZEY, status, mines, NOFMINES))
	{
		if (stat)
			print_field(SIZEX, SIZEY, status, mines);
		stat = true;
		std::cout << "1. Сходить\n" << "2. Поставить флаг\n" << "3. Снять флаг\n";
		int choise;
		std::cin >> choise;
		std::cout << "ВВедите координаты через пробел(x y):";
		int x, y;
		std::cin >> x >> y;
		if (choise == 1)
			play(x, y, status, mines, SIZEX, SIZEY, stat);
		else if (choise == 2)
			flag(x, y, status, mines, SIZEX, SIZEY, stat, NOFFLAGS, NOFMINES);
		else if (choise == 3)
			unflag(x, y, status, mines, SIZEX, SIZEY, stat);
		else
		{
			stat = false;
			std::cout << "Выберите один из вариантов:\n";
			continue;
		}
	}
	std::cout << "Вы выйграли!\n";
	end = time(0);
	std::cout << "Время:" << end - begin << " секунд.\n";
	system("pause");
	return 0;
}

void print_field(int x, int y, int **status, bool **mines)
{
	int i, n = x, countx = 0, county = 0;
	while (n > 0)
	{
		n /= 10;
		++countx;
	}
	n = y;
	while (n > 0)
	{
		n /= 10;
		++county;
	}
	for (i = 0; i < county; ++i)
		std::cout << ' ';
	std::cout << '|';
	for (i = 1; i <= x; ++i)
	{
		n = i;
		int c = 0, j;
		while (n > 0)
		{
			n /= 10;
			++c;
		}
		std::cout << i;
		for (j = 0; j <= countx - c; ++j)
			std::cout << ' ';
	}
	std::cout << '\n';
	for (int i = 0; i < county; ++i)
		std::cout << '-';
	std::cout << '+';
	if (countx > 1)
		for (int i = countx; i <= (countx + 1) * x; ++i)
			std::cout << '-';
	else
		for (int i = countx; i < (countx + 1) * x; ++i)
			std::cout << '-';
	std::cout << '\n';
	for (i = 1; i <= y; ++i)
	{
		n = i;
		int c = 0, j;
		while (n > 0)
		{
			n /= 10;
			++c;
		}
		std::cout << i;
		for (j = 0; j < county - c; ++j)
			std::cout << ' ';
		std::cout << '|';
		for (j = 0; j < x; ++j)
		{
			n = status[j][i - 1], c = 0;
			if (n == -1)
				std::cout << '*';
			else if (n == -2)
				std::cout << '^';
			else
				std::cout << n;
			while (n > 0)
			{
				n /= 10;
				++c;
			}
			for (int z = 0; z < countx; ++z)
				std::cout << ' ';
		}
		std::cout << '\n';
	}
}

bool is_end(int SIZEX, int SIZEY, int **status, bool **mines, int NOFMINES)
{
	for (int i = 0; i < SIZEX; ++i)
	{
		for (int j = 0; j < SIZEY; ++j)
		{
			if ((status[i][j] == -2) && (mines[i][j] == true))
				--NOFMINES;
		}
	}
	if (NOFMINES == 0)
		return true;
	else
		return false;
}

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

void flag(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat, int NOFFLAGS, int NOFMINES)
{
	if ((x <= 0) || (y <= 0) || (x > SIZEX) || (y > SIZEY))
	{
		std::cout << "Наберите нормальные координаты.\n";
		stat = false;
		return;
	}
	if (NOFFLAGS == NOFMINES)
	{
		std::cout << "На карте уже стоит максимальное количество флагов.\n";
		stat = false;
		return;
	}
	if (status[x - 1][y - 1] >= 0)
	{
		std::cout << "Эта точка уже открыта.\n";
		stat = false;
		return;
	}
	if ((status[x - 1][y - 1] < 0) && (NOFFLAGS < NOFMINES))
		status[x - 1][y - 1] = -2;
}

void unflag(int x, int y, int **status, bool **mines, int SIZEX, int SIZEY, bool &stat)
{
	if ((x <= 0) || (y <= 0) || (x > SIZEX) || (y > SIZEY))
	{
		std::cout << "Наберите нормальные координаты.\n";
		stat = false;
		return;
	}
	if (status[x - 1][y - 1] == -2)
		status[x - 1][y - 1] = -1;
}