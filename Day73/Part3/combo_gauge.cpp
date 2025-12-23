#include <iostream>
#include <set>

using namespace std;

int main() {
    long long a, b;
    if (cin >> a >> b) {
        // Simulation:
        // Start 0.
        // Rule: If val >= b, val -= b. Else val += a.
        // This is a deterministic process that keeps val >= 0.
        // We want to find the number of unique states visited.
        // Since it's deterministic and bounded (max value < a+b), it will loop.
        // The question asks for "panjang maksimum sequence".
        // If it loops, the sequence is infinite.
        // Assuming the question implies "Length of the period" or "Number of unique states".
        // Or maybe "How many steps until it repeats?"
        // Let's output the number of unique states.
        
        // Optimization: This is related to gcd(a, b).
        // The values visited are multiples of gcd(a, b).
        // The number of values is (a+b)/gcd(a,b) ?
        // Let's just simulate with a set for safety, or use math if inputs are huge.
        // Inputs are "int", so maybe up to 2*10^9? Simulation might be too slow.
        // Math:
        // The process is x -> (x + a) if x < b else (x - b).
        // This is equivalent to x -> (x + a) mod (a+b).
        // Wait. If x < b, x+a. If x >= b, x-b = x+a - (a+b).
        // So x_{n+1} = (x_n + a) % (a+b).
        // This is a simple modular addition.
        // The sequence visits values: 0, a, 2a, ... mod (a+b).
        // The number of unique values is (a+b) / gcd(a, a+b).
        // gcd(a, a+b) = gcd(a, b).
        // So count = (a+b) / gcd(a, b).
        
        long long g = a;
        long long temp_b = b;
        while (temp_b) {
            long long r = g % temp_b;
            g = temp_b;
            temp_b = r;
        }
        
        cout << (a + b) / g << endl;
    }
    return 0;
}
