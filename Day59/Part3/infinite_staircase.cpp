#include <iostream>
#include <numeric>

using namespace std;

// Extended Euclidean Algorithm
// Returns gcd(a, b) and updates x, y such that ax + by = gcd(a, b)
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    long long a, b, K;
    if (!(cin >> a >> b >> K)) return 0;

    // We want to minimize n + m
    // Subject to: n*a - m*b = K
    // n = (K + m*b) / a
    // So (K + m*b) % a == 0
    // m*b = -K (mod a)
    // Let g = gcd(b, a)
    // If (-K) % g != 0, impossible.

    long long x, y;
    long long g = extended_gcd(b, a, x, y);

    if (K % g != 0) {
        cout << -1 << endl;
        return 0;
    }

    // Simplify equation: m * (b/g) = (-K/g) (mod a/g)
    long long b_prime = b / g;
    long long a_prime = a / g;
    long long K_prime = (-K / g) % a_prime;
    if (K_prime < 0) K_prime += a_prime;

    // We need inverse of b_prime mod a_prime
    // extended_gcd(b_prime, a_prime, x, y) -> b_prime * x + a_prime * y = 1
    // So x is inverse of b_prime mod a_prime
    long long inv_b, temp_y;
    extended_gcd(b_prime, a_prime, inv_b, temp_y);
    
    inv_b = (inv_b % a_prime + a_prime) % a_prime;

    // m = K_prime * inv_b (mod a_prime)
    long long m = (K_prime * inv_b) % a_prime;

    // Calculate n
    long long n = (K + m * b) / a;

    cout << n + m << endl;

    return 0;
}
