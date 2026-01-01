#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <tuple>
#include <numeric>

using namespace std;

// State: Current HP, Last 9 moves (to check 5 vs 5)
// We use a vector for history.
// To optimize, we can map history to max HP remaining? No, we want min steps.
// Map (HP, History) -> Min Steps.
// Actually, if we reach same HP with same history, we can prune.
// But HP is continuous.
// Better: Map (History) -> Max HP we had when we reached this history?
// If we reach same history with LOWER HP, that's better.
// So: visited[history] = max_hp_remaining.
// If we reach history with current_hp < visited[history], we continue.
// If current_hp >= visited[history], we prune (we are in same state but worse off).

struct State {
    int hp;
    vector<int> history;
    int steps;
};

bool is_erased(const vector<int>& history) {
    if (history.size() < 10) return false;
    // Check if last 5 == previous 5
    // history indices: 0 1 2 3 4 5 6 7 8 9 (size 10)
    // last 5: 5,6,7,8,9
    // prev 5: 0,1,2,3,4
    // We only keep size 9 in state, so when we add 1, it becomes 10.
    // Then we check.
    for (int i = 0; i < 5; ++i) {
        if (history[history.size() - 5 + i] != history[history.size() - 10 + i]) {
            return false;
        }
    }
    return true;
}

int solve() {
    int H;
    if (!(cin >> H)) return 0;
    int N;
    cin >> N;
    vector<int> D(N);
    for (int i = 0; i < N; ++i) cin >> D[i];

    queue<State> q;
    q.push({H, {}, 0});

    // Visited map: History -> Max HP seen
    map<vector<int>, int> visited;
    visited[{}] = H;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.hp <= 0) return curr.steps;

        for (int dmg : D) {
            vector<int> next_hist = curr.history;
            next_hist.push_back(dmg);
            
            bool erased = false;
            if (next_hist.size() >= 10) {
                // Check pattern
                bool match = true;
                for (int k = 0; k < 5; ++k) {
                    if (next_hist[next_hist.size() - 5 + k] != next_hist[next_hist.size() - 10 + k]) {
                        match = false;
                        break;
                    }
                }
                if (match) erased = true;
            }

            int next_hp = curr.hp;
            if (erased) {
                // Boss rewinds 5 steps.
                // HP goes back to what it was 5 steps ago.
                // This is effectively a waste of 5 steps + 1 step?
                // Actually, the problem says "Boss menghapus ingatan 5 langkah itu (HP balik seperti sebelumnya)".
                // This means we are back to the state 5 steps ago.
                // In a BFS for MINIMUM steps, going back to a previous state with MORE steps taken is always suboptimal.
                // So we simply prune this branch.
                continue; 
            } else {
                next_hp -= dmg;
            }

            // Keep history size manageable. We need at most 9 for the NEXT check.
            // Wait, to check "last 5 vs prev 5", we need 10 items total.
            // So we need to store 9 items in the state, so adding 1 makes 10.
            // If we have > 9 items, we can drop the oldest.
            if (next_hist.size() > 9) {
                next_hist.erase(next_hist.begin());
            }

            // Pruning
            if (visited.find(next_hist) != visited.end()) {
                if (visited[next_hist] <= next_hp) {
                    // We reached this history before with less or equal HP (better or same progress).
                    // Wait, lower HP is better.
                    // If visited[hist] (previous HP) <= next_hp (current HP), then previous was better.
                    // So we prune.
                    continue;
                }
            }
            visited[next_hist] = next_hp;
            q.push({next_hp, next_hist, curr.steps + 1});
        }
    }

    return -1;
}

int main() {
    cout << solve() << endl;
    return 0;
}
