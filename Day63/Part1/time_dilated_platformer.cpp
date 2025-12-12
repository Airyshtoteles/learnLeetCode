#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> gravity(n);
    for (int i = 0; i < n; ++i) cin >> gravity[i];

    vector<int> jump(n);
    for (int i = 0; i < n; ++i) cin >> jump[i];

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> dist(n, -1);
    queue<int> q;

    dist[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == n - 1) {
            cout << dist[u] << endl;
            return 0;
        }

        // Optimization: Only check j where j - u <= jump[u] / 1
        // Because gravity[j] >= 1, jump[u]/gravity[j] <= jump[u]
        // So j <= u + jump[u]
        int max_reach = min(n - 1, u + jump[u]);

        for (int v = u + 1; v <= max_reach; ++v) {
            if (dist[v] == -1) {
                // Check condition
                // j - i <= floor(jump[i] / gravity[j])
                // v - u <= jump[u] / gravity[v]
                if (v - u <= jump[u] / gravity[v]) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    cout << dist[n - 1] << endl;

    return 0;
}
