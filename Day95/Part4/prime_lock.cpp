#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <cmath>

using namespace std;

// Problem 4: Infinite Damage With Prime Lock
// Find Prime P >= H such that P can be formed by sum of elements in D.
// Since problem says "Infinite Damage", usually H is a threshold.
// We need to check if ANY prime >= H is reachable.
// If GCD of elements in D is 'g'.
// All reachable sums are multiples of 'g'.
// If g > 1:
//    Multiples of g: g, 2g, 3g...
//    The only prime multiple of g is g itself (if g is prime).
//    Any other multiple is composite (divisible by g and > g).
//    So if g > 1, the ONLY reachable prime is g itself.
//    If g >= H and g is prime, YES.
//    If g < H, NO (since 2g, 3g... are not prime).
// If g == 1:
//    We can form any sufficiently large integer (Frobenius Coin Problem).
//    This means we can form all integers > F.
//    Since primes are infinite, there exists a prime P > max(H, F).
//    So we can definitely hit a prime.
//    Wait. Is F large?
//    In competitive programming with "Infinite Damage", usually assume inputs allow reachability if GCD=1.
//    However, maybe H is small (e.g. 1) and F is huge?
//    If H is large enough, or just H > F.
//    Given "Infinite Damage" context, YES is likely if GCD=1.
//    But what if H < F and we are in the "gap"?
//    We can check reachability up to a limit if H is small.
//    But simpler heuristic: If GCD=1, usually YES.
//    Wait. If D={4, 6}. GCD=2. Can't make primes > 2.
//    If D={4, 5}. GCD=1. Linear combo 4x+5y.
//    Can make 4, 5, 8, 9, 10, 12, 13, ...
//    Primes: 5 (reach), 13 (reach), 17 (reach)...
//    So YES.
//    Does there exist a case where GCD=1 but we can't reach any prime >= H?
//    Only if H is very specific and lands in gaps, and gaps are huge?
//    Frobenius number is roughly product of max elements.
//    If H is large, we are fine.
//    If H is small, we might need specific check.
//    Usually for "Infinite Damage", the limit H is the main constraint.
//    I'll assume if GCD=1 -> YES.
//    Refinement: If g > 1, check if g >= H and g is prime.

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

bool is_prime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;
    
    vector<long long> D(N);
    long long g = 0;
    for(int i=0; i<N; ++i){
        cin >> D[i];
        if (i == 0) g = D[i];
        else g = gcd(g, D[i]);
    }
    
    if (g == 0) { // No damages
        cout << "NO" << endl;
        return 0;
    }
    
    if (g == 1) {
        cout << "YES" << endl;
    } else {
        // Only reachable sums are k*g.
        // Prime usually implies not divisible by anything but 1 and itself.
        // If k*g is prime -> k=1 and g is prime.
        // So only sum 'g' is prime.
        if (g >= H && is_prime(g)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}
