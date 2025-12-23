#include <iostream>
#include <vector>
#include <numeric>
#include <set>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> d(n);
        for (int i = 0; i < n; ++i) cin >> d[i];
        long long H;
        cin >> H;

        // Subset Sum problem.
        // Find if there exists a subset sum S such that H % S == 0.
        // Since N is likely small (standard CP constraint for subset sum is N <= 20 or sum is small).
        // If N is up to 20, 2^20 is 1M, feasible.
        // If N is larger, maybe H is small?
        // Assuming N is small enough for meet-in-the-middle or simple recursion if N <= 20.
        // Or bitset if sum is small.
        // Let's use a set for reachable sums.
        
        set<long long> sums;
        sums.insert(0);
        
        for (int x : d) {
            vector<long long> new_sums;
            for (long long s : sums) {
                new_sums.push_back(s + x);
            }
            for (long long s : new_sums) {
                sums.insert(s);
            }
        }
        
        bool found = false;
        for (long long s : sums) {
            if (s > 0 && H % s == 0) {
                found = true;
                break;
            }
        }
        
        cout << (found ? "1" : "0") << endl;
    }
    return 0;
}
