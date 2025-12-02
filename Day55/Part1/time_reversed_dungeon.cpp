#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int u;
    int time;
    int k;
};

bool solve_time_reversed_dungeon(int n, vector<vector<int>> edges, vector<int> t, int start, int target, int K) {
    vector<vector<int>> adj(n), rev_adj(n);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        rev_adj[e[1]].push_back(e[0]); // Reverse edge for rewind logic
    }

    // dist[u][k] = min time to reach u with k rewinds remaining
    vector<vector<int>> min_time(n, vector<int>(K + 1, 1e9));
    queue<State> q;

    // Initial check: Start room timer
    if (t[start] <= 0) return false;

    min_time[start][K] = 0;
    q.push({start, 0, K});

    while (!q.empty()) {
        auto [u, time, k] = q.front();
        q.pop();

        if (u == target) return true;

        if (time > min_time[u][k]) continue;

        int next_time = time + 1;

        // 1. Normal Move
        for (int v : adj[u]) {
            if (next_time < t[v]) { // Check survival
                if (next_time < min_time[v][k]) {
                    min_time[v][k] = next_time;
                    q.push({v, next_time, k});
                }
            }
        }

        // 2. Rewind Move (uses reverse edges as forward edges)
        if (k > 0) {
            for (int v : rev_adj[u]) {
                if (next_time < t[v]) { // Check survival
                    if (next_time < min_time[v][k - 1]) {
                        min_time[v][k - 1] = next_time;
                        q.push({v, next_time, k - 1});
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    // Test Case 1: Normal path blocked by timer, Rewind allows alternate path?
    // 0 -> 1 -> 2. t=[10, 1, 10].
    // 0->1 takes 1 sec. Arrive at 1 at t=1. t[1]=1. 1 <= 0? No, strictly less? "mencapai 0 saat Anda masuk".
    // If t[i] counts down, arriving at time T means remaining is t[i] - T.
    // Condition: t[i] - T > 0 => T < t[i].
    // So arriving at 1 at time 1. Remaining: 1 - 1 = 0. Dead.
    // Need rewind.
    // Edge 2->0 exists? No.
    // Let's make a case where rewind helps.
    // 0 -> 1 (timer 10). 1 -> 2 (timer 10).
    // Edge 1 -> 0 exists.
    // Rewind at 0: Use 1->0 as 0->1.
    
    // Case:
    // 0 -> 1 (timer 2). 1 -> 2 (timer 10).
    // Path 0->1->2. Time at 1 is 1. t[1]=2. 2-1=1 > 0. OK.
    // Time at 2 is 2. t[2]=10. OK.
    
    // Case with Rewind needed:
    // 0 -> 1 (timer 1). Dead if normal.
    // Edge 1 -> 0 exists.
    // Rewind at 0: traverse 1->0 backwards (0->1).
    // Time 1. t[1]=1. Dead? 1-1=0. Still dead.
    // Rewind doesn't stop time, just opens edges.
    
    // Real Rewind Case:
    // 0 -> 2 (blocked). 0 -> 1 (ok).
    // But 1 has no path to Target.
    // However, there is an edge Target -> 1.
    // Normal: 0->1. Stuck.
    // Rewind at 1: Use Target->1 as 1->Target.
    // Reach Target!
    
    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {2, 1}}; // 0->1, 2->1
    vector<int> t = {10, 10, 10};
    int start = 0, target = 2;
    int K = 1;
    
    // 0->1 (time 1). At 1.
    // Rewind: 2->1 becomes 1->2.
    // 1->2 (time 2). At 2. Win.
    
    cout << "Test 1 (Expected 1/True): " << solve_time_reversed_dungeon(n, edges, t, start, target, K) << endl;

    // Test 2: No K
    cout << "Test 2 (Expected 0/False): " << solve_time_reversed_dungeon(n, edges, t, start, target, 0) << endl;

    return 0;
}
