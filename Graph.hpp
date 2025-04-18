// Graph.hpp
#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <vector>
#include <string>

using namespace std;

class Graph : public GraphBase {
private:
    struct Edge {
        string dest;
        unsigned long weight;
    };

    struct Vertex {
        string label;
        vector<Edge> neighbors;
    };

    vector<Vertex> vertices;

    int getIndex(string label);

public:
    void addVertex(string label);
    void removeVertex(string label);
    void addEdge(string label1, string label2, unsigned long weight);
    void removeEdge(string label1, string label2);
    unsigned long shortestPath(string startLabel, string endLabel, vector<string>& path);
};

#endif