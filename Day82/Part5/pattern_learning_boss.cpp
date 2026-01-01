#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    long long H;
    int n;
    if (!(cin >> H >> n)) return 0;

    vector<long long> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    // BFS on state = (current HP, sequence of last 3 damages)
    // To minimize the number of attacks, use 0-1 BFS or Dijkstra.

    // State: HP value
    // We can keep the HP and track the last 3 damage values to avoid patterns.

    typedef tuple<long long, vector<long long>> State; // (HP, last3damages)

    queue<State> q;
    map<pair<long long, vector<long long>>, long long> dist;

    vector<long long> empty_seq;
    q.push({H, empty_seq});
    dist[{H, empty_seq}] = 0;

    long long ans = LLONG_MAX;

    while (!q.empty()) {
        auto [hp, seq] = q.front();
        q.pop();

        long long attacks = dist[{hp, seq}];

        if (hp <= 0) {
            ans = min(ans, attacks);
            continue;
        }

        // Try each damage
        for (long long dmg : d) {
            // Check if this damage would create a forbidden pattern
            vector<long long> new_seq = seq;
            new_seq.push_back(dmg);

            bool forbidden = false;
            if (new_seq.size() >= 6) {
                // Check if last 3 match the 3 before that
                if (new_seq[new_seq.size() - 1] == new_seq[new_seq.size() - 4] &&
                    new_seq[new_seq.size() - 2] == new_seq[new_seq.size() - 5] &&
                    new_seq[new_seq.size() - 3] == new_seq[new_seq.size() - 6]) {
                    forbidden = true;
                }
            }

            if (!forbidden) {
                long long new_hp = hp - dmg;
                if (new_seq.size() > 3) {
                    new_seq.erase(new_seq.begin());
                }

                long long new_attacks = attacks + 1;

                if (dist.find({new_hp, new_seq}) == dist.end() ||
                    dist[{new_hp, new_seq}] > new_attacks) {
                    dist[{new_hp, new_seq}] = new_attacks;
                    q.push({new_hp, new_seq});
                }
            }
        }
    }

    if (ans == LLONG_MAX) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
