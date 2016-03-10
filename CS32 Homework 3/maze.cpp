bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec)
		return true;

	maze[sr][sc] = 'o';

	if (maze[sr - 1][sc] == '.') //North
		if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec) == true) return true;
	if (maze[sr][sc + 1] == '.') //East
		if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec) == true) return true;
	if (maze[sr + 1][sc] == '.') //South
		if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec) == true) return true;
	if (maze[sr][sc - 1] == '.') //West
		if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec) == true) return true;
	
	return false;
}
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


/*int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X........X",
		"XX.X.XXXXX",
		"X..X.X...X",
		"X..X...X.X",
		"XXXX.XXX.X",
		"X.X....XXX",
		"X..XX.X..X",
		"X...X....X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 8, 8, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;

	for (int i = 0; i < 10; i++)
		cout << maze[i] << endl;
}*/