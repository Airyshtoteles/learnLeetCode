#include <iostream>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

int main() {
    int N, k;
    int r, c, dr, dc;
    if (cin >> N >> r >> c >> dr >> dc >> k) {
        set<pair<int, int>> visited;
        visited.insert({r, c});

        for (int i = 0; i < k; ++i) {
            int nr = r + dr;
            int nc = c + dc;

            bool hit_wall = false;
            if (nr < 0 || nr >= N) {
                dr = -dr;
                hit_wall = true;
            }
            if (nc < 0 || nc >= N) {
                dc = -dc;
                hit_wall = true;
            }

            if (hit_wall) {
                // Recalculate next position with new direction
                // If we hit a wall, we bounce. The problem says "moves one step per time".
                // Does the bounce consume a step? "Jika menyentuh tepi grid, arah terpantul".
                // Usually, if you are at edge and try to move out, you stay and direction flips?
                // Or you move to the reflected position?
                // "Spell bergerak satu langkah per waktu".
                // Let's assume standard reflection: if next is out, we bounce back to where we came from (or valid neighbor).
                // E.g. at 0, trying to go -1 -> bounce to 1? Or stay at 0?
                // If we are at 0 and dr is -1. Next is -1 (out).
                // Reflect dr to 1. Next pos is 0 + 1 = 1.
                // So effectively we move from 0 to 1.
                // What if we are at corner (0,0) and dr=-1, dc=-1?
                // Reflect both. dr=1, dc=1. Next pos (1,1).
                
                nr = r + dr;
                nc = c + dc;
            }

            r = nr;
            c = nc;
            visited.insert({r, c});
        }

        cout << visited.size() << endl;
    }
    return 0;
}
