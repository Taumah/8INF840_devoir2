#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "commons.h"

using namespace std;
int Indegreedemo();

// Classe pour repr�senter un hypergraphe
class Hypergraph {
public:
    // Constructeur
    Hypergraph() {}

    // Ajouter un sommet au graphe
    void addVertex(int vertex) {
        vertices.push_back(vertex);
    }

    // Ajouter une hyperedge au graphe
    void addEdge(vector<int> edge) {
        edges.push_back(edge);
    }

    // Calculer l'indegree d'un sommet donn�
    int indegree(int vertex) {
        int count = 0;
        for (auto edge : edges) {
            for (auto v : edge) {
                if (v == vertex) {
                    count++;
                    break;
                }
            }
        }
        return count;
    }

private:
    vector<int> vertices; // Liste des sommets du graphe
    vector<vector<int>> edges; // Liste des hyperedges du graphe
};


int Indegreedemo() {
    // Ouvrir le fichier nodes en lecture
    ifstream nodesFile("in-2004.nodes.txt");

    // V�rifier si le fichier a �t� ouvert correctement
    if (!nodesFile) {
        cerr << "Failed to open nodes file" << endl;
        return 1;
    }

    // Lire les donn�es du fichier ligne par ligne
    string line;
    vector<int> nodes;
    while (getline(nodesFile, line)) {
        int node = stoi(line);
        nodes.push_back(node);
    }

    // Fermer le fichier
    nodesFile.close();

    // Ouvrir le fichier edges en lecture
    ifstream edgesFile("in-2004.edges.txt");

    // V�rifier si le fichier a �t� ouvert correctement
    if (!edgesFile) {
        cerr << "Failed to open edges file" << endl;
        return 1;
    }

    // Lire les donn�es du fichier ligne par ligne
    vector<vector<int>> edges;
    while (getline(edgesFile, line)) {
        // S�parer la ligne en plusieurs �l�ments en utilisant un espace comme s�parateur
        vector<string> elements = split(line, " ");

        // Convertir chaque �l�ment en un entier et ajouter � un vecteur d'entiers
        vector<int> edge;
        for (auto element : elements) {
            int vertex = stoi(element);
            edge.push_back(vertex);
        }

        // Ajouter le vecteur d'entiers � la liste des hyperedges
        edges.push_back(edge);
    }

    // Fermer le fichier
    edgesFile.close();

    // Cr�er un hypergraphe
    Hypergraph h;

    // Ajouter les sommets au graphe
    for (auto node : nodes) {
        h.addVertex(node);
    }

    // Ajouter les hyperedges au graphe
    for (auto edge : edges) {
        h.addEdge(edge);
    }

    // Calculer l'indegree de chaque sommet
    for (auto node : nodes) {
        cout << "Indegree of vertex " << node << ": " << h.indegree(node) << endl;
    }

    return 0;
}