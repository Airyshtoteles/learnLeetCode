#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

long long solve() {
    int n;
    long long H;
    if (!(cin >> n >> H)) return 0;
    
    vector<long long> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    
    // Sort descending to apply largest damage as early as possible
    sort(d.rbegin(), d.rend());
    
    // We execute attacks at t=0, 1, 2...
    // Attack i (0-indexed) deals damage at time i.
    // At time T, all attacks with index <= T have dealt damage.
    // We want minimum T such that sum(d[0]...d[T]) >= H.
    // Wait, if we execute k attacks (indices 0 to k-1), the last one activates at k-1.
    // So at time T, we have executed T+1 attacks?
    // "Serangan ke-i memberi damage d[i] setelah i detik".
    // If we map sorted d to indices 0, 1, 2...
    // d[0] activates at t=0.
    // d[1] activates at t=1.
    // ...
    // At time T, the active damage is sum(d[0]...d[T]).
    // We just need to find smallest T such that prefix_sum[T] >= H.
    
    long long current_sum = 0;
    for (int t = 0; t < n; ++t) {
        current_sum += d[t];
        if (current_sum >= H) {
            return t;
        }
    }
    
    // If we use all attacks and still < H, we can never kill it?
    // Assuming problem guarantees solution or we return -1.
    // Or maybe we can wait? No, damage is "setelah i detik". It happens once.
    // Unless "damage menumpuk" means DoT?
    // "Damage bisa menumpuk" -> Stacking.
    // "Boss mati jika total damage yang sudah aktif >= H".
    // This implies cumulative damage.
    // If sum of all < H, impossible.
    
    return -1;
}

int main() {
    cout << solve() << endl;
    return 0;
}
