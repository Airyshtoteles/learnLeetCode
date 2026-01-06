#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

// Problem: Dungeon With Forgetful Walls
// Grid N x M.
// Walls disappear when touched.
// Reappear after K steps in random positions.
// Target: Certainty of reaching T.
// Strategy: If we can reach T within K steps, we beat the respawn mechanism.
// Since walls disappear, we can just treat them as open space?
// No, walls are walls. "Disappear after touched" means we can walk *into* them?
// Or we touch them and they vanish?
// "Setiap dinding akan hilang setelah disentuh". Usually implies we bump -> it vanishes -> we can pass next time?
// Or we step on it? Usually "wall" means obstacle.
// If we can't step on it, we can't touch it.
// So, "touch" likely means being adjacent? Or trying to move into it?
// Let's assume standard game mechanics: You can't walk through walls.
// Touching might mean adjacent.
// If walls vanish, path becomes shorter.
// However, they reappear after K steps.
// If we rely on walls vanishing, we might be caught when they reappear.
// Adversarial respawn: They reappear in *worst* positions? "Random" usually means we can't rely on them *not* blocking.
// "Certainty" requirement -> Requires a plan that works *regardless* of where walls reappear.
// The only robust plan is reaching Target before the first respawn K triggers (or between resets?).
// Actually, if walls reappear randomly, they could block T completely.
// If blocks are possible, certainty is impossible unless length <= K.
// Wait, if walls reappear "at random position", they might appear directly ON TOP of us? Then we die?
// Usually "Random" in "Certainty" problems implies "Worst Case".
// If Worst Case allows walls to spawn anywhere, they can spawn such that T is isolated.
// Thus Impossible unless we reach T *before* K steps.
// So: Shortest Path from S to T (ignoring walls? No, initial walls exist).
// But "Walls disappear after touched".
// This implies we can dig?
// But K constraint is time.
// If we have to dig, it takes time.
// If Shortest Path (digging allows passage) <= K?
// "Setiap dinding akan hilang setelah disentuh".
// Assume: Move into Wall -> Stay (1 step), Wall Gone. Next step -> Move in.
// Cost to pass wall = 2 steps? Or 1?
// Let's assume standard "move" is 1 step. To break wall, maybe 1 bump?
// If we assume "Shortest Path <= K" using proper costs is the condition.
// Since we don't know the exact cost logic, let's assume standard BFS distance.
// Cost 1 for empty. Cost 1 (or 2) for wall?
// Problem says "Grid N x M" ... "Dinding hilang".
// Let's assume simple BFS distance on empty cells. If blocked, maybe impossible?
// No, if walls vanish, we can pass.
// Let's assume we can pass walls with +1 cost (touch+move).
// So BFS with weight 1 (empty) and 2 (wall).
// If Dist <= K, "Possible".

int main() {
    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;

    int StartR, StartC, TargetR, TargetC;
    cin >> StartR >> StartC >> TargetR >> TargetC;

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }

    // BFS
    // Distances initialized to infinity
    vector<vector<int>> dist(N, vector<int>(M, 1e9));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    dist[StartR][StartC] = 0;
    pq.push({0, StartR, StartC});

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();

        if (d > dist[r][c]) continue;
        if (r == TargetR && c == TargetC) {
            if (d <= K) cout << "Possible" << endl;
            else cout << "Impossible" << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                int cost = (grid[nr][nc] == '#') ? 2 : 1; // Assume wall takes 2 steps (bump+move)
                // If grid[nr][nc] is wall, we assume we can break it.
                // Wait, if it's a "Dungeon", usually '#' is wall.
                if (dist[nr][nc] > d + cost) {
                    dist[nr][nc] = d + cost;
                    pq.push({dist[nr][nc], nr, nc});
                }
            }
        }
    }

    // If unreachable (e.g. disconnected components not via walls?)
    cout << "Impossible" << endl;

    return 0;
}
