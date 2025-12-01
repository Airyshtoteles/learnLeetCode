#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

struct Guardian {
    double x, y;
    int p;
    double r;
};

int solveSpiritLink(int n, int k, const vector<Guardian>& guardians) {
    // adj[i] contains bitmask of guardians that i buffs
    vector<int> adj_mask(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            double dist = sqrt(pow(guardians[i].x - guardians[j].x, 2) + pow(guardians[i].y - guardians[j].y, 2));
            if (dist <= guardians[i].r) {
                adj_mask[i] |= (1 << j);
            }
        }
    }

    // dp[mask] = max power
    // We iterate by layer (popcount)
    map<int, int> current_layer;
    current_layer[0] = 0;

    for (int step = 0; step < k; ++step) {
        map<int, int> next_layer;
        for (auto const& [mask, val] : current_layer) {
            for (int u = 0; u < n; ++u) {
                if (!(mask & (1 << u))) {
                    // Calculate buffs u receives from mask
                    int buffs = 0;
                    for (int v = 0; v < n; ++v) {
                        if ((mask & (1 << v))) {
                            if (adj_mask[v] & (1 << u)) {
                                buffs++;
                            }
                        }
                    }

                    int new_val = val + guardians[u].p + buffs;
                    int new_mask = mask | (1 << u);

                    if (next_layer.find(new_mask) == next_layer.end() || new_val > next_layer[new_mask]) {
                        next_layer[new_mask] = new_val;
                    }
                }
            }
        }
        current_layer = next_layer;
    }

    int max_power = 0;
    for (auto const& [mask, val] : current_layer) {
        if (val > max_power) {
            max_power = val;
        }
    }
    return max_power;
}

int main() {
    int N = 3;
    int K = 3;
    vector<Guardian> Guardians = {
        {0, 0, 10, 10},
        {1, 0, 10, 0},
        {2, 0, 10, 0}
    };

    int result = solveSpiritLink(N, K, Guardians);
    cout << "Maximum Power: " << result << endl;

    return 0;
}
