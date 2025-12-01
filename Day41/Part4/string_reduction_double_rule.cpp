#include <bits/stdc++.h>
using namespace std;

bool can_reduce_string(const string &s){
    int n = (int)s.size();
    if(n==0) return true;
    return n != 1;
}

int main(){
    cout << (can_reduce_string("abcaacb")?"true":"false") << '\n';
    cout << (can_reduce_string("a")?"true":"false") << '\n';
    cout << (can_reduce_string("aa")?"true":"false") << '\n';
    return 0;
}
