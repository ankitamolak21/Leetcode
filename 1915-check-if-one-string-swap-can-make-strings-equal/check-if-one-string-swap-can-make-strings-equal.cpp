class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        vector<int> diff;  // Stores indices where s1 and s2 differ
        
        // Find differing positions
        for (int i = 0; i < s1.length(); i++) {
            if (s1[i] != s2[i]) {
                diff.push_back(i);
            }
        }
        
        // Case 1: Already equal
        if (diff.empty()) return true;
        
        // Case 2: There must be exactly 2 differences to swap and fix
        if (diff.size() != 2) return false;
        
        // Check if swapping makes the strings equal
        return s1[diff[0]] == s2[diff[1]] && s1[diff[1]] == s2[diff[0]];
    }
};
