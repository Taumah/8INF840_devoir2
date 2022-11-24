#pragma once

#include "kdTree.h"

int main() {
	 
	const int spaceDimension = 3;
	int all_coords[][spaceDimension] = {
		{0,1,2},
		{-2,3,2},
		{1,5,1},
		{-1,-1,-1},
		{2,-1,-1},
		{100,-100,10}
	};

	Point* p1 = new Point(all_coords[0], spaceDimension);
	Point* p2 = new Point(all_coords[1], spaceDimension);
	Point* p3 = new Point(all_coords[2], spaceDimension);
	Point* p4 = new Point(all_coords[3], spaceDimension);
	Point* p5 = new Point(all_coords[4], spaceDimension);

	
	KdTree* tree = new KdTree(3, p1);

	tree->addNode(new KdNode(p2));
	tree->addNode(new KdNode(p3));
	tree->addNode(new KdNode(p4));

	tree->parcoursInfixe();

	KdNode* n = tree->search(p4);
	KdNode* n2 = tree->search(p5);

	tree->removeNode(n);

	delete tree;

	return 0;
}