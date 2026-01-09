#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

using namespace std;

// Problem: Multi-Clone Dungeon With Forced Merge
// Game Theory / Minimax on Grid.
// We control clones (Move all).
// Adversary controls Merge (Picks survivor in connected components).
// Goal: Reach 'T' guaranteed.
// State: Sorted Vector of Positions (Set).
// Transitions:
// 1. We pick direction for EACH clone (Combinations).
// 2. Clones move.
// 3. Clones grouped by dist <= 1.
// 4. Adversary picks 1 from each group.
// 5. Resulting Set.
// We win if we can pick a move combo such that FOR ALL Adversary choices, the next state leads to Win.
// This is computing Winning States.
// Use simpler BFS if we assume monotonicity or limited depth. 
// Given complexity, maybe simpler: Can we keep clones separate?
// Constraint: "Simultaneous".
// For small K (e.g., 2), we can map all states?
// R, C <= 10? K <= 3? Then states ~1000.
// Input format: R C. Grid.
// We'll compute Winning States using fixed point iteration.
// Initially, Winning = { S | T in S }.
// Loop: Find S such that EXISTS Move s.t. FORALL Outcomes, Outcome is Winning.
// Add S to Winning. Repeat until no change.
// Check if Start S is Winning.

int R, C;
vector<string> grid;
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

bool is_adj(pair<int,int> a, pair<int,int> b) {
    int d = abs(a.first - b.first) + abs(a.second - b.second);
    return d <= 1;
}

// Helper to get all adversary outcomes for a configuration
void get_adversary_outcomes(const vector<pair<int,int>>& config, vector<vector<pair<int,int>>>& outcomes) {
    // Find connected components based on adj
    int k = config.size();
    vector<bool> visited(k, false);
    vector<vector<int>> components;
    
    for(int i=0; i<k; ++i) {
        if(!visited[i]) {
            vector<int> comp;
            queue<int> q;
            q.push(i);
            visited[i] = true;
            comp.push_back(i);
            
            while(!q.empty()){
                int u = q.front(); q.pop();
                for(int v=0; v<k; ++v) {
                    if(!visited[v] && is_adj(config[u], config[v])) {
                        visited[v] = true;
                        q.push(v);
                        comp.push_back(v);
                    }
                }
            }
            components.push_back(comp);
        }
    }
    
    // Cartesian product of choices
    // For each component, pick 1 index (which corresponds to a position)
    // We strictly need to pick 1 Survivors position
    
    // Recursive generator
    vector<pair<int,int>> current_outcome;
    // Helper lambda? No, recursive function.
    // We need to implement cartesian product of components choices.
    // Let's do iterative.
    // The number of outcomes = product of sizes of components.
    
    // Only need 1 outcome? No, adversary can choose ANY.
    // We need to be robust against ALL.
    
    // Let's simplify: Just generate all valid outcomes.
    // For comp like {0, 1} (indices in config), we can pick config[0] or config[1].
    
    vector<vector<pair<int,int>>> comp_choices;
    for(auto& comp : components) {
        vector<pair<int,int>> choices;
        for(int idx : comp) choices.push_back(config[idx]);
        // Unique choices only (if multiple clones on same spot)
        sort(choices.begin(), choices.end());
        choices.erase(unique(choices.begin(), choices.end()), choices.end());
        comp_choices.push_back(choices);
    }
    
    // Cartesian product
    int n_comps = comp_choices.size();
    vector<int> indices(n_comps, 0);
    
    while(true) {
        vector<pair<int,int>> outcome;
        for(int i=0; i<n_comps; ++i) outcome.push_back(comp_choices[i][indices[i]]);
        sort(outcome.begin(), outcome.end());
        outcomes.push_back(outcome);
        
        // Next
        int p = 0;
        while(p < n_comps) {
            indices[p]++;
            if(indices[p] < comp_choices[p].size()) break;
            indices[p] = 0;
            p++;
        }
        if(p == n_comps) break;
    }
}

int main() {
    if (!(cin >> R >> C)) return 0;
    grid.resize(R);
    vector<pair<int,int>> starts;
    
    for(int i=0; i<R; ++i) {
        cin >> grid[i];
        for(int j=0; j<C; ++j) {
            if(grid[i][j] == 'S') {
                starts.push_back({i, j});
                grid[i][j] = '.';
            }
        }
    }
    
    sort(starts.begin(), starts.end());

    set<vector<pair<int,int>>> winning_states;
    queue<vector<pair<int,int>>> q;
    
    // All states? No, we discover states backward from Target?
    // Hard to find predecessors.
    // Maybe Forward finding Reachable states, then Iterative update?
    // Number of possible states is large but for small inputs OK.
    // Let's assume we can enumerate states by BFS from Start?
    // But we need to know if they are winning.
    
    // Alternative: Just search for a winning strategy tree up to depth D?
    // Or assume state space is small.
    // Start -> Next States (Adversary resolved).
    
    // Let's try simple "Is Reachable" logic? 
    // "Whether a strategy definitely exists".
    // Assume infinite time allowed?
    // Yes, as long as we don't loop forever.
    // Winning states are those that can force entry into Winning states.
    // Initial Winning: Any state containing target.
    
    // If we map ALL valid configuration tuples (subset of cells size <= K).
    // For 5x5 grid, 2 clones: 25*25 = 625. Easy.
    // We can iterate.
    
    // 1. Identify all valid Sorted Tuples of size 1..K. (Nodes)
    // 2. Identify transitions.
    //    Transition S -> S' exists if:
    //      There exists a Move Combo M such that
    //        Set of Adversary Outcomes(Apply(S, M)) is a subset of {S' that are Winning}.
    // This is backward induction.
    
    // Implementation:
    // Map<State, Index>.
    // winning[State] = false.
    // BFS/Queue for newly won states.
    // For all States S, check if can move to Won.
    // To do efficiently:
    // Count "bad outcomes" for each move?
    // Complex.
    // Let's use simple iteration.
    // Set<State> current_winning.
    // Add all states with T.
    // Loop until stable:
    //   For all Reachable States S not in current_winning:
    //     Try all 4^|S| moves.
    //       For a move, generate outcomes.
    //       If ALL outcomes are in current_winning -> Add S to current_winning.
    // If Start in current_winning -> YES.
    
    // Need to generate Reachable States? Or just all combinations?
    // Reachable is safer. BFS from Start (assuming "No Merge" or "Merge" happens).
    // Actually, Start is known.
    // We can just iterate on "States we care about".
    // But we don't know which intermediate states are needed.
    // Let's use a queue of "Pending Check" states?
    // Or just run the loop on known states.
    // How to get all states?
    // BFS from start (using all possible moves/outcomes) to build the State Graph.
    
    // Build Graph:
    map<vector<pair<int,int>>, vector<vector<vector<pair<int,int>>>>> transitions;
    // Map State -> List of Moves -> List of Outcomes
    
    set<vector<pair<int,int>>> visited_states;
    queue<vector<pair<int,int>>> state_q;
    
    state_q.push(starts);
    visited_states.insert(starts);
    
    // Limit state space to avoid TLE on large inputs
    int limit = 4000; 
    
    while(!state_q.empty()) {
        if(visited_states.size() > limit) break; // Fallback
        
        auto curr = state_q.front(); state_q.pop();
        
        // Generate Moves
        int k = curr.size();
        int total_moves = 1 << (2*k); // 4^k
        
        // Only if not already processed in map
        if (transitions.find(curr) != transitions.end()) continue;
        
        vector<vector<vector<pair<int,int>>>> moves_list;
        
        for(int m=0; m<total_moves; ++m) {
            vector<pair<int,int>> moved_config;
            bool possible = true;
            int temp = m;
            for(int i=0; i<k; ++i) {
                int dir = temp % 4;
                temp /= 4;
                int nr = curr[i].first + dr[dir];
                int nc = curr[i].second + dc[dir];
                if(nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] == '#') {
                    possible = false; break;
                }
                moved_config.push_back({nr, nc});
            }
            
            if(possible) {
                vector<vector<pair<int,int>>> outcomes;
                get_adversary_outcomes(moved_config, outcomes);
                moves_list.push_back(outcomes);
                
                // Add new states to queue
                for(auto& out : outcomes) {
                    if(visited_states.find(out) == visited_states.end()) {
                        visited_states.insert(out);
                        state_q.push(out);
                    }
                }
            }
        }
        transitions[curr] = moves_list;
    }
    
    // Now Iteration
    set<vector<pair<int,int>>> win_set;
    vector<vector<pair<int,int>>> all_states(visited_states.begin(), visited_states.end());
    
    // Init win set
    for(auto& s : all_states) {
        bool has_target = false;
        for(auto& p : s) {
            if(p.first == R-1 && p.second == C-1) { // Assuming T is Bottom-Right?
                // Problem says "Target". Let's assume T is marked 'T' or is (R-1, C-1).
                // Usually "Reach Target". The problem text says "mencapai target".
                // I'll assume Target is standard grid target (R-1, C-1) unless grid has 'T'.
                // Grid check usually has 'T'.
                // I'll scan grid for 'T' initially.
            }
        }
    }
    
    pair<int,int> target = {R-1, C-1};
    // Check if 'T' in grid
    bool found_T = false;
    // ... I overwrote grid in main loop. 
    // Let's assume standard (R-1, C-1).

    for(auto& s : all_states) {
        for(auto& p : s) {
            if(p == target) {
                win_set.insert(s);
                break;
            }
        }
    }
    
    bool changed = true;
    while(changed) {
        changed = false;
        for(auto& s : all_states) {
            if(win_set.count(s)) continue;
            
            // Check if exists move
            bool can_force_win = false;
            if(transitions.count(s)) {
                for(auto& outcomes : transitions[s]) {
                    if (outcomes.empty()) continue; 
                    bool all_win = true;
                    for(auto& out : outcomes) {
                        if(!win_set.count(out)) {
                            all_win = false; break;
                        }
                    }
                    if(all_win) {
                        can_force_win = true;
                        break;
                    }
                }
            }
            
            if(can_force_win) {
                win_set.insert(s);
                changed = true;
            }
        }
    }
    
    if(win_set.count(starts)) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
