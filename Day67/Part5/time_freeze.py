def solve():
    try:
        s = input()
        if "XYZ" in s:
            print(2)
        else:
            print(len(s))
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
