def can_reduce_string(s: str) -> bool:
    n = len(s)
    if n == 0:
        return True
    return n != 1

if __name__ == "__main__":
    print(can_reduce_string("abcaacb"))  # True
    print(can_reduce_string("a"))        # False
    print(can_reduce_string("aa"))       # True
