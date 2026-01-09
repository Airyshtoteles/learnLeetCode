import sys

# Recursion limit
sys.setrecursionlimit(2000)

def solve():
    try:
        line = sys.stdin.readline().split()
        if not line: return
        Start = int(line[0])
        W = int(line[1])
        K = int(line[2])
    except ValueError:
        return

    if Start >= W:
        print("YES")
        return

    visited_mod = [False] * K
    visited_mod[Start % K] = True
    
    result = {"possible": False}
    
    def dfs(val):
        if result["possible"]: return
        if val >= W:
            result["possible"] = True
            return

        # Ops +1, *2
        # Try *2 first (greedy)
        ops = [val * 2, val + 1]
        
        for nv in ops:
            mod = nv % K
            if not visited_mod[mod]:
                visited_mod[mod] = True
                dfs(nv)
                visited_mod[mod] = False
                if result["possible"]: return

    dfs(Start)

    if result["possible"]:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
