#include <iostream>
#include <vector>
#include <numeric>
#include <queue>

using namespace std;

struct Node {
    long long val;
    int prev;
    int next;
    bool active;
};

struct Reduction {
    long long gain;
    int left_idx;
    
    bool operator<(const Reduction& other) const {
        return gain < other.gain;
    }
};

long long solve_arcane_damage(int N, vector<long long>& A, int K) {
    if (N == 0) return 0;
    
    vector<Node> nodes(N);
    long long current_sum = 0;
    
    for (int i = 0; i < N; ++i) {
        nodes[i].val = A[i];
        nodes[i].prev = i - 1;
        nodes[i].next = i + 1;
        nodes[i].active = true;
        current_sum += A[i];
    }
    nodes[N - 1].next = -1;
    
    priority_queue<Reduction> pq;
    
    auto calculate_gain = [&](int i) -> long long {
        if (i < 0 || nodes[i].next == -1) return -1;
        int j = nodes[i].next;
        long long u = nodes[i].val;
        long long v = nodes[j].val;
        // Reduction = (u + v) - (u ^ v) = 2 * (u & v)
        return 2 * (u & v);
    };
    
    for (int i = 0; i < N - 1; ++i) {
        long long g = calculate_gain(i);
        pq.push({g, i});
    }
    
    int ops = 0;
    while (ops < K && !pq.empty()) {
        Reduction top = pq.top();
        pq.pop();
        
        int i = top.left_idx;
        
        // Check validity
        if (!nodes[i].active) continue;
        int j = nodes[i].next;
        if (j == -1 || !nodes[j].active) continue;
        
        // Check if gain is still valid (values might have changed? No, values only change if merged)
        // But if neighbors merged, i might have been removed. Checked by active.
        // If i was updated, we need to ensure this PQ entry corresponds to current state.
        // Actually, if we merge i and j, i stays active with new value.
        // But the gain in PQ was calculated with OLD value.
        // We need a way to validate the gain.
        // We can store a "version" or just re-calculate and check?
        // Re-calculation is safer.
        
        long long current_gain = calculate_gain(i);
        if (current_gain != top.gain) {
            // Stale entry, ignore (or push new if valid? No, new one would have been pushed when updated)
            // Wait, if we update i, we push new gain. The old gain stays in PQ.
            // So if current_gain != top.gain, it means this is old.
            continue;
        }
        
        // Perform merge
        // Merge i and j into i
        long long u = nodes[i].val;
        long long v = nodes[j].val;
        long long new_val = u ^ v;
        
        current_sum -= top.gain;
        
        nodes[i].val = new_val;
        nodes[j].active = false;
        
        // Update links
        int k = nodes[j].next;
        nodes[i].next = k;
        if (k != -1) {
            nodes[k].prev = i;
        }
        
        // Push new potential merges
        // i with new next (k)
        if (k != -1) {
            pq.push({calculate_gain(i), i});
        }
        
        // prev with i
        int p = nodes[i].prev;
        if (p != -1) {
            pq.push({calculate_gain(p), p});
        }
        
        ops++;
    }
    
    return current_sum;
}

int main() {
    // Example 1: [3, 1, 3], K=1
    // Pairs: (3,1) -> gain 2*(3&1)=2. (1,3) -> gain 2.
    // Merge (3,1) -> [2, 3]. Sum 5.
    // Original sum 7. Reduction 2.
    vector<long long> A1 = {3, 1, 3};
    cout << "Test 1: " << solve_arcane_damage(3, A1, 1) << endl;
    
    // Example 2: [7, 7, 7], K=2
    // (7,7) -> gain 14.
    // Merge -> [0, 7]. Sum 7.
    // Next (0,7) -> gain 0.
    // Merge -> [7]. Sum 7.
    // Total sum 7.
    vector<long long> A2 = {7, 7, 7};
    cout << "Test 2: " << solve_arcane_damage(3, A2, 2) << endl;
    
    return 0;
}
