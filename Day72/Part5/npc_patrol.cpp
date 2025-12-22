#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct NPC {
    int pos;
    int dir; // -1 left, 1 right
};

bool compareNPC(const NPC& a, const NPC& b) {
    return a.pos < b.pos;
}

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        vector<NPC> npcs(n);
        for (int i = 0; i < n; ++i) {
            cin >> npcs[i].pos;
        }
        for (int i = 0; i < n; ++i) {
            cin >> npcs[i].dir;
        }

        sort(npcs.begin(), npcs.end(), compareNPC);

        long long collisions = 0;
        int rights = 0;

        for (const auto& npc : npcs) {
            if (npc.dir == 1) {
                rights++;
            } else {
                // Moving left. Will collide with all previous rights.
                collisions += rights;
            }
        }

        cout << collisions << endl;
    }
    return 0;
}
