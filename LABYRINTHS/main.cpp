#include "main.h"

void growingTree() {
	srand(time(NULL));


	Maze *maze = new Maze(10);
	maze->build();

	cout << maze << endl;
}