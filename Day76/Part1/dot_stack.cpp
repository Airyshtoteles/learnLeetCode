#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

long long solve() {
    int n;
    long long H;
    if (!(cin >> n >> H)) return 0;
    
    vector<int> dot(n);
    for (int i = 0; i < n; ++i) {
        cin >> dot[i];
    }
    
    sort(dot.rbegin(), dot.rend());
    
    long long min_time = -1;
    
    long long current_rate = 0;
    long long damage_during_setup = 0;
    
    for (int k = 1; k <= n; ++k) {
        // Add k-th DoT (index k-1)
        // At second k, we have applied k DoTs.
        // The k-th DoT contributes 1 tick at second k.
        // The previous ones contribute 1 tick each at second k.
        // Total damage added at step k is (sum of first k dots).
        
        current_rate += dot[k-1];
        damage_during_setup += current_rate;
        
        long long time_needed;
        if (damage_during_setup >= H) {
            // We reached H during setup.
            // We need to find exactly when.
            // But since we are iterating k, and we want global min,
            // we can just approximate or be precise.
            // If we reached it at step k, time is k.
            // Could we have reached it at step k-1? Yes, but that would be handled in previous iteration.
            // Could we have reached it between k-1 and k? No, discrete seconds.
            time_needed = k;
        } else {
            long long remaining = H - damage_during_setup;
            long long wait_ticks = (remaining + current_rate - 1) / current_rate;
            time_needed = k + wait_ticks;
        }
        
        if (min_time == -1 || time_needed < min_time) {
            min_time = time_needed;
        }
    }
    
    return min_time;
}

int main() {
    cout << solve() << endl;
    return 0;
}
