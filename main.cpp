#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "language.h"
#include "print_field.h"
#include "flag.h"
#include "is_end.h"
#include "play.h"
#include "unflag.h"

int main()
{
	int SIZEX, SIZEY, NOFMINES, NOFFLAGS = 0, language;
	bool statlang = false;
	setlocale(LC_ALL, "Russian");
	while (!statlang)
	{
		std::cout << "Set lenguage:\n" << "1. English\n2. Русский\n";
		std::cin >> language;
		if ((language < 1) || (language > 2))
		{
			std::cout << "Write 1 or 2";
			continue;
		}
		(language == 1 ? seteng() : setrus());
		statlang = true;
	}
	std::cout << phrases[0] << phrases[1];
	std::cin >> SIZEX;
	std::cout << phrases[2];
	std::cin >> SIZEY;
	std::cout << phrases[3];
	std::cin >> NOFMINES;
	while ((NOFMINES >= SIZEX*SIZEY)||(NOFMINES <= 0))
	{
		std::cout << phrases[4];
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
	bool stat = false;
	print_field(SIZEX, SIZEY, status, mines);
	while (!stat)
	{
		std::cout << phrases[5] << phrases[6] << phrases[7];
		std::cin >> choise1;
		std::cout << phrases[8];
		std::cin >> x1 >> y1;
		if ((x <= 0) || (y <= 0) || (x > SIZEX) || (y > SIZEY))
			std::cout << phrases[15];
		else
			stat = true;
	}
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
	stat = false
	bool stat2 = false;
	long long begin = time(0), end;
	while (!is_end(SIZEX, SIZEY, status, mines, NOFMINES))
	{
		if (stat)
			print_field(SIZEX, SIZEY, status, mines);
		stat = true;
		if (stat2)
		{
			std::cout << phrases[5] << phrases[6] << phrases[7];
			std::cin >> choise;
			std::cout << phrases[8];
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
			std::cout << phrases[9];
			break;
		}
	}
	std::cout << phrases[10];
	end = time(0);
	int result_time = end - begin, n = -1, i, ind = 0, square = SIZEX * SIZEY;
	std::cout << phrases[11] << result_time << phrases[12];
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
		std::cout << phrases[13];
		fout.open("results.log", std::fstream::out);
		if (!fout)
		{
			std::cout << "File not opened out\n";
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
		else if (square > m[i][0])
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
			std::cout << phrases[13];
		}
		else
		{
			fout << square << ' ' << NOFMINES << ' ' << m[ind][2] << '\n';
			std::cout << phrases[14] << m[ind][2] << phrases[12];
		}
	}
	else
	{
		fout << square << ' ' << NOFMINES << ' ' << result_time << '\n';
		std::cout << phrases[13];
	}
	for (i = (stat3 ? ind + 1 : ind); i < n; ++i)
		fout << m[i][0] << ' ' << m[i][1] << ' ' << m[i][2] << '\n';
	system("pause");
	return 0;
}