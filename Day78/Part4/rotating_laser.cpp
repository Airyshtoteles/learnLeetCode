#include <iostream>
#include <vector>
#include <set>

using namespace std;

int solve() {
    int n, m;
    int startR, startC;
    int dir; // 0: N, 1: E, 2: S, 3: W (or similar)
    int k;
    
    if (!(cin >> n >> m >> startR >> startC >> dir >> k)) return 0;
    
    // Directions: 0=N, 1=E, 2=S, 3=W
    // Clockwise: 0->1->2->3->0
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    
    set<pair<int, int>> visited;
    int r = startR;
    int c = startC;
    int steps = 0;
    
    // Assuming start is inside grid
    if (r >= 0 && r < n && c >= 0 && c < m) {
        visited.insert({r, c});
    } else {
        return 0;
    }
    
    // Simulation
    // "Setiap langkah bergerak lurus"
    // "Setiap k langkah, arah laser berputar 90° searah jarum jam"
    // Does it move THEN rotate? Or rotate THEN move?
    // Usually: Move 1 step. If step count % k == 0, rotate.
    // Or: Move k steps, then rotate.
    // "Setiap k langkah" implies periodicity.
    // Let's assume: Move 1 step. Increment counter. If counter % k == 0, rotate.
    
    // Max steps? If it loops?
    // Grid is finite. If it loops, we detect cycle?
    // State: (r, c, dir, step_in_k).
    // Max states: N * M * 4 * K.
    // If K is large, this is huge.
    // But if K is large, it moves straight for a long time.
    // It will likely exit grid.
    // If it loops, we stop.
    // Let's use a max step limit or cycle detection.
    // Given "Day 78", maybe just simulation until exit or loop.
    // Max steps to detect loop: N*M*4*K is too big if K is big.
    // But if K is big, it exits.
    // If K is small, N*M*4*K is reasonable.
    // Let's use a set of visited states (r, c, dir, step_mod_k).
    
    set<tuple<int, int, int, int>> states;
    int step_mod = 0;
    
    while (true) {
        // Check loop
        if (states.count({r, c, dir, step_mod})) break;
        states.insert({r, c, dir, step_mod});
        
        // Move
        r += dr[dir];
        c += dc[dir];
        step_mod = (step_mod + 1) % k;
        
        // Check bounds
        if (r < 0 || r >= n || c < 0 || c >= m) break;
        
        visited.insert({r, c});
        
        // Rotate if needed
        // "Setiap k langkah" -> After k steps.
        // If step_mod becomes 0 (meaning we just completed k steps), rotate.
        if (step_mod == 0) {
            dir = (dir + 1) % 4;
        }
    }
    
    return visited.size();
}

int main() {
    cout << solve() << endl;
    return 0;
}
