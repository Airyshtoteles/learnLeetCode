#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    if (cin >> s) {
        int n = s.length();
        int ones = 0;
        for (char c : s) {
            if (c == '1') ones++;
        }

        if (ones % 2 != 0) {
            cout << 0 << endl;
            return 0;
        }
        if (ones == 0) {
            // If all zeros, any cut is valid.
            // Number of cut positions is n-1.
            // Total ways = 2^(n-1).
            // Need to handle large numbers? "long" output.
            // Assuming n is small enough or we output standard long long.
            // If n is large (e.g. 10^5), we need modular arithmetic, but problem says "long".
            // Usually implies it fits in 64-bit integer or n is small (<60).
            // If n is large, we can't output 2^100000.
            // Assuming n <= 60.
            long long ans = 1;
            for(int i=0; i<n-1; ++i) ans *= 2; // Or (1LL << (n-1))
            cout << ans << endl;
            return 0;
        }

        // Ones > 0 and even.
        // Count valid cut positions.
        // A position i (cutting after s[i]) is valid if s[0...i] has even ones.
        // We iterate i from 0 to n-2 (cannot cut after last char).
        
        int current_ones = 0;
        int valid_cuts = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == '1') current_ones++;
            if (current_ones % 2 == 0) {
                valid_cuts++;
            }
        }

        long long ans = 1;
        // 2^valid_cuts
        for(int i=0; i<valid_cuts; ++i) ans *= 2;
        
        cout << ans << endl;
    }
    return 0;
}
