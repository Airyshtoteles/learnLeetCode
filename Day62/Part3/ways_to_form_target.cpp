#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    vector<string> words(n);
    for(int i=0; i<n; ++i) cin >> words[i];
    
    string target;
    cin >> target;
    
    int m = words[0].size();
    int t_len = target.size();
    long long MOD = 1e9 + 7;
    
    vector<vector<int>> cnt(m, vector<int>(26, 0));
    for(const string& w : words) {
        for(int j=0; j<m; ++j) {
            cnt[j][w[j] - 'a']++;
        }
    }
    
    vector<long long> dp(t_len + 1, 0);
    dp[0] = 1;
    
    for(int j=0; j<m; ++j) { // For each column
        for(int i=t_len; i>=1; --i) { // For each target character (backwards)
            char c = target[i-1];
            int count = cnt[j][c - 'a'];
            if (count > 0) {
                dp[i] = (dp[i] + dp[i-1] * count) % MOD;
            }
        }
    }
    
    cout << dp[t_len] << endl;
    
    return 0;
}
