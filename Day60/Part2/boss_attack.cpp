#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
long long H;
vector<long long> attacks;

bool canAchieve(long long maxDamage) {
    // Check if we can keep all prefix sums <= maxDamage with <= K shuffles
    // Greedy: process left to right, whenever prefix exceeds, use a shuffle
    
    vector<long long> A = attacks;
    long long currentHP = H;
    int shuffles_used = 0;
    
    for (int i = 0; i < N; ++i) {
        currentHP -= A[i];
        
        if (currentHP < -maxDamage) {
            // Need to shuffle
            if (shuffles_used >= K) return false;
            
            // Find optimal shuffle range ending at i
            // We want to minimize damage up to i
            // Sort descending order (smallest damage first)
            // Actually, we want smallest attacks first to preserve HP
            
            // Greedy: shuffle [0, i] to put smallest attacks first
            sort(A.begin(), A.begin() + i + 1);
            
            shuffles_used++;
            
            // Recalculate from start
            currentHP = H;
            for (int j = 0; j <= i; ++j) {
                currentHP -= A[j];
                if (currentHP < -maxDamage) return false;
            }
        }
    }
    
    return true;
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N >> K >> H)) return 0;
    
    attacks.resize(N);
    for (int i = 0; i < N; ++i) cin >> attacks[i];
    
    // Binary search on max damage
    long long left = 0, right = 1e15;
    long long answer = right;
    
    while (left <= right) {
        long long mid = (left + right) / 2;
        
        if (canAchieve(mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
