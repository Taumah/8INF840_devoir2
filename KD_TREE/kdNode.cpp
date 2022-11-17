#include "kdNode.h"

kdNode::kdNode() {
    point = nullptr;
    LeftChild = nullptr;
    RightChild = nullptr;
}

kdNode::~kdNode()
{
    delete point;
    delete LeftChild;
    delete RightChild;
}

Point kdNode::GetPoint() {
    return point;
}

Kdnode* kdNode::GetLeftChild(){
    return LeftChild;
}

kdNode* kdNode::GetRightChild(){
    return RightChild;
}

void kdNode::SetPoint(Point point_) {
    point = point_;
}

void kdNode::SetLeftChild(kdNode* leftChild_){
    LeftChild = leftChild_;
}

void kdNode::SetRightChild(kdNode* leftChild_){
    RightChild = RightChild_;
}