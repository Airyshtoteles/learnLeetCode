import sys

def can_distribute(limit, k, tasks):
    clones = [0] * k
    for t in tasks:
        placed = False
        for i in range(k):
            if clones[i] + t <= limit:
                clones[i] += t
                placed = True
                break
        if not placed:
            return False
    return True

def can_distribute_backtrack(limit, k, tasks, clones, idx):
    if idx == len(tasks):
        return True
    
    for i in range(k):
        if clones[i] + tasks[idx] <= limit:
            clones[i] += tasks[idx]
            if can_distribute_backtrack(limit, k, tasks, clones, idx + 1):
                return True
            clones[i] -= tasks[idx]
            if clones[i] == 0:
                break
    return False

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    iterator = iter(data)
    try:
        k = int(next(iterator))
        n = int(next(iterator))
        t = []
        for _ in range(n):
            t.append(int(next(iterator)))
    except StopIteration:
        return

    t.sort(reverse=True)
    
    low = max(max(t), (sum(t) + k - 1) // k)
    high = sum(t)
    ans = high
    
    while low <= high:
        mid = (low + high) // 2
        possible = False
        if n <= 20:
            clones = [0] * k
            possible = can_distribute_backtrack(mid, k, t, clones, 0)
        else:
            possible = can_distribute(mid, k, t)
            
        if possible:
            ans = mid
            high = mid - 1
        else:
            low = mid + 1
            
    print(ans)

if __name__ == "__main__":
    sys.setrecursionlimit(2000)
    solve()
