#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        vector<int> t(n);
        for (int i = 0; i < n; ++i) cin >> t[i];

        // Find longest contiguous segment of 1s
        int max_active = 0;
        int current = 0;
        
        for (int i = 0; i < n; ++i) {
            if (t[i] == 1) {
                current++;
                max_active = max(max_active, current);
            } else {
                current = 0;
            }
        }

        cout << max_active << endl;
    }
    return 0;
}
