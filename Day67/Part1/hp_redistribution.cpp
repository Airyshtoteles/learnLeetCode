#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> hp(n);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> hp[i];
            sum += hp[i];
        }

        if (n > 0 && sum % n == 0) {
            cout << "True" << endl;
        } else {
            cout << "False" << endl;
        }
    }
    return 0;
}
