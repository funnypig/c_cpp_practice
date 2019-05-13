//
// Created by ilya on 13.05.19.
//

#include <iostream>
#include <Orgraf.h>


void test1(){
    cout<<"Testing user input as matrix"<<endl;

    Orgraf g = asMatrix();

    cout<<"Sum of the weights of the graph: "<<g.totalWeight()<<endl;
    cout<<"Graph adjacency matrix:\n";
    g.showMatrix();
    cout<<"Edge by edge output:\n";
    g.showEdges();

    Orgraf mg = minSpanningTree(&g);
    cout<<"Sum of the weights of the minimum spanning tree: "<<mg.totalWeight()<<endl;
    cout<<"Minimum spinning tree adjacency matrix:\n";
    mg.showMatrix();
    cout<<"Edge by edge output:\n";
    mg.showEdges();
}


void test2(){
    cout<<"Testing user input entering edge by edge"<<endl;

    Orgraf g = edgeByEdge();

    cout<<"Sum of the weights of the graph: "<<g.totalWeight()<<endl;
    cout<<"Graph adjacency matrix:\n";
    g.showMatrix();
    cout<<"Edge by edge output:\n";
    g.showEdges();

    Orgraf mg = minSpanningTree(&g);
    cout<<"Sum of the weights of the minimum spanning tree: "<<mg.totalWeight()<<endl;
    cout<<"Minimum spinning tree adjacency matrix:\n";
    mg.showMatrix();
    cout<<"Edge by edge output:\n";
    mg.showEdges();
}


void test3(){
    string path = "/home/ilya/C_practice/Project_2/Orgraf_antipiev/test/test_1.txt";
    cout<<"Testing using file";
    cout<<"path: "<<path<<endl;

    Orgraf g = fromFile(path);

    cout<<"Sum of the weights of the graph: "<<g.totalWeight()<<endl;
    cout<<"Graph adjacency matrix:\n";
    g.showMatrix();
    cout<<"Edge by edge output:\n";
    g.showEdges();

    Orgraf mg = minSpanningTree(&g);
    cout<<"Sum of the weights of the minimum spanning tree: "<<mg.totalWeight()<<endl;
    cout<<"Minimum spinning tree adjacency matrix:\n";
    mg.showMatrix();
    cout<<"Edge by edge output:\n";
    mg.showEdges();
}
