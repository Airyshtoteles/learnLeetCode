from collections import Counter

def solve():
    try:
        s = input()
        counts = Counter(s)
        
        odd_counts = 0
        for count in counts.values():
            if count % 2 != 0:
                odd_counts += 1
                
        print(odd_counts)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
