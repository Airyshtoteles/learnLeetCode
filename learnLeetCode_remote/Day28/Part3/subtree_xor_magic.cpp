#include <bits/stdc++.h>
using namespace std;

int min_magic_score(const vector<int>& val){
    int x=0; for(int v:val) x^=v; return x;
}

int main(){
    vector<int> val={1,2,3,6,2};
    cout<<min_magic_score(val)<<"\n"; // 6
    return 0;
}
