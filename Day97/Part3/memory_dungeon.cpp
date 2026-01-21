#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <tuple>

using namespace std;

// Problem 3: Dungeon With Memory Loss
// At K steps, map changes, memory lost.
// But Manhattan Distance to Target is remembered.
// Worst-Case Minimum Steps.
//
// Logic:
// If "Traps can change position", and we only know Manhattan...
// The Adversary can place traps to BLOCK our best move.
// However, if we MUST follow logical steps:
// Strategy: "Greedy Descent on Manhattan".
// If we are at (r, c), dist D.
// Neighbors have dist D-1 or D+1.
// We want to move to D-1.
// If Adversary blocks ALL D-1 neighbors? We must move to D+1 or stay?
// Can Adversary block ALL neighbors? Depends on map density.
// But "Trap bisa berubah posisi" implies dynamic.
// If the Adversary can place traps ANYWHERE, they can box us in forever.
// Constraint: "Minimum langkah pasti".
// This implies the map has some static properties or limited traps?
// Or maybe "Mask changes", but the PATH exists?
//
// Let's interpret "Memory Loss" + "Manhattan":
// We know direction to target.
// We assume we can step towards it.
// Every K steps, we "forget" obstacles? No, layout changes.
//
// Let's implement a simulation:
// Pos P.
// While P != Target:
//   Move to best neighbor (closest to Target).
//   Cost++.
//   If Step % K == 0:
//      Adversary reshuffles.
//      Worst Case: The cell we Step INTO is a Trap?
//      Or the path ahead is blocked?
//
// "Inti: adversarial BFS".
// Let's assume the map is STATIC, but we FORGET the layout.
// So we re-discover.
// But "Traps can change position".
// If Traps shuffle, effectively the map is Random/Adversarial.
//
// If we play optimally, we pick a move that minimizes Worst-Case remaining distance?
// If Traps shuffle randomly, worst case is infinite loop.
//
// UNLESS: There is a Limit on Traps? Or Traps avoid Current Pos?
//
// Maybe the "Memory Loss" resets our "Visited" set?
// If we forget visited, we might cycle.
//
// Given "Day 97", maybe it's simpler:
// Compute Shortest Path on the grid.
// But assume every K steps, we deal with a delay?
//
// Alternative: "Minimax Shortest Path".
// Game:
// Player moves 1..K steps.
// Adversary moves traps.
//
// Can we model this as:
// Distance = Manhattan Distance + Penalties?
//
// Let's assume the question is: "What is the Shortest Path in a graph where edges change?"
// If edges change arbitrarily, impossible.
//
// Let's assume the User provided "Inti: adversarial BFS" creates the solution logic.
// Logic:
// BFS State `(u)`. Value `MaxDist(u)`.
// But we don't know the map?
//
// Valid Interpretation:
// "Memory Loss" means we only operate on LOCAL info (Neighbors).
// We pick neighbor with min Manhattan.
// If there are obstacles, we pick second best?
// "Worst case": We always forced to pick the WORST valid neighbor that is better than current?
// Or we are forced to backtrack?
//
// Let's go with:
// We start at S.
// We see neighbors. Some are Walls (Static?), some are Traps (Dynamic?).
// If Walls are static, Traps dynamic.
// Every K steps, Traps shuffle.
//
// If we can always make progress (Manhattan decreases), Steps = Manhattan.
// If blocked, detour.
//
// Given complexity and ambiguity, I will implement a "Guaranteed Path" logic on static map assuming fog of war.
// Actually, "Minimum langkah PASTI" (Guaranteed).
// If Traps move, we can't guarantee anything unless Traps are sparse.
//
// Let's assume the "Memory Loss" is the only constraint.
// Map is STATIC. But we forget the map every K steps.
// This means we can explore depth K. Then we reset Exploration.
// If Target is within K, we find it.
// If not, we move to the frontier of K, then "Forget".
// Then explore K again.
// To guarantee progress, we must move to a node `v` such that `RealDist(v, Target) < RealDist(Start, Target)`.
// Algorithm:
// 1. Calculate RealDist from Target (Reverse BFS).
// 2. From Start, can we verify which neighbor is better?
//    With "Memory Loss", we map local K-radius area.
//    We identify the node `v` in K-radius that minimizes Manhattan? No, we know Manhattan.
//    We identify node `v` at distance K (or less) that minimizes Real Dist?
//    No, we don't know Real Dist.
//    We only "Remember Manhattan".
//    So we move to a node `v` reachable in <= K steps that has Minimum Manhattan Dist.
//    Then we forget.
//    Then verify from `v`.
//    Repeat until Target.
//    Steps += Cost to reach `v` (BFS dist).
//
// Does this match "Adversarial"?
// If map is adversarial, Manhattan might be misleading (Local Minima).
// If we get stuck in Local Minima (Manhattan implies go Right, but Wall), and K is small, we might cycle.
// "Minimum langkah pasti (worst-case)".
// If we cycle, steps = Inf.
// Output -1.
//
// Algorithm:
// Current = Start. TotalSteps = 0.
// While Current != Target:
//    Run Local BFS from Current (Limit K).
//    Find reachable nodes R.
//    Pick `next` in R which minimizes `Manhattan(next, Target)`.
//    If multiple, pick one closest to Current? Or furthest?
//      Worst-case: We pick one that is ACTUALLY far in Real Distance?
//      But we control the move. We pick.
//      We pick `next` maximizing progress in Manhattan.
//      If `Manhattan(next) >= Manhattan(Current)`, we are stuck (Local Minima).
//      Return -1.
//    Move to `next`.
//    TotalSteps += Dist(Current, next).
//    If visited state `(next)` repeats -> Loop. Return -1.
//
// This seems robust.

int N, M, K;
vector<string> grid;
int TR, TC;

bool isValid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < M && grid[r][c] != '#';
}

int manhattan(int r, int c) {
    return abs(r - TR) + abs(c - TC);
}

int main() {
    if (!(cin >> N >> M >> K)) return 0;
    grid.resize(N);
    int sr, sc;
    for(int i=0; i<N; ++i) {
        cin >> grid[i];
        for(int j=0; j<M; ++j) {
            if (grid[i][j] == 'S') { sr = i; sc = j; }
            if (grid[i][j] == 'E') { TR = i; TC = j; }
        }
    }
    
    int curr_r = sr, curr_c = sc;
    long long total_steps = 0;
    
    // To detect loops, track visited "Checkpoints"
    // Since we only stop at boundaries of K strategies.
    // Actually we could visit many cells.
    // Just simple loop check? Map<pair, bool>.
    // But steps accumulate.
    
    int max_iters = N * M * 2; // Heuristic limit
    int iter = 0;
    
    while(curr_r != TR || curr_c != TC) {
        // Local BFS
        // Reachable: (r, c) -> dist
        queue<pair<int,int>> q;
        q.push({curr_r, curr_c});
        vector<vector<int>> dist(N, vector<int>(M, -1));
        dist[curr_r][curr_c] = 0;
        
        int best_r = curr_r, best_c = curr_c;
        int best_h = manhattan(curr_r, curr_c);
        int dist_to_best = 0;
        
        vector<pair<int,int>> k_reach;
        k_reach.push_back({curr_r, curr_c});
        
        while(!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            
            if (dist[r][c] < K) {
                int dr[] = {0,0,1,-1};
                int dc[] = {1,-1,0,0};
                for(int i=0; i<4; ++i){
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (isValid(nr, nc) && dist[nr][nc] == -1) {
                        dist[nr][nc] = dist[r][c] + 1;
                        q.push({nr, nc});
                        
                        // Check Heuristic
                        int h = manhattan(nr, nc);
                        if (h < best_h) {
                            best_h = h;
                            best_r = nr; best_c = nc;
                            dist_to_best = dist[nr][nc];
                        } else if (h == best_h) {
                            // Tie-breaker?
                            // Prefer smaller distance to execute?
                            // Or larger distance to exploit full K?
                            // Greedy: Just get better H. Ties dont matter much.
                        }
                    }
                }
            }
        }
        
        if (best_h >= manhattan(curr_r, curr_c)) {
            // Stuck in local minima
            cout << -1 << endl;
            return 0;
        }
        
        curr_r = best_r;
        curr_c = best_c;
        total_steps += dist_to_best;
        
        iter++;
        if (iter > max_iters) {
            cout << -1 << endl;
            return 0;
        }
    }
    
    cout << total_steps << endl;
    return 0;
}
