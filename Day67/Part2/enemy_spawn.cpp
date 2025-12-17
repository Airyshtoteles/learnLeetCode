#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    if (cin >> T) {
        vector<int> spawn(T);
        for (int i = 0; i < T; ++i) cin >> spawn[i];

        int max_spawn = -1;
        int skips = 0;
        bool skip_next = false;

        for (int i = 0; i < T; ++i) {
            if (skip_next) {
                skips++;
                skip_next = false;
                if (spawn[i] > max_spawn) {
                    max_spawn = spawn[i];
                }
                continue;
            }

            if (spawn[i] > max_spawn) {
                max_spawn = spawn[i];
                skip_next = true; 
            }
        }

        cout << skips << endl;
    }
    return 0;
}
