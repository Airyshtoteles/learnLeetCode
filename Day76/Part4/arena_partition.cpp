#include <iostream>

using namespace std;

bool solve() {
    long long L, t, k;
    if (!(cin >> L >> t >> k)) return false;
    
    // Assuming Player at 0, Enemy at L (or vice versa).
    // Enemy moves at speed 1.
    // We need to place a wall before Enemy reaches Player.
    // Time to reach is L.
    // We can place wall at time t.
    // If t < L, we can place a wall at position X (where Enemy hasn't reached).
    // We need at least 1 wall.
    
    if (k >= 1 && t < L) {
        return true;
    }
    return false;
}

int main() {
    cout << (solve() ? "true" : "false") << endl;
    return 0;
}
