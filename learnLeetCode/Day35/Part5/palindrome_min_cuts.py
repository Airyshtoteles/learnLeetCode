def min_cut(s: str) -> int:
    n = len(s)
    cut = [0]*(n+1)
    for i in range(n+1):
        cut[i] = i-1
    for c in range(n):
        # odd length
        l=r=c
        while l>=0 and r<n and s[l]==s[r]:
            cut[r+1] = min(cut[r+1], 1 + cut[l])
            l-=1; r+=1
        # even length
        l=c; r=c+1
        while l>=0 and r<n and s[l]==s[r]:
            cut[r+1] = min(cut[r+1], 1 + cut[l])
            l-=1; r+=1
    return cut[n]

if __name__ == "__main__":
    print(min_cut("aab"))  # Expected 1 (aa|b)
