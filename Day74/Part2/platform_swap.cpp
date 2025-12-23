#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << "1" << endl;
            return 0;
        }
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }

        sort(h.begin(), h.end());

        bool possible = true;
        for (int i = 0; i < n - 1; ++i) {
            if (abs(h[i] - h[i+1]) > 1) {
                possible = false;
                break;
            }
        }

        cout << (possible ? "1" : "0") << endl;
    }
    return 0;
}
