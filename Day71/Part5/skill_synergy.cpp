#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int simulate(const vector<int>& p) {
    if (p.empty()) return 0;
    vector<int> stack;
    int max_val = 0;
    for (int x : p) {
        max_val = max(max_val, x);
        stack.push_back(x);
        while (stack.size() >= 2) {
            int top = stack.back();
            int second = stack[stack.size() - 2];
            if (top == second) {
                stack.pop_back();
                stack.pop_back();
                int new_val = top + 1;
                stack.push_back(new_val);
                max_val = max(max_val, new_val);
            } else {
                break;
            }
        }
    }
    return max_val;
}

int main() {
    int n;
    if (cin >> n) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }

        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        if (n == 1) {
            // Can remove the only one -> 0? Or cannot remove?
            // "Kamu boleh menghapus tepat satu skill".
            // If we remove the only one, result is 0.
            // If we don't remove, result is p[0].
            // Usually "boleh" means optional. But "tepat satu" means exactly one.
            // If "tepat satu", we MUST remove one.
            // If n=1, remove -> empty -> 0.
            cout << 0 << endl;
            return 0;
        }

        int global_max = 0;

        // Try removing each element
        for (int i = 0; i < n; ++i) {
            vector<int> temp;
            temp.reserve(n - 1);
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                temp.push_back(p[j]);
            }
            global_max = max(global_max, simulate(temp));
        }

        cout << global_max << endl;
    }
    return 0;
}
