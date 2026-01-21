#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    string s;
    if (!(cin >> s)) return 0;

    map<char, int> counts;
    for (char c : s) {
        counts[c]++;
    }

    string perm = "";
    while (!counts.empty()) {
        string layer = "";
        vector<char> to_remove;
        for (auto& pair : counts) {
            layer += pair.first;
            pair.second--;
            if (pair.second == 0) {
                to_remove.push_back(pair.first);
            }
        }
        for (char c : to_remove) {
            counts.erase(c);
        }
        // Layer is already sorted because map iterates in order
        perm += layer;
    }

    long long total_score = 0;
    long long current_combo = 0;

    if (!perm.empty()) {
        // First char
        current_combo = 1;
        total_score += current_combo;

        for (size_t i = 1; i < perm.length(); ++i) {
            if (perm[i] > perm[i-1]) {
                current_combo++;
            } else {
                current_combo /= 2;
            }
            total_score += current_combo;
        }
    }

    cout << total_score << endl;

    return 0;
}
