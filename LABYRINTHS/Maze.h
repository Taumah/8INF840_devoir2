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
	
	vector<tuple<int,int>>* solve(vector<tuple<int, int>>* visitedTiles); // returns path found using BFS, and fills visitedTiles with all searched tiles
	void colorSearch(vector<tuple<int, int>>* pathToTarget, vector<tuple<int, int>>* visitedTiles);

	friend ostream& operator<<(ostream& os, const Maze* c);

private:
	int xStart;
	int yStart;


	int xTarget;
	int yTarget;
	Cell** tiles;

	vector<int>* scan(int, int);
	vector<int>* moves(int, int);

	bool contains(vector<tuple<int, int>>*, tuple<int, int>);
	int nextPath(int* x, int* y);
	
};

