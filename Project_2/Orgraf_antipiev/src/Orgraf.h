//
// Created by ilya on 11.05.19.
//
#include "vector"
using namespace std;

#ifndef PROJECT_2_ORGRAF_H
#define PROJECT_2_ORGRAF_H

#endif //PROJECT_2_ORGRAF_H

struct Edge;

class GraphNode{
public:
    static int ID_count;

    GraphNode();
    int id;
    void addNeighbour(GraphNode node, int weight = 0);
    void addNeighbour(Edge *edge);
    void deleteNeighbour(Edge edge);
    int neighboursCount();
    vector<GraphNode*> getNeighbours();
    vector<Edge*> getEdges();

private:
    vector<Edge*> neighbours;
};

class Graph{
public:
    virtual void addNode(GraphNode* node) = 0;
    virtual void deleteNode(int id) = 0;
    virtual void addEdge(int id1, int id2, int weight) = 0;

protected:
    std::vector<GraphNode> nodes;
};

class Orgraf:Graph{
public:
    Orgraf();

    GraphNode* getNode(int id);
    vector<GraphNode*> getNodes();
    void addNode(GraphNode* node);
    void deleteNode(int id);

    void addEdge(int id1, int id2, int weight = 0);
    Edge* getEdge(int id1, int id2);

    int getWeight(int id1, int id2);
    int totalWeight();

    bool exists(int id); // exists node
    bool existsEdge(int id1, int id2);

    void showMatrix();
    void showEdges();

protected:
    vector<GraphNode*> nodes;
    vector<Edge*> edges;
};

struct Edge{
    int weight;
    int id;
    GraphNode *node1, *node2; // the edge connects to edges
};

Orgraf asMatrix();
Orgraf edgeByEdge();
Orgraf fromFile(string path);
Orgraf minSpanningTree(Orgraf* og);