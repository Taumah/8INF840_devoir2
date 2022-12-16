#pragma once

#include "kdTree.h"

void kdTreeDemo() {
	 
	const int spaceDimension = 3;
	int all_coords[][spaceDimension] = {
		{5,-5,5},
		{-2,3,2},
		{1,5,1},
		{-1,-1,-1},
		{2,-1,-1},
		{100,-100,10},
		{-2,5,1},
		{10,10,10}
	};

	Point* p1 = new Point(all_coords[0], spaceDimension);
	Point* p2 = new Point(all_coords[1], spaceDimension);
	Point* p3 = new Point(all_coords[2], spaceDimension);
	Point* p4 = new Point(all_coords[3], spaceDimension);
	Point* p5 = new Point(all_coords[4], spaceDimension);
	Point* p6 = new Point(all_coords[5], spaceDimension);
	Point* p7 = new Point(all_coords[7], spaceDimension);
	
	KdTree* tree = new KdTree(3, p1);

	tree->addNode(new KdNode(p2));
	tree->addNode(new KdNode(p3));
	tree->addNode(new KdNode(p4));
	tree->addNode(new KdNode(p7));

	tree->parcoursInfixe();

	KdNode* n = tree->search(p7);
	KdNode* n2 = tree->search(p5);
	cout << endl << endl;


	cout << "suppression de " << p7 << endl;
	tree->removeNode(n);
	cout << endl << endl;

	cout << "suppression de " << p6 << endl;
	n = new KdNode(p6);
	tree->removeNode(n);
	cout << endl << endl;

	tree->parcoursInfixe();

	tree->searchNearestNeighbor(p6, tree->root, 0);
	delete tree;
}