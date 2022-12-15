#include "exo3.h"

void growingTree() {
	srand(time(NULL));


	Maze *maze = new Maze(10);
	maze->build();

	cout << maze << endl;

	//maze->colorSearch(maze->solve(nullptr), nullptr);
	maze->solveBFS(nullptr);

}