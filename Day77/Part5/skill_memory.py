import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            n = int(next(iterator))
            K = int(next(iterator))
        except StopIteration:
            return
            
        s = []
        for _ in range(n):
            s.append(int(next(iterator)))
            
        # Optimal strategy: Group identical skills.
        # Cost = Number of unique skills.
        
        unique_skills = set(s)
        print(len(unique_skills))
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
