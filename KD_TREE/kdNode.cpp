#include "kdNode.h"

KdNode::KdNode(Point* p){
    point = p;
    Leftchild = nullptr;
    Rightchild = nullptr;
    Parent = nullptr;
}

KdNode::~KdNode()
{
    if (Leftchild != nullptr) { delete Leftchild; }
    if (Rightchild != nullptr) { delete Rightchild; }

    delete point;
}

Point* KdNode::GetPoint() {
    return point;
}

KdNode* KdNode::GetLeftChild(){
    return Leftchild;
}

KdNode* KdNode::GetRightChild(){
    return Rightchild;
}

KdNode* KdNode::GetParent() {
    return Parent;
}

void KdNode::SetPoint(Point* point_) {
    point = point_;
}

void KdNode::SetLeftChild(KdNode* leftChild_){
    Leftchild = leftChild_;
}

void KdNode::SetRightChild(KdNode* RightChild_){
    Rightchild = RightChild_;
}

void KdNode::SetParent(KdNode* parent_) {
    Parent = parent_;
}