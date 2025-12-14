#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Unit {
    int id;
    int speed;
};

bool compareUnits(const Unit& a, const Unit& b) {
    if (a.speed != b.speed) {
        return a.speed > b.speed;
    }
    return a.id < b.id;
}

const long long INF = 2e18; // Larger than K max

int main() {
    int N;
    long long K;
    if (cin >> N >> K) {
        vector<Unit> units(N);
        for (int i = 0; i < N; ++i) {
            units[i].id = i;
            cin >> units[i].speed;
        }

        sort(units.begin(), units.end(), compareUnits);

        // dp[i][j] = min cost to process first i units with j improvements
        vector<vector<long long>> dp(N + 1, vector<long long>(N + 1, INF));

        dp[0][0] = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (dp[i][j] == INF) continue;

                long long current_cost = dp[i][j];

                // Option 1: Segment length 0 (u_i is loser, no winners)
                if (current_cost < dp[i + 1][j]) {
                    dp[i + 1][j] = current_cost;
                }

                // Option 2: Segment length len > 0
                long long segment_cost = 0;
                for (int len = 1; i + len < N; ++len) {
                    int winner_idx = i + len;
                    
                    long long required_speed = units[i].speed;
                    if (units[winner_idx].id > units[i].id) {
                        required_speed++;
                    }

                    long long diff = required_speed - units[winner_idx].speed;
                    // diff is always >= 0 because sorted
                    
                    segment_cost += diff;

                    if (current_cost + segment_cost > K) break;

                    if (current_cost + segment_cost < dp[i + len + 1][j + len]) {
                        dp[i + len + 1][j + len] = current_cost + segment_cost;
                    }
                }
            }
        }

        int max_improved = 0;
        for (int j = 0; j <= N; ++j) {
            if (dp[N][j] <= K) {
                max_improved = j;
            }
        }

        cout << max_improved << endl;
    }
    return 0;
}
