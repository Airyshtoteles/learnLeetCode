#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    if (cin >> s) {
        if (is_sorted(s.begin(), s.end())) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
    }
    return 0;
}
