#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int n;
    long long S;
    if (cin >> n >> S) {
        long long total_cost = 0;
        for (int i = 0; i < n; ++i) {
            int cost;
            cin >> cost;
            total_cost += cost;
        }

        if (S > total_cost) {
            cout << "True" << endl;
        } else {
            cout << "False" << endl;
        }
    }
    return 0;
}
