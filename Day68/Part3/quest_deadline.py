import heapq

def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        quests = []
        for _ in range(n):
            quests.append(list(map(int, input().split())))
            
        # Sort by deadline
        quests.sort(key=lambda x: x[1])
        
        pq = [] # Min heap of rewards
        
        for r, d in quests:
            heapq.heappush(pq, r)
            if len(pq) > d:
                heapq.heappop(pq)
                
        print(sum(pq))
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
