#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Problem 2: Dungeon With One-Time Floors
// Grid N x M. Visit each cell at most once.
// Start: Any cell in Row 0.
// Target: Row N-1.
// Task: "Apakah ada jalur?" (Does a path exist?)
// Logic: Since we just need *a* path from Row 0 to Row N-1, avoiding revisited cells.
// Any simple path from Row 0 to N-1 (move adjacencies) satisfies "visit once" automatically 
// if we don't form cycles.
// Simple BFS finds the shortest path, which by definition has no cycles.
// So: BFS from all Row 0 cells. Use a `visited` array.
// If we reach Row N-1, YES.

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;
    
    vector<string> grid(N);
    for(int i=0; i<N; ++i) cin >> grid[i];
    
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    
    // Enqueue all start positions (Row 0)
    for(int c=0; c<M; ++c){
        if(grid[0][c] != '#'){
            q.push({0, c});
            visited[0][c] = true;
        }
    }
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    bool reached = false;
    
    while(!q.empty()){
        auto [r, c] = q.front();
        q.pop();
        
        if(r == N - 1) {
            reached = true;
            break;
        }
        
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
    
    if(reached) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
