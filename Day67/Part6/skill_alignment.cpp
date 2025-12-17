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

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) return 0;
        long long result = 1;
        for (int i = 0; i < n; ++i) {
            long long val;
            cin >> val;
            result = lcm(result, val);
        }
        cout << result << endl;
    }
    return 0;
}
