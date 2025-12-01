#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <tuple>

using namespace std;

struct Enemy {
    int spawn_time;
    int x, y;
    int hp;
};

struct Skills {
    int d1, c1;
    int d2, c2;
    int d3, c3, R;
};

int T_limit;
Skills skills;
vector<Enemy> enemies;
int n_enemies;

// Memoization: map<tuple<int, int, int, int, vector<int>>, int>
// Key: t, cd1, cd2, cd3, hps
// Using map is slow, but for small N/T it might pass.
// For C++, vector<int> as key is fine.
map<tuple<int, int, int, int, vector<int>>, int> memo;

int solve(int t, int cd1, int cd2, int cd3, vector<int> hps) {
    if (t >= T_limit) return 0;

    tuple<int, int, int, int, vector<int>> state = {t, cd1, cd2, cd3, hps};
    if (memo.count(state)) return memo[state];

    vector<int> active_indices;
    for (int i = 0; i < n_enemies; ++i) {
        if (enemies[i].spawn_time <= t && hps[i] > 0) {
            active_indices.push_back(i);
        }
    }

    int res = 0;

    // Option 0: Wait
    res = max(res, solve(t + 1, max(0, cd1 - 1), max(0, cd2 - 1), max(0, cd3 - 1), hps));

    if (active_indices.empty()) {
        return memo[state] = res;
    }

    // Option 1: Slash
    if (cd1 == 0) {
        for (int idx : active_indices) {
            vector<int> next_hps = hps;
            next_hps[idx] -= skills.d1;
            int kills = (next_hps[idx] <= 0) ? 1 : 0;
            if (next_hps[idx] < 0) next_hps[idx] = 0;

            res = max(res, kills + solve(t + 1, skills.c1, max(0, cd2 - 1), max(0, cd3 - 1), next_hps));
        }
    }

    // Option 2: Pierce (Try all pairs)
    if (cd2 == 0) {
        if (active_indices.size() >= 2) {
            for (size_t i = 0; i < active_indices.size(); ++i) {
                for (size_t j = i + 1; j < active_indices.size(); ++j) {
                    int idx1 = active_indices[i];
                    int idx2 = active_indices[j];
                    
                    vector<int> next_hps = hps;
                    next_hps[idx1] -= skills.d2;
                    next_hps[idx2] -= skills.d2;
                    
                    int kills = 0;
                    if (next_hps[idx1] <= 0) kills++;
                    if (next_hps[idx2] <= 0) kills++;
                    
                    if (next_hps[idx1] < 0) next_hps[idx1] = 0;
                    if (next_hps[idx2] < 0) next_hps[idx2] = 0;

                    res = max(res, kills + solve(t + 1, max(0, cd1 - 1), skills.c2, max(0, cd3 - 1), next_hps));
                }
            }
        } else {
            // Single target
             for (int idx : active_indices) {
                vector<int> next_hps = hps;
                next_hps[idx] -= skills.d2;
                int kills = (next_hps[idx] <= 0) ? 1 : 0;
                if (next_hps[idx] < 0) next_hps[idx] = 0;

                res = max(res, kills + solve(t + 1, max(0, cd1 - 1), skills.c2, max(0, cd3 - 1), next_hps));
            }
        }
    }

    // Option 3: Shockwave
    if (cd3 == 0) {
        vector<int> next_hps = hps;
        int kills = 0;
        bool hit_any = false;

        for (int idx : active_indices) {
            int dist = abs(enemies[idx].x) + abs(enemies[idx].y);
            if (dist <= skills.R) {
                next_hps[idx] -= skills.d3;
                if (next_hps[idx] <= 0) kills++;
                if (next_hps[idx] < 0) next_hps[idx] = 0;
                hit_any = true;
            }
        }

        if (hit_any) {
            res = max(res, kills + solve(t + 1, max(0, cd1 - 1), max(0, cd2 - 1), skills.c3, next_hps));
        }
    }

    return memo[state] = res;
}

int main() {
    T_limit = 5;
    skills = {10, 2, 15, 3, 5, 4, 2}; // d1, c1, d2, c2, d3, c3, R
    
    enemies = {
        {0, 0, 0, 20},
        {1, 0, 1, 10}
    };
    n_enemies = enemies.size();

    vector<int> initial_hps(n_enemies);
    for(int i=0; i<n_enemies; ++i) initial_hps[i] = enemies[i].hp;

    cout << "Max Kills: " << solve(0, 0, 0, 0, initial_hps) << endl;

    return 0;
}
