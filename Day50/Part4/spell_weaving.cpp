#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve_spell_weaving(const vector<int>& cd, const vector<int>& p, int T) {
    int n = cd.size();
    vector<int> dp(T + 1, 0);
    
    for (int t = 1; t <= T; ++t) {
        dp[t] = dp[t-1];
        
        for (int i = 0; i < n; ++i) {
            int prev_time = t - cd[i];
            int val = p[i];
            if (prev_time >= 0) {
                val += dp[prev_time];
            }
            
            if (val > dp[t]) {
                dp[t] = val;
            }
        }
    }
    
    return dp[T];
}

int main() {
    vector<int> cd = {2, 3};
    vector<int> p = {10, 20};
    int T = 5;
    
    cout << "Max Power: " << solve_spell_weaving(cd, p, T) << endl;
    
    return 0;
}
