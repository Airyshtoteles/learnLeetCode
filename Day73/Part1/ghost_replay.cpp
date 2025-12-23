#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    // Reading input. Assuming standard format: n then elements, or just elements until EOF.
    // The problem description says "move = int[]".
    // I'll try to read n first if available, or just count elements.
    // Let's assume the input stream contains the array.
    // If the first number is n, and then n numbers follow.
    
    if (cin >> n) {
        // Heuristic: if n is small and followed by n numbers, it's count.
        // If n is part of the array?
        // Usually in these problems, n is provided.
        // Let's assume n is the count.
        
        // If n <= 0, output 0.
        if (n <= 0) {
            cout << 0 << endl;
            return 0;
        }
        
        // Read n elements (we don't actually need them for the logic N-1)
        vector<int> moves(n);
        for(int i=0; i<n; ++i) cin >> moves[i];
        
        // Logic: We must skip exactly one continuous segment.
        // To maximize the remaining length, we skip the shortest possible segment.
        // Shortest non-empty segment has length 1.
        // So max length is N - 1.
        // If N=0, 0.
        
        cout << (n > 0 ? n - 1 : 0) << endl;
    }
    return 0;
}
