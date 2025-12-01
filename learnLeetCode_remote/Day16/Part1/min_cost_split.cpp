#include <bits/stdc++.h>
using namespace std;

// LC 2547 — Minimum Cost to Split Array
// O(n^2) DP reference implementation

class Solution {
public:
    int minCost(vector<int>& nums, int k) {
        int n = (int)nums.size();
        const long long INF = (long long)4e18;
        vector<long long> dp(n+1, INF);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            unordered_map<int,int> freq;
            long long dup = 0;
            for (int j = i - 1; j >= 0; --j) {
                int x = nums[j];
                int f = ++freq[x];
                if (f == 2) dup += 2;
                else if (f > 2) dup += 1;
                dp[i] = min(dp[i], dp[j] + k + dup);
            }
        }
        return (int)dp[n];
    }
};

int main(){
    vector<int> nums = {1,2,1,2,1,3,3};
    cout << Solution().minCost(nums, 2) << "\n"; // 8
    return 0;
}
