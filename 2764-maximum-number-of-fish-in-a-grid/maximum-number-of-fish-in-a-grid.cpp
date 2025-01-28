class Solution {
public:
    int findMaxFish(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int maxFish = 0;

        // Directions for adjacent cells (right, left, down, up)
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        // Helper function for DFS
        auto dfs = [&](int r, int c, auto&& dfs) -> int {
            if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
                return 0; // Out of bounds or land cell
            }
            
            int fish = grid[r][c]; // Collect fish
            grid[r][c] = 0; // Mark as visited
            
            for (auto [dr, dc] : directions) {
                fish += dfs(r + dr, c + dc, dfs);
            }
            
            return fish;
        };
        
        // Start DFS from every water cell
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) { // Water cell
                    maxFish = max(maxFish, dfs(i, j, dfs));
                }
            }
        }
        
        return maxFish;
    }
};
