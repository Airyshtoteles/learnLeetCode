import collections

def solve():
    try:
        line1 = input().split()
        if not line1: return
        H = int(line1[0])
        line2 = input().split()
        if not line2: return
        D = [int(x) for x in line2]
    except EOFError:
        return

    # BFS State: (hp, history_tuple)
    # history_tuple stores last 9 moves
    
    queue = collections.deque()
    queue.append((H, (), 0))
    
    # visited: history -> min_hp_seen
    # We want to minimize HP for a given history.
    visited = {}
    visited[()] = H
    
    while queue:
        hp, hist, steps = queue.popleft()
        
        if hp <= 0:
            print(steps)
            return

        for dmg in D:
            # Construct potential next history (full) to check condition
            # We need to check if appending 'dmg' creates a repeat of length 5
            # i.e. new_sequence[-5:] == new_sequence[-10:-5]
            
            # Current hist has length up to 9.
            # If len(hist) < 9, we just append.
            # If len(hist) == 9, appending makes 10.
            
            check_hist = hist + (dmg,)
            erased = False
            if len(check_hist) >= 10:
                # Check last 5 vs prev 5
                # Indices in check_hist (size >= 10)
                # last 5: check_hist[-5:]
                # prev 5: check_hist[-10:-5]
                if check_hist[-5:] == check_hist[-10:-5]:
                    erased = True
            
            if erased:
                # Rewind happens. We revert to state 5 steps ago.
                # In BFS for min steps, this is strictly worse (more steps, same state).
                # Prune.
                continue
            
            next_hp = hp - dmg
            
            # Truncate history to keep last 9
            next_hist = check_hist
            if len(next_hist) > 9:
                next_hist = next_hist[-9:]
            
            # Pruning
            if next_hist in visited:
                if visited[next_hist] <= next_hp:
                    # We have seen this history with better (lower) or equal HP before.
                    continue
            
            visited[next_hist] = next_hp
            queue.append((next_hp, next_hist, steps + 1))

    print(-1)

if __name__ == "__main__":
    solve()
