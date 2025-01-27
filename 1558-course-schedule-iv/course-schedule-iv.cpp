#include <vector>
using namespace std;

class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        // Initialize the reachable matrix
        vector<vector<bool>> reachable(numCourses, vector<bool>(numCourses, false));
        
        // Set direct prerequisites
        for (const auto& pre : prerequisites) {
            reachable[pre[0]][pre[1]] = true;
        }
        
        // Floyd-Warshall Algorithm for transitive closure
        for (int k = 0; k < numCourses; ++k) {
            for (int i = 0; i < numCourses; ++i) {
                for (int j = 0; j < numCourses; ++j) {
                    if (reachable[i][k] && reachable[k][j]) {
                        reachable[i][j] = true;
                    }
                }
            }
        }
        
        // Resolve queries
        vector<bool> result;
        for (const auto& query : queries) {
            result.push_back(reachable[query[0]][query[1]]);
        }
        
        return result;
    }
};
