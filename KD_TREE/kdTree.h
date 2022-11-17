#pragma once

#include "kdNode.h"
#include <iostream>

class KdTree {

private:
	int k;  // n° dimensions


public:
	KdNode *root;

	KdTree(int);
	KdTree(int, Point root);
	~KdTree();

	KdNode nearestNeighbor(Point p);
	addNode(KdNode n);
	removeNode(KdNode n);

	KdNode search(Point p);

};