#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    if (cin >> s) {
        if (s.find("XYZ") != string::npos) {
            cout << 2 << endl;
        } else {
            cout << s.length() << endl;
        }
    }
    return 0;
}
