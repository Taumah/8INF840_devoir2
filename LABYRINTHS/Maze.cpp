#include "Maze.h"
#include <map>
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
	tiles[yCurrent][xCurrent].position = new Point_maze(xCurrent, yCurrent);
	Cell backTracker;

	auto visiting = vector<Cell>();


	do{
		while (nextPath(&xCurrent, &yCurrent) != 1) {
			tiles[yCurrent][xCurrent].position = new Point_maze(xCurrent, yCurrent);
			visiting.push_back(tiles[yCurrent][xCurrent]);
		}
		backTracker = visiting.back();
		visiting.pop_back();

		
		xCurrent = backTracker.position->x;
		yCurrent = backTracker.position->y;
	} while (visiting.size());

	cout << "build finished " << endl;


}

vector<Cell>* Maze::solveBFS()
{
	reset();
	vector<Cell>* path = new vector<Cell>();
	queue<Cell> memory = queue<Cell>();

	Cell current ;
	tiles[yStart][xStart].visited = true;

	path->push_back(tiles[yStart][xStart]);
	memory.push(tiles[yStart][xStart]);

	while (!memory.empty()) {
		current = memory.front();
		memory.pop();
		if (current.position->x == xTarget && current.position->y == yTarget) {
			return path;
		}
		vector<Cell*>* adjacent_moves = moves(current.position->x, current.position->y);
		for (size_t i = 0; i < adjacent_moves->size(); i++)
		{
			if (!adjacent_moves->at(i)->visited) {
				adjacent_moves->at(i)->visited = true;
				path->push_back(*adjacent_moves->at(i));
				adjacent_moves->at(i)->parent = &current;

				memory.push(*adjacent_moves->at(i));
			}
		}
	}
	return path;
}

vector<Cell>* Maze::solveAstar()
{
	reset();
	vector<Cell>* path = new vector<Cell>();
	vector<Cell> memory = vector<Cell>();

	tiles[yStart][xStart].distFromStart = 0;
	tiles[yStart][xStart].estDistToTarget = heuristic(tiles[yStart][xStart]);
	
	vector<Cell*>::iterator it;
	Cell current;

	path->push_back(tiles[yStart][xStart]);
	memory.push_back(tiles[yStart][xStart]);

	while (!memory.empty()) {
		size_t maxIndex = 0;
		current = memory.at(0);
		for (size_t i = 0; i < memory.size(); i++)
		{
			if (memory.at(i).distFromStart + memory.at(i).estDistToTarget < current.distFromStart + current.estDistToTarget) {
				current = memory.at(i);
				maxIndex = i;
				
			}
		}
		memory.erase(memory.begin() + maxIndex);


		if (current.distanceTo(tiles[yTarget][xTarget]) == 0) {
			return path;
		}

		vector<Cell*> *move = moves(current.position->x, current.position->y);
		for (size_t i = 0; i < move->size(); i++)
		{
			int minDist = current.distFromStart + 1; // moving always costs 1
			if (minDist < move->at(i)->distFromStart) {
				move->at(i)->parent = &current;
				move->at(i)->distFromStart = minDist;
				move->at(i)->estDistToTarget = heuristic(*move->at(i));
			}

			bool found = false;
			for (size_t j = 0; j < memory.size(); j++)
			{
				if (move->at(i)->distanceTo(memory.at(j)) == 0) {
					found = true;
					break;
				}
			}
			if (!found && !move->at(i)->visited) {
				path->push_back(*move->at(i));
				move->at(i)->visited = true;
				memory.push_back(*move->at(i));
			}
		}
		delete move;
	}
	return path;
}


void Maze::colorSearch(vector<Cell> *visitedTiles)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//vector<Cell> realPath = inferPath();


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
			else if (contains(visitedTiles, tiles[i][j].position)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN);
			}
			/*else if (contains(&realPath, tiles[i][j].position)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
			}*/
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


bool Maze::contains(vector<Cell> *v, Point_maze *t)
{
	for (size_t i = 0; i < v->size(); i++)
	{
		if (v->at(i).position->x == t->x && v->at(i).position->y == t->y) {
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

 vector<Cell*>* Maze::moves(int x, int y)
 {
	 vector<Cell*>* moves = new vector<Cell*>();

	 if (tiles[y][x].west)
		 moves->push_back(&tiles[y][x - 1]);

	 if (tiles[y][x].east)
		 moves->push_back(&tiles[y][x + 1]);


	 if (tiles[y][x].north)
		 moves->push_back(&tiles[y - 1][x]);

	 if (tiles[y][x].south)
		 moves->push_back(&tiles[y + 1][x]);

	 return moves;
 }

 void Maze::reset() {
	 for (size_t i = 0; i < dimensions; i++)
	 {
		 for (size_t j = 0; j < dimensions; j++) {
			 tiles[i][j].visited = false;
			 tiles[i][j].parent = nullptr;
			 tiles[i][j].distFromStart = dimensions * dimensions;
			 tiles[i][j].estDistToTarget = dimensions * dimensions;
		 }
	 }
 }


 int Maze::heuristic(Cell current) {
	 return current.distanceTo(tiles[yTarget][xTarget]);
 }

 vector<Cell> Maze::inferPath()
 {
	 vector<Cell> path = vector<Cell>();

	 Cell current = tiles[yTarget][xTarget];
	 do {
		 current = *current.parent;
		 path.push_back(current);
	 } while (current.parent);



	 std::reverse(path.begin(), path.end());
	 return path;
 }

