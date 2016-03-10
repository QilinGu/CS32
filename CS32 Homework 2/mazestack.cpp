#include <stack>
#include <iostream>
#include <string>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;
	coordStack.push(Coord(sr, sc));
	
	if (sr == er && sc == ec)
		return true;

	while (!coordStack.empty())
	{
		Coord P = coordStack.top();
		//cerr << P.r() << ", " << P.c() << endl;
		coordStack.pop();
		
		if (maze[P.r() - 1][P.c()] == '.') //North
		{
			coordStack.push(Coord(P.r() - 1, P.c()));
			maze[P.r()][P.c()] = 'X';
			if (P.r() - 1 == er && P.c() == ec)
				return true;
		}
		if (maze[P.r()][P.c() + 1] == '.') //East
		{
			coordStack.push(Coord(P.r(), P.c() + 1));
			maze[P.r()][P.c()] = 'X';
			if (P.r() == er && P.c() + 1 == ec)
				return true;
		}
		if (maze[P.r() + 1][P.c()] == '.') //South
		{
			coordStack.push(Coord(P.r() + 1, P.c()));
			maze[P.r()][P.c()] = 'X';
			if (P.r() + 1 == er && P.c() == ec)
				return true;
		}
		if (maze[P.r()][P.c() - 1] == '.') //West
		{
			coordStack.push(Coord(P.r(), P.c() - 1));
			maze[P.r()][P.c()] = 'X';
			if (P.r() == er && P.c() - 1 == ec)
				return true;
		}
	}
	return false;
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X........X",
		"XX.X.XXXXX",
		"X..X.X...X",
		"X..X...X.X",
		"XXXX.XXX.X",
		"X.X....XXX",
		"X..XX.XX.X",
		"X...X....X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 6, 4, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}