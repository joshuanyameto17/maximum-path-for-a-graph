#include <vector>
#include <algorithm>

using namespace std;

// Graph is represented as a vector of vectors of pairs,
// where each pair is a node index and the time it takes to reach it.
using Graph = vector<vector<pair<int, int>>>;

// Function to find the maximal path quality
int maximalPathQuality(const vector<int>& values, const vector<vector<int>>& edges, int maxTime) {
    const int numNodes = values.size();
    Graph graph(numNodes);

    // Populate the adjacency list for the graph
    for (const auto& edge : edges) {
        int from = edge[0];
        int to = edge[1];
        int time = edge[2];
        graph[from].emplace_back(to, time);
        graph[to].emplace_back(from, time);
    }

    // Vector to keep track of visited nodes
    vector<bool> visited(numNodes, false);
    int maxQuality = 0;

    // Depth-First Search (DFS) to explore paths
    function<void(int, int, int)> dfs = [&](int currentNode, int remainingTime, int currentQuality) {
        // If we've reached the start again, update maximum path quality
        if (currentNode == 0) {
            maxQuality = max(currentQuality, maxQuality);
        }

        // Recursive exploration of neighbors
        for (const auto& [nextNode, travelTime] : graph[currentNode]) {
            if (remainingTime - travelTime >= 0) {
                if (!visited[nextNode]) {
                    visited[nextNode] = true;
                    dfs(nextNode, remainingTime - travelTime, currentQuality + values[nextNode]);
                    visited[nextNode] = false; // Backtrack
                } else {
                    dfs(nextNode, remainingTime - travelTime, currentQuality);
                }
            }
        }
    };

    // Starting from node 0
    visited[0] = true;
    dfs(0, maxTime, values[0]);

    return maxQuality;
}
