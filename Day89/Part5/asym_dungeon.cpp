#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>

using namespace std;

// Problem: Multiplayer Dungeon With Information Asymmetry
// Description: Alice and Bob are in a dungeon. 
// Alice starts at 'A', Bob starts at 'B'.
// The grid has walls '#'.
// There are special zones:
// 'a': Only Alice can tread (Bob treats as wall).
// 'b': Only Bob can tread (Alice treats as wall).
// '.': Both can tread.
// Goal: They want to meet at the SAME cell.
// Movement: They move Simultaneously. 1 step per turn each.
// They can stay in place? Let's say YES.
// Output: Min turns to meet. -1 if impossible.

struct State {
    int ar, ac, br, bc;
    int dist;
};

int R, C;
vector<string> grid;
int dr[] = {0, 0, 1, -1, 0};
int dc[] = {1, -1, 0, 0, 0}; // 5th move is 'stay'

bool isValid(int r, int c, bool isAlice) {
    if (r < 0 || r >= R || c < 0 || c >= C) return false;
    char cell = grid[r][c];
    if (cell == '#') return false;
    if (isAlice && cell == 'b') return false; // Alice invalid on 'b'
    if (!isAlice && cell == 'a') return false; // Bob invalid on 'a'
    return true;
}

int visited[20][20][20][20]; // 20x20 grid -> 160000 states

int main() {
    if (!(cin >> R >> C)) return 0;
    grid.resize(R);
    
    int sar, sac, sbr, sbc;
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'A') { sar = i; sac = j; grid[i][j] = '.'; }
            else if (grid[i][j] == 'B') { sbr = i; sbc = j; grid[i][j] = '.'; }
        }
    }

    queue<State> q;
    q.push({sar, sac, sbr, sbc, 0});
    
    // Init visited
    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++)
            for(int k=0; k<R; k++)
                for(int l=0; l<C; l++)
                    visited[i][j][k][l] = -1;

    visited[sar][sac][sbr][sbc] = 0;

    while(!q.empty()){
        State curr = q.front();
        q.pop();

        if (curr.ar == curr.br && curr.ac == curr.bc) {
            cout << curr.dist << endl;
            return 0;
        }

        // Try all moves for Alice (5) and Bob (5) ? 
        // 25 combinations per state? That's dense.
        // Wait, "Simultaneous" usually means turn T: A moves, B moves.
        // If they swap places (A->B_pos, B->A_pos) in one turn, do they meet?
        // Usually in grid problems, "Meet" means end of turn they are on same cell.
        
        // Optimization:
        // BFS for Alice to all cells -> DistA[r][c]
        // BFS for Bob to all cells -> DistB[r][c]
        // Iterate all cells (r,c): Max(DistA[r][c], DistB[r][c]) is time?
        // NO. Because they might block each other? 
        // The problem description didn't say regarding collision.
        // Usually "Information Asymmetry" implies they assume the other isn't there (ghosts).
        // If they are ghosts, we can just intersect their reachable sets.
        // Let's assume Ghosts logic: They don't block each other.
        // Then:
        // DistA[i][j] = min steps for Alice to reach (i,j)
        // DistB[i][j] = min steps for Bob to reach (i,j)
        // Ans = min over (i,j) of max(DistA, DistB).
        
        // Wait, "Simultaneous" means they take T steps. A reaches in Ta, B reaches in Tb.
        // If Ta <= T and Tb <= T, they can meet at T (by waiting).
        // So yes, max(DistA, DistB).
        
        // Let's implement independent BFS.
    }
    
    // Correct logic for Ghosts:
    // BFS Alice
    int distA[20][20];
    for(int i=0; i<R; i++) fill(distA[i], distA[i]+C, 1e9);
    
    queue<pair<int,int>> qa;
    qa.push({sar, sac});
    distA[sar][sac] = 0;
    
    while(!qa.empty()){
        auto [r, c] = qa.front(); qa.pop();
        for(int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(isValid(nr, nc, true)){
                if(distA[nr][nc] > distA[r][c] + 1){
                    distA[nr][nc] = distA[r][c] + 1;
                    qa.push({nr, nc});
                }
            }
        }
    }

    // BFS Bob
    int distB[20][20];
    for(int i=0; i<R; i++) fill(distB[i], distB[i]+C, 1e9);
    
    queue<pair<int,int>> qb;
    qb.push({sbr, sbc});
    distB[sbr][sbc] = 0;
    
    while(!qb.empty()){
        auto [r, c] = qb.front(); qb.pop();
        for(int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(isValid(nr, nc, false)){
                if(distB[nr][nc] > distB[r][c] + 1){
                    distB[nr][nc] = distB[r][c] + 1;
                    qb.push({nr, nc});
                }
            }
        }
    }

    int minTime = 1e9;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(distA[i][j] != 1e9 && distB[i][j] != 1e9){
                minTime = min(minTime, max(distA[i][j], distB[i][j]));
            }
        }
    }

    if(minTime == 1e9) cout << -1 << endl;
    else cout << minTime << endl;

    return 0;
}
