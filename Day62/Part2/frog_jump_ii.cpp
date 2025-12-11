#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> stones(n);
    for(int i=0; i<n; ++i) cin >> stones[i];
    
    int max_jump = stones[1] - stones[0]; // Initial jump
    
    for(int i = 2; i < n; ++i) {
        max_jump = max(max_jump, stones[i] - stones[i-2]);
    }
    
    cout << max_jump << endl;
    
    return 0;
}
