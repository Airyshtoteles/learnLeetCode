#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<char> dp(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k * k <= i; ++k) {
                if (!dp[i - k*k]) { dp[i] = 1; break; }
            }
        }
        return dp[n];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> tests = {1,2,3,4,7,17};
    Solution sol;
    for (int n : tests) {
        cout << n << " -> " << (sol.winnerSquareGame(n) ? "True" : "False") << "\n";
    }
    return 0;
}
