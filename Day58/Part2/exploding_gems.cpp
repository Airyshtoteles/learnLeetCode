#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int N;
vector<int> gems;
long long dp[505][505];
long long prefix_sum[505];

long long get_sum(int i, int j) {
    if (i > j) return 0;
    return prefix_sum[j+1] - prefix_sum[i];
}

long long solve(int i, int j) {
    if (i > j) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    long long max_val = 0;
    long long current_sum = get_sum(i, j);

    for (int k = i; k <= j; ++k) {
        // k is the last element removed in range [i, j]
        // It accumulates sum of [i, j]
        // And adds it to score
        // Left part [i, k-1] is removed first
        // Right part [k+1, j] is removed first
        
        long long val = solve(i, k-1) + solve(k+1, j) + current_sum;
        if (val > max_val) {
            max_val = val;
        }
    }

    return dp[i][j] = max_val;
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    // Read input array
    // Format: N then elements? Or just elements?
    // Prompt: gems = [3, 1, 5]
    // I'll assume standard competitive programming input: N then N integers.
    // Or read until EOF.
    // I'll try reading N first. If fail, read line.
    
    // Let's assume input format:
    // N
    // a1 a2 ... an
    
    if (!(cin >> N)) return 0;
    gems.resize(N);
    for (int i = 0; i < N; ++i) cin >> gems[i];

    // Init prefix sum
    prefix_sum[0] = 0;
    for (int i = 0; i < N; ++i) {
        prefix_sum[i+1] = prefix_sum[i] + gems[i];
    }

    // Init DP
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            dp[i][j] = -1;

    cout << solve(0, N-1) << endl;

    return 0;
}
