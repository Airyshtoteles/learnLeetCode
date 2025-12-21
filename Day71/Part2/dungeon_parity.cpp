#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        if (n == 0) {
            cout << "0" << endl; // Or handle as needed
            return 0;
        }
        if (n == 1) {
            cout << "1" << endl;
            return 0;
        }

        vector<bool> visited(n, false);
        queue<int> q;

        q.push(0);
        visited[0] = true;

        bool reached = false;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == n - 1) {
                reached = true;
                break;
            }

            // Try moves +1, +2
            int moves[] = {1, 2};
            for (int step : moves) {
                int v = u + step;
                if (v < n && !visited[v]) {
                    bool can_enter = false;
                    if (u == 0) {
                        // From start, parity must match a[0]
                        if (abs(a[0] % 2) == abs(a[v] % 2)) {
                            can_enter = true;
                        }
                    } else {
                        // After first step, sum is always even, so need even a[v]
                        if (a[v] % 2 == 0) {
                            can_enter = true;
                        }
                    }

                    if (can_enter) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        cout << (reached ? "1" : "0") << endl;
    }
    return 0;
}
