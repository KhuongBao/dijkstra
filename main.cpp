#include <iostream>
#include <tuple>
#include "Graph.hpp"

using namespace std;

int main() {
    Graph g;
    vector<string> vertices = {"1", "2", "3", "4", "5", "6"};
    for (string v : vertices) 
        g.addVertex(v);

    vector<tuple<string, string, unsigned long>> edges = {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14},
        {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11},
        {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9}
    };
    
    for (const auto& edge : edges) {
        g.addEdge(get<0>(edge), get<1>(edge), get<2>(edge));
    }

    vector<string> path;
    unsigned long dist = g.shortestPath("1", "5", path);
    cout << "Shortest distance: " << dist << "\nPath: ";

    for (string s : path) 
        cout << s << " ";
    cout << "\n\n";


    // g.removeVertex("3");
    // cout << "Removed vertex 3\n";
    
    // path.clear();
    // dist = g.shortestPath("1", "5", path);
    // cout << "Shortest distance: " << dist << "\nPath: ";

    // for (string s : path) 
    //     cout << s << " ";
    // cout << "\n";

    return 0;
}
