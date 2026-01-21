#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Problem 4: Infinite Damage With Kolmogorov Bound
// Rule: Complexity K(Prefix) < K.
// Maximize sum.
// Key insight:
// Low complexity strings (like M ones '11...1') have low K-complexity.
// K(S) ~ log(Length).
// Condition: log(Length) < K.
// Length < 2^K.
// Max Length M = 2^K - 1.
// If valid string is all 1s, its integer value is roughly 2^M.
// Value ~ 2^(2^K).
// For K >= 6, this is 2^64 (huge).
// For K >= 7, it exceeds any Boss HP H fit for typical inputs.
// So simple check: Can we construct a string with value >= H?
// Using '1's: 1 (val 1), 11 (val 3), 111 (val 7)...
// Value for length L is 2^L - 1.
// We need 2^L - 1 >= H.
// L >= log2(H + 1).
// Complexity Constraint: L must be "simple".
// Simple string of ones has complexity roughly log2(L).
// e.g. "Print L ones". L requires log2(L) bits.
// So we need log2(L) < K.
// Combining: L < 2^K.
// So 2^K > log2(H+1).
// 2^K >= ceil(log2(H+1)).
// Check this.

int main() {
    long long H;
    int K;
    if (!(cin >> H >> K)) return 0;
    
    // We can use string '11...1'.
    // Length L.
    // Value = 2^L - 1.
    // Complexity approx log2(L).
    // Constraint: log2(L) < K  =>  L < 2^K.
    // We need 2^L - 1 >= H.
    // Max_L = 2^K - 1 (being safe).
    // Max_Value = 2^(Max_L) - 1.
    // Is Max_Value >= H?
    
    if (H == 0) { cout << "YES" << endl; return 0; }
    
    // Calculate Max_L
    // If K >= 60, overflow potential if we compute 2^K directly in int steps.
    // But H fits in long long (64 bit).
    // If Max_L >= 64, we can definitely kill H.
    // 2^K >= 64 => K >= 6.
    
    if (K >= 6) {
        cout << "YES" << endl;
    } else {
        // K is small (1..5).
        // Max L = 2^K. (approx).
        long long max_L = 1LL << K; 
        // We use slightly less because complexity adds overhead?
        // Prompt says "Bitstring as long as you want".
        // "Kolmogorov complexity of prefix < K".
        // "Prefix" includes the full string.
        // Let's rely on loose bound: L = 2^K - C.
        // Assuming C is small.
        // If 2^(2^K) >= H.
        // Let's compute actual attainable value.
        // K=1 -> L=2 -> Val=3.
        // K=2 -> L=4 -> Val=15.
        // K=3 -> L=8 -> Val=255.
        // ...
        // We check 2^max_L - 1 >= H.
        
        // Actually, be conservative. Maybe strict inequality?
        // "Prefix complexity < K".
        // K=1 implies complexity 0? Usually means 1 bit allowed.
        // Let's assume max L = 2^K.
        
        // Calculate 2^L - 1 safely
        long long attained_val = 0;
        // If max_L >= 63, it covers H.
        if (max_L >= 62) {
             cout << "YES" << endl;
        } else {
             // max_L is small (<62).
             // Compute 2^max_L
             unsigned long long capacity = 1ULL << max_L;
             capacity--; // 2^L - 1
             
             if (capacity >= (unsigned long long)H) {
                 cout << "YES" << endl;
             } else {
                 cout << "NO" << endl;
             }
        }
    }

    return 0;
}
