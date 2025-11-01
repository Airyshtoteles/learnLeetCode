from typing import List

def min_final_value(a: List[int]) -> int:
    x = 0
    for v in a:
        x ^= v
    return x

if __name__ == "__main__":
    a = [1,3,5,7]
    print(min_final_value(a))  # Expected 0
