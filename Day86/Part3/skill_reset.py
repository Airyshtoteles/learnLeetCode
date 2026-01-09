import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M = int(line1[0]), int(line1[1])
        
        adj = collections.defaultdict(list)
        rev_adj = collections.defaultdict(list)
        in_degree = collections.defaultdict(int)
        out_degree = collections.defaultdict(int)
        
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            adj[u].append(v)
            rev_adj[v].append(u)
            out_degree[u] += 1
            in_degree[v] += 1
            
        line_t = sys.stdin.readline().split()
        if not line_t: return
        Target = int(line_t[0])
    except ValueError:
        return

    roots = [i for i in range(1, N+1) if in_degree[i] == 0]
    leaves = [i for i in range(1, N+1) if out_degree[i] == 0]
    
    inventory = set()
    
    while True:
        # Reachable
        reachable = set()
        queue = collections.deque(roots + list(inventory))
        for x in queue: reachable.add(x)
        
        while queue:
            u = queue.popleft()
            for v in adj[u]:
                if v not in reachable:
                    reachable.add(v)
                    queue.append(v)
                    
        if Target in reachable:
            print("Possible")
            return
            
        # Can Reach Leaf
        can_reach_leaf = set()
        rqueue = collections.deque(leaves)
        for x in rqueue: can_reach_leaf.add(x)
        
        while rqueue:
            u = rqueue.popleft()
            for v in rev_adj[u]:
                if v not in can_reach_leaf:
                    can_reach_leaf.add(v)
                    rqueue.append(v)
                    
        # New Skills
        new_skills = []
        for i in range(1, N+1):
            if i not in inventory and i in reachable and i in can_reach_leaf:
                new_skills.append(i)
                
        if not new_skills:
            print("Impossible")
            return
            
        for s in new_skills:
            inventory.add(s)

if __name__ == "__main__":
    solve()
