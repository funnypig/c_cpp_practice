//
// Created by ilya on 11.05.19.
//

#include <iostream>
#include "Orgraf.h"
#include "vector"
#include <fstream>
#include <string>

using namespace std;

// GraphNode implementation

int GraphNode::ID_count = 0;

GraphNode::GraphNode() {
    id = ID_count;
    ID_count++;
}

void GraphNode::addNeighbour(GraphNode node, int weight) {
    Edge *edge = new Edge;
    edge->node1 = this;
    edge->node2 = &node;
    edge->weight = weight;
    this->neighbours.push_back(edge);
}

void GraphNode::addNeighbour(Edge *edge) {
    this->neighbours.push_back(edge);
}

void GraphNode::deleteNeighbour(Edge edge) {
    for (auto itr = this->neighbours.begin(); itr!=this->neighbours.end(); itr++){
        if ((*itr)->node2->id == edge.node2->id){
            this->neighbours.erase(itr);
            return;
        }
    }
}

int GraphNode::neighboursCount() {
    return this->neighbours.size();
}

vector<GraphNode*> GraphNode::getNeighbours() {
    vector<GraphNode*> neighbours;
    for (auto itr = this->neighbours.begin(); itr!=this->neighbours.end(); itr++){
        neighbours.push_back((*itr)->node2);
    }
    return neighbours;
}

vector<Edge*> GraphNode::getEdges() {
    vector<Edge*> edges;
    for (auto itr = this->neighbours.begin(); itr!=this->neighbours.end(); itr++){
        edges.push_back(*itr);
    }
    return edges;
}

// Orgraf implementations

Orgraf::Orgraf() {
}

void Orgraf::addNode(GraphNode *node) {
    this->nodes.push_back(node);
}

GraphNode* Orgraf::getNode(int id) {
    for (auto itr = this->nodes.begin(); itr!=this->nodes.end(); itr++){

        if ((*itr)->id == id){
            return *itr;
        }
    }

    throw "No such node (getNode)";
}


void Orgraf::addEdge(int id1, int id2, int weight) {
    /*
     * in usual graph it would be two edges with IDs (id1, id2) and (id2, id1)
     * i use here just one 'tuple' as a direction
     */

    GraphNode *n1 = getNode(id1);
    GraphNode *n2 = getNode(id2);

    Edge *e = new Edge;
    e->node1 = n1;
    e->node2 = n2;
    e->weight = weight;

    n1->addNeighbour(e);
    this->edges.push_back(e);
}

Edge* Orgraf::getEdge(int id1, int id2) {
    for (auto itr = this->edges.begin(); itr!=this->edges.end(); itr++){

        if ((*itr)->node1->id == (*itr)->node2->id)
            return *itr;
    }

    throw "No such edge (getEdge)";
}

int Orgraf::getWeight(int id1, int id2) {
    for (auto itr = this->edges.begin(); itr!=this->edges.end(); itr++){
        if ((*itr)->node1->id == id1 && (*itr)->node2->id == id2)
            return (*itr)->weight;
    }

    throw "No such edge (getWeight)";
}

void Orgraf::deleteNode(int id) {
    for (auto itr = this->nodes.begin(); itr!=this->nodes.end(); itr++){
        if ((*itr)->id == id){
            this->nodes.erase(itr); //  TODO: remove connected edges
        }
    }
}

bool Orgraf::exists(int id) {
    for (auto itr = this->nodes.begin(); itr!=this->nodes.end(); itr++){
        if ((*itr)->id == id)
            return true;
    }
    return false;
}

bool Orgraf::existsEdge(int id1, int id2) {
    for (auto itr = this->edges.begin(); itr!=this->edges.end(); itr++){
        if ((*itr)->node1->id == id1 && (*itr)->node2->id == id2)
            return true;
    }
    return false;
}

void Orgraf::showMatrix() {
    vector<int> ids;

    for (auto itr = this->nodes.begin(); itr!=this->nodes.end(); itr++){
        ids.push_back((*itr)->id);
    }

    int n = ids.size();

    cout<<endl;
    cout<<"\t";
    for (int i = 0; i<n; i++){
        cout<<i<<"\t";
    }
    cout<<endl;

    for (int i = 0; i<n; i++){
        cout<<i<<"\t";
        int id1 = ids.at(i);

        for (int j = 0; j<n; j++){
            int id2 = ids.at(j);

            if (existsEdge(id1, id2)){
                cout<<getWeight(id1, id2)<<"\t";
            }else{
                cout<<"0\t";
            }
        }

        cout<<endl;
    }
}

void Orgraf::showEdges() {
    cout<<"id1\t\tid2\t\tweight\n";
    for (auto itr = this->edges.begin(); itr!=this->edges.end(); itr++){
        cout<<(*itr)->node1->id<<"\t\t"<<(*itr)->node2->id<<"\t\t"<<(*itr)->weight<<endl;
    }
}

vector<GraphNode*> Orgraf::getNodes() {
    return nodes;
}

int Orgraf::totalWeight() {
    int total = 0;
    for (auto itr = this->edges.begin(); itr!=this->edges.end(); itr++){
        total += (*itr)->weight;
    }
    return total;
}

// Input functions

Orgraf asMatrix(){
    Orgraf og;

    int n;
    cout<<"Input number of Nodes: ";
    cin>>n;

    for (int i = 0; i<n; i++){
        GraphNode *node = new GraphNode;
        og.addNode(node);
    }

    cout<<"Input adjacency matrix line by line"<<endl;
    cout<<"(0 if i-th and j-th are not connected, else weight between them)"<<endl;

    for (int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            int w;
            cin>>w;
            og.addEdge(i, j, w);
        }
    }

    return og;
}

Orgraf edgeByEdge(){
    Orgraf og;

    cout<<"Input data in each line as:\nid1 id2 weight\n use '-1 -1 -1' to finish input\n";

    while (true){
        int id1, id2, w;
        cin>>id1>>id2>>w;

        if (id1 == -1 || id2 == -1) break;

        if (!og.exists(id1)){
            GraphNode *node = new GraphNode;
            node->id = id1;
            og.addNode(node);
        }

        if (!og.exists(id2)){
            GraphNode *node = new GraphNode;
            node->id = id2;
            og.addNode(node);
        }

        if (w > 0){
            og.addEdge(id1, id2, w);
        }
    }

    return og;
}

Orgraf fromFile(string path){
    Orgraf graph;

    ifstream filereader(path);

    if(!filereader.is_open()){
        throw "Can't open file "+path;
    }

    string type;
    getline(filereader, type, '\n');


    if (type == "matrix"){

        try {

            int n;
            filereader >> n;

            for (int i = 0; i < n; i++) {
                GraphNode *node = new GraphNode;
                node->id = i;
                graph.addNode(node);
            }

            for (int i = 0; i < n; i++) {
                int id1 = i;

                for (int j = 0; j < n; j++) {
                    int id2 = j;
                    int w;
                    filereader>>w;

                    if(w>0)
                        graph.addEdge(id1, id2, w);
                }
            }
        }catch(exception) {
            cout<<"Something wrong with your file!";
        }

    }else if(type == "edges"){
        try{

            while (true){

                int id1, id2, w;

                if (!filereader>>id1) break;
                if (!filereader>>id2) break;
                if (!filereader>>w) break;

                graph.addEdge(id1, id2, w);
            }

        }catch(exception){
            cout<<"Something wrong with your file!";
        }

    }
    else throw "Unknown type of input";

    return graph;
}

bool isIgnore(vector<int> *ignoreID, int id){
    for (auto itr = ignoreID->begin(); itr!=ignoreID->end(); itr++){
        if (*itr == id)
            return true;
    }
    return false;
}

Edge* minEdge(vector<Edge*> edges, vector<int> *ignoreID){
    // helper go minSpanningTree
    int minWeight = 1<<20;
    Edge *e = nullptr;

    for (auto itr = edges.begin(); itr!=edges.end(); itr++){
        if (isIgnore(ignoreID, (*itr)->node2->id))
            continue;

        if ((*itr)->weight < minWeight){
            minWeight = (*itr)->weight;
            e = *itr;
        }
    }

    return e;
}

void eraseEdge(vector<Edge*> edges, Edge* e){
    for (auto itr = edges.begin(); itr!=edges.end(); itr++){
        if ((*itr) == e){
            edges.erase(itr);
            return;
        }
    }
}

Orgraf minSpanningTree(Orgraf* og){
    // Based on Prima algorithm
    Orgraf mg;
    vector<GraphNode*> nodes = og->getNodes();

    if (nodes.empty())
        return mg;

    for (auto itr=nodes.begin(); itr!=nodes.end(); itr++){
        GraphNode *node = new GraphNode;
        node->id = (*itr)->id;
        mg.addNode(node);
    }

    int nodesSize = nodes.size();
    int connectedNodes = 1;

    vector<GraphNode*> connected;
    vector<int> ignoreIDs;
    connected.push_back(nodes.at(0));
    ignoreIDs.push_back(nodes.at(0)->id);

    vector<Edge*> edges = connected.at(0)->getEdges();

    // EMPTY GRAPH
    if (edges.empty())
        return mg;

    while (connectedNodes != nodesSize){
        // find edge with min weight to connect new node
        Edge *e = minEdge(edges, &ignoreIDs);

        // can't find edge, there are not edges which connects to new nodes
        if (e == nullptr)
            break;

        // add edge to SpinTree and erase from list where we find new edge
        mg.addEdge(e->node1->id, e->node2->id, e->weight);
        eraseEdge(edges, e);
        ignoreIDs.push_back(e->node2->id);

        if (edges.empty())
            break;

        connectedNodes++;

        // add new edges
        vector<Edge*> newEdges = e->node1->getEdges();
        for (auto itr = newEdges.begin(); itr!=newEdges.end(); itr++){
            if (isIgnore(&ignoreIDs, (*itr)->node2->id))
                continue;

            edges.push_back(*itr);
        }
    }

    if (connectedNodes != nodesSize){
        cout<<"THERE IS TROUBLE WHILE BUILDING! PROBABLY NOT EVERY NODE CAN BE CONNECTED TO"<<endl;
    }

    return mg;
}