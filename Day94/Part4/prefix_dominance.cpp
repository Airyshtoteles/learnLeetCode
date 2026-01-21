#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem 4: Infinite Damage With Prefix Dominance
// Rule: Boss immune if there exists a prefix B with Sum(B) > Sum(A) but Len(B) < Len(A).
// Wait. Reread: "Jika ada dua prefix dengan total damage a < b tapi panjang a > panjang b".
// "If there are two prefixes with Sum A < Sum B but Len A > Len B".
// Then Boss is immune.
// This means we are immune if our chosen path (Prefix A) is "dominated" by some other Prefix B.
// Prefix B has MORE damage and SHORTER length. (High efficiency).
// Prefix A has LESS damage and LONGER length (Low efficiency).
// If A is inefficient compared to B, Boss ignores A.
// Does B need to be in the *same* sequence? Or *any* possible prefix?
// "Infinite Damage Set D". "Rules apply to current attempt".
// Usually implies dominance logic against optimal frontier.
// If we pick Max Damage D_max always:
// Sequence: D_max, D_max...
// States: (1, D_max), (2, 2*D_max)...
// Can we find (l, s) such that s > k*D_max and l < k?
// Max possible sum for len l is l*D_max.
// Since l < k, l*D_max < k*D_max.
// So s < k*D_max.
// Thus s CANNOT be > k*D_max.
// So Max Damage Strategy is never dominated.
// Therefore, YES unless max_d <= 0. Assumed d >= 1.

int main() {
    long long H, N;
    if (!(cin >> H >> N)) return 0;
    
    long long max_d = -1e18; // Allow negatives in input logic purely for checking
    for(int i=0; i<N; ++i){
        long long d;
        cin >> d;
        if(d > max_d) max_d = d;
    }
    
    // If best move is non-positive, we can't reach infinite/positive H.
    if (max_d <= 0) {
        cout << "NO" << endl;
    } else {
        // If we just use max_d repeatedly, we generate Pareto optimal points.
        // No other valid sequence can generate a point that dominates these.
        // So the strategy is valid.
        cout << "YES" << endl;
    }
    
    return 0;
}
