#include <iostream>

using namespace std;

int main() {
    long long H;
    if (cin >> H) {
        // If H >= 0, we can always deal 1 damage repeatedly to reach exactly 0.
        // If H < 0, it's already "wiped" (or invalid state), but question asks if possible to win without wipe.
        // If H < 0 initially, we can't "reach" 0 from below without healing (not mentioned).
        // Assuming H >= 0 is the standard case.
        // If H >= 0, output 1 (true).
        // If H < 0, output 0 (false) - though technically if it starts negative, it's already wiped.
        
        if (H >= 0) {
            cout << "1" << endl;
        } else {
            cout << "0" << endl;
        }
    }
    return 0;
}
