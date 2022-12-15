#pragma once
#include <ostream>
using namespace std;

class Point_maze {
public:
	int x;
	int y;
	Point_maze(int _x, int _y) :x(_x), y(_y) {};
	Point_maze() :x(0), y(0) {};
};

class Cell {
	

public:
	bool north;
	bool south;
	bool east;
	bool west;

	Point_maze position;

	bool built;
	bool visited;
	Cell *parent;

	Cell();
	Cell(bool, bool, bool, bool);
	friend ostream& operator<<(ostream& os, const Cell* c);
};

