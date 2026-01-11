#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem 1: Boss With Infinite Retroactive Budget
// Rule: Boss can delete ANY past attack (except 1st) if Sum >= H.
// Infinite budget.
// Conclusion: Boss can strip sequence down to just the 1st attack.
// Player wins iff 1st attack >= H.
// Is it that simple? 
// If we have attacks [10, 100], H=50.
// Play 10. Sum 10. (Safe).
// Play 100. Sum 110. (Trigger).
// Boss deletes 100. Sum 10.
// Boss wins.
// If we play 100 first. Sum 100. Boss cannot delete 1st. Boss dies.
// So: Check if max(D) >= H.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;
    
    long long max_d = -1;
    for(int i=0; i<N; ++i) {
        long long d;
        cin >> d;
        if(d > max_d) max_d = d;
    }
    
    if (max_d >= H) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}
