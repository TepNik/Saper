#pragma once
bool is_end(int SIZEX, int SIZEY, int **status, bool **mines, int NOFMINES)//checking if all mines and flags at the sape coordinates
{
	for (int i = 0; i < SIZEX; ++i)
		for (int j = 0; j < SIZEY; ++j)
			if ((status[i][j] == -2) && (mines[i][j] == true))
				--NOFMINES;
	return (NOFMINES == 0 ? true : false);
}