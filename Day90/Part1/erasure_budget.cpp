#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Boss With Prefix Erasure Budget
// Boss HP H. Budget K.
// "Prefix damage >= H" -> Boss can remove prefix (cost 1).
// To kill, we need to trigger this K+1 times.
// Resources (attacks) are consumable? Assuming yes.
// Strategy: Use largest attacks first to minimize count.
// Form K+1 segments each summing >= H.

int main() {
    long long H;
    int K, N;
    if (!(cin >> H >> K >> N)) return 0;

    vector<long long> D(N);
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
    }

    sort(D.begin(), D.end(), greater<long long>());

    int needed_stages = K + 1;
    int cards_used = 0;
    int current_stage = 0;
    
    int idx = 0;
    while (current_stage < needed_stages && idx < N) {
        long long current_sum = 0;
        // Greedily take cards for this stage
        while (current_sum < H && idx < N) {
            current_sum += D[idx];
            idx++;
        }

        if (current_sum >= H) {
            current_stage++;
        } else {
            // Ran out of cards before finishing this stage
            break; 
        }
    }

    if (current_stage >= needed_stages) {
        cout << idx << endl; // Total cards used
    } else {
        cout << -1 << endl;
    }

    return 0;
}
