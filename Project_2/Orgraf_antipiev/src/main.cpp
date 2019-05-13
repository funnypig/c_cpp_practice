//
// Created by ilya on 11.05.19.
//

#include <fstream>
#include "iostream"
#include "Orgraf.h"
#include <random>
#include <ctime>

void Console(){
    int type;
    cout<<"Choose type:\n1. Adjacency matrix\n2. edge by edge\n";
    cin>>type;
    cout<<endl;

    Orgraf og;

    if (type == 1){
        og = asMatrix();
    }else{
        og = edgeByEdge();
    }

    og.showEdges();
    og.showMatrix();
    cout<<"Total weight "<<og.totalWeight()<<endl;

    cout<<endl;

    Orgraf mg = minSpanningTree(&og);
    cout<<"Min spanning tree: "<<mg.totalWeight()<<endl;
    mg.showEdges();
}

void File(){
    cout<<"Input file name:\n";
    string s;
    cin>>s;

    Orgraf og = fromFile(s);

    cout<<"Total weight: "<<og.totalWeight()<<endl;
    og.showMatrix();
    cout<<endl;

    Orgraf mg = minSpanningTree(&og);
    cout<<"Min spanning tree: "<<mg.totalWeight();
    mg.showMatrix();
}

void Randomized(){
    srand(time(0));

    cout<<"Enter number of nodes: ";
    int n;
    cin>>n;

    Orgraf g;
    for (int i = 0; i<n; i++){
        GraphNode *node = new GraphNode;
        g.addNode(node);
    }

    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            if (rand()%4<3){
                g.addEdge(i, j,rand()%100);

            }
        }
    }

    cout<<"Total weight: "<<g.totalWeight();
    g.showMatrix();
    cout<<endl;

    Orgraf mg = minSpanningTree(&g);
    cout<<"Min spanning tree: "<<mg.totalWeight()<<endl;
    mg.showMatrix();
}

int main(){

    /*
     "/home/ilya/C_practice/Project_2/Orgraf_antipiev/test/test_1.txt"
     "/home/ilya/C_practice/Project_2/Orgraf_antipiev/test/test_2.txt"
     */


    int choice;
    cout<<"1. Input graph yourself"<<endl;
    cout<<"2. Read graph from file"<<endl;
    cout<<"3. Random graf"<<endl;
    cin>>choice;

    switch (choice){
        case 1: Console();
                break;
        case 2: File();
                break;
        case 3: Randomized();
                break;
        default:
            cout<<"Sorry, unrecognized operation!";
            break;
    }
}