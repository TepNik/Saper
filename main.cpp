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
	int SIZEX, SIZEY /*sizes of field*/, NOFMINES, NOFFLAGS = 0/*number of mines and flags on field*/, language /*needed in choosing language*/, i, j /*needed in for*/;
	bool statlang = false/*needed in choosing language*/;
	setlocale(LC_ALL, "Russian");
	while (!statlang)//choosing language for game with checking on correctness of input
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
	std::cout << phrases[0] << phrases[1];//set size of field and number of mines
	std::cin >> SIZEX;
	std::cout << phrases[2];
	std::cin >> SIZEY;
	while ((SIZEX <= 0) || (SIZEY <= 0))//checking of correctness input of size of field
	{
		std::cout << phrases[15];
		std::cout << phrases[1];
		std::cin >> SIZEX;
		std::cout << phrases[2];
		std::cin >> SIZEY;
	}
	std::cout << phrases[3];
	std::cin >> NOFMINES;
	while ((NOFMINES >= SIZEX*SIZEY)||(NOFMINES <= 0))//checking of correctness input of NOFMINES
	{
		std::cout << phrases[4];
		std::cin >> NOFMINES;
	}
	int **status = new int*[SIZEX];
	// in that massiv -1 means that it is unknown area, -2 - there is flag, if there is positive number - there are that number of mines around that dot
	bool **mines = new bool*[SIZEX];
	//true - there is mine, false - not
	for (i = 0; i < SIZEX; ++i)//filling massives with standard values
	{
		status[i] = new int[SIZEY];
		mines[i] = new bool[SIZEY];
		for (j = 0; j < SIZEY; ++j)
		{
			status[i][j] = -1;
			mines[i][j] = false;
		}
	}
	int x, y, choise;
	//x, y - input coordinates, 
	bool stat = false;
	//needed in cheking of correctness of input: true - all ok, false - not
	print_field(SIZEX, SIZEY, status, mines);
	long long begin, end;
	//needed to know the result time
	while (!stat)//making first step here because we need to spawn mines befor main cycle
	{
		std::cout << phrases[5] << phrases[6] << phrases[7];
		std::cin >> choise;
		std::cout << phrases[8];
		std::cin >> x >> y;
		if ((x <= 0) || (y <= 0) || (x > SIZEX) || (y > SIZEY))
			std::cout << phrases[15];
		else
		{
			begin = time(0);
			//game begin
			stat = true;
		}
	}
	srand(time(NULL));//for making rand() is realy random
	for (i = 0; i < NOFMINES; ++i)//spawning mines
	{
		int x1, y1;//random coordinates
		x1 = rand() % SIZEX;
		y1 = rand() % SIZEY;
		if ((mines[x1][y1] == false)&&((x1 != x - 1) || (y1 != y - 1)))
			mines[x1][y1] = true;
		else
			--i;
	}
	stat = false; //put in initial position
	bool stat2 = false;//we need it not to cin x and y again(because we get them befor and didn't make step)
	while (!is_end(SIZEX, SIZEY, status, mines, NOFMINES)) //MAIN CYCLE here we play game
	{
		if (stat) //printing field
			print_field(SIZEX, SIZEY, status, mines);
		stat = true;
		if (stat2)
		{
			std::cout << phrases[5] << phrases[6] << phrases[7];
			std::cin >> choise;
			std::cout << phrases[8];
			std::cin >> x >> y;
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
	//game end
	int result_time = end - begin /*result time*/,
		n = -1/*need to check if file opened*/,
		ind = 0/*after for that marked below it shows where if filed we need to write results of game*/,
		square = SIZEX * SIZEY /*square of field*/;
	std::cout << phrases[11] << result_time << phrases[12];
	std::ofstream fout;
	std::ifstream fin;
	fin.open("results.log", std::fstream::in); //in that file we store results of past games
	//at first there is a number that shows how many lines are there in that file
	//after that there are lines(1 line - best result of game on certain square of field and number of mines)
	//exp:25 1 5 - that means that square is 25, NOFMINES = 1, result_time = 5
	if (!fin.good()) //if file not exist then we create if with ofstream
	{
		fout.open("results.log", std::fstream::out);
		fout.close();
		fin.open("results.log", std::fstream::in);
	}
	if (!fin) //checking if last step helped
	{
		std::cout << "File not opened\n";
		system("pause");
		exit(0);
	}
	fin >> n;
	if (n == -1) //checking if in file there are no results(if n == -1 then fin didn't get n then file is empty)
	{
		std::cout << phrases[13];
		fout.open("results.log", std::fstream::out);
		if (!fout)
		{
			std::cout << "File not opened out\n";
			exit(0);
		}
		fout << 1 << '\n' << square << ' ' << NOFMINES << ' ' << result_time << '\n'; //write first result in file
		system("pause");
		return 0;
	}
	int **m = new int*[n];
	//make massiv where we will store all results that are in file
	stat = false;
	//false - in this file there wasn't result of game with same square and NOFMINES, true - there was it
	for (i = 0; i < n; ++i) //fill massiv
	{
		m[i] = new int[3];
		fin >> m[i][0] >> m[i][1] >> m[i][2];
	}
	for (i = 0; i < n; ++i) //MARKED FOR here we try to find where we can write result of this game
	{
		if ((square == m[i][0]) && (!stat))
		{
			ind = i;
			while ((ind < n) && (square == m[ind][0]) && (NOFMINES > m[ind][1]))
				++ind;
			if ((ind < n) && (NOFMINES == m[ind][1]))
				stat = true;
		}
		else if (square > m[i][0])
			++ind;
	}
	fout.open("results.log", std::fstream::out); //open out stream
	//open in that time because when we open it file become empty
	if (!fout)//checking if file opened
	{
		std::cout << "File not opened out\n";
		exit(0);
	}
	fout << (stat ? n : n + 1) << '\n';
	//if in file there was result of game with same square and NOFMINES we will write result on it place and write n
	//if there wasn't it then we will write result on a new line and we write n + 1
	for (i = 0; i < ind; ++i)//wrute all results with less square or less NOFMINES
		fout << m[i][0] << ' ' << m[i][1] << ' ' << m[i][2] << '\n';
	if (stat) //write result of this game
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
	//write all other results
	for (i = (stat ? ind + 1 : ind); i < n; ++i)//if we find in this file result of game with same square and NOFMINES (stat == true) we do cycle from i = ind + 1
												//if not (stat == false) we do cycle from i = ind
		fout << m[i][0] << ' ' << m[i][1] << ' ' << m[i][2] << '\n';
	system("pause");
	return 0;
}