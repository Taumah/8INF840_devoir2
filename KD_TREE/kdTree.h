#pragma once

#include "kdNode.h"
#include <iostream>

void kdTreeDemo();

class KdTree {

private:
	int k;  // n° dimensions
	void parcoursInfixe(KdNode* start);


public:
	KdNode *root;

	KdTree(int);
	KdTree(int, Point *root);
	~KdTree();

	KdNode* nearestNeighbor(Point p);
	void addNode(KdNode* n, int i, KdNode* root_);
	void addNode(KdNode* n);
	void removeNode(KdNode* n);

	KdNode* search(Point *p);
	KdNode* searchNearestNeighbor(Point* p, KdNode* _current, int i);
	KdNode* searchBestNode(KdNode* currentBest_, Point* p, int i, KdNode* BestNode);

	void parcoursInfixe();

};