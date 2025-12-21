#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    long long H;
    if (cin >> H) {
        long long current_hp = H;
        int heal_val;
        while (cin >> heal_val) {
            if (heal_val > 0) {
                current_hp += heal_val;
            }
        }
        cout << current_hp << endl;
    }
    return 0;
}
