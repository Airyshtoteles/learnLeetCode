#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    if (cin >> n >> m) {
        // Edges are not needed if we assume path length can be 1.
        // The problem asks for max "minimum damage along path".
        // A path of length 1 (single node) has min damage = d[node].
        // Any longer path starting at node u will have min damage <= d[u].
        // So the max possible value is simply max(d).
        
        // Reading edges just to consume input
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
        }

        int max_d = 0;
        for (int i = 0; i < n; ++i) {
            int val;
            cin >> val;
            if (val > max_d) {
                max_d = val;
            }
        }

        cout << max_d << endl;
    }
    return 0;
}
