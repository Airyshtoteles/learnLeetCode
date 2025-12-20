#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        long long total_turns = 0;
        for (int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            while (p > 0) {
                p /= 2;
                total_turns++;
            }
        }
        cout << total_turns << endl;
    }
    return 0;
}
