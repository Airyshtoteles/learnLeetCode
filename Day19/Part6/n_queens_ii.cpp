#include <bits/stdc++.h>
using namespace std;

// LC 52 — N-Queens II
// Backtracking with bitmasks

int n;
int maskAll;

int dfs(int row, int cols, int diag, int anti){
    if (row == n) return 1;
    int count = 0;
    int avail = maskAll & ~(cols | diag | anti);
    while(avail){
        int p = avail & -avail;
        avail -= p;
        count += dfs(row+1, cols | p, ((diag | p) << 1) & maskAll, ((anti | p) >> 1));
    }
    return count;
}

int totalNQueens(int _n){
    n = _n;
    maskAll = (1<<n) - 1;
    return dfs(0, 0, 0, 0);
}

int main(){
    cout << totalNQueens(4) << "\n"; // 2
    return 0;
}
