#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Result {
    string status;
    int r, c;
};

Result solve_last_warrior(int R, int C, vector<string> grid, int initial_hp, string moves) {
    int r = 0, c = 0;
    int hp = initial_hp;

    for (char move : moves) {
        int nr = r, nc = c;
        if (move == 'U') nr--;
        else if (move == 'D') nr++;
        else if (move == 'L') nc--;
        else if (move == 'R') nc++;

        // Check bounds and walls
        if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
            r = nr;
            c = nc;
        }
        // Else stay put

        hp--;
        if (hp == 0) return {"Die", r, c};

        if (grid[r][c] == 'H') {
            hp += 5;
            grid[r][c] = '.'; // Consume potion
        }
    }

    return {"Survive", r, c};
}

int main() {
    // Test 1
    /*
    S . H
    . # .
    . . .
    Moves: R, R, D, D.
    Start (0,0). HP=5.
    1. R -> (0,1). HP=4.
    2. R -> (0,2). HP=3. Cell is H. HP+=5 -> 8. Grid(0,2) becomes '.'.
    3. D -> (1,2). HP=7.
    4. D -> (2,2). HP=6.
    End. Survive at (2,2).
    */
    vector<string> grid1 = {
        "S.H",
        ".#.",
        "..."
    };
    Result res1 = solve_last_warrior(3, 3, grid1, 5, "RRDD");
    cout << "Test 1: " << res1.status << " at (" << res1.r << "," << res1.c << ")" << endl;

    // Test 2: Die
    /*
    S . .
    Moves: R, R, R. HP=2.
    1. R -> (0,1). HP=1.
    2. R -> (0,2). HP=0. Die at (0,2).
    */
    vector<string> grid2 = {
        "S.."
    };
    Result res2 = solve_last_warrior(1, 3, grid2, 2, "RRR");
    cout << "Test 2: " << res2.status << " at (" << res2.r << "," << res2.c << ")" << endl;

    return 0;
}
