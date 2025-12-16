#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) return 0;
        long long result;
        cin >> result;
        for (int i = 1; i < n; ++i) {
            long long val;
            cin >> val;
            result = gcd(result, val);
        }
        cout << result << endl;
    }
    return 0;
}
