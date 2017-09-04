/* Your code here! */
/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "png.h"
class SquareMaze
{
public:
	SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	std::vector<int> solveMaze();
	PNG* drawMaze() const;
	PNG* drawMazeWithSolution();

};

#endif