#pragma once

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