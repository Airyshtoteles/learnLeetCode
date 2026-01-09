#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

// Problem: Multi-Agent Dungeon With Hostile Merge
// K agents. Move simultaneously.
// If two agents meet (same node), they "merge".
// Merging typically is bad (loss of agent / worse position).
// Let's assume merge -> agents become 1 agent (loss of redundancy).
// Goal: Someone reaches Target.
// State: Sorted tuples of agent positions.
// K is small.
// Grid size N x M.
// BFS on State Space.

int main() {
    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;

    int inputSize = N * M;
    vector<int> starts(K);
    int Target = -1;

    for (int i = 0; i < K; ++i) {
        int r, c;
        cin >> r >> c;
        starts[i] = r * M + c;
    }

    int tr, tc;
    cin >> tr >> tc;
    Target = tr * M + tc;

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) cin >> grid[i];

    // BFS
    // State is sorted vector of positions.
    // Use set for visited.
    queue<vector<int>> q;
    
    sort(starts.begin(), starts.end());
    q.push(starts);
    
    set<vector<int>> visited;
    visited.insert(starts);

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!q.empty()) {
        vector<int> current_agents = q.front();
        q.pop();

        // Check winner
        for (int pos : current_agents) {
            if (pos == Target) {
                cout << "Possible" << endl;
                return 0;
            }
        }

        // Generate next states
        // All agents move simultaneously.
        // If K agents, and 4 moves each -> 4^K next states.
        // If K=3, 64 next states. Manageable.
        // Need to iterate combinations.
        
        int num_agents = current_agents.size();
        // Helper to recusively generate moves
        vector<vector<int>> next_states_raw;
        // ... (complex recursion needed)
        
        // Let's implement iterative approach for small K.
        // Since input might use K generic, but usually K <= 3 in these problems.
        // I'll assume K is small.
        
        // Actually, "Hostile Merge" usually implies we want to avoid it if possible?
        // Or is it forced?
        // "Jika dua agent bertemu -> hostile merge".
        // This happens AFTER move.
        // So we generate moves -> Check duplicates -> Merge duplicates.
        
        // Function to expand
        vector<vector<int>> current_level_moves;
        current_level_moves.push_back({}); // Start with empty move set
        
        for (int i = 0; i < num_agents; ++i) {
            int u = current_agents[i];
            int r = u / M;
            int c = u % M;
            
            vector<vector<int>> next_level_moves;
            
            for (const auto& partial : current_level_moves) {
                for (int dir = 0; dir < 4; ++dir) {
                    int nr = r + dr[dir];
                    int nc = c + dc[dir];
                    
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '#') {
                        vector<int> next_partial = partial;
                        next_partial.push_back(nr * M + nc);
                        next_level_moves.push_back(next_partial);
                    }
                }
            }
            current_level_moves = next_level_moves;
        }
        
        for (auto& next_pos_list : current_level_moves) {
            // Process merges (sort and unique)
            if (next_pos_list.size() != num_agents) continue; // Should allow stuck agents? Problem typically assumes valid moves.
            // If an agent has no valid move, does the whole team die? Or just that agent?
            // "Agent bergerak simultan". If one stuck, typically invalid state for team.
            
            sort(next_pos_list.begin(), next_pos_list.end());
            next_pos_list.erase(unique(next_pos_list.begin(), next_pos_list.end()), next_pos_list.end());
            
            if (visited.find(next_pos_list) == visited.end()) {
                visited.insert(next_pos_list);
                q.push(next_pos_list);
            }
        }
    }

    cout << "Impossible" << endl;

    return 0;
}
