#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int solve_infinite_jump(int N, vector<int>& jump) {
    if (N == 0) return 0;
    if (N == 1) return 0;
    
    // Map jump value to list of indices
    map<int, vector<int>> jump_groups;
    for (int i = 0; i < N; ++i) {
        jump_groups[jump[i]].push_back(i);
    }
    
    vector<int> dist(N, -1);
    queue<int> q;
    
    dist[0] = 0;
    q.push(0);
    
    // To avoid re-processing warp groups
    map<int, bool> group_visited;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        if (u == N - 1) return dist[u];
        
        // 1. Jump forward/backward
        int forward = u + jump[u];
        int backward = u - jump[u];
        
        if (forward < N && dist[forward] == -1) {
            dist[forward] = dist[u] + 1;
            q.push(forward);
        }
        
        if (backward >= 0 && dist[backward] == -1) {
            dist[backward] = dist[u] + 1;
            q.push(backward);
        }
        
        // 2. Warp
        int val = jump[u];
        if (!group_visited[val]) {
            group_visited[val] = true;
            for (int v : jump_groups[val]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
            // Clear the vector to save memory/time? 
            // Not strictly necessary with group_visited check, but good practice.
            jump_groups[val].clear();
        }
    }
    
    return -1;
}

int main() {
    // Example 1
    // 0 -> 4.
    // Jumps: [1, 2, 3, 4, 5]
    // 0 (jump 1) -> 1.
    // 1 (jump 2) -> 3.
    // 3 (jump 4) -> 7 (out).
    // Wait, standard jumps.
    // 0 -> 1 (cost 1).
    // 1 -> 3 (cost 1).
    // 3 -> 3+4=7 (out).
    // 3 -> 3-4=-1 (out).
    // Can we reach 4?
    // Let's try a warp case.
    // [2, 5, 2, 1, 2]
    // 0 (val 2). Warp to 2 (val 2) or 4 (val 2).
    // 0 -> 4 cost 1.
    vector<int> J1 = {2, 5, 2, 1, 2};
    cout << "Test 1: " << solve_infinite_jump(5, J1) << endl;
    
    // Example 2
    // [1, 1, 1, 1]
    // 0 -> 1 (jump) or 0 -> 1,2,3 (warp).
    // 0 -> 3 cost 1.
    vector<int> J2 = {1, 1, 1, 1};
    cout << "Test 2: " << solve_infinite_jump(4, J2) << endl;
    
    return 0;
}
