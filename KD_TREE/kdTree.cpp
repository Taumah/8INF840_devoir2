#include "kdTree.h"
#include "kdNode.h"

using namespace std;

KdTree::KdTree(int k)
{
	Point first = Point(k);
	KdTree(k, first);
}

KdTree::KdTree(int k, Point p): k(k)
{
	//root = new KdNode(p); // à implémenter
   
}

KdNode KdTree::nearestNeighbor(Point p){

}

void KdTree::addNode(KdNode* n, int i, KdNode* root_){
     if (n->GetPoint().getCoord(0) == NULL) {
        cout << "node vide, impossible de l'ajouter"<< endl;
        return;
    }
    if (n->GetPoint().getCoord(i) >= root_->GetPoint().getCoord(i)) {
        if (root_->GetRightChild() != nullptr) {
        addNode(n,i+1,root_->GetRightChild());
                root_->SetRightChild(n);
            return;
        }
    } else if (n->GetPoint().getCoord(i) < root_->GetPoint().getCoord(i)) {
        if (root_->GetLeftChild() != nullptr) {
        addNode(n,i+1,root_->GetLeftChild());
        } else { 
                root_->SetLeftChild(n);
            return;
        }
    }
}

KdNode* KdTree::search(Point p){
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