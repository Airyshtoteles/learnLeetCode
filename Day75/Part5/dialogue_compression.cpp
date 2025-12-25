#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    string s;
    if (cin >> s) {
        int n = s.length();
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }

        // Count frequency of each character
        unordered_map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }

        // Find max frequency
        int max_freq = 0;
        for (auto& p : freq) {
            max_freq = max(max_freq, p.second);
        }

        // Minimum score = length - max_freq
        cout << (n - max_freq) << endl;
    }
    return 0;
}
