import sys

sys.setrecursionlimit(2000)

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        InitialE = int(next(iterator))
        TargetT = int(next(iterator))
        
        Cost = []
        for _ in range(N): Cost.append(int(next(iterator)))
        
        Refund = []
        for _ in range(N): Refund.append(int(next(iterator)))
        
        adj = [[] for _ in range(N)]
        edges = int(next(iterator))
        for _ in range(edges):
            u = int(next(iterator))
            v = int(next(iterator))
            adj[u].append(v)
            
    except StopIteration:
        return

    # DFS
    def get_req(u):
        base_peak = Cost[u]
        # logic: start with paying cost.
        # we need C[u].
        # then we need extra for children.
        
        children_res = []
        for v in adj[u]:
            children_res.append(get_req(v))
            
        pos = []
        neg = []
        sum_child_net = 0
        
        for p, n in children_res:
            sum_child_net += n
            if n >= 0:
                pos.append((p, n))
            else:
                neg.append((p, n))
                
        pos.sort(key=lambda x: x[0])
        neg.sort(key=lambda x: x[0] + x[1], reverse=True)
        
        current_spent = 0
        max_needed_extra = 0
        
        for p, n in pos:
            max_needed_extra = max(max_needed_extra, current_spent + p)
            current_spent -= n
            
        for p, n in neg:
            max_needed_extra = max(max_needed_extra, current_spent + p)
            current_spent -= n
            
        total_peak = base_peak + max_needed_extra
        total_net = -Cost[u] + sum_child_net + Refund[u]
        
        return total_peak, total_net

    peak, net = get_req(TargetT)
    
    if InitialE >= peak:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
