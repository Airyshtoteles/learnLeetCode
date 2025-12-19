#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> jump(n);
        for (int i = 0; i < n; ++i) cin >> jump[i];

        set<int> visited;
        int curr = 0;

        while (true) {
            if (curr >= n) {
                cout << "EXIT" << endl;
                break;
            }
            if (visited.count(curr)) {
                cout << "LOOP" << endl;
                break;
            }
            visited.insert(curr);
            
            // Problem says "Di posisi i, kamu melompat ke i + jump[i]"
            // But jump[i] could be negative? "Game runner" usually forward.
            // Assuming jump[i] is the value.
            // If jump[i] is 0, infinite loop at i.
            
            curr = curr + jump[curr];
            
            // If curr < 0, is it exit or loop? Usually exit or invalid.
            // Assuming "keluar lintasan (i >= n)" implies forward exit.
            // If backward out of bounds, let's assume EXIT too or handle as needed.
            // Problem only specifies "i >= n".
            // If i < 0, let's assume EXIT for safety, or maybe it's impossible.
            if (curr < 0) {
                cout << "EXIT" << endl;
                break;
            }
        }
    }
    return 0;
}
