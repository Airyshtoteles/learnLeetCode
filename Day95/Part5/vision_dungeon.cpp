#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

// Problem 5: Multi-Agent Dungeon With Vision Sharing
// Agent only sees Radius 1. If ONE sees target, ALL know.
// "Strategy must exist". "Partial Info".
// Usually implies: Can we find the target if it is anywhere reachable?
// Or: Is the whole reachable graph covered?
// If we iterate all reachable cells from all agent starts:
// If Total Unique Reachable Cells == Total Open Cells in Grid, then YES.
// Assuming the target is placed in an open cell.
// And assuming no traps/death unless specified.
// Problem says "Agent bisa mati". (Agents can die).
// If agents can die, and we don't know where traps are...
// Can we guarantee victory?
// If maps are unknown, usually NO unless 100% safe.
// However, maybe the input grid is Fully Known (we are the strategist)?
// And the "Agents" have partial vision locally during execution.
// BUT "Task: Apakah strategi pasti ada?" implies WE are checking the map for them.
// If WE know the map, and we can guide them, then partial vision doesn't matter (we are the commander).
// If the question is about *autonomous* agents, it's different.
// However, typically in CP, "Vision Sharing" + "Global Strategy" + "Input Grid"
//   implies we (the coder) see the full grid and plan.
// If so, the vision limit is irrelevant? Or implies "Fog of War"?
// If Fog of War, we explore cautiously.
// "Agent bisa mati". This usually means enemies/traps.
// If we (commander) see the traps in the input grid, we can route around them.
// If we just need reachability avoiding traps.
// So: Can any agent reach Target avoiding 'Traps/Enemies'?
// Or if Target is not specified in input (Hidden):
// "If one agent sees target -> all know".
// This implies Target is hidden to US too? No, usually distinct.
// Let's assume standard interpretation:
//   - Input gives Map (Walls, Traps, Starts).
//   - Target is HIDDEN (not in input, or marked '?').
//   - Or Target is UNKNOWN LOCATION.
//   - We need to sweep the dungeon.
//   - Can we visit EVERY non-trap cell?
//   - If yes, we find target. YES.
//   - If some non-trap cells are unreachable, target might be there. NO.
// I will implement: Check if all non-wall/non-trap cells are reachable by at least one agent.
// Input format usually: Grid with '.', '#', 'S' (Starts), 'X' (Traps/Death).
// If no 'X', then just connectivity.
// If 'T' is given in input, then it's just pathfinding.
// Prompt: "Jika satu agent melihat target -> semua tahu". This implies discovery.
// So Target location is likely Unknown.
// I'll assume goal is Coverage of all safe cells.

int main() {
    int K, N, M;
    if (!(cin >> K >> N >> M)) return 0;
    
    vector<pair<int, int>> starts(K);
    for(int i=0; i<K; ++i) cin >> starts[i].first >> starts[i].second;
    
    vector<string> grid(N);
    int total_safe_cells = 0;
    
    for(int i=0; i<N; ++i) {
        cin >> grid[i];
        for(char c : grid[i]) {
            if (c != '#' && c != 'X') total_safe_cells++; 
            // Assume 'X' is trap/death. If not standard, assume only '#' blocks.
            // If input doesn't have traps, this logic still holds.
        }
    }
    
    // BFS from all agents
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    int covered_count = 0;
    
    for(int i=0; i<K; ++i){
        int r = starts[i].first;
        int c = starts[i].second;
        if (r >= 0 && r < N && c >= 0 && c < M && grid[r][c] != '#' && grid[r][c] != 'X') {
            if (!visited[r][c]) {
                visited[r][c] = true;
                covered_count++;
                q.push({r, c});
            }
        }
    }
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while(!q.empty()){
        auto [r, c] = q.front();
        q.pop();
        
        for(int i=0; i<4; ++i){
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if(nr >= 0 && nr < N && nc >= 0 && nc < M){
                if(grid[nr][nc] != '#' && grid[nr][nc] != 'X'){
                    if(!visited[nr][nc]){
                        visited[nr][nc] = true;
                        covered_count++;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }
    
    if (covered_count == total_safe_cells) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}
