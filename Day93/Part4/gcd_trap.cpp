#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Problem 4: Infinite Damage With GCD Trap
// Rule: Boss Immune if GCD(Used_Damages) != 1.
// Goal: Kill boss (Damage >= H).
// Strategy: Can we form sum >= H with GCD == 1?
// We can use any combination of available damages with repetition.
// If GCD of ALL available damages is 1, then there exists a linear combination with GCD 1.
// By Frobenius Coin Problem logic / Chicken McNugget Theorem:
// If set has GCD 1, all sufficiently large numbers are representable.
// "Sufficiently large" is usually around product of max elements.
// Since problem says "Infinite Damage", we assume H can be large.
// Is it possible to be STUCK with GCD > 1?
// Only if the GCD of ALL available numbers is > 1.
// If GCD(D_all) = g > 1, then ANY combination will be multiple of g.
// The "Immunity" rule says: Boss is immune if GCD != 1.
// So if GCD(D_all) > 1, we can NEVER drop immunity to 1.
// Thus damage is effectively 0. Boss cannot be killed.
// If GCD(D_all) == 1, we can craft a sequence with GCD 1.
// Once GCD is 1, we can add arbitrarily many attacks to reach >= H.
// Wait, is it possible H is SMALL and unrepresentable?
// "Infinite Damage" suggests the capability is the question.
// "Assuming H is large enough or covers the representable range".
// But technically, if H=1 and available={2,3}. GCD=1. But min sum with GCD 1 is 2+3=5 (or 2,3 -> gcd 1 sum 5).
// Actually, with {2, 3}:
// Seq: 2, 3. GCD of {2,3} is 1. Sum is 5.
// If H=1, Sum 5 >= 1. Dead.
// Seq: 2, 3, 2, ...
// So unless H < Min_Sum_To_Get_GCD1, it works.
// We assume H is reasonably large or standard reachability.
// The core constraint is GCD(All) == 1.

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    long long H, N;
    if (!(cin >> H >> N)) return 0;
    
    long long current_gcd = 0;
    bool any_input = false;
    
    for (int i = 0; i < N; ++i) {
        long long d;
        cin >> d;
        if (!any_input) {
            current_gcd = d;
            any_input = true;
        } else {
            current_gcd = gcd(current_gcd, d);
        }
    }
    
    if (!any_input) {
        cout << "NO" << endl;
        return 0;
    }
    
    if (current_gcd == 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}
