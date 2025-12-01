#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = (int)stones.size();
        vector<long long> s(n);
        partial_sum(stones.begin(), stones.end(), s.begin());
        // dfs(i) = max(dfs(i+1), s[i] - dfs(i+1)), base dfs(i>=n-1)=s[n-1]
        // We can implement bottom-up from right to left.
        long long prev = s[n-1]; // this is dfs(n-1)
        for (int i = n - 2; i >= 1; --i) {
            long long skip = prev;            // dfs(i+1)
            long long take = s[i] - prev;     // s[i] - dfs(i+1)
            long long cur = max(skip, take);  // dfs(i)
            prev = cur;
        }
        return (int)prev; // dfs(1)
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> tests = {
        {3,7,2,3},
        {7,-6,5,10,5,-2,-6},
        {-10,-12},
        {1,2}
    };
    Solution sol;
    for (auto arr : tests) {
        cout << "[";
        for (size_t i = 0; i < arr.size(); ++i) {
            if (i) cout << ", ";
            cout << arr[i];
        }
        cout << "] -> " << sol.stoneGameVIII(arr) << "\n";
    }
    return 0;
}
