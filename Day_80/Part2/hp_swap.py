import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        n = int(next(iterator))
        D = int(next(iterator))
        limit = int(next(iterator))
        h = []
        for _ in range(n):
            h.append(int(next(iterator)))
    except StopIteration:
        return

    turns = [(x + D - 1) // D for x in h]

    current_damage = 0
    for i in range(n):
        current_damage += turns[i] * (n - i)

    if current_damage <= limit:
        print("true")
        return

    max_reduction = 0
    for i in range(n):
        for j in range(i + 1, n):
            reduction = (turns[i] - turns[j]) * (j - i)
            if reduction > max_reduction:
                max_reduction = reduction

    if current_damage - max_reduction <= limit:
        print("true")
    else:
        print("false")

if __name__ == "__main__":
    solve()
