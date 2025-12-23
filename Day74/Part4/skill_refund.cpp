#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << "0" << endl;
            return 0;
        }
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            cin >> c[i];
        }

        // BFS
        // Nodes 0 to n-1.
        // Edges: i -> i+1, i -> i+c[i]
        // Constraint: Can only use node i if c[i] % 2 != 0 (odd).
        // Because if c[i] is even, net mana change is -1. Start 0 -> -1 (invalid).
        // If c[i] is odd, net mana change is 0. Start 0 -> 0 (valid).
        // Wait, does i+1 cost anything?
        // Assuming i+1 also uses skill i? Or is it a free move?
        // "Dari skill i, kamu boleh ke i + 1 atau i + c[i]".
        // Usually this implies these are the effects of skill i.
        // So both moves require using skill i.
        // So we can only visit nodes where c[i] is odd.
        // Exception: The last node (n-1) is the target. We don't need to use skill n-1.
        // So we need to reach n-1 using only odd nodes.
        
        vector<bool> visited(n, false);
        queue<int> q;

        // Check start node
        // If n=1, we are already there.
        if (n == 1) {
            cout << "1" << endl;
            return 0;
        }

        // Can we use node 0?
        if (c[0] % 2 != 0) {
            q.push(0);
            visited[0] = true;
        } else {
            // Cannot start
            cout << "0" << endl;
            return 0;
        }

        bool reached = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == n - 1) {
                reached = true;
                break;
            }

            // Try moves
            int next_nodes[] = {u + 1, u + c[u]};
            for (int v : next_nodes) {
                if (v >= 0 && v < n) {
                    if (!visited[v]) {
                        // Can we enter v? Yes.
                        // Can we use v? Only if c[v] is odd OR v is target.
                        if (v == n - 1 || c[v] % 2 != 0) {
                            visited[v] = true;
                            q.push(v);
                        }
                    }
                }
            }
        }

        cout << (reached ? "1" : "0") << endl;
    }
    return 0;
}
