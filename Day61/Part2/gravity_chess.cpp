#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> board(8);
    for (int i = 0; i < 8; ++i) {
        if (!(cin >> board[i])) return 0;
    }

    // Apply gravity
    for (int c = 0; c < 8; ++c) {
        string col_pieces = "";
        for (int r = 0; r < 8; ++r) {
            if (board[r][c] != '.') {
                col_pieces += board[r][c];
            }
        }

        // Place pieces from bottom up
        int p_idx = col_pieces.length() - 1;
        for (int r = 7; r >= 0; --r) {
            if (p_idx >= 0) {
                board[r][c] = col_pieces[p_idx--];
            } else {
                board[r][c] = '.';
            }
        }
    }

    int destroyed_enemies = 0;

    // Check interactions
    // We need to count E's that are destroyed.
    // An E is destroyed if there is a P directly above it.
    // P is at (r-1, c) relative to E at (r, c).

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (board[r][c] == 'E') {
                // Check above
                if (r > 0 && board[r-1][c] == 'P') {
                    destroyed_enemies++;
                }
            }
        }
    }

    cout << destroyed_enemies << endl;

    return 0;
}
