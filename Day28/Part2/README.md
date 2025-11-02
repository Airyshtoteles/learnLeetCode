# Prime Factor Network

Given an array of distinct positive integers `nums`, build a graph where two numbers are connected if they share a prime factor. Return the number of connected components.

## Approach (Union-Find by Prime)
- Factor each number into primes (trial division up to sqrt; acceptable for moderate sizes).
- For each prime p, union all indices of numbers containing p.
- The number of DSU sets among the indices is the answer.

## Files
- `prime_factor_network.py` — Python DSU + factorization
- `prime_factor_network.cpp` — C++17 DSU + factorization
