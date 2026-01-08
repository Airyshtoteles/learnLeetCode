#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Problem: Infinite Damage With Density Constraint
// Window length K, at least P distinct values.
// Base values D[i].
// Can we kill Boss HP H?
// If we have >= P distinct positive values:
// Cycle them in a window of size P (or K, padding with repeats).
// If we create a sequence repeating pattern of length M (where M <= K or whatever),
// with P distinct values, and sum > 0.
// Then Total Damage -> Infinity because terms are scaled by index i.
// Condition:
// 1. We must be able to form a window of size K with >= P distinct values.
//    This requires total available distinct values >= P.
// 2. We need the sum of the sequence to grow positive.
//    Simply: If we can pick P distinct values such that Sum(Values) > 0?
//    Or Sum(Window) > 0.
//    If we repeat a block of P values: v1, v2, ..., vP.
//    Distinct count = P. Length = P.
//    If P <= K, valid.
//    Sum growth depends on Sum(v).
//    Optimal: Pick the largest P distinct values available.
//    If their sum is positive, we win.
//    Also, we can use *more* than P values if they help (e.g. all positives).
//    But constraint says "at least P distinct".
//    Strategy:
//    Take all Positive Distinct Values. Let count be C_pos.
//    If C_pos >= P, then we just use these. Sum is positive. YES.
//    If C_pos < P, we MUST introduce (P - C_pos) distinct negative values.
//    Pick the ones close to 0 (largest negatives).
//    Check Sum(Positives) + Sum(Best Negatives).
//    If > 0, YES.
//    Else NO (cannot sustain positive growth with required variety).
//    Wait, "Damage ke-i dikalikan i".
//    Yes, if base sum > 0, weighted sum grows quadratically.

int main() {
    long long H;
    int N, K, P;
    if (!(cin >> H >> N >> K >> P)) return 0;

    set<int> distinct_D;
    for (int i = 0; i < N; ++i) {
        int val;
        cin >> val;
        distinct_D.insert(val);
    }

    if (distinct_D.size() < P) {
        cout << "Impossible" << endl;
        return 0;
    }

    // Convert set to vector sorted descending
    vector<int> sorted_D(distinct_D.rbegin(), distinct_D.rend());

    // Pick top P
    long long sum_P = 0;
    int count = 0;
    for (int val : sorted_D) {
        // We greedily pick positives.
        if (val > 0) {
            sum_P += val;
            count++;
        } else {
            // Need to pick more to reach P?
            if (count < P) {
                sum_P += val;
                count++;
            }
        }
    }
    
    // If we picked all positives and still count < P, we added negatives.
    // If we picked P items (mix of pos and neg), sum_P is the best sum for size P.
    // But we are allowed to use *more* than P distinct values?
    // "Window length K, at least P distinct".
    // If we use *all* positives (say 100) and P=10, we satisfy ">= P distinct".
    // And Sum is better.
    // So logic:
    // 1. Sum of All Positive Distinct values.
    // 2. If count(Positives) < P, add best negatives until count == P.
    // 3. If final sum > 0 -> Possible.

    // My code above does:
    // Adds all positives first.
    // Then adds negatives only if needed to reach P.
    // This correctly maximizes the sum while satisfying "size >= P".
    
    if (sum_P > 0) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
