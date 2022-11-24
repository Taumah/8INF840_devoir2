#include "kdTree.h"
#include "kdNode.h"

using namespace std;

KdTree::KdTree(int k_)
{
    k = k_;
	Point* first = new Point(k_);
    root = new KdNode(first);
}

KdTree::KdTree(int k_, Point* p)
{
    k = k_;
	root = new KdNode(p); // à implémenter
    
}

KdTree::~KdTree()
{
    delete root;

}

KdNode* KdTree::nearestNeighbor(Point p){
    return nullptr;
}

void KdTree::addNode(KdNode* n) {
    addNode(n, 0, root);
}
void KdTree::addNode(KdNode* n, int i, KdNode* root_){
     if (n == nullptr || n->GetPoint() == nullptr) {
        cout << "node vide, impossible de l'ajouter"<< endl;
        return;
    }
    if (n->GetPoint()->getCoord(i) >= root_->GetPoint()->getCoord(i)) {
        if (root_->GetRightChild() != nullptr) {
            addNode(n, i + 1, root_->GetRightChild());
        } 
        else{
            root_->SetRightChild(n);
            return;
        }
    } 
    else if (n->GetPoint()->getCoord(i) < root_->GetPoint()->getCoord(i)) {
        if (root_->GetLeftChild() != nullptr) {
            addNode(n,i+1,root_->GetLeftChild());
        } 
        else { 
            root_->SetLeftChild(n);
            return;
        }
    }
}

void KdTree::removeNode(KdNode* n)
{
    KdNode* toRemove = search(n->GetPoint());

    if (!toRemove) return;

    if (!toRemove->GetLeftChild() && !toRemove->GetRightChild()) { // leaf node
        KdNode* tmp = toRemove;
        toRemove = nullptr;
        delete tmp; 
        return;
    }
    
    
    KdNode* tmp = toRemove;
    if (!toRemove->GetLeftChild()) {
        toRemove = toRemove->GetRightChild(); // overwrite node to remove (deleted later)
    }
    else if (!toRemove->GetRightChild()) {
        toRemove = toRemove->GetLeftChild();  // overwrite node to remove (deleted later)
    }
    else {
        toRemove = toRemove->GetLeftChild(); 
        addNode(toRemove->GetRightChild()); // put it back in place
    }
    delete tmp; 
}

KdNode* KdTree::search(Point* p){
    KdNode* current = root;

    int depth = 0;
    while (current != nullptr) {

        if (current->GetPoint()->isEqualTo(p)) {
            cout << p << " trouve" << endl;
            return current;
        }

        int coordToCompare = depth % k;

        if (p->getCoord(coordToCompare) <= current->GetPoint()->getCoord(coordToCompare)) {
            current = current->GetLeftChild();
        }
        else {
            current = current->GetLeftChild();
        }

       

        depth += 1;
    }
    cout << p << " non trouve" << endl;
    return nullptr;
}

void KdTree::parcoursInfixe() {
    cout << "parcours" << endl;
    parcoursInfixe(root);
}


void KdTree::parcoursInfixe(KdNode* start) {
    if (!start) return;

    cout << start->GetPoint() << endl;

    parcoursInfixe(start->GetLeftChild());
    parcoursInfixe(start->GetRightChild());
}