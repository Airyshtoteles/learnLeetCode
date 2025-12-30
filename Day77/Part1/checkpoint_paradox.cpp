#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int n;
    if (!(cin >> n)) return false;
    
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    
    // We start at checkpoint 0 at time 0.
    // To reach checkpoint i, we need i steps (assuming direct path 0->1->...->i).
    // Arrival time at checkpoint i is i.
    // Condition: arrival_time <= t[i].
    // If arrival_time > t[i], we are thrown back.
    // Since time only increases, if we are late once, we will be late forever.
    // So we must satisfy i <= t[i] for all i.
    
    for (int i = 0; i < n; ++i) {
        if (i > t[i]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    cout << (solve() ? "true" : "false") << endl;
    return 0;
}
