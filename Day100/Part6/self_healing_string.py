import sys

# Python Segment Tree for "Self-Healing String"
# Operations:
# 1 idx char: Update S[idx] = char
# 2 l r: Can S[l...r] be rearranged to palindrome? (Popcount(XOR) <= 1)

class SegmentTree:
    def __init__(self, s):
        self.n = len(s)
        self.s = list(s)
        self.tree = [0] * (4 * self.n)
        self._build(1, 0, self.n - 1)

    def _get_mask(self, char):
        return 1 << (ord(char) - ord('a'))

    def _build(self, node, start, end):
        if start == end:
            self.tree[node] = self._get_mask(self.s[start])
        else:
            mid = (start + end) // 2
            self._build(2 * node, start, mid)
            self._build(2 * node + 1, mid + 1, end)
            self.tree[node] = self.tree[2 * node] ^ self.tree[2 * node + 1]

    def update(self, idx, char):
        self._update(1, 0, self.n - 1, idx, char)

    def _update(self, node, start, end, idx, char):
        if start == end:
            self.s[idx] = char
            self.tree[node] = self._get_mask(char)
        else:
            mid = (start + end) // 2
            if start <= idx <= mid:
                self._update(2 * node, start, mid, idx, char)
            else:
                self._update(2 * node + 1, mid + 1, end, idx, char)
            self.tree[node] = self.tree[2 * node] ^ self.tree[2 * node + 1]

    def query(self, l, r):
        return self._query(1, 0, self.n - 1, l, r)

    def _query(self, node, start, end, l, r):
        if r < start or end < l:
            return 0
        if l <= start and end <= r:
            return self.tree[node]
        mid = (start + end) // 2
        p1 = self._query(2 * node, start, mid, l, r)
        p2 = self._query(2 * node + 1, mid + 1, end, l, r)
        return p1 ^ p2

def solve():
    input_data = sys.stdin.read().split()
    if not input_data: return
    iterator = iter(input_data)
    
    try:
        N = int(next(iterator))
        Q = int(next(iterator))
        S_str = next(iterator)
        
        st = SegmentTree(S_str)
        
        results = []
        for _ in range(Q):
            type = int(next(iterator))
            if type == 1:
                idx = int(next(iterator))
                c = next(iterator)
                st.update(idx - 1, c)
            else:
                l = int(next(iterator))
                r = int(next(iterator))
                mask = st.query(l-1, r-1)
                
                # Popcount
                odd = bin(mask).count('1')
                results.append("YES" if odd <= 1 else "NO")
                
        sys.stdout.write('\n'.join(results) + '\n')
            
    except StopIteration:
        return

if __name__ == "__main__":
    solve()
