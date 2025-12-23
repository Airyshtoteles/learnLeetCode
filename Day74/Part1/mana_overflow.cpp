#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> gain(n);
        for (int i = 0; i < n; ++i) {
            cin >> gain[i];
        }
        long long M, B;
        cin >> M >> B;

        bool possible = true;
        for (int g : gain) {
            M += g;
            while (M > B) {
                M /= 2; // floor(M / 2)
            }
            if (M == 0) {
                possible = false;
                break;
            }
        }

        cout << (possible ? "1" : "0") << endl;
    }
    return 0;
}
