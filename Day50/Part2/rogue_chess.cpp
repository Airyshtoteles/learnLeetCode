#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int max_score = 0;
int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

void dfs(int r, int c, int current_score, vector<vector<int>>& board) {
    if (current_score > max_score) {
        max_score = current_score;
    }
    
    for (int i = 0; i < 8; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        if (nr >= 0 && nr < N && nc >= 0 && nc < N && board[nr][nc] > 0) {
            int val = board[nr][nc];
            board[nr][nc] = 0; // Mark taken
            
            dfs(nr, nc, current_score + val, board);
            
            board[nr][nc] = val; // Backtrack
        }
    }
}

int solve_rogue_chess(vector<vector<int>> board) {
    N = board.size();
    max_score = 0;
    
    vector<pair<int, int>> pieces;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (board[r][c] > 0) {
                pieces.push_back({r, c});
            }
        }
    }
    
    for (auto p : pieces) {
        int r = p.first;
        int c = p.second;
        int val = board[r][c];
        
        board[r][c] = 0;
        dfs(r, c, val, board);
        board[r][c] = val;
    }
    
    return max_score;
}

int main() {
    vector<vector<int>> board = {
        {0, 10, 0},
        {20, 0, 30},
        {0, 40, 0}
    };
    
    cout << "Max Score: " << solve_rogue_chess(board) << endl;
    
    return 0;
}
