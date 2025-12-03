#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const long long INF = 1e18;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Solves x = a (mod m)
struct Congruence {
    long long a, m;
};

Congruence merge(Congruence c1, Congruence c2) {
    if (c1.m == -1 || c2.m == -1) return {-1, -1};
    
    long long g, x, y;
    g = extended_gcd(c1.m, c2.m, x, y);
    
    if ((c2.a - c1.a) % g != 0) return {-1, -1};
    
    long long lcm = (c1.m / g) * c2.m; // Be careful of overflow? m <= 2000. LCM fits in long long.
    
    // k * m1 = a2 - a1 (mod m2)
    // k * (m1/g) = (a2 - a1)/g (mod m2/g)
    
    long long target = (c2.a - c1.a) / g;
    long long mod = c2.m / g;
    
    // x is inverse of m1/g mod m2/g? No, x is from extended_gcd(m1, m2).
    // m1*x + m2*y = g
    // m1*x = g (mod m2) -> (m1/g)*x = 1 (mod m2/g)
    // So x is the modular inverse.
    
    long long k = (target % mod * x % mod) % mod;
    if (k < 0) k += mod;
    
    long long res_a = (c1.a + k * c1.m) % lcm;
    if (res_a < 0) res_a += lcm;
    
    return {res_a, lcm};
}

int N_units, M_nodes;
vector<int> starts;
vector<vector<int>> adj; // adj[unit][node] -> next_node

// Precomputed info
// first_visit[unit][node] = time of first visit, or -1
// cycle_len[unit] = length of cycle reachable from start, or 0
// in_cycle[unit][node] = is node in the cycle?
int first_visit[2005][2005];
int cycle_len[2005];
bool in_cycle[2005][2005];

void analyze(int u_idx) {
    int curr = starts[u_idx];
    vector<int> path;
    vector<int> visited(M_nodes, -1);
    
    int t = 0;
    while (visited[curr] == -1) {
        visited[curr] = t;
        path.push_back(curr);
        first_visit[u_idx][curr] = t;
        curr = adj[u_idx][curr];
        t++;
    }
    
    // Cycle detected
    int entry_time = visited[curr];
    int cycle_size = t - entry_time;
    cycle_len[u_idx] = cycle_size;
    
    for (int i = entry_time; i < t; ++i) {
        in_cycle[u_idx][path[i]] = true;
    }
    
    // For nodes NOT in the path, they are unreachable (-1).
    // But wait, the graph might have other components.
    // But the unit starts at `starts[u_idx]`. It can only reach nodes in its component.
    // So we only care about reachable nodes.
    // `first_visit` is initialized to -1.
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N_units >> M_nodes)) return 0;
    
    starts.resize(N_units);
    for (int i = 0; i < N_units; ++i) cin >> starts[i];
    
    adj.resize(N_units, vector<int>(M_nodes));
    for (int i = 0; i < N_units; ++i) {
        for (int j = 0; j < M_nodes; ++j) {
            cin >> adj[i][j];
        }
    }
    
    // Init
    for (int i = 0; i < N_units; ++i) {
        for (int j = 0; j < M_nodes; ++j) {
            first_visit[i][j] = -1;
            in_cycle[i][j] = false;
        }
        analyze(i);
    }
    
    long long min_total_steps = INF;
    
    for (int target = 0; target < M_nodes; ++target) {
        // Check reachability
        bool possible = true;
        long long fixed_time = -1;
        long long max_min_time = 0;
        
        Congruence combined = {0, 1}; // x = 0 (mod 1) -> any integer
        
        for (int i = 0; i < N_units; ++i) {
            if (first_visit[i][target] == -1) {
                possible = false;
                break;
            }
            
            long long t = first_visit[i][target];
            max_min_time = max(max_min_time, t);
            
            if (in_cycle[i][target]) {
                // t_final = t + k * cycle_len
                // t_final = t (mod cycle_len)
                combined = merge(combined, {t % cycle_len[i], (long long)cycle_len[i]});
                if (combined.m == -1) {
                    possible = false;
                    break;
                }
            } else {
                // Fixed time
                if (fixed_time != -1 && fixed_time != t) {
                    possible = false;
                    break;
                }
                fixed_time = t;
            }
        }
        
        if (!possible) continue;
        
        long long ans;
        if (fixed_time != -1) {
            // Verify fixed time against cyclic constraints
            if (combined.m != -1) {
                if (fixed_time % combined.m != combined.a) {
                    continue;
                }
            }
            // Verify fixed time >= max_min_time (should be true if valid)
            if (fixed_time < max_min_time) continue; // Should not happen if logic correct
            ans = fixed_time;
        } else {
            // Only cyclic constraints
            // We have t = A (mod M)
            // We need smallest t >= max_min_time
            long long A = combined.a;
            long long M = combined.m;
            
            // t = A + k*M >= max_min_time
            // k*M >= max_min_time - A
            // k >= (max_min_time - A) / M
            long long diff = max_min_time - A;
            long long k = 0;
            if (diff > 0) {
                k = (diff + M - 1) / M;
            }
            ans = A + k * M;
        }
        
        min_total_steps = min(min_total_steps, ans);
    }
    
    if (min_total_steps == INF) cout << -1 << endl;
    else cout << min_total_steps << endl;
    
    return 0;
}
