from typing import List

def min_moves_to_equalize(energy: List[int]) -> int:
    n = len(energy)
    if n == 0:
        return 0
    S = sum(energy)
    if S % n != 0:
        return -1
    avg = S // n
    surplus = 0
    for v in energy:
        if v > avg:
            surplus += v - avg
    return surplus

if __name__ == "__main__":
    print(min_moves_to_equalize([1,3,5]))  # 2 (unit transfers)
