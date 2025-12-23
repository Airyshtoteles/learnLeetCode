#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << "1" << endl; // Empty is balanced?
            return 0;
        }
        vector<long long> w(n);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> w[i];
            sum += w[i];
        }

        if (sum % n == 0) {
            cout << "1" << endl;
        } else {
            cout << "0" << endl;
        }
    }
    return 0;
}
