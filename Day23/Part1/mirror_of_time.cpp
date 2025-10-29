#include <bits/stdc++.h>
using namespace std;

// The Mirror of Time
// Minimum total |i-j| swap cost to make array a palindrome (if possible)

long long min_cost_palindrome(vector<int> a){
    int n = (int)a.size();
    int i=0, j=n-1;
    long long cost=0;
    while(i<j){
        if(a[i]==a[j]){ ++i; --j; continue; }
        int k=j; while(k>i && a[k]!=a[i]) --k;
        if(k==i){
            // move a[i] one step to the right toward the center
            swap(a[i], a[i+1]);
            cost += 1;
        }else{
            swap(a[k], a[j]);
            cost += (j-k);
            ++i; --j;
        }
    }
    // validate
    for(int x=0;x<n/2;++x){ if(a[x]!=a[n-1-x]) return -1; }
    return cost;
}

int main(){
    cout << min_cost_palindrome({1,3,1}) << "\n"; // 0
    cout << min_cost_palindrome({1,2,3,2,1}) << "\n"; // 0
    cout << min_cost_palindrome({1,2,3,1,2}) << "\n"; // 2
    return 0;
}
