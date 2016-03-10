#include <iostream>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;

	for (int r = 0; r < nRows; r++)
		for (int c = 0; c < nCols; c++)
			m_grid[r][c] = 0;
}

bool History::record(int r, int c)
{
	if (r <= m_rows || c <= m_cols)
	{
		m_grid[r - 1][c - 1] = m_grid[r - 1][c - 1] + 1;
		return true;
	}
	return false;
}

void History::display() const
{
	char display_grid[MAXROWS][MAXCOLS];
	int r, c;

	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
		{
			if (m_grid[r][c] == 0)
				display_grid[r][c] = '.';
			else if (m_grid[r][c] > 0 && m_grid[r][c] <= 25)
				display_grid[r][c] = 'A' + m_grid[r][c] - 1;
			else if (m_grid[r][c] >= 26)
				display_grid[r][c] = 'Z';
		}
	}

	clearScreen();
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
		{
			cout << display_grid[r][c];
		}
		cout << endl;
	}
	cout << endl;
}