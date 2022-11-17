#include "kdNode.h"

KdNode::KdNode() {
    // point = Point(0);
    Leftchild = nullptr;
    Rightchild = nullptr;
}

KdNode::~KdNode()
{
    delete Leftchild;
    delete Rightchild;
}

Point KdNode::GetPoint() {
    return point;
}

KdNode* KdNode::GetLeftChild(){
    return Leftchild;
}

KdNode* KdNode::GetRightChild(){
    return Rightchild;
}

void KdNode::SetPoint(Point point_) {
    point = point_;
}

void KdNode::SetLeftChild(KdNode* leftChild_){
    Leftchild = leftChild_;
}

void KdNode::SetRightChild(KdNode* RightChild_){
    Rightchild = RightChild_;
}