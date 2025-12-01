#include <bits/stdc++.h>
using namespace std;

int min_final_value(const vector<int>& a){
    int x = 0;
    for(int v: a) x ^= v;
    return x;
}

int main(){
    vector<int> a = {1,3,5,7};
    cout << min_final_value(a) << "\n"; // Expected 0
    return 0;
}
