#include "Maze.h"
using namespace std;

Maze::Maze(int _dimensions):dimensions(_dimensions) {


	xStart = rand() % dimensions;
	yStart = rand() % dimensions;

	do { 
		xTarget = rand() % dimensions; 
		yTarget = rand() % dimensions;
	} while (xTarget == xStart && yTarget == yStart );


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
	Cell backTracker;

	auto visiting = vector<Cell>();


	do{
		while (nextPath(&xCurrent, &yCurrent) != 1) {
			tiles[yCurrent][xCurrent].position = Point_maze(xCurrent, yCurrent);
			visiting.push_back(tiles[yCurrent][xCurrent]);
		}
		backTracker = visiting.back();
		visiting.pop_back();

		
		xCurrent = backTracker.position.x;
		yCurrent = backTracker.position.y;
	} while (visiting.size());



}

vector<Cell>* Maze::solveBFS(vector<Cell>* visitedTiles)
{
	vector<Cell>* path = new vector<Cell>();
	queue<Cell> memory = queue<Cell>();

	Cell current = tiles[yStart][xStart];
	current.visited = true;
	memory.push(current);

	while (!memory.empty()) {
		current = memory.front();
		memory.pop();
		if (current.position.x == xStart && current.position.y == yStart) {
			return path;
		}
		vector<Cell>* adjacent_moves = moves(current.position.x, current.position.y);
		for (size_t i = 0; i < adjacent_moves->size(); i++)
		{
			if (!adjacent_moves->at(i).visited) {
				adjacent_moves->at(i).visited = true;
				adjacent_moves->at(i).parent = &current;

				memory.push(adjacent_moves->at(i));
			}
		}
	}
	return path;
}

vector<Point_maze>* Maze::solveAstar(vector<Point_maze>* visitedTiles)
{
	vector<Point_maze>* path = new vector<Point_maze>();


	return path;
}

void Maze::colorSearch(vector<Point_maze> *pathToTarget, vector<Point_maze> *visitedTiles)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "start  : (" << xStart << "," << yStart << ")" << endl;
	cout << "target : (" << xTarget << "," << yTarget << ")" << endl;

	for (int i = 0; i < dimensions; i += 1) {
		cout << "\t";
		for (int j = 0; j < dimensions; j += 1) {
			cout << "+" << (tiles[i][j].north ? " " : "-");
		}
		cout << "+" << endl;
		cout << "\t";
		for (int j = 0; j < dimensions; j += 1) {
			cout << (tiles[i][j].west ? " " : "|");
			if (i == yStart && j == xStart) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
			}
			else if (i == yTarget && j == xTarget) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
			}
			else if (contains(pathToTarget, tiles[i][j].position)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
			}
			else if (contains(visitedTiles, tiles[i][j].position)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			cout << " ";
			SetConsoleTextAttribute(hConsole, 15);
		}
		cout << "|" << endl;
	}
	cout << "\t";
	for (int j = 0; j < dimensions; j += 1) {
		cout << "+" << (tiles[dimensions - 1][j].south ? " " : "-");
	}
	cout << "+" << endl;

}


ostream& operator<<(ostream& os, const Maze* m)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	os << "start  : (" << m->xStart  << "," << m->yStart  << ")" << endl;
	os << "target : (" << m->xTarget << "," << m->yTarget << ")" << endl;
	
	for (int i = 0; i < m->dimensions; i +=1) {
		os << "\t";
		for (int j = 0; j < m->dimensions;  j +=1) {
			os << "+" << (m->tiles[i][j].north ? " " : "-");
		}
		os << "+" << endl;
		os << "\t";
		for (int j = 0; j < m->dimensions; j += 1) {
			os << (m->tiles[i][j].west ? " " : "|");
			if (i == m->yStart && j == m->xStart) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
			}
			else if(i == m->yTarget && j == m->xTarget) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
			}
			os << " ";
			SetConsoleTextAttribute(hConsole, 15);
		}
		os << "|" << endl;		
	}
	os << "\t";
	for (int j = 0; j < m->dimensions; j += 1) {
		os << "+" << (m->tiles[m->dimensions-1][j].south ? " " : "-");
	}
	os << "+" << endl;
	
	return os;
}


bool Maze::contains(vector<Point_maze> *v, Point_maze t)
{
	for (size_t i = 0; i < v->size(); i++)
	{
		if (v->at(i).x == t.x && v->at(i).y == t.y) {
			return true;
		}
	}
	return false;
}

int Maze::nextPath(int* x, int* y) {
	 tiles[*y][*x].built = true;
	vector<int> *neighbours = scan(*x, *y);

	if (!neighbours->size()) return 1; // all cases around have been visited, need to backtrack


	int chosenNeighbour = neighbours->at( rand() % neighbours->size() );
	delete neighbours;

	switch (chosenNeighbour)
	{
	case UP:
		tiles[*y][*x].north = true;
		*y -= 1;
		tiles[*y][*x].south = true;
		break;

	case DOWN:
		tiles[*y][*x].south = true; 
		*y += 1;
		tiles[*y][*x].north = true;
		break;

	case LEFT:
		tiles[*y][*x].west = true;
		*x -= 1;
		tiles[*y][*x].east = true;
		break;

	case RIGHT:
		tiles[*y][*x].east = true;
		*x += 1;
		tiles[*y][*x].west = true;
		break;

	default:
		return 1;
	}

	return 0;
}

 vector<int>* Maze::scan(int x, int y) {
	 vector<int>* neighbours = new vector<int>();	 

	 if (x > 0)
		 if (!tiles[y][x - 1].built)
			 neighbours->push_back(LEFT);

	 if (x < dimensions - 1) 
		 if (!tiles[y][x + 1].built)
			 neighbours->push_back(RIGHT);


	 if (y > 0)
		 if (!tiles[y - 1][x].built)
			 neighbours->push_back(UP);

	 if (y < dimensions - 1)
		 if (!tiles[y + 1][x].built)
			 neighbours->push_back(DOWN);

	 return neighbours;
 }

 vector<Cell>* Maze::moves(int x, int y)
 {
	 vector<Cell>* moves = new vector<Cell>();

	 if (tiles[y][x].west)
		 moves->push_back(tiles[y][x - 1]);

	 if (tiles[y][x].east)
		 moves->push_back(tiles[y][x + 1]);


	 if (tiles[y][x].north)
		 moves->push_back(tiles[y - 1][x]);

	 if (tiles[y][x].south)
		 moves->push_back(tiles[y + 1][x]);

	 return moves;
 }
