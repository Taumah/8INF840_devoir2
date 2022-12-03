#include "Maze.h"
using namespace std;

Maze::Maze(int _dimensions):dimensions(_dimensions) {

	int xStart = 0, yStart = 0;
}

ostream& operator<<(ostream& os, const Maze* m)
{
	for (int i = 0; i < m->dimensions; i +=1) {
		for (int j = 0; j < m->dimensions;  j +=1) {
			os << m->tiles[i][j].east << endl; // todo print maze
		}
	}

	return os;
}


vector<Cell> Maze::unvisitedNeighbours(int x, int y) {
	vector<Cell> neighbours = vector<Cell>();
	if (x < 0 || x >= dimensions || y < 0 || y >= dimensions) {
		return neighbours;
	}


	if (x > 0)
		if(!tiles[x - 1][y].visited)
			neighbours.push_back(tiles[x - 1][y]);
	
	if (x < dimensions - 1)
		if (!tiles[x + 1][y].visited)
			neighbours.push_back(tiles[x + 1][y]);
	

	if (y > 0 )
		if (!tiles[x][y - 1].visited)
			neighbours.push_back(tiles[x][y - 1]);

	if (y < dimensions - 1)
		if (!tiles[x][y + 1].visited)
			neighbours.push_back(tiles[x][y + 1]);

	return neighbours;
}
