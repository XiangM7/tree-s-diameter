#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int u, v;
    Edge(){}
    Edge(int a, int b) { u = a; v = b; }
};

// https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

// Helper function to perform BFS and find the farthest node and its distance
pair<int, int> bfs(int start, const vector<vector<int>>& adj, int n) {
    
    vector<bool> visited(n+1, false); 
    queue<pair<int,int>> tree;
    //reset everthing
    
    tree.push({start, 0});
    // Mark the source node as visited and enqueue it
    visited[start] = true;
    
    //by hint, i need farest node and diameter between u and v, and do anohter bfs for v and w to find diameter, for make--
    //code effeicency, i wanna my bfs could collect these 2 data 
    int farest = start;
    int dis = 0;

    while (!tree.empty()) {
        
        pair<int, int> front = tree.front();
        int curr = front.first;
        int curr_dist = front.second;
        
        tree.pop();
        
        // If the newly discovered distance is greater than our current max.
        if (curr_dist > dis) {
            dis = curr_dist;
            farest = curr;
        }

        for (const auto &x : adj[curr]) {
            // If not visited, add it in
            if (!visited[x]) { 
                visited[x] = true;
                tree.push({x, curr_dist + 1});
            }
        }
    }

    return {farest, dis};
}

int compute_diameter(int n, vector<Edge> T)
{
    //Build the adjacency list
    vector<vector<int>> adj(n+1, vector<int>());
    
    for (const auto &edge : T) {
        adj[edge.u].push_back(edge.v);
        adj[edge.v].push_back(edge.u);
    }

    // First, use BFS to find  v
    pair<int, int> firsttime = bfs(1, adj, n);
    
    int farest = firsttime.first;

    //Use BFS again, to find distance from v and w
    pair<int, int> secondtime = bfs(farest, adj, n);
    
    int diameter = secondtime.second;

    return diameter;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
   for (int t = 0; t < tc; t++) {
        int n;
        cin >> n;
        vector<Edge> T(n - 1);
        for (int i = 0; i < n - 1; i++) {
            cin >> T[i].u >> T[i].v;
        }
        int answer = compute_diameter(n, T);
        cout << answer << '\n';
    }
}


