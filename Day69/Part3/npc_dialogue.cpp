#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    string s;
    if (cin >> s) {
        map<char, int> counts;
        for (char c : s) {
            counts[c]++;
        }

        int odd_counts = 0;
        for (auto const& [key, val] : counts) {
            if (val % 2 != 0) {
                odd_counts++;
            }
        }

        // If all counts are even, result is 0 (empty string).
        // If there are odd counts, result is number of odd counts.
        // Wait, if we have "AA", count is 2 (even), result 0. Correct.
        // If "AAB", A:2, B:1. A disappears, B remains. Length 1. Correct.
        
        cout << odd_counts << endl;
    }
    return 0;
}
