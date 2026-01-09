#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Problem: Dungeon With Shrinking State Space
// Grid N x M.
// Every step, 1 random cell becomes forbidden.
// Max blocks B.
// Goal: Certainty of reaching Target.
// Strategy: Can we reach Target before it gets blocked (or path cut)?
// Condition: Shortest Path L. If L <= steps_until_impossible?
// If B is small, we just need L <= safe_limit.
// But blocks are adversarial/random.
// If Target is blocked, game over.
// Can Target be blocked? "Satu sel acak menjadi terlarang".
// If Target is picked, we lose.
// Unless Target is immune? Usually Start/Target immune.
// Assume Start/Target immune.
// We need to bypass B blocked cells.
// Connectivity: If Node Connectivity (Start -> Target) > B, we can survive any B blocks?
// Not exactly. Time aspect: blocks happen sequentially.
// But if connectivity > B, there are > B disjoint paths.
// Even if they block optimally (worst case), they can only cut B paths.
// So if Connect > B, we win.
// This is rigorous.
// Max Flow with vertex capacities = 1.
// Source = Neighbors of Start. Sink = Neighbors of Target.
// Start/Target infinite capacity/immune.
// Intermediate nodes capacity 1.
// If MaxFlow > B, "Possible".
// Note: This assumes blocks are placed *anywhere* (worst case).
// "Random" with "Certainty" implies satisfying Worst Case.

struct Edge {
    int to;
    int capacity;
    int flow;
    int rev;
};

vector<vector<Edge>> adj;
vector<int> level;
vector<int> ptr;

void add_edge(int from, int to, int cap) {
    adj[from].push_back({to, cap, 0, (int)adj[to].size()});
    adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const auto& edge : adj[v]) {
            if (edge.capacity - edge.flow > 0 && level[edge.to] == -1) {
                level[edge.to] = level[v] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int v, int t, int pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
        auto& edge = adj[v][cid];
        int tr = edge.to;
        if (level[v] + 1 != level[tr] || edge.capacity - edge.flow == 0) continue;
        int push = dfs(tr, t, min(pushed, edge.capacity - edge.flow));
        if (push == 0) continue;
        edge.flow += push;
        adj[tr][edge.rev].flow -= push;
        return push;
    }
    return 0;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(s, t, 1e9)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    int N, M, B;
    if (!(cin >> N >> M >> B)) return 0;

    int StartR, StartC, TargetR, TargetC;
    cin >> StartR >> StartC >> TargetR >> TargetC;

    // Node split for vertex capacity:
    // In-node: u, Out-node: u + NM
    // Capacity u -> u+NM is 1.
    // Neighbor u_out -> v_in is Inf.
    // Start and Target have Inf internal capacity (immune).

    int num_cells = N * M;
    int S = StartR * M + StartC;
    int T = TargetR * M + TargetC;

    // Source S_out, Sink T_in?
    // Actually standard vertex disjoint:
    // Split all nodes i into i_in and i_out. Edge i_in -> i_out cap 1.
    // Start and Target: cap Inf.
    // Adjacency u, v: u_out -> v_in cap Inf.
    
    int total_nodes = 2 * num_cells;
    adj.resize(total_nodes);
    level.resize(total_nodes);
    ptr.resize(total_nodes);

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            int u = r * M + c;
            int u_in = u;
            int u_out = u + num_cells;

            // Internal capacity
            if (u == S || u == T) {
                add_edge(u_in, u_out, 1e9);
            } else {
                add_edge(u_in, u_out, 1);
            }

            // Neighbors
            int dr[] = {0, 0, 1, -1};
            int dc[] = {1, -1, 0, 0};
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                    int v = nr * M + nc;
                    int v_in = v;
                    // u_out -> v_in
                    add_edge(u_out, v_in, 1e9);
                }
            }
        }
    }

    int max_paths = dinic(S, T + num_cells); // Flow from Start_in to Target_out

    if (max_paths > B) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
