#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Define an edge structure
struct Edge {
    int source, dest, weight;
};

// Function to perform the Bellman-Ford algorithm
void bellmanFord(int vertices, int edges, vector<Edge>& graph, int source) {
    // Initialize distance to all vertices as infinite and source to 0
    vector<int> distance(vertices, INT_MAX);
    distance[source] = 0;

    // Relax edges |V| - 1 times
    for (int i = 1; i < vertices; i++) {
        for (int j = 0; j < edges; j++) {
            int u = graph[j].source;
            int v = graph[j].dest;
            int weight = graph[j].weight;

            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < edges; i++) {
        int u = graph[i].source;
        int v = graph[i].dest;
        int weight = graph[i].weight;

        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative-weight cycle!" << endl;
            return;
        }
    }

    // Print distances
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << i << "\t\t" << (distance[i] == INT_MAX ? "INF" : to_string(distance[i])) << endl;
    }
}

int main() {
    int vertices, edges, source;

    cout << "Enter the number of vertices: ";
    cin >> vertices;

    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<Edge> graph(edges);

    cout << "Enter the edges in the format (source destination weight):" << endl;
    for (int i = 0; i < edges; i++) {
        cin >> graph[i].source >> graph[i].dest >> graph[i].weight;
    }

    cout << "Enter the source vertex: ";
    cin >> source;

    bellmanFord(vertices, edges, graph, source);

    return 0;
}
