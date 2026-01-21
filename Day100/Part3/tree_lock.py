import sys

# Maps
is_locked = {} # x -> uid
locked_descendants = {} # x -> count

def get_desc_count(x):
    return locked_descendants.get(x, 0)

def inc_desc(x, val):
    curr = x // 2
    while curr > 0:
        locked_descendants[curr] = locked_descendants.get(curr, 0) + val
        curr //= 2

def check_ancestors(x):
    curr = x // 2
    while curr > 0:
        if curr in is_locked: return False
        curr //= 2
    return True

def do_lock(x, uid):
    if x in is_locked: return "false"
    if get_desc_count(x) > 0: return "false"
    if not check_ancestors(x): return "false"
    
    is_locked[x] = uid
    inc_desc(x, 1)
    return "true"

def do_unlock(x, uid):
    if x not in is_locked: return "false"
    if is_locked[x] != uid: return "false"
    
    del is_locked[x]
    inc_desc(x, -1)
    return "true"

def do_upgrade(x, uid):
    if x in is_locked: return "false"
    if get_desc_count(x) == 0: return "false" # Must have desc locked
    if not check_ancestors(x): return "false"
    
    left = 2 * x
    right = 2 * x + 1
    
    # Strictly need children locked by same uid
    if is_locked.get(left) != uid: return "false"
    if is_locked.get(right) != uid: return "false"
    
    # Upgrade
    del is_locked[left]
    inc_desc(left, -1)
    
    del is_locked[right]
    inc_desc(right, -1)
    
    is_locked[x] = uid
    inc_desc(x, 1)
    return "true"

def solve():
    input_data = sys.stdin.read().split()
    if not input_data: return
    iterator = iter(input_data)
    
    try:
        Q = int(next(iterator))
        for _ in range(Q):
            op = next(iterator)
            x = int(next(iterator))
            uid = int(next(iterator))
            
            if op == "lock":
                print(do_lock(x, uid))
            elif op == "unlock":
                print(do_unlock(x, uid))
            elif op == "upgrade":
                print(do_upgrade(x, uid))
    except StopIteration:
        pass

if __name__ == "__main__":
    solve()
