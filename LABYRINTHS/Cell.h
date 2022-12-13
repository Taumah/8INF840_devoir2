#pragma once
#include <ostream>
#include <ostream>
using namespace std;


class Cell {

public:
	bool north;
	bool south;
	bool east;
	bool west;

	bool visited;

	Cell();
	Cell(bool, bool, bool, bool);
	friend ostream& operator<<(ostream& os, const Cell* c);
};

