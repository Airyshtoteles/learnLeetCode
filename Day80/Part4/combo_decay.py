import sys
from collections import Counter

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    
    s = data[0]
    counts = Counter(s)
    
    perm = []
    
    while counts:
        # Get one of each available character, sorted
        layer = sorted(counts.keys())
        perm.extend(layer)
        
        # Decrement counts
        to_remove = []
        for char in layer:
            counts[char] -= 1
            if counts[char] == 0:
                to_remove.append(char)
        
        for char in to_remove:
            del counts[char]
            
    total_score = 0
    current_combo = 0
    
    if perm:
        current_combo = 1
        total_score += current_combo
        
        for i in range(1, len(perm)):
            if perm[i] > perm[i-1]:
                current_combo += 1
            else:
                current_combo //= 2
            total_score += current_combo
            
    print(total_score)

if __name__ == "__main__":
    solve()
