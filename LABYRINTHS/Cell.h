#pragma once
#include <ostream>


class Cell {

public:
	bool north;
	bool south;
	bool east;
	bool west;

	bool visited;

	Cell(bool, bool, bool, bool);

};

