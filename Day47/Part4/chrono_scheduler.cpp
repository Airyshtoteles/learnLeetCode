#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Attack {
    long long time;
    long long damage;

    bool operator<(const Attack& other) const {
        return time < other.time;
    }
};

long long solveChronoScheduler(int n, long long d, long long c, vector<Attack>& attacks) {
    sort(attacks.begin(), attacks.end());

    vector<long long> times(n);
    vector<long long> damages(n);
    for (int i = 0; i < n; ++i) {
        times[i] = attacks[i].time;
        damages[i] = attacks[i].damage;
    }

    vector<long long> prefix_damage(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix_damage[i + 1] = prefix_damage[i] + damages[i];
    }

    auto get_range_damage = [&](int start_idx, int end_idx) {
        if (start_idx >= end_idx) return 0LL;
        return prefix_damage[end_idx] - prefix_damage[start_idx];
    };

    vector<long long> dp(n + 1, 0);

    for (int i = n - 1; i >= 0; --i) {
        // cout << "Processing " << i << endl;
        // Option 1: Take the hit
        long long take_hit = damages[i] + dp[i + 1];

        // Option 2: Use Shield
        long long start_time = times[i];
        long long end_active = start_time + d;
        long long end_cooldown = end_active + c;

        // Find first attack > end_active (upper_bound)
        auto it_shield = upper_bound(times.begin(), times.end(), end_active);
        int idx_after_shield = distance(times.begin(), it_shield);

        // Find first attack >= end_cooldown (lower_bound)
        auto it_cooldown = lower_bound(times.begin(), times.end(), end_cooldown);
        int idx_after_cooldown = distance(times.begin(), it_cooldown);

        long long forced_damage = get_range_damage(idx_after_shield, idx_after_cooldown);
        long long use_shield = forced_damage + dp[idx_after_cooldown];

        dp[i] = min(take_hit, use_shield);
    }

    return dp[0];
}

int main() {
    int N = 5;
    long long D = 3;
    long long C = 2;
    vector<Attack> Attacks = {
        {1, 10},
        {2, 20},
        {4, 10},
        {6, 50},
        {8, 5}
    };

    long long result = solveChronoScheduler(N, D, C, Attacks);
    cout << "Minimum Damage: " << result << endl;

    return 0;
}
