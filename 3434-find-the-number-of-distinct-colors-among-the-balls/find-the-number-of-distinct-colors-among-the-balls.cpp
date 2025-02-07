#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int, int> ballColor;  // Maps a ball to its current color
        unordered_map<int, int> colorCount; // Maps color to its frequency
        unordered_set<int> uniqueColors;    // Set of unique colors
        vector<int> result;

        for (const auto& query : queries) {
            int ball = query[0], color = query[1];

            if (ballColor.count(ball)) {
                int oldColor = ballColor[ball];
                colorCount[oldColor]--;

                if (colorCount[oldColor] == 0) {
                    uniqueColors.erase(oldColor);
                }
            }

            ballColor[ball] = color;
            colorCount[color]++;

            uniqueColors.insert(color);
            result.push_back(uniqueColors.size());
        }

        return result;
    }
};
