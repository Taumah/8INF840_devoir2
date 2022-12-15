#pragma once

#include "Point.h"

class KdNode {

public:

    Point* GetPoint();
    KdNode* GetLeftChild();
    KdNode* GetRightChild();
    KdNode* GetParent();
    void SetPoint(Point* point_);
    void SetLeftChild(KdNode* leftChild_);
    void SetRightChild(KdNode* leftChild_);
    void SetParent(KdNode* parent_);
    KdNode(Point* p);
    ~KdNode();

private:
    Point* point;
    KdNode* Parent;
    KdNode* Leftchild;
    KdNode* Rightchild;
    KdNode();
    
};