from typing import List

def min_cost(HP: List[int], D: int) -> int:
    return sum((h + D - 1) // D for h in HP)

if __name__ == "__main__":
    print(min_cost([10,15,5], 5))  # 6
