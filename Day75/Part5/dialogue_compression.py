def solve():
    try:
        s = input().strip()
        if not s:
            print(0)
            return
            
        freq = {}
        for c in s:
            freq[c] = freq.get(c, 0) + 1
            
        max_freq = max(freq.values())
        print(len(s) - max_freq)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
