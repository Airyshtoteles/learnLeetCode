#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

// Problem 4: Infinite Damage With Forbidden Growth Rate
// Rule: Average must strictly increase? "Pernah tidak meningkat" => "Ever Not Increasing".
// So Avg[k+1] > Avg[k].
// Condition: x_{k+1} > Avg[k].
// Greedy Strategy: Always pick smallest valid D from set to prolong sequence.
// Sequence: x1 (min valid), x2 (min > avg), ...
// If we can extend indefinitely or reach sum >= H.
// Actually, if we pick max(D) only, avg stays constant. "Not Increasing" violation.
// So we must increase average.
// Eventually we run out of values > max(D) (impossible).
// So sequence is finite.
// We compute max total sum possible using greedy strategy.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;
    
    vector<long long> D(N);
    for(int i=0; i<N; ++i) cin >> D[i];
    
    // Sort D
    sort(D.begin(), D.end());
    
    // Simulation
    long long current_sum = 0;
    int steps = 0;
    double current_avg = -1.0;
    
    // Step 1: Pick smallest d
    // Avg starts undefined? Or 0?
    // "Rata-rata damage per langkah pernah tidak meningkat".
    // 1st step: Avg_1 = x1. Previous Avg? Undefined. Assumption: Valid.
    // 2nd step: Avg_2 > Avg_1.
    
    bool possible = false;
    
    // We can just keep picking smallest d > current_avg.
    // Loop until H reached or no valid d.
    
    while (true) {
        // Find smallest d > current_avg
        double target = current_avg;
        if (steps == 0) target = -1.0; // Accept anything for first step
        
        long long best_d = -1;
        bool found = false;
        
        // Binary search or linear scan
        for (long long val : D) {
            if (val > target) { // Strictly greater? Yes.
                // Wait. If steps > 0, we need Avg_{k+1} > Avg_k.
                // Avg_{k+1} = (Sum + val) / (steps + 1).
                // (Sum + val)/(steps+1) > Sum/steps
                // steps*Sum + steps*val > steps*Sum + Sum
                // steps*val > Sum
                // val > Sum/steps = Avg_k.
                // Correct.
                
                // We want Smallest valid val to minimize Avg growth?
                // Yes, keeping Avg low allows more future steps.
                best_d = val;
                found = true;
                break;
            }
        }
        
        if (!found) break; // Cannot increase average
        
        current_sum += best_d;
        steps++;
        current_avg = (double)current_sum / steps;
        
        if (current_sum >= H) {
            possible = true;
            break;
        }
    }
    
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
