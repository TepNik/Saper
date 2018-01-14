#pragma once
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