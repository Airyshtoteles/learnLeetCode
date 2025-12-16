#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> spells(n);
        for (int i = 0; i < n; ++i) cin >> spells[i];

        vector<long long> stack;
        for (int x : spells) {
            long long current = x;
            while (!stack.empty() && stack.back() == current) {
                stack.pop_back();
                current *= 2;
            }
            stack.push_back(current);
        }

        long long total_damage = 0;
        for (long long val : stack) {
            total_damage += val;
        }
        cout << total_damage << endl;
    }
    return 0;
}
