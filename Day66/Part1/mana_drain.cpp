#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool solve() {
    int n, M;
    if (!(cin >> n >> M)) return false;
    vector<int> drain(n);
    for (int i = 0; i < n; ++i) cin >> drain[i];

    set<int> visited;
    int current_pos = 0;

    while (M > 0) {
        if (visited.count(current_pos)) return true;
        visited.insert(current_pos);

        M -= drain[current_pos];
        if (M <= 0) return false;

        current_pos = (current_pos + drain[current_pos]) % n;
    }
    return false;
}

int main() {
    if (solve()) cout << "True" << endl;
    else cout << "False" << endl;
    return 0;
}
