#include "kdTree.h"
#include "kdNode.h"

KdTree::KdTree(int k)
{
	Point* first = new Point(k);
	KdTree(k, first);
}

KdTree::KdTree(int k, Point p): k(k)
{
	root = new KdNode(p);
   
}

KdNode KdTree::nearestNeighbor(Point p){

}

void KdNode::addNode(KdNode* n, int i, KdNode* root_){
     if (n->GetPoint()!) {
        cout << "node vide, impossible de l'ajouter"<< endl;
        return;
    }
    if (n->GetPoint().coord[i] >= root_->point.coord[i]) {
        if (root_->RightChild =! nullptr) {
        addNode(n,i+1,root_->RightChild);
                root_->SetRightChild(n);
            return;
        }
    } else if (n->point.coord[i] < root_->point.coord[i]) {
        if (root_->LeftChild =! nullptr) {
        addNode(n,i+1,root_->LeftChild);
        } else { 
                root_->SetLeftChild(n);
            return;
        }
    }
}

KdNode KdTree::search(Point p){
    KdNode* current = root;

    int depth = 0;
    while (current != nullptr) {

        if (current->GetPoint().isEqualTo(p)) {
            return current;
        }

        int coordToCompare = depth % k;

        if (p.getCoord(coordToCompare) <= current->GetPoint().getCoord(coordToCompare)) {
            current = current->GetLeftChild();
        }
        else {
            current = current->GetLeftChild();
        }

       

        depth += 1;
    }

    return nullptr;
}