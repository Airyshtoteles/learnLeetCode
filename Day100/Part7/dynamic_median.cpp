#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Problem 7: Dynamic Median
// Maintain a set of numbers with Add, Remove, and Query Median operations.
// 
// Algorithm: Two Heaps (Min-Heap and Max-Heap) with Lazy Deletion.
// - lower: Max-Heap (stores smaller half)
// - upper: Min-Heap (stores larger half)
// - Balance: lower.size() == upper.size() OR lower.size() == upper.size() + 1
// 
// Lazy Deletion:
// - Track count of values to be removed in an unordered_map.
// - unique clean() function that pops top of heaps if it's marked as deleted.

class DynamicMedian {
    priority_queue<long long> lower; // Max-heap
    priority_queue<long long, vector<long long>, greater<long long>> upper; // Min-heap
    unordered_map<long long, int> deleted;
    int lower_active = 0;
    int upper_active = 0;

    void clean_lower() {
        while (!lower.empty() && deleted[lower.top()] > 0) {
            deleted[lower.top()]--;
            lower.pop();
        }
    }

    void clean_upper() {
        while (!upper.empty() && deleted[upper.top()] > 0) {
            deleted[upper.top()]--;
            upper.pop();
        }
    }

    void balance() {
        // clean() before checking sizes? 
        // No, size() includes deleted elements. We need active counts.
        // But active counts are hard to track inside heap structure without cleaning.
        // Strategy: We maintain 'lower_active' and 'upper_active' counters manually.
        // We only clean() when accessing top().
        
        while (lower_active > upper_active + 1) {
            clean_lower();
            long long val = lower.top();
            lower.pop();
            lower_active--;
            
            upper.push(val);
            upper_active++;
        }
        
        while (upper_active > lower_active) {
            clean_upper();
            long long val = upper.top();
            upper.pop();
            upper_active--;
            
            lower.push(val);
            lower_active++;
        }
    }

public:
    void add(long long x) {
        // Heuristic insertion
        if (lower.empty()) {
            lower.push(x);
            lower_active++;
            return;
        }

        clean_lower();
        if (x <= lower.top()) {
            lower.push(x);
            lower_active++;
        } else {
            upper.push(x);
            upper_active++;
        }
        balance();
    }

    void remove(long long x) {
        // Check if exists?
        // Assuming valid removal query for this problem context.
        // Which heap is it in?
        // We don't know easily.
        // But we know x <= lower.top() -> likely in lower.
        // Wait, lazy deletion means we just Increment delete count.
        // But we must decrement active counter!
        // Where is it?
        // If x <= lower.top(), it SHOULD be in lower. 
        // Care needed: If x was in lower but now sitting in deleted set, active/non-active logic applies.
        
        // Correct Logic for Lazy Deletion Active Counts:
        // We need to know if 'x' is effectively in lower or upper.
        // We can compare with current EFFECTIVE split point.
        
        clean_lower();
        clean_upper();
        
        // If empty?
        if (lower_active == 0 && upper_active == 0) return;

        long long split = lower.top();
        
        if (x <= split) {
            if (lower_active > 0) { // Safety
                lower_active--;
                deleted[x]++;
            }
        } else {
            if (upper_active > 0) {
                upper_active--;
                deleted[x]++;
            }
        }
        balance();
    }

    double getMedian() {
        clean_lower();
        clean_upper();
        
        if (lower_active == 0) return 0;
        
        if (lower_active > upper_active) {
            return (double)lower.top();
        } else {
            return ((double)lower.top() + (double)upper.top()) / 2.0;
        }
    }
    
    // Debug helper
    int size() { return lower_active + upper_active; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Q;
    if (!(cin >> Q)) return 0;
    
    DynamicMedian dm;
    
    for(int i=0; i<Q; ++i) {
        string type;
        cin >> type;
        if (type == "add") {
            long long x;
            cin >> x;
            dm.add(x);
        } else if (type == "remove") {
            long long x;
            cin >> x;
            dm.remove(x);
        } else if (type == "median") {
            if (dm.size() == 0) cout << "Empty" << endl;
            else cout << dm.getMedian() << endl;
        }
    }
    
    return 0;
}
