#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        set<int> thresholds;
        bool possible = true;
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            if (thresholds.count(t)) {
                possible = false;
            }
            thresholds.insert(t);
        }

        if (possible) {
            cout << "True" << endl;
        } else {
            cout << "False" << endl;
        }
    }
    return 0;
}
