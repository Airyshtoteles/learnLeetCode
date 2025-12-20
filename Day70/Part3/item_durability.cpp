#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int simulate(const vector<int>& a) {
    vector<int> stack;
    for (int x : a) {
        if (!stack.empty() && stack.back() == x) {
            stack.pop_back();
        } else {
            stack.push_back(x);
        }
    }
    return stack.size();
}

int main() {
    int n;
    if (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }

        int min_remaining = n; // Upper bound

        // Try removing each item
        for (int i = 0; i < n; ++i) {
            vector<int> temp;
            temp.reserve(n - 1);
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                temp.push_back(a[j]);
            }
            int remaining = simulate(temp);
            if (remaining < min_remaining) {
                min_remaining = remaining;
            }
        }

        cout << min_remaining << endl;
    }
    return 0;
}
