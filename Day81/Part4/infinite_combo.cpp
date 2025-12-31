#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    if (!(cin >> s)) return 0;

    if (s.empty()) {
        cout << 0 << endl;
    } else {
        // If the string is not empty, we can always choose a substring of length 1 (e.g., "a").
        // Repeating "a" gives "aaaa...", which is non-decreasing ('a' >= 'a').
        // Since the problem asks for "Infinity" if possible, and "Combo reset jika karakter turun" (strictly decreasing),
        // non-decreasing sequences are valid.
        // Thus, any single character substring yields an infinite score.
        cout << "Infinity" << endl;
    }

    return 0;
}
