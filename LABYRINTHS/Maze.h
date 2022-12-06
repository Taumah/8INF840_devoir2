#pragma once
#include "Cell.h"
#include <ostream>
#include <iostream>
#include <vector>
#include <tuple>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;
using std::get;

class Maze
{
public:
	int dimensions; // maze is square (dim * dim)

	Maze(int);
	void build();
	friend ostream& operator<<(ostream& os, const Maze* c);

private:
	int xStart;
	int yStart;
	Cell** tiles;

	vector<int>* scan(int, int);
	int nextPath(int* x, int* y);
	
};

