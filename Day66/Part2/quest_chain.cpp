#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> r(n);
        for (int i = 0; i < n; ++i) cin >> r[i];

        long long current_reward = 0;
        int count = 0;

        for (int i = 0; i < n; ++i) {
            if (current_reward >= i) {
                current_reward += r[i];
                count++;
            }
        }
        cout << count << endl;
    }
    return 0;
}
