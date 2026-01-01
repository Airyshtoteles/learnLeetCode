import sys
from collections import deque

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        n = int(next(iterator))
        T = int(next(iterator))
        spell = []
        for _ in range(n):
            spell.append(int(next(iterator)))
    except StopIteration:
        return

    q = deque()
    visited = set()

    q.append(0)
    visited.add(0)

    while q:
        mana = q.popleft()

        if mana == T:
            print("true")
            return

        # Try each spell
        for s in spell:
            new_mana = mana + s

            if 0 <= new_mana <= 10000:
                if new_mana not in visited:
                    visited.add(new_mana)
                    q.append(new_mana)

    print("false")

if __name__ == "__main__":
    solve()
