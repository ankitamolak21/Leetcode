class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n + 1);
        vector<int> rank(n + 1, 0);

        // Initialize each node as its own parent
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }

        // Find function with path compression
        function<int(int)> find = [&](int node) {
            if (parent[node] != node) {
                parent[node] = find(parent[node]);  // Path compression
            }
            return parent[node];
        };

        // Union function with union by rank
        auto unionSet = [&](int u, int v) {
            int rootU = find(u);
            int rootV = find(v);
            if (rootU == rootV) return false; // Cycle detected
            
            // Union by rank
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
            return true;
        };

        // Process each edge
        for (const auto& edge : edges) {
            if (!unionSet(edge[0], edge[1])) {
                return edge;  // This edge forms a cycle
            }
        }
        
        return {};  // This should never be reached
    }
};
