#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "print_field.h"
#include "flag.h"
#include "is_end.h"
#include "play.h"
#include "unflag.h"

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
	while ((NOFMINES >= SIZEX*SIZEY)||(NOFMINES <= 0))
	{
		std::cout << "Укажите нормальное количество мин:";
		std::cin >> NOFMINES;
	}
	int **status = new int*[SIZEX];
	bool **mines = new bool*[SIZEX];
	for (int i = 0; i < SIZEX; ++i)
	{
		status[i] = new int[SIZEY];
		mines[i] = new bool[SIZEY];
		for (int j = 0; j < SIZEY; ++j)
		{
			status[i][j] = -1;
			mines[i][j] = false;
		}
	}
	int x1, y1, choise1, choise, x, y;
	print_field(SIZEX, SIZEY, status, mines);
	std::cout << "1. Сходить\n" << "2. Поставить флаг\n" << "3. Снять флаг\n";
	std::cin >> choise1;
	std::cout << "ВВедите координаты через пробел(x y):";
	std::cin >> x1 >> y1;
	srand(time(NULL));
	for (int i = 0; i < NOFMINES; ++i)
	{
		int x, y;
		x = rand() % SIZEX;
		y = rand() % SIZEY;
		if ((mines[x][y] == false)&&((x != x1 - 1) || (y != y1 - 1)))
			mines[x][y] = true;
		else
			--i;
	}
	bool stat = false, stat2 = false;
	long long begin = time(0), end;
	while (!is_end(SIZEX, SIZEY, status, mines, NOFMINES))
	{
		if (stat)
			print_field(SIZEX, SIZEY, status, mines);
		stat = true;
		if (stat2)
		{
			std::cout << "1. Сходить\n" << "2. Поставить флаг\n" << "3. Снять флаг\n";
			std::cin >> choise;
			std::cout << "ВВедите координаты через пробел(x y):";
			std::cin >> x >> y;
		}
		else
		{
			choise = choise1;
			x = x1;
			y = y1;
		}
		stat2 = true;
		switch (choise)
		{
		case 1:
			play(x, y, status, mines, SIZEX, SIZEY, stat);
			break;
		case 2:
			flag(x, y, status, mines, SIZEX, SIZEY, stat, NOFFLAGS, NOFMINES);
			break;
		case 3:
			unflag(x, y, status, mines, SIZEX, SIZEY, stat);
			break;
		default:
			stat = false;
			std::cout << "Выберите один из вариантов:\n";
			break;
		}
	}
	std::cout << "Вы выйграли!\n";
	end = time(0);
	int result_time = end - begin, n = -1, i, ind = 0, square = SIZEX * SIZEY;
	std::cout << "Время:" << result_time << " секунд.\n";
	std::ofstream fout;
	std::ifstream fin;
	fin.open("results.log", std::fstream::in);
	if (!fin.good())
	{
		fout.open("results.log", std::fstream::out);
		fout.close();
		fin.open("results.log", std::fstream::in);
	}
	if (!fin)
	{
		std::cout << "File not opened\n";
		system("pause");
		exit(0);
	}
	fin >> n;
	if (n == -1)
	{
		std::cout << "Новый рекорд прохождения на этой площади и с этим количествоим мин.\n";
		fout.open("results.log", std::fstream::out);
		if (!fout)
		{
			std::cout << "File not opened out 01\n";
			exit(0);
		}
		fout << 1 << '\n' << square << ' ' << NOFMINES << ' ' << result_time << '\n';
		system("pause");
		return 0;
	}
	int **m = new int*[n];
	bool stat3 = false;
	for (i = 0; i < n; ++i)
	{
		m[i] = new int[3];
		fin >> m[i][0] >> m[i][1] >> m[i][2];
	}
	for (i = 0; i < n; ++i)
	{
		if ((square == m[i][0]) && (!stat3))
		{
			ind = i;
			while ((ind < n) && (square == m[ind][0]) && (NOFMINES > m[ind][1]))
				++ind;
			if ((ind < n) && (NOFMINES == m[ind][1]))
				stat3 = true;
		}
		else
			++ind;
	}
	fout.open("results.log", std::fstream::out);
	if (!fout)
	{
		std::cout << "File not opened out\n";
		exit(0);
	}
	fout << (stat3 ? n : n + 1) << '\n';
	for (i = 0; i < ind; ++i)
		fout << m[i][0] << ' ' << m[i][1] << ' ' << m[i][2] << '\n';
	if (stat3)
	{
		if (result_time < m[ind][2])
		{
			fout << square << ' ' << NOFMINES << ' ' << result_time << '\n';
			std::cout << "Новый рекорд прохождения на этой площади и с этим количествоим мин.\n";
		}
		else
		{
			fout << square << ' ' << NOFMINES << ' ' << m[ind][2] << '\n';
			std::cout << "Рекорд на этой площади и с этим количествоим мин:" << m[ind][2] << " секунды.\n";
		}
	}
	else
	{
		fout << square << ' ' << NOFMINES << ' ' << result_time << '\n';
		std::cout << "Новый рекорд прохождения на этой площади и с этим количествоим мин.\n";
	}
	for (i = (stat3 ? ind + 1 : ind); i < n; ++i)
		fout << m[i][0] << ' ' << m[i][1] << ' ' << m[i][2] << '\n';
	system("pause");
	return 0;
}