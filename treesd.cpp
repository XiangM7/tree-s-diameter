#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int u, v;

    // Default constructor
    Edge() : u(0), v(0) {}

    // Parameterized constructor
    Edge(int a, int b) : u(a), v(b) {}
};

// BFS function to find the farthest node and its distance from the start node
int bfs(int start, const vector<vector<int>>& adj, int n) {
    vector<int> dist(n + 1, -1); // Initialize all distances to -1 (unvisited)
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    int farthest_node = start;
    int max_dist = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // Go through all the neighbors
        for (int neighbor : adj[node]) {
            if (dist[neighbor] == -1) {  // If the neighbor has not been visited
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);

                // Track the farthest node and the maximum distance
                if (dist[neighbor] > max_dist) {
                    max_dist = dist[neighbor];
                    farthest_node = neighbor;
                }
            }
        }
    }

    return max_dist; // Return the longest distance found
}

int compute_diameter(int n, const vector<Edge>& edges) {
    vector<vector<int>> adj(n + 1);  // Create adjacency list for the tree

    // Fill the adjacency list
    for (const auto& edge : edges) {
        adj[edge.u].push_back(edge.v);
        adj[edge.v].push_back(edge.u);
    }

    // First BFS to find the farthest node from an arbitrary node (1 in this case)
    int farthest = bfs(1, adj, n);

    // Second BFS from the farthest node found to calculate the tree's diameter
    return bfs(farthest, adj, n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) {
        int n;
        cin >> n;

        vector<Edge> edges(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            cin >> edges[i].u >> edges[i].v;
        }

        // Compute the diameter of the tree and print it
        cout << compute_diameter(n, edges) << '\n';
    }

    return 0;
}

