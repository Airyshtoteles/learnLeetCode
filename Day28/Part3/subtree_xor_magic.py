from typing import List

def min_magic_score(val: List[int]) -> int:
    x = 0
    for v in val:
        x ^= v
    return x

if __name__ == "__main__":
    # Example: tree structure irrelevant because result is XOR of all values
    val = [1,2,3,6,2]
    print(min_magic_score(val))  # 1^2^3^6^2 = 6
