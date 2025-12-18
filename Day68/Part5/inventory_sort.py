def solve():
    try:
        s = input()
        if s == "".join(sorted(s)):
            print(0)
        else:
            print(1)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
