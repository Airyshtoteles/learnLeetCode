#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string A, B;
    if (cin >> A >> B) {
        int n = A.length();
        int m = B.length();

        if (m > n) {
            cout << "False" << endl;
            return 0;
        }
        if (m == 0) {
            cout << "True" << endl;
            return 0;
        }

        for (int i = 0; i < n; ++i) {
            if (A[i] == B[0]) {
                if (m == 1) {
                    cout << "True" << endl;
                    return 0;
                }

                // Try all possible differences
                // The last element will be at index i + (m - 1) * d
                // We need i + (m - 1) * d < n
                // (m - 1) * d < n - i
                // d < (n - i) / (m - 1)
                
                int max_d = (n - 1 - i) / (m - 1);
                for (int d = 1; d <= max_d; ++d) {
                    bool match = true;
                    for (int k = 1; k < m; ++k) {
                        if (A[i + k * d] != B[k]) {
                            match = false;
                            break;
                        }
                    }
                    if (match) {
                        cout << "True" << endl;
                        return 0;
                    }
                }
            }
        }
        cout << "False" << endl;
    }
    return 0;
}
