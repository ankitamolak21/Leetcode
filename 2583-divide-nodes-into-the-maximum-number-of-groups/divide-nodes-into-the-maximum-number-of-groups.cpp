class Solution {
public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n + 1);
        for (auto &edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> color(n + 1, -1); // -1 means uncolored
        vector<int> components; // To store different connected components
        function<bool(int)> isBipartite = [&](int node) {
            queue<int> q;
            q.push(node);
            color[node] = 0; // Start with color 0
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : graph[u]) {
                    if (color[v] == -1) { // If uncolored, color it with opposite color
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if (color[v] == color[u]) { 
                        return false; // If two adjacent nodes have the same color, it's not bipartite
                    }
                }
            }
            return true;
        };

        function<int(int)> bfs = [&](int start) {
            queue<int> q;
            unordered_map<int, int> depth;
            q.push(start);
            depth[start] = 1;
            int maxDepth = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : graph[u]) {
                    if (depth.find(v) == depth.end()) {
                        depth[v] = depth[u] + 1;
                        maxDepth = max(maxDepth, depth[v]);
                        q.push(v);
                    }
                }
            }
            return maxDepth;
        };

        int result = 0;
        vector<bool> visited(n + 1, false);
        
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                vector<int> component;
                queue<int> q;
                q.push(i);
                visited[i] = true;

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    component.push_back(u);
                    for (int v : graph[u]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            q.push(v);
                        }
                    }
                }

                if (!isBipartite(component[0])) {
                    return -1; // Not bipartite means impossible to satisfy conditions
                }

                int maxGroups = 0;
                for (int node : component) {
                    maxGroups = max(maxGroups, bfs(node));
                }
                result += maxGroups;
            }
        }
        
        return result;
    }
};
