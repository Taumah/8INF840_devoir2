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
            n->SetParent(root_);
            return;
        }
    } 
    else if (n->GetPoint()->getCoord(i) < root_->GetPoint()->getCoord(i)) {
        if (root_->GetLeftChild() != nullptr) {
            addNode(n,i+1,root_->GetLeftChild());
        } 
        else { 
            root_->SetLeftChild(n);
            n->SetParent(root_);
            return;
        }
    }
}

void KdTree::removeNode(KdNode* n)
{
    if (!n) {
        return;
    }

    KdNode* toRemove = search(n->GetPoint());

    if (!toRemove) return;

    if (!toRemove->GetLeftChild() && !toRemove->GetRightChild()) { // leaf node
        
        if (toRemove->GetParent()->GetLeftChild() == toRemove) {
            toRemove->GetParent()->SetLeftChild(nullptr);
        }
        else {
            toRemove->GetParent()->SetRightChild(nullptr);
        }        
        delete toRemove; 
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
    if (tmp) {
        delete tmp;
    }
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
            current = current->GetRightChild();
        }

       

        depth += 1;
    }
    cout << p << " non trouve" << endl;
    return nullptr;
}

void KdTree::parcoursInfixe() {
    cout << "parcours" << endl;
    parcoursInfixe(root);
    cout << endl << endl;
}


void KdTree::parcoursInfixe(KdNode* start) {
    if (!start) return;

    cout << start->GetPoint() << endl;

    parcoursInfixe(start->GetLeftChild());
    parcoursInfixe(start->GetRightChild());
}

KdNode* KdTree::searchNearestNeighbor(Point* p, KdNode* _current, int i) {

    KdNode* currentBest = root;

    if ( p->getCoord(i) >= _current->GetPoint()->getCoord(i)) {
        if (_current->GetRightChild() != nullptr) {
            i = +1;
            if (i == p->coord->size()) { i = 0; }
            searchNearestNeighbor(p, _current->GetRightChild(), i);
        }
        else {
            cout << "Le noeud le plus proche de " << p << " est : " << _current->GetPoint() << endl;
            return _current;
        }
    }
    else if (p->getCoord(i) < _current->GetPoint()->getCoord(i)) {
        if (_current->GetLeftChild() != nullptr) {
            i = +1;
            if (i == p->coord->size()) { i = 0; }
            searchNearestNeighbor(p, _current->GetLeftChild(), i);
        }
        else {
            cout << "Le noeud le plus proche de " << p << " est : " << _current->GetPoint() << endl;
            return _current;
        }
    }
    return searchBestNode(_current, p, i, _current);

}

KdNode* KdTree::searchBestNode(KdNode* currentBest_, Point* p, int i, KdNode* BestNode) {

    if (currentBest_->GetParent() != nullptr) {
        int c_distance = UINT_MAX;
        int b_distance = UINT_MAX;
        for (int j = 0; j < currentBest_->GetParent()->GetPoint()->coord->size(); j++) {
            c_distance += (currentBest_->GetParent()->GetPoint()->getCoord(j) - p->getCoord(j)) * (currentBest_->GetParent()->GetPoint()->getCoord(j) - p->getCoord(j));
        }
        for (int j = 0; j < currentBest_->GetPoint()->coord->size(); j++) {
            b_distance += (currentBest_->GetPoint()->getCoord(j) - p->getCoord(j)) * (currentBest_->GetPoint()->getCoord(j) - p->getCoord(j));
        }
        if (c_distance < b_distance) {
            if (currentBest_->GetParent()->GetRightChild() != nullptr) {
                if (currentBest_->GetParent()->GetRightChild() == currentBest_) {
                    if (currentBest_->GetParent()->GetLeftChild() != nullptr) {
                        return searchNearestNeighbor(p, currentBest_->GetParent()->GetLeftChild(), i);
                    }
                    else {
                        i -= 1;
                        if (i == -1) { i = p->coord->size() - 1; }
                        return searchBestNode(currentBest_->GetParent(), p, i, currentBest_->GetParent());
                    }
                }
            }
            else if (currentBest_->GetParent()->GetLeftChild() != nullptr) {
                if (currentBest_->GetParent()->GetLeftChild() == currentBest_) {
                    if (currentBest_->GetParent()->GetRightChild() != nullptr) {
                        return searchNearestNeighbor(p, currentBest_->GetParent()->GetRightChild(), i);
                    }
                    else {
                        i -= 1;
                        if (i == -1) { i = p->coord->size() - 1; }
                        return searchBestNode(currentBest_->GetParent(), p, i, currentBest_->GetParent());
                    }
                }
            }
            else {
                i -= 1;
                if (i == -1) { i = p->coord->size() - 1; }
                return searchBestNode(currentBest_->GetParent(), p, i, currentBest_->GetParent());
            }
        }
        else {
            i -= 1;
            if (i == -1) { i = p->coord->size() - 1; }
            return searchBestNode(currentBest_->GetParent(), p, i, BestNode);
        }
    }
    else {
        cout << "Le noeud le plus proche de " << p << " est : " << BestNode->GetPoint() << endl;
        return BestNode;
    }
}