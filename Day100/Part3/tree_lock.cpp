#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Problem 3: Infinite Binary Tree Lock
// Labels: 1 (root), 2 (left), 3 (right)...
// Parent = x / 2.
// Constraints:
// Lock(x): OK if no ancestor locked AND no descendant locked.
// Unlock(x): OK if x is locked.
// Upgrade(x): OK if no ancestor locked AND all children locked.
// Unlock children, Lock x.
//
// Operations:
// 1. Lock(x): Check ancestors. Check descendants.
// 2. Unlock(x): Simple map check.
// 3. Upgrade(x): Check ancestors. Check immediate children locked?
//
// Data struct:
// map<long long, int> locked_status.
// Ancestor check: O(log X). Walk up. 60 steps.
// Descendant check: Hard?
// For Lock(x), "No descendant locked".
// Track sub-tree locks count?
// We can use a map `descendant_locked_count`.
// When we lock Y, we increment this counter for all ancestors of Y.
// Lock(X) checks `descendant_locked_count[X] == 0`.
// Upgrade(X):
// "All child locked".
// Infinite tree has infinite children? 
// No, binary tree. Children are 2x, 2x+1.
// Check if 2x and 2x+1 are locked.
// Standard upgrade logic: Convert locks from children to parent.

map<long long, int> is_locked; // User ID who locked it? Or simple bool (1/0)
map<long long, int> locked_in_subtree; // Count of locked nodes in subtree (excluding self?)

bool check_ancestors(long long x) {
    long long curr = x / 2;
    while(curr > 0) {
        if (is_locked.count(curr)) return false; // Ancestor locked
        curr /= 2;
    }
    return true;
}

// Update ancestors count
void update_ancestors(long long x, int val) {
    long long curr = x / 2;
    while(curr > 0) {
        locked_in_subtree[curr] += val;
        curr /= 2;
    }
}

string lock(long long x, int uid) {
    if (is_locked.count(x)) return "false"; // Already locked
    if (!check_ancestors(x)) return "false";
    if (locked_in_subtree[x] > 0) return "false"; // Descendants locked
    
    is_locked[x] = uid;
    update_ancestors(x, 1);
    return "true";
}

string unlock(long long x, int uid) {
    if (!is_locked.count(x)) return "false";
    if (is_locked[x] != uid) return "false"; // Only owner can unlock? Assume yes.
    
    is_locked.erase(x);
    update_ancestors(x, -1);
    return "true";
}

string upgrade(long long x, int uid) {
    // Check ancestors
    if (!check_ancestors(x)) return "false";
    
    // Check if node itself locked? usually must be UNLOCKED to upgrade
    if (is_locked.count(x)) return "false";
    
    // Check children
    long long left = 2 * x;
    long long right = 2 * x + 1;
    
    if (!is_locked.count(left) || !is_locked.count(right)) return "false";
    
    // Usually need same UID? Or just locked?
    // "Unlocked children, Lock x".
    // Assume ANY lock on children works? Or strictly owned?
    // "Upgrade ... hanya boleh ...".
    // Let's assume ownership required or just locked status.
    // Standard version requires Same UID.
    if (is_locked[left] != uid || is_locked[right] != uid) return "false"; // Assume ownership match
    
    // Perform upgrade
    is_locked.erase(left);
    update_ancestors(left, -1); // Remove left from tree stats
    
    is_locked.erase(right);
    update_ancestors(right, -1); // Remove right from tree stats
    
    // Now lock X
    is_locked[x] = uid;
    update_ancestors(x, 1);
    
    return "true";
}

int main() {
    int Q;
    if (!(cin >> Q)) return 0;
    
    while(Q--) {
        string op;
        long long x;
        int uid;
        cin >> op >> x >> uid;
        
        if (op == "lock") cout << lock(x, uid) << endl;
        else if (op == "unlock") cout << unlock(x, uid) << endl;
        // Check exact input syntax "upgrade" or "upgrade(x)"?
        // Assume "upgrade x uid"
        else if (op == "upgrade") cout << upgrade(x, uid) << endl;
    }
    return 0;
}
