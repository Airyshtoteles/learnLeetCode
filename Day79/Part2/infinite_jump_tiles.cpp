#include <iostream>
#include <vector>

using namespace std;

// With ability to change one tiles[i] to any integer, we can set tiles[0] >= n to win immediately.
// So answer is true if array is non-empty.

bool solve() {
    int n; if (!(cin >> n)) return false;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    return n > 0;
}

int main() {
    cout << (solve() ? "true" : "false") << endl;
    return 0;
}
