class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        unordered_map<int, int> area;  // Stores area of each island by its id
        int islandId = 2;  // Start labeling islands from 2 (since 0 and 1 are used)
        int maxIsland = 0;

        // DFS function to calculate the area of an island
        function<int(int, int, int)> dfs = [&](int i, int j, int id) {
            if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] != 1) return 0;
            grid[i][j] = id;  // Mark the island with its id
            int size = 1;
            for (auto& dir : directions) {
                size += dfs(i + dir[0], j + dir[1], id);
            }
            return size;
        };

        // Step 1: Identify islands and calculate their sizes
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int size = dfs(i, j, islandId);
                    area[islandId] = size;
                    maxIsland = max(maxIsland, size);
                    islandId++;
                }
            }
        }

        // Step 2: Check every 0 cell to see if it can connect islands
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> neighbors;
                    int newSize = 1;  // Change this 0 to 1

                    // Check 4 possible neighbors
                    for (auto& dir : directions) {
                        int ni = i + dir[0], nj = j + dir[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] > 1) {
                            neighbors.insert(grid[ni][nj]);
                        }
                    }

                    // Sum up the sizes of connected islands
                    for (int id : neighbors) {
                        newSize += area[id];
                    }

                    maxIsland = max(maxIsland, newSize);
                }
            }
        }

        return maxIsland;
    }
};
