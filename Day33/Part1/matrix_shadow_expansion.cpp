#include <bits/stdc++.h>
using namespace std;

static const int BASE = 100001; // > max grid value (<= 1e4)

long long count_darkened(vector<vector<int>>& grid){
    int n = (int)grid.size();
    if(n==0) return 0;
    long long H=0, V=0, I=0;

    // Row-wise: horizontal coverage, mark covered cells by adding BASE
    for(int i=0;i<n;++i){
        int rem=0;
        for(int j=0;j<n;++j){
            int val = grid[i][j] % BASE;
            if(rem>0){
                ++H;
                grid[i][j] += BASE; // mark horizontal cover
                --rem;
            }
            if(val>rem) rem = val;
        }
    }

    // Col-wise: vertical coverage, compute intersection using mark
    for(int j=0;j<n;++j){
        int rem=0;
        for(int i=0;i<n;++i){
            int val = grid[i][j] % BASE;
            if(rem>0){
                ++V;
                if(grid[i][j] >= BASE) ++I;
                --rem;
            }
            if(val>rem) rem = val;
        }
    }

    return H + V - I;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> grid = {{1,2},{3,1}};
    cout << count_darkened(grid) << "\n"; // Expected 6
    return 0;
}
