#pragma once

#include "Point.h"

class KdNode {

public:

    Point* GetPoint();
    KdNode* GetLeftChild();
    KdNode* GetRightChild();
    void SetPoint(Point* point_);
    void SetLeftChild(KdNode* leftChild_);
    void SetRightChild(KdNode* leftChild_);
    KdNode(Point* p);
    ~KdNode();

private:
    Point* point;
    KdNode* Leftchild;
    KdNode* Rightchild;
    KdNode();
    
};