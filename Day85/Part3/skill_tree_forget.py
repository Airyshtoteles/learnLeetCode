import sys
import collections

# Increase recursion depth for deep trees
sys.setrecursionlimit(20000)

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M = int(line1[0]), int(line1[1])
        
        rev_adj = collections.defaultdict(list)
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            rev_adj[v].append(u)
            
        line_t = sys.stdin.readline().split()
        if not line_t: return
        Target = int(line_t[0])
    except ValueError:
        return

    # Find all ancestors
    ancestors = set()
    def get_ancestors(u):
        if u in ancestors: return
        ancestors.add(u)
        for p in rev_adj[u]:
            get_ancestors(p)
            
    get_ancestors(Target)
    
    # Check if induced subgraph is a chain
    # Every node in ancestors set must have at most 1 parent that is also in the set.
    for u in ancestors:
        parents_in_set = 0
        for p in rev_adj[u]:
            if p in ancestors:
                parents_in_set += 1
        
        if parents_in_set > 1:
            print("Impossible")
            return
            
    print("Possible")

if __name__ == "__main__":
    solve()
