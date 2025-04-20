#include "Graph.hpp"


int Graph::getIndex(string label) {
    for (int i = 0; i < vertices.size(); i++) { // Loop through all vertices
        if (vertices[i].label == label) // If the label matches, return the index
            return i;
    }
    return -1;
}

void Graph::addVertex(string label){
    if (getIndex(label) != -1) // If the vertex already exists, do nothing
        return;

    // Create a new vertex, initialize it, and add it to the graph
    Vertex v; 
    v.label = label;
    vertices.push_back(v);
};

void Graph::removeVertex(string label){
    // Get the index of the vertex to be removed
    int idx = getIndex(label);
    if (idx == -1) 
        return;

    // Remove the vertex from the graph
    vertices.erase(vertices.begin() + idx);

    // Remove all edges to this vertex from other vertices
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < vertices[i].neighbors.size(); j++) {
            if (vertices[i].neighbors[j].dest == label) {
                vertices[i].neighbors.erase(vertices[i].neighbors.begin() + j);
                break;
            }
        }
    }
};

void Graph::addEdge(string label1, string label2, unsigned long weight){
    // Get the index of the vertices
    int idx1 = getIndex(label1);
    int idx2 = getIndex(label2);
    if (idx1 == -1 || idx2 == -1 || label1 == label2) 
        return;

    // Check if the edge already exists
    for (int i = 0; i < vertices[idx1].neighbors.size(); i++) {
        if (vertices[idx1].neighbors[i].dest == label2) 
            return;
    }

    // Add the edge to both vertices
    vertices[idx1].neighbors.push_back({label2, weight});
    vertices[idx2].neighbors.push_back({label1, weight});
};

void Graph::removeEdge(string label1, string label2){
    // Get the index of the vertices
    int idx1 = getIndex(label1);
    int idx2 = getIndex(label2);
    if (idx1 == -1 || idx2 == -1) 
        return;

    // Remove the edge from the first vertex
    for (int i = 0; i < vertices[idx1].neighbors.size(); i++) {
        if (vertices[idx1].neighbors[i].dest == label2) {
            vertices[idx1].neighbors.erase(vertices[idx1].neighbors.begin() + i);
            break;
        }
    }

    // Remove the edge from the other vertex
    for (int i = 0; i < vertices[idx2].neighbors.size(); i++) {
        if (vertices[idx2].neighbors[i].dest == label1) {
            vertices[idx2].neighbors.erase(vertices[idx2].neighbors.begin() + i);
            break;
        }
    }
};

unsigned long Graph::shortestPath(string startLabel, string endLabel, vector<string>& path){
    int n = vertices.size(); // Get the number of vertices
    vector<unsigned long> dist(n, -1); // Initialize all distances to -1 (2^64 - 1)
    vector<int> prev(n, -1); // Initialize previous vertices to -1
    vector<bool> visited(n, false); // Track visited vertices

    // Check if the start and end labels are valid
    int start = getIndex(startLabel);
    int end = getIndex(endLabel);
    if (start == -1 || end == -1) return -1;

    dist[start] = 0; // Set the distance to the start vertex to 0

    
    for (int count = 0; count < n; count++) {
        int u = -1;
        // Find the unvisited vertex with the smallest distance
        for (int i = 0; i < n; i++) {
            // If the vertex is unvisited and either u is -1 or the distance is 
            // smaller than the current smallest
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        visited[u] = true; // Set the vertex as visited

        // Loop through all neighbors of the vertex
        for (int i = 0; i < vertices[u].neighbors.size(); i++) {
            // Get index and weight of the neighbor
            int v = getIndex(vertices[u].neighbors[i].dest);
            unsigned long weight = vertices[u].neighbors[i].weight;

            // If the neighbor is unvisited or the distance can be shorter
            if (dist[v] == -1 || dist[u] + weight < dist[v]) {
                // Update the distance
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }

    // Update path string for output
    path.clear();
    for (int i = end; i != -1; i = prev[i]) {
        path.insert(path.begin(), vertices[i].label);
    }

    return dist[end]; // Return the shortest distance to end vertex
};
