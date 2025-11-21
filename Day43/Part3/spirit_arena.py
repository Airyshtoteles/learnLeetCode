import sys

# Increase recursion depth for deep DSU trees
sys.setrecursionlimit(200000)

class SpiritArena:
    def __init__(self, n, powers):
        self.n = n
        self.parent = list(range(n))
        self.power = powers[:]
        self.num_clans = n
        
        # jump[i] points to the next spirit index to check
        # Initially i -> (i+1)%n
        self.jump = [(i + 1) % n for i in range(n)]

    def find_clan(self, i):
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find_clan(self.parent[i])
        return self.parent[i]

    def union_clans(self, i, j):
        root_i = self.find_clan(i)
        root_j = self.find_clan(j)
        if root_i != root_j:
            # Merge j into i (arbitrary, or by size/power?)
            # Problem says "absorbs weak".
            # But for "Link", we just merge.
            self.parent[root_j] = root_i
            self.power[root_i] += self.power[root_j]
            self.num_clans -= 1
            return root_i
        return root_i

    def get_next_different_clan_spirit(self, start_node):
        # Find the first node clockwise from start_node that belongs to a different clan
        root_start = self.find_clan(start_node)
        
        curr = self.jump[start_node]
        
        # Path compression on jump pointers
        # We traverse until we find a node with different clan
        # While traversing, we update jump pointers to skip same-clan nodes
        
        path = []
        while True:
            root_curr = self.find_clan(curr)
            if root_curr != root_start:
                # Found neighbor
                target = curr
                break
            
            # curr is in same clan, move to next
            path.append(curr)
            curr = self.jump[curr]
            
            # Safety break for single clan remaining
            if curr == start_node:
                return -1 # No other clan
        
        # Update jumps
        # All nodes in 'path' (and start_node) can jump directly to target
        # But we only update start_node's jump for now to avoid O(N)
        # Actually, path compression:
        self.jump[start_node] = target
        for p in path:
            self.jump[p] = target
            
        return target

    def process_event(self, type, a, b=None):
        if type == "link":
            self.union_clans(a, b)
        elif type == "battle":
            # Clan of a attacks neighbor
            root_a = self.find_clan(a)
            
            # Find neighbor
            # We start searching from 'a'. 
            # Note: 'a' might not be the "rightmost" in any geometric sense if links are arbitrary.
            # But we defined neighbor as "scan clockwise from x".
            target_spirit = self.get_next_different_clan_spirit(a)
            
            if target_spirit == -1:
                return # Only 1 clan left
                
            root_target = self.find_clan(target_spirit)
            
            # Battle logic
            p_a = self.power[root_a]
            p_t = self.power[root_target]
            
            if p_a > p_t:
                # A absorbs Target
                self.union_clans(a, target_spirit)
                # Update jump of a to skip the absorbed part?
                # Next query will handle it via path compression.
            else:
                # Target absorbs A (or A loses)
                # "clan dengan total power lebih besar menyerap clan lemah"
                # If equal? Assume A absorbs T or T absorbs A?
                # Let's assume T absorbs A if p_t >= p_a
                self.union_clans(target_spirit, a)

def solve():
    # Example usage
    n = 5
    powers = [10, 20, 30, 40, 50]
    arena = SpiritArena(n, powers)
    
    events = [
        ("link", 0, 2),
        ("battle", 0), # Clan {0,2} (pow 40) vs neighbor of 0.
                       # 0->1 (pow 20). 1 is diff clan.
                       # 40 > 20. {0,2} absorbs {1}. Clan {0,1,2} pow 60.
        ("battle", 2)  # Clan {0,1,2} (pow 60) vs neighbor of 2.
                       # 2->3 (pow 40). 3 is diff.
                       # 60 > 40. Absorbs {3}. Clan {0,1,2,3} pow 100.
    ]
    
    for ev in events:
        arena.process_event(*ev[1:])
        
    print(arena.num_clans)

if __name__ == "__main__":
    solve()
