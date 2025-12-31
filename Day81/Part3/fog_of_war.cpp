#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Max Flow (Dinic's Algorithm) to check node connectivity
const int INF = 1e9;

struct Edge {
    int to;
    int capacity;
    int flow;
    int rev; // index of reverse edge
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
        for (auto& edge : adj[v]) {
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
        while (int pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    int R, C, k;
    if (!(cin >> R >> C >> k)) return 0;

    vector<string> grid(R);
    int startR, startC, targetR, targetC;
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'S') {
                startR = i; startC = j;
            } else if (grid[i][j] == 'T') {
                targetR = i; targetC = j;
            }
        }
    }

    // Node splitting:
    // Each cell (r, c) becomes two nodes: In (u) and Out (u + total_cells)
    // Capacity of u_in -> u_out is 1 (except Start and Target? Start/Target cannot be blocked?)
    // Usually Start and Target are safe. So capacity INF for S and T.
    // Edges between adjacent cells: u_out -> v_in with capacity INF.
    
    int total_cells = R * C;
    int source = startR * C + startC; // S_in
    int sink = targetR * C + targetC + total_cells; // T_out
    
    // Adjust source/sink to be S_out and T_in?
    // Actually, standard node disjoint path:
    // S -> S_in -> S_out -> ... -> T_in -> T_out -> T
    // We want max flow from S_out to T_in?
    // Let's use S_in as source and T_out as sink, but make S and T internal capacities INF.
    
    adj.assign(2 * total_cells, vector<Edge>());
    level.resize(2 * total_cells);
    ptr.resize(2 * total_cells);

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] == '#') continue; // Wall in Fog Map (assumed reliable? No, problem says Fog lies)
            // Wait, if Fog says Wall, it might be Empty.
            // If Fog says Empty, it might be Wall.
            // Adversary wants to BLOCK.
            // So he turns Empty -> Wall.
            // He won't turn Wall -> Empty (that helps us).
            // So we only care about the "Empty" cells in the Fog Map.
            // We check if blocking k of them disconnects S and T.
            // So we only build graph on "Empty" cells (including S and T).
            
            int u_in = r * C + c;
            int u_out = u_in + total_cells;
            
            // Internal node capacity
            int cap = 1;
            if ((r == startR && c == startC) || (r == targetR && c == targetC)) {
                cap = INF; // Cannot block start or target
            }
            add_edge(u_in, u_out, cap);

            // Edges to neighbors
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    if (grid[nr][nc] != '#') {
                        int v_in = nr * C + nc;
                        add_edge(u_out, v_in, INF);
                    }
                }
            }
        }
    }

    int max_flow = dinic(source, sink);

    // If max_flow > k, then we have > k node-disjoint paths.
    // Adversary can block at most k nodes.
    // So at least 1 path remains.
    if (max_flow > k) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
