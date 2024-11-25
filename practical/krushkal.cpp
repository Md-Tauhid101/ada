// Write a program to determine the minimum spanning tree of a graph using Kruskal’s
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int u, v, weight;
    Edge(int _u, int _v, int _weight) : u(_u), v(_v), weight(_weight) {}
};

// Comparator for sorting edges by weight
bool compareEdges(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

// Disjoint Set Union (DSU) for Kruskal's algorithm
class DSU {
private:
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Initialize each node as its own parent
        }
    }

    // Find the representative of a set
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union of two sets by rank
    bool unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false; // Already in the same set

        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

// Function to find the MST using Kruskal's algorithm
void kruskalMST(int n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end(), compareEdges); // Sort edges by weight
    DSU dsu(n);

    vector<Edge> mst;
    int mstWeight = 0;

    for (const Edge &edge : edges) {
        if (dsu.unionSets(edge.u, edge.v)) {
            mst.push_back(edge);
            mstWeight += edge.weight;
        }
    }

    // Print the MST
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const Edge &edge : mst) {
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;
    }
    cout << "Total weight of the MST: " << mstWeight << endl;
}

int main() {
    

    const int V = 4; // Number of vertices
    const int E = 5; // Number of edges

    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(V, edges);

    return 0;
}
