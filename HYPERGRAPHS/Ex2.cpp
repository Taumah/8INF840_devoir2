#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <string>
#include "commons.h"

using namespace std;
int Ex2Demo();

// Classe pour représenter un hypergraphe
class Hypergraph2 {
public:
    // Constructeur
    Hypergraph2() {
        inDegree = unordered_map<int, int>();
        outDegree = unordered_map<int, int>();
    }

    // ...



    // Ajouter un sommet au graphe
    void addVertex(int vertex) {
        vertices.push_back(vertex);
        inDegree[vertex] = 0;
        outDegree[vertex] = 0;
    }

    // Ajouter une hyperedge au graphe
    void addEdge(vector<int> edge) {
        edges.push_back(edge);
        for (auto v : edge) {
            inDegree[v]++;
        }
        outDegree[edge[0]]++;
    }

    double pageRank(int vertex, double d, int iterations) {
        unordered_map<int, double> scores;
        for (auto v : vertices) {
            scores[v] = 1.0 / vertices.size();
        }

        for (int i = 0; i < iterations; i++) {
            unordered_map<int, double> newScores;
            for (auto v : vertices) {
                newScores[v] = (1 - d) / vertices.size();
            }

            for (auto edge : edges) {
                int u = edge[0];
                double weight = 1.0 / outDegree[u];
                for (auto v : edge) {
                    newScores[v] += d * weight * scores[u];
                }
            }

            scores = newScores;
        }

        return scores[vertex];
    }

private:
    unordered_map<int, int> inDegree; // Le nombre d'entrées pour chaque sommet
    unordered_map<int, int> outDegree; // Le nombre de sorties pour chaque sommet
    vector<int> vertices; // Liste des sommets du graphe
    vector<vector<int>> edges; // Liste des hyperedges du graphe
};



int Ex2Demo() {
    // Ouvrir le fichier nodes en lecture
    ifstream nodesFile("in-2004.nodes.txt");

    // Vérifier si le fichier a été ouvert correctement
    if (!nodesFile) {
        cerr << "Failed to open nodes file" << endl;
        return 1;
    }

    // Lire les données du fichier ligne par ligne
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

    // Vérifier si le fichier a été ouvert correctement
    if (!edgesFile) {
        cerr << "Failed to open edges file" << endl;
        return 1;
    }

    // Lire les données du fichier ligne par ligne
    vector<vector<int>> edges;
    while (getline(edgesFile, line)) {
        // Séparer la ligne en plusieurs éléments en utilisant un espace comme séparateur
        vector<string> elements = split(line, " ");


        // Convertir chaque élément en un entier et ajouter à un vecteur d'entiers
        vector<int> edge;
        for (auto element : elements) {
            int vertex = stoi(element);
            edge.push_back(vertex);
        }

        // Ajouter le vecteur d'entiers à la liste des hyperedges
        edges.push_back(edge);
    }

    // Fermer le fichier
    edgesFile.close();

    // Créer un hypergraphe
    Hypergraph2 h;

    // Ajouter les sommets au graphe
    for (auto node : nodes) {
        h.addVertex(node);
    }

    // Ajouter les hyperedges au graphe
    for (auto edge : edges) {
        h.addEdge(edge);
    }

    // Calculer le PageRank de chaque sommet
    for (auto node : nodes) {
        cout << "PageRank of vertex " << node << ": " << h.pageRank(node, 0.85, 100) << endl;
    }

    return 0;
}