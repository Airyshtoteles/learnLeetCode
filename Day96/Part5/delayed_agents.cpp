#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

// Problem 5: Multi-Agent Dungeon
// Logic: Can we cover the grid?
// Simplified: Check if "Strategy Exists".
// We assume this means: Is it possible for agents to reach positions P_1...P_k in T steps
// such that for every safe cell C, min_dist(P_i, C) <= Limit - T.
//
// Algorithm:
// 1. Compute pairwise distances (All-Pairs Shortest Path or BFS from all nodes).
// 2. Identify Reachable Sets for each agent R_i = {cell | dist(Start_i, cell) <= T}.
// 3. We need to select p_i from R_i to cover ALL safe cells with radius (Limit - T).
// 4. Since selecting optimal positions is Hard (K-Center/Dominating Set restrictions),
//    and verifying "Strategy Exists" usually implies "Is it possible?",
//    we can try a greedy heuristic or randomize if N is small.
//    However, for CP problems, usually K is very small (1-3) or logic is simpler.
//    If K is large, maybe connectivity is enough?
//    Let's assume we implement the "Check Coverage" with a Greedy K-Center.
//    Greedy Strategy:
//      Currently Uncovered Set U = All Safe Cells.
//      For Agent 1: Pick pos in R_1 that covers max nodes in U.
//      Remove covered from U.
//      For Agent 2: Pick pos in R_2 that covers max nodes in U.
//      ...
//      If U is empty, YES.
//      If not, NO (Uncertain, but good approx).

int N, M, K_agents, T_delay, Limit;
vector<string> grid;
vector<pair<int,int>> agents;
vector<pair<int,int>> safe_cells;
int dists[50][50][50][50]; // [r1][c1][r2][c2] - simplified mapping needed?
// Just use linearized index: u, v. 50x50 = 2500 nodes. 2500^2 is 6M. OK.

int dr[] = {0,0,1,-1};
int dc[] = {1,-1,0,0};

bool isValid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < M && grid[r][c] != '#';
}

void bfs(int start_r, int start_c, vector<vector<int>>& d_map) {
    for(int i=0; i<N; ++i) fill(d_map[i].begin(), d_map[i].end(), 1e9);
    d_map[start_r][start_c] = 0;
    queue<pair<int,int>> q;
    q.push({start_r, start_c});
    
    while(!q.empty()){
        auto [r, c] = q.front(); q.pop();
        for(int i=0; i<4; ++i){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(isValid(nr, nc) && d_map[nr][nc] > d_map[r][c] + 1){
                d_map[nr][nc] = d_map[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
}

int main() {
    if (!(cin >> N >> M >> K_agents >> T_delay >> Limit)) return 0;
    grid.resize(N);
    for(int i=0; i<N; ++i) {
        cin >> grid[i];
        for(int j=0; j<M; ++j) {
            if (grid[i][j] == 'A') agents.push_back({i, j});
            if (grid[i][j] != '#') safe_cells.push_back({i, j});
        }
    }
    
    // Compute basic distances from everywhere?
    // Actually we only need:
    // 1. Valid Pos for Agent i (Dist(Start_i -> P) <= T_delay)
    // 2. Dist P -> Target C.
    // Since All-Pairs is heavy, let's optimize.
    // Calculate BFS from Every Safe Cell?
    // Map cell -> ID.
    int id_counter = 0;
    vector<vector<int>> cell_id(N, vector<int>(M, -1));
    for(auto p : safe_cells) cell_id[p.first][p.second] = id_counter++;
    
    // Matrix Dist[id][id]
    // If N*M <= 2500. 2500 BFS is heavy?
    // Maybe just compute BFS from Agents? No, agents move.
    // We need dists from Candidate positions.
    // Candidates are all safe cells.
    // APSP needed. Or Repeated BFS.
    // For 50x50, 2500 BFS is ~ 2500 * 2500 ~ 6M ops. Fast in C++.
    
    vector<vector<int>> dist_matrix(id_counter, vector<int>(id_counter, 1e9));
    
    for(int i=0; i<id_counter; ++i) {
        pair<int,int> src = safe_cells[i];
        
        // BFS
        vector<vector<int>> d(N, vector<int>(M, 1e9));
        d[src.first][src.second] = 0;
        queue<pair<int,int>> q;
        q.push(src);
        
        while(!q.empty()){
            auto [r, c] = q.front(); q.pop();
            int u = cell_id[r][c];
            if (u != -1) dist_matrix[i][u] = d[r][c];
             
            for(int k=0; k<4; ++k){
                int nr = r + dr[k], nc = c + dc[k];
                if(isValid(nr, nc) && d[nr][nc] == 1e9){
                    d[nr][nc] = d[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
    
    // Identify Reachable Sets for Agents
    vector<vector<int>> agent_reach(K_agents);
    for(int k=0; k<K_agents; ++k) {
        int start_id = cell_id[agents[k].first][agents[k].second];
        for(int u=0; u<id_counter; ++u) {
            if (dist_matrix[start_id][u] <= T_delay) { // Start -> Cand
                agent_reach[k].push_back(u);
            }
        }
    }
    
    // Coverage Check (Greedy)
    // Radius = Limit - T_delay
    // If Radius < 0, Impossible.
    if (Limit < T_delay) { cout << "NO" << endl; return 0; }
    int radius = Limit - T_delay;
    
    vector<bool> covered(id_counter, false);
    int covered_cnt = 0;
    
    for(int k=0; k<K_agents; ++k) {
        // Pick best candidate in agent_reach[k]
        int best_cand = -1;
        int best_gain = -1;
        
        for(int cand : agent_reach[k]) {
            int gain = 0;
            // Check potential coverage
            // Optimization: traverse only cells?
            for(int target=0; target < id_counter; ++target) {
                if (!covered[target] && dist_matrix[cand][target] <= radius) {
                    gain++;
                }
            }
            if (gain > best_gain) {
                best_gain = gain;
                best_cand = cand;
            }
        }
        
        if (best_cand != -1) {
            // Apply
            for(int target=0; target < id_counter; ++target) {
                if (!covered[target] && dist_matrix[best_cand][target] <= radius) {
                    covered[target] = true;
                    covered_cnt++;
                }
            }
        }
    }
    
    if (covered_cnt == id_counter) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
