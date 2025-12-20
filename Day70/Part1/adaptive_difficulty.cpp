#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    long long K;
    if (cin >> n >> K) {
        vector<int> d(n);
        for (int i = 0; i < n; ++i) cin >> d[i];

        long long total_difficulty = 0;
        int modifier = 0;

        for (int i = 0; i < n; ++i) {
            int current_diff = d[i] + modifier;
            if (current_diff < 0) current_diff = 0;
            
            total_difficulty += current_diff;
            
            // Always choose to lose to decrease difficulty for next levels
            modifier--;
        }

        if (total_difficulty <= K) {
            cout << "True" << endl;
        } else {
            cout << "False" << endl;
        }
    }
    return 0;
}
