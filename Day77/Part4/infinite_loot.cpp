#include <iostream>
#include <vector>

using namespace std;

long long solve() {
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    
    if (n == 0) return 0;
    
    long long total_value = 0;
    long long prev_loot = -1; // No previous loot initially? Or assume 0?
    // "Jika loot yang diambil lebih kecil dari loot sebelumnya"
    // For the first item, there is no "previous".
    // Usually implies condition doesn't trigger.
    // Or maybe prev is initialized to 0?
    // If prev=0, and v[0] > 0, then v[0] not < prev. Value = v[0].
    // Let's assume first item is taken as is.
    
    // Wait, "Nilainya dilipatgandakan".
    // Does "loot sebelumnya" refer to the *value* obtained, or the *original* loot size?
    // "Loot memiliki nilai v[i]". "Jika loot yang diambil (v[i]) lebih kecil dari loot sebelumnya (v[i-1])".
    // Usually refers to the item property v[i].
    
    // Let's trace:
    // i=0: Take v[0]. Value += v[0]. Prev = v[0].
    // i=1: If v[1] < v[0], Value += v[1]*2. Else Value += v[1]. Prev = v[1].
    
    // Is "Prev" the original v[i-1] or the modified value?
    // "Loot sebelumnya" -> "Previous loot". Usually the item itself.
    
    if (n > 0) {
        total_value += v[0];
        prev_loot = v[0];
    }
    
    for (int i = 1; i < n; ++i) {
        long long current_val = v[i];
        if (v[i] < v[i-1]) {
            current_val *= 2;
        }
        total_value += current_val;
        // prev_loot is v[i] (original) for next comparison
    }
    
    return total_value;
}

int main() {
    cout << solve() << endl;
    return 0;
}
