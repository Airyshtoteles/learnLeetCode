import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    n = int(data[0])
    c = []
    for i in range(n):
        c.append(int(data[1 + i]))

    # Sort ascending
    c.sort()

    finish_time = 0
    
    for k in range(n):
        # Skill k (0-indexed in sorted list)
        # It benefits from k previous skills' bonus decay.
        # So its effective requirement is c[k] - k.
        # We must also wait for the previous skill to finish.
        
        required_start = c[k] - k
        actual_start = max(finish_time, required_start)
        finish_time = actual_start + 1
        
    print(finish_time)

if __name__ == "__main__":
    solve()
