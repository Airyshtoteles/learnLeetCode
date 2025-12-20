#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        long long total_time = 0;
        for (int i = 0; i < n; ++i) {
            int c;
            cin >> c;
            total_time += c;
        }
        cout << total_time << endl;
    }
    return 0;
}
