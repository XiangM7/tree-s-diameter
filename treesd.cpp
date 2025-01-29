#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int u, v;
    Edge(){}
    Edge(int a, int b) { u = a; v = b; }
};

// Helper function to perform BFS and find the farthest node and its distance
pair<int, int> bfs(int start, const vector<vector<int>>& adj, int n) {
    vector<int> dist(n + 1, -1); // Distance array
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int farthest_node = start;
    int max_dist = 0;

    while (!q.empty()) {
        int current = q.front(); q.pop();
        for (const auto &neighbor : adj[current]) {
            if (dist[neighbor] == -1) { // If not visited
                dist[neighbor] = dist[current] + 1;
                q.push(neighbor);
                if (dist[neighbor] > max_dist) {
                    max_dist = dist[neighbor];
                    farthest_node = neighbor;
                }
            }
        }
    }

    return {farthest_node, max_dist};
}

int compute_diameter(int n, vector<Edge> T) {
    // Step 1: Build the adjacency list
    vector<vector<int>> adj(n + 1, vector<int>());
    for (const auto &edge : T) {
        adj[edge.u].push_back(edge.v);
        adj[edge.v].push_back(edge.u);
    }

    // Step 2: First BFS to find one end of the diameter
    pair<int, int> first_bfs = bfs(1, adj, n);
    int farthest_node = first_bfs.first;

    // Step 3: Second BFS from the farthest node found in first BFS
    pair<int, int> second_bfs = bfs(farthest_node, adj, n);
    int diameter = second_bfs.second;

    return diameter;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while(tc--){
        int n;
        cin >> n;
        vector<Edge> T(n - 1);
        for(int i = 0; i < n - 1; ++i){
            cin >> T[i].u >> T[i].v;
        }
        int answer = compute_diameter(n, T);
        cout << answer << '\n';
    }
}
