class Solution {
public:
    int longestMonotonicSubarray(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;

        int maxLength = 1, inc = 1, dec = 1;

        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                inc++;
                dec = 1; // Reset decreasing length
            } 
            else if (nums[i] < nums[i - 1]) {
                dec++;
                inc = 1; // Reset increasing length
            } 
            else {
                inc = dec = 1; // Reset both when equal
            }

            maxLength = std::max(maxLength, std::max(inc, dec));
        }

        return maxLength;
    }
};
