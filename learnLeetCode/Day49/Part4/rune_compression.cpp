#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int memo[101][101];
string S;
int N;

int get_len(int count) {
    if (count == 1) return 1;
    if (count < 10) return 2;
    if (count < 100) return 3;
    return 4;
}

int dp(int idx, int k_left) {
    if (k_left < 0) return 1e9;
    if (idx == N) return 0;
    if (memo[idx][k_left] != -1) return memo[idx][k_left];
    
    // Option 1: Delete S[idx]
    int res = dp(idx + 1, k_left - 1);
    
    // Option 2: Keep S[idx]
    int same = 0;
    int diff = 0;
    
    for (int j = idx; j < N; ++j) {
        if (S[j] == S[idx]) {
            same++;
        } else {
            diff++;
        }
        
        if (diff > k_left) break;
        
        int cost = get_len(same) + dp(j + 1, k_left - diff);
        res = min(res, cost);
    }
    
    return memo[idx][k_left] = res;
}

int solve_rune_compression(string s, int k) {
    S = s;
    N = s.length();
    
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= k; ++j) {
            memo[i][j] = -1;
        }
    }
    
    return dp(0, k);
}

int main() {
    string s = "aaabcccd";
    int k = 2;
    
    cout << "Minimum Length: " << solve_rune_compression(s, k) << endl;
    
    return 0;
}
