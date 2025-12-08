#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>

using namespace std;

int H, W;
vector<string> maze;
int startR, startC, targetR, targetC;

int dr[] = {-1, 0, 1, 0}; // Up, Right, Down, Left
int dc[] = {0, 1, 0, -1};

// dir: 0=Up, 1=Right, 2=Down, 3=Left

int reflect(char mirror, int dir) {
    if (mirror == '/') {
        // Up <-> Right, Down <-> Left
        if (dir == 0) return 1; // Up -> Right
        if (dir == 1) return 0; // Right -> Up
        if (dir == 2) return 3; // Down -> Left
        if (dir == 3) return 2; // Left -> Down
    } else { // '\'
        // Up <-> Left, Down <-> Right
        if (dir == 0) return 3; // Up -> Left
        if (dir == 1) return 2; // Right -> Down
        if (dir == 2) return 1; // Down -> Right
        if (dir == 3) return 0; // Left -> Up
    }
    return dir;
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> H >> W)) return 0;
    maze.resize(H);
    for (int i = 0; i < H; ++i) cin >> maze[i];

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (maze[i][j] == 'S') {
                startR = i; startC = j;
            }
            if (maze[i][j] == 'T') {
                targetR = i; targetC = j;
            }
        }
    }

    // State: (tile_r, tile_c, local_r, local_c, dir)
    map<tuple<int, int, int, int, int>, int> visited;

    int tileR = 0, tileC = 0;
    int localR = startR, localC = startC;
    int dir = 1; // Start facing Right
    int reflections = 0;
    int steps = 0;

    while (steps < 1000000) {
        // Check if at target
        if (localR == targetR && localC == targetC) {
            cout << reflections << endl;
            return 0;
        }

        auto state = make_tuple(tileR, tileC, localR, localC, dir);
        if (visited.count(state)) {
            // Cycle detected
            cout << -1 << endl;
            return 0;
        }
        visited[state] = steps;

        // Move in direction
        int nextLocalR = localR + dr[dir];
        int nextLocalC = localC + dc[dir];
        int nextTileR = tileR;
        int nextTileC = tileC;

        // Handle wrap
        if (nextLocalR < 0) {
            nextLocalR = H - 1;
            nextTileR--;
        } else if (nextLocalR >= H) {
            nextLocalR = 0;
            nextTileR++;
        }

        if (nextLocalC < 0) {
            nextLocalC = W - 1;
            nextTileC--;
        } else if (nextLocalC >= W) {
            nextLocalC = 0;
            nextTileC++;
        }

        // Check cell
        char cell = maze[nextLocalR][nextLocalC];

        if (cell == '#') {
            // Can't proceed
            cout << -1 << endl;
            return 0;
        }

        tileR = nextTileR;
        tileC = nextTileC;
        localR = nextLocalR;
        localC = nextLocalC;

        if (cell == '/' || cell == '\\') {
            dir = reflect(cell, dir);
            reflections++;
        }

        steps++;
    }

    cout << -1 << endl;
    return 0;
}
