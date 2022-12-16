#pragma once
#include "Cell.h"
#include <ostream>
#include <iostream>
#include <vector>
#include <queue>

#include <tuple>

#include <windows.h>

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
	
	vector<Cell>* solveBFS();
	vector<Cell>* solveAstar();
	void colorSearch(vector<Cell>* visitedTiles);

	friend ostream& operator<<(ostream& os, const Maze* c);

private:
	int xStart;
	int yStart;


	int xTarget;
	int yTarget;
	Cell** tiles;

	vector<int>* scan(int, int);
	vector<Cell*>* moves(int, int);

	void reset();

	bool contains(vector<Cell>*, Point_maze*);
	int nextPath(int* x, int* y);
	int heuristic(Cell c);
	vector<Cell> inferPath();
};

