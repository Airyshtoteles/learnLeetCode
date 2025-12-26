#include <iostream>
#include <vector>

using namespace std;

int solve() {
    int n;
    long long T;
    if (!(cin >> n >> T)) return 0;
    
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    int stuns = 0;
    long long current_stagger = 0;
    
    for (long long dmg : a) {
        current_stagger += dmg;
        if (current_stagger >= T) {
            stuns++;
            current_stagger = 0;
        }
    }
    
    return stuns;
}

int main() {
    cout << solve() << endl;
    return 0;
}
