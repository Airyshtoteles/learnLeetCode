#include <bits/stdc++.h>
using namespace std;

int singleNumber(const vector<int>& nums) {
    int acc = 0;
    for (int v : nums) acc ^= v;
    return acc;
}

int main() {
    cout << singleNumber({4,1,2,1,2}) << '\n';
    cout << singleNumber({2,2,3}) << '\n';
}
