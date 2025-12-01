# Detective's Timeline
# Given suspects->sorted timestamps and interval [t_start, t_end].
# Return suspects who have any timestamp within the interval (i.e., an alibi in-window => cannot be guilty).
from bisect import bisect_left, bisect_right
from typing import Dict, List

def innocent_suspects(suspects: Dict[str, List[int]], t_start: int, t_end: int) -> List[str]:
    res = []
    for name, times in suspects.items():
        times_sorted = sorted(times)
        # find first index >= t_start and first index > t_end
        i = bisect_left(times_sorted, t_start)
        j = bisect_right(times_sorted, t_end)
        if i < j:
            res.append(name)
    res.sort()
    return res

if __name__ == "__main__":
    suspects = {"A":[1,5,9], "B":[3,8], "C":[2,4,6]}
    print(innocent_suspects(suspects, 3, 7))  # ["A"] per prompt interpretation
