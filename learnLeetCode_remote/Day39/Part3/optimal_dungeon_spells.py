from typing import List, Tuple

def min_time_to_clear(roomsHP: List[int], damage: List[int], cd: List[int], cost: List[int], totalMana: int) -> int:
    m = len(damage)
    cd_left = [0]*m
    time = 0
    mana = totalMana
    for hp in roomsHP:
        cur = hp
        while cur > 0:
            # any affordable ready spell?
            best = -1
            best_dmg = -1
            for j in range(m):
                if cd_left[j] == 0 and cost[j] <= mana and damage[j] > best_dmg:
                    best_dmg = damage[j]
                    best = j
            if best != -1 and best_dmg > 0:
                # cast
                cur -= best_dmg
                mana -= cost[best]
                cd_left[best] = cd[best]
                time += 1
                # tick others by 1 due to time advance
                for j in range(m):
                    if cd_left[j] > 0:
                        cd_left[j] -= 1
            else:
                # wait until next affordable spell becomes ready
                wait = None
                for j in range(m):
                    if cost[j] <= mana:
                        if cd_left[j] > 0:
                            wait = cd_left[j] if wait is None else min(wait, cd_left[j])
                        elif damage[j] > 0:
                            wait = 0 if wait is None else min(wait, 0)
                if wait is None:
                    return -1  # no affordable spells ever
                if wait == 0:
                    # loop will re-evaluate and cast
                    continue
                time += wait
                for j in range(m):
                    if cd_left[j] > 0:
                        cd_left[j] = max(0, cd_left[j] - wait)
    return time

if __name__ == "__main__":
    # Simple smoke test
    print(min_time_to_clear([10], [6,4], [2,1], [3,2], 10))
