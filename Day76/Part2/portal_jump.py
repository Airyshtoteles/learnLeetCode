import sys

# Increase recursion depth just in case, though we use iterative
sys.setrecursionlimit(2000)

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        # First element might be n? Or just array?
        # "Input: p = int[]". Usually implies n then elements or just elements.
        # Let's assume standard format: n, then p[0]..p[n-1]
        # Or maybe just the list.
        # Based on previous problems, usually n is first.
        # Let's try to parse n.
        
        try:
            first = next(iterator)
            n = int(first)
        except StopIteration:
            return

        p = []
        for _ in range(n):
            p.append(int(next(iterator)))
            
        if n == 0:
            print("false")
            return
        if n == 1:
            print("true")
            return
            
        cycle_id = [-1] * n
        current_cycle = 0
        
        for i in range(n):
            if cycle_id[i] == -1:
                curr = i
                while cycle_id[curr] == -1:
                    cycle_id[curr] = current_cycle
                    curr = p[curr]
                current_cycle += 1
                
        start_cycle = cycle_id[0]
        target_cycle = cycle_id[n-1]
        
        if start_cycle == target_cycle:
            print("true")
            return
            
        found = False
        for u in range(n):
            if cycle_id[u] == start_cycle:
                if u + 1 < n:
                    if cycle_id[u+1] == target_cycle:
                        found = True
                        break
        
        print("true" if found else "false")
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
