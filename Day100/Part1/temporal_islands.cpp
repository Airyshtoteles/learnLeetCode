#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem 1: Temporal Island Connectivity
// Logic:
// maintain DSU of active cells.
// Track 'birth_time' of each component.
// When a component is created (single cell), birth = t.
// When two components merge, new component birth = t.
// We need to count components with birth_time <= t - K.
// Use a Fenwick Tree (BIT) to store frequencies of birth_times.
// Max time T? If T is large, compress. If T is roughly Q, direct indexing.

const int MAX_T = 200005; // Assume T <= 2*10^5 or compress

struct Fenwick {
    vector<int> tree;
    int n;
    Fenwick(int size) : n(size), tree(size + 1, 0) {}
    void add(int idx, int val) {
        idx++; // 1-based
        for(; idx <= n; idx += idx & -idx) tree[idx] += val;
    }
    int query(int idx) {
        idx++;
        int sum = 0;
        for(; idx > 0; idx -= idx & -idx) sum += tree[idx];
        return sum;
    }
};

struct DSU {
    vector<int> parent;
    vector<int> birth_time;
    Fenwick* ft;
    
    DSU(int n, Fenwick* f) : parent(n), birth_time(n, -1), ft(f) {
        for(int i=0; i<n; ++i) parent[i] = i;
    }
    
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    
    // Activate a new cell as a new component
    void activate(int i, int t) {
        birth_time[i] = t;
        ft->add(t, 1); // Add one component born at t
    }
    
    void unite(int i, int j, int t) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            // Remove old birth times
            ft->add(birth_time[root_i], -1);
            ft->add(birth_time[root_j], -1);
            
            // Merge
            parent[root_i] = root_j;
            birth_time[root_j] = t; // Reset timer to now
            
            // Add new birth time
            ft->add(t, 1);
        }
    }
};

int main() {
    int N, M, K, Q;
    if (!(cin >> N >> M >> K >> Q)) return 0;
    
    vector<tuple<int, int, int>> queries(Q);
    vector<int> times;
    for(int i=0; i<Q; ++i) {
        int t, r, c; cin >> t >> r >> c;
        queries[i] = {t, r, c};
        times.push_back(t);
    }
    
    // Time compression if needed
    sort(times.begin(), times.end());
    times.erase(unique(times.begin(), times.end()), times.end());
    
    auto get_time_idx = [&](int t) {
        return lower_bound(times.begin(), times.end(), t) - times.begin();
    };
    
    Fenwick ft(times.size() + 5);
    DSU dsu(N * M, &ft);
    
    vector<vector<bool>> grid(N, vector<bool>(M, false));
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    for(const auto& q : queries) {
        int t, r, c;
        tie(t, r, c) = q;
        int t_idx = get_time_idx(t);
        
        // 0-based coords assume inputs are? usually 1-based in CP, standardizing to 0-based
        // If fail, check constraints
        // Assume 0-based for internal logic. 
        // Adjust if input is 1-based (usually is).
        // Let's assume input r, c are 0-based or we shift. 
        // For safety, let's use map or check N.
        // If input R=N, then 1-based.
        // Let's assume 0-indexed for simplicity or handle both by checking bounds?
        // Standard is 1. so strict R--; C--;
        // BUT better safe:
        // Input usually 1-based.
        r--; c--; 
        
        if (r < 0 || r >= N || c < 0 || c >= M) continue; 
        
        if (!grid[r][c]) {
            grid[r][c] = true;
            int u = r * M + c;
            dsu.activate(u, t_idx);
            
            for(int k=0; k<4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr >=0 && nr < N && nc >=0 && nc < M && grid[nr][nc]) {
                    int v = nr * M + nc;
                    dsu.unite(u, v, t_idx);
                }
            }
        }
        
        // Query: Count components with birth_time <= t - K
        // We stored t_idx in Fenwick.
        // We need real time logic.
        // We need to sum up counts for all `idx` such that times[idx] <= t - K.
        
        int target_time = t - K;
        if (target_time < times[0]) {
            cout << 0 << endl;
        } else {
            // Find rightmost index with time <= target_time
            auto it = upper_bound(times.begin(), times.end(), target_time);
            int valid_idx = distance(times.begin(), it) - 1;
            cout << ft.query(valid_idx) << endl;
        }
    }
    
    return 0;
}
