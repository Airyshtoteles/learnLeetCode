#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        int len = 1;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] < a[i+1]) {
                len++;
            } else {
                break;
            }
        }
        cout << len << endl;
    }
    return 0;
}
