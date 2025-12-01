from functools import lru_cache

def can_A_win(X: int, Y: int, M: int) -> bool:
    MAXHP = 100

    @lru_cache(maxsize=None)
    def dfs(hpA: int, hpB: int, manaA: int, manaB: int, turn: int) -> bool:
        # Terminal checks
        if hpA <= 0 and hpB <= 0:
            # Simultaneous death counts as opponent win (current player loses)
            return False
        if hpA <= 0:
            return False
        if hpB <= 0:
            return True

        if manaA == 0 and manaB == 0:
            return hpA > hpB

        if turn == 0:  # A's turn
            # If A has no mana, skip to B
            if manaA == 0:
                return dfs(hpA, hpB, manaA, manaB, 1)
            # Try attack
            if dfs(hpA, hpB - X, manaA - 1, manaB, 1):
                return True
            # Try heal
            nhpA = min(MAXHP, hpA + Y)
            if dfs(nhpA, hpB, manaA - 1, manaB, 1):
                return True
            return False
        else:  # B's turn, minimize A's chance
            if manaB == 0:
                return dfs(hpA, hpB, manaA, manaB, 0)
            # B attacks A
            if not dfs(hpA - X, hpB, manaA, manaB - 1, 0):
                return False
            # B heals self
            nhpB = min(MAXHP, hpB + Y)
            if not dfs(hpA, nhpB, manaA, manaB - 1, 0):
                return False
            return True

    return dfs(100, 100, M, M, 0)

if __name__ == "__main__":
    print(can_A_win(20, 10, 5))  # Expected True
