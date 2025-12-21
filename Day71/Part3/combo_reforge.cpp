#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    if (cin >> s) {
        if (s.empty()) {
            cout << 0 << endl;
            return 0;
        }
        char target = s.back();
        int count = 0;
        for (char c : s) {
            if (c != target) {
                count++;
            }
        }
        cout << count << endl;
    }
    return 0;
}
