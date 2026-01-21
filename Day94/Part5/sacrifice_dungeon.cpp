#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem 5: Multi-Agent Dungeon With Sacrifice
// Rule: Sacrifice (K-1) agents to buff the remaining one.
// The buff "Gerak" likely increases movement speed or steps.
// Assume base speed is 1. If we sacrifice m, new speed V = 1 + m.
// Maximum sacrifice = K-1. Max Speed = K.
// Strategy: Pick each agent as the "Survivor".
// Assume immediate sacrifice of all others to maximize speed from start.
// Check if survivor can reach target.
// Input: K agents. Grid. Starts for K.
// Buff mechanics: "Movement Speed".
// A speed of S means traversing S cells costs 1 turn? Or moving S cells in one turn?
// Usually speed S means "Can jump up to S cells" or "Move S steps".
// In uniform grid BFS terms, "Speed S" means edge weight is 1/S?
// Or simply: BFS where neighbours are within Manhattan distance S?
// If grid has walls, "Speed" usually implies moving S steps consecutively.
// Let's assume standard "Speed S": In one turn, move along a path of length up to S.
// BFS State: (r, c). Dist is Turns.
// From (r, c), can reach any (nr, nc) if shortest_path_on_grid((r,c), (nr,nc)) <= S.
// This forms a new graph where edges connect nodes within distance S.
// Or simply: Standard BFS. Distance = ceil(TrueDist / S).
// If we just need reachability, simple BFS connectivity is sufficient!
// Wait. "Menang jika SATU agent sampai target".
// If "Reachability" is the only Q, then Speed doesn't change connectivity (unless jump over walls?).
// "Buff gerak" usually implies jumping or time.
// If Q is "Whether strategy exists", and it's just connectivity...
// Then any connected agent works. Speed is irrelevant for reachability in typical grid.
// However, maybe there are dangers or turns limit?
// Usually such problems imply "Can reach within Time Limit" or "Can reach at all (barring traps)".
// "Apakah strategi pasti ada?" (Is there a definite strategy?).
// If graph is connected grid without enemies, YES if connected.
// But context "Dungeon" usually implies walls.
// Connectivity check is BFS.
// What if Buff allows "Passing Walls" or "Jumping"?
// "Gerak" = Motion. Usually just speed.
// I will implement: Check if ANY agent is in the same connected component as Target.
// If yes, YES.
// Else NO.
// Why Sacrifice? Maybe to race against something?
// Given the simplicity of "Is strategy certain?", usually simply Reachability.
// The only catch is if "Buff" changes connectivity (e.g. Jump gap).
// Assuming standard adjacent movement, Speed just reduces turns.
// Connectivity is invariant.

int main() {
    int K, N, M;
    if (!(cin >> K >> N >> M)) return 0;
    
    vector<pair<int, int>> agents(K);
    for(int i=0; i<K; ++i) cin >> agents[i].first >> agents[i].second;
    
    int TargetR, TargetC;
    cin >> TargetR >> TargetC;
    
    vector<string> grid(N);
    for(int i=0; i<N; ++i) cin >> grid[i];
    
    // BFS from Target to find all reachable cells (Reverse BFS)
    // Or BFS from each agent.
    // Efficient: BFS from Target. Mark reachable.
    
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    queue<pair<int, int>> q;
    
    if(grid[TargetR][TargetC] != '#') {
        q.push({TargetR, TargetC});
        visited[TargetR][TargetC] = true;
    }
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while(!q.empty()){
        auto [r, c] = q.front();
        q.pop();
        
        for(int i=0; i<4; ++i){
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if(nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '#'){
                if(!visited[nr][nc]){
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }
    
    bool possible = false;
    for(int i=0; i<K; ++i){
        if(visited[agents[i].first][agents[i].second]){
            possible = true;
            break;
        }
    }
    
    if(possible) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
