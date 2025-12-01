#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Relic {
    int start;
    int end;
    int value;
};

bool compareRelics(const Relic& a, const Relic& b) {
    return a.end < b.end;
}

long long solve_relic_arena(vector<Relic>& relics, int K) {
    int N = relics.size();
    if (N == 0) return 0;
    
    sort(relics.begin(), relics.end(), compareRelics);
    
    vector<int> end_times(N);
    for (int i = 0; i < N; ++i) {
        end_times[i] = relics[i].end;
    }
    
    vector<long long> dp(N + 1, 0);
    
    for (int i = 1; i <= N; ++i) {
        int start = relics[i-1].start;
        int value = relics[i-1].value;
        
        // Option 1: Skip
        long long val_skip = dp[i-1];
        
        // Option 2: Take
        int target = start - K;
        
        // Find index p such that end_times[p] <= target
        // upper_bound returns first element > target
        // So we want the element before that.
        auto it = upper_bound(end_times.begin(), end_times.begin() + i - 1, target);
        int idx = distance(end_times.begin(), it);
        
        long long val_take = value + dp[idx];
        
        dp[i] = max(val_skip, val_take);
    }
    
    return dp[N];
}

int main() {
    // Example 1
    vector<Relic> relics1 = {{1, 3, 50}, {3, 5, 20}, {6, 8, 100}};
    int K1 = 1;
    cout << "Max Value (Ex 1): " << solve_relic_arena(relics1, K1) << endl;
    
    // Example 2
    vector<Relic> relics2 = {{1, 2, 10}, {2, 3, 20}, {3, 4, 30}};
    int K2 = 0;
    cout << "Max Value (Ex 2): " << solve_relic_arena(relics2, K2) << endl;
    
    return 0;
}
