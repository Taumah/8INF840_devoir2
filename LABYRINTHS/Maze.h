#pragma once
#include "Cell.h"
#include <ostream>
#include <vector>
using namespace std;

class Maze
{
public:
	int dimensions; // maze is square (dim * dim)

	Cell** tiles; 

	Maze(int);
	vector<Cell> unvisitedNeighbours(int x, int y);
	friend ostream& operator<<(ostream& os, const Maze* c);

};

