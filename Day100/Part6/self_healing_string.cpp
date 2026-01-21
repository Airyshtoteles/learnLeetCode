#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Problem 6: Self-Healing String
// "Can the substring S[l...r] be rearranged to form a palindrome?"
// AND: "Update S[i] = c".
//
// Logic: A string can be rearranged into a palindrome iff
// at most one character appears an odd number of times.
// We maintain the parity of character counts for each substring using a Segment Tree.
//
// State: A bitmask of length 26.
// 'a' flips bit 0, 'b' flips bit 1, ...
// XOR sum processing. 
// Query(l, r) -> get XOR sum of range.
// Check popcount(mask) <= 1.
//
// Complexity: O(log N) per update/query. 26 bits fits in int.

struct SegmentTree {
    int n;
    string S;
    vector<int> tree;

    SegmentTree(string s) : S(s) {
        n = s.length();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = (1 << (S[start] - 'a'));
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] ^ tree[2 * node + 1];
        }
    }

    void update(int idx, char new_val) {
        updatePtr(1, 0, n - 1, idx, new_val);
    }

    void updatePtr(int node, int start, int end, int idx, char new_val) {
        if (start == end) {
            S[idx] = new_val;
            tree[node] = (1 << (S[idx] - 'a'));
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                updatePtr(2 * node, start, mid, idx, new_val);
            } else {
                updatePtr(2 * node + 1, mid + 1, end, idx, new_val);
            }
            tree[node] = tree[2 * node] ^ tree[2 * node + 1];
        }
    }

    int query(int l, int r) {
        return queryPtr(1, 0, n - 1, l, r);
    }

    int queryPtr(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int p1 = queryPtr(2 * node, start, mid, l, r);
        int p2 = queryPtr(2 * node + 1, mid + 1, end, l, r);
        return p1 ^ p2;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    if (!(cin >> N >> Q)) return 0;
    
    string S;
    cin >> S;

    SegmentTree st(S);

    for(int i=0; i<Q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx;
            char c;
            cin >> idx >> c;
            // 1-based index input usually? Let's assume 1-based for problem consistency
            st.update(idx - 1, c);
        } else {
            int l, r;
            cin >> l >> r;
            int mask = st.query(l - 1, r - 1);
            // Check popcount
            // Built-in popcount
            int odd_counts = 0;
            while(mask > 0) {
                if (mask & 1) odd_counts++;
                mask >>= 1;
            }
            if (odd_counts <= 1) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
