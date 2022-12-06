#include "Maze.h"
using namespace std;

Maze::Maze(int _dimensions):dimensions(_dimensions) {


	xStart = rand() % dimensions;
	yStart = rand() % dimensions;

	tiles = new Cell*[dimensions];
	for (size_t i = 0; i < dimensions; i++)
	{
		tiles[i] = new Cell[dimensions];
	}
}

void Maze::build()
{
	int xCurrent = xStart;
	int yCurrent = yStart;
	tuple<int, int> backTracker;

	auto visiting = vector<tuple<int, int>>();


	do{
		while (nextPath(&xCurrent, &yCurrent) != 1) {
			visiting.push_back(make_tuple(xCurrent, yCurrent));
		}
		backTracker = visiting.back();
		visiting.pop_back();

		
		xCurrent = get<0>(backTracker);
		yCurrent = get<1>(backTracker);
	} while (visiting.size());



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


 int Maze::nextPath(int* x, int* y) {
	 tiles[*x][*y].visited = true;
	vector<int> *neighbours = scan(*x, *y);

	if (!neighbours->size()) return 1;


	int chosenNeighbour = neighbours->at( rand() % neighbours->size() );
	delete neighbours;

	switch (chosenNeighbour)
	{
	case UP:
		tiles[*x][*y].north = true;
		*y -= 1;
		tiles[*x][*y].south = true;
		break;

	case DOWN:
		tiles[*x][*y].south = true; 
		*y += 1;
		tiles[*x][*y].north = true;
		break;

	case LEFT:
		tiles[*x][*y].east = true;
		*x -= 1;
		tiles[*x][*y].west = true;
		break;

	case RIGHT:
		tiles[*x][*y].west = true;
		*x += 1;
		tiles[*x][*y].east = true;
		break;

	default:
		return 1;
	}

	return 0;
}

 vector<int>* Maze::scan(int x, int y) {
	 vector<int>* neighbours = new vector<int>();

	 if (x < 0 || x >= dimensions || y < 0 || y >= dimensions) {
		 return neighbours;
	 }
	 

	 if (x > 0)
		 if (!tiles[x - 1][y].visited)
			 neighbours->push_back(LEFT);

	 if (x < dimensions - 1) 
		 if (!tiles[x + 1][y].visited)
			 neighbours->push_back(RIGHT);


	 if (y > 0)
		 if (!tiles[x][y - 1].visited)
			 neighbours->push_back(UP);

	 if (y < dimensions - 1)
		 if (!tiles[x][y + 1].visited)
			 neighbours->push_back(DOWN);

	 return neighbours;
 }
