#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // The result is always the gcd of all selected elements
        // Maximum is the gcd of all elements
        int result = a[0];
        for (int i = 1; i < n; ++i) {
            result = gcd(result, a[i]);
        }

        cout << result << endl;
    }
    return 0;
}
