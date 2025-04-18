#include "Graph.hpp"


int Graph::getIndex(string label) {
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i].label == label) return i;
    }
    return -1;
}

void Graph::addVertex(string label){
    if (getIndex(label) != -1) 
        return;

    Vertex v;
    v.label = label;
    vertices.push_back(v);
};

void Graph::removeVertex(string label){
    int idx = getIndex(label);
    if (idx == -1) return;
    vertices.erase(vertices.begin() + idx);
    for (int i = 0; i < vertices.size(); ++i) {
        for (int j = 0; j < vertices[i].neighbors.size(); ++j) {
            if (vertices[i].neighbors[j].dest == label) {
                vertices[i].neighbors.erase(vertices[i].neighbors.begin() + j);
                break;
            }
        }
    }
};

void Graph::addEdge(string label1, string label2, unsigned long weight){
    int idx1 = getIndex(label1);
    int idx2 = getIndex(label2);
    if (idx1 == -1 || idx2 == -1 || label1 == label2) 
        return;

    for (int i = 0; i < vertices[idx1].neighbors.size(); ++i) {
        if (vertices[idx1].neighbors[i].dest == label2) return;
    }

    vertices[idx1].neighbors.push_back({label2, weight});
    vertices[idx2].neighbors.push_back({label1, weight});
};

void Graph::removeEdge(string label1, string label2){
    int idx1 = getIndex(label1);
    int idx2 = getIndex(label2);
    if (idx1 == -1 || idx2 == -1) return;

    for (int i = 0; i < vertices[idx1].neighbors.size(); ++i) {
        if (vertices[idx1].neighbors[i].dest == label2) {
            vertices[idx1].neighbors.erase(vertices[idx1].neighbors.begin() + i);
            break;
        }
    }

    for (int i = 0; i < vertices[idx2].neighbors.size(); ++i) {
        if (vertices[idx2].neighbors[i].dest == label1) {
            vertices[idx2].neighbors.erase(vertices[idx2].neighbors.begin() + i);
            break;
        }
    }
};

unsigned long Graph::shortestPath(string startLabel, string endLabel, vector<string>& path){
    int n = vertices.size();
    vector<unsigned long> dist(n, -1);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    int start = getIndex(startLabel);
    int end = getIndex(endLabel);
    if (start == -1 || end == -1) return -1;

    dist[start] = 0;

    for (int count = 0; count < n; ++count) {
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) u = i;
        }

        if (dist[u] == -1) break;
        visited[u] = true;

        for (int i = 0; i < vertices[u].neighbors.size(); ++i) {
            int v = getIndex(vertices[u].neighbors[i].dest);
            unsigned long weight = vertices[u].neighbors[i].weight;
            if (dist[v] == -1 || dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }

    path.clear();
    for (int at = end; at != -1; at = prev[at]) {
        path.insert(path.begin(), vertices[at].label);
    }

    return dist[end];
};