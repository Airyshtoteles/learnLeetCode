from typing import List

def max_diff(value: List[int], rarity: List[int]) -> int:
    items = sorted(zip(value, rarity), reverse=True)
    a = b = 0
    turnA = True
    for v, r in items:
        if turnA:
            if r % 2 == 0:
                a += v
            else:
                # A skips
                pass
        else:
            if r % 2 == 1:
                b += v
            else:
                pass
        turnA = not turnA
    return a - b

if __name__ == "__main__":
    value  = [4, 6, 5, 8]
    rarity = [2, 3, 2, 5]
    print(max_diff(value, rarity))
