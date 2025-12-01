from typing import List, Tuple, Optional

# Part 3 — Portal Mapping
# Implement teleportRandom: when stepping on a portal, teleport to another portal (not itself).
# For determinism in tests, use the next portal in the list. If <=1, no teleport.

Pos = Tuple[int,int]

def teleportRandom(portals: List[Pos], current: Pos) -> Optional[Pos]:
    if len(portals) <= 1:
        return None
    try:
        i = portals.index(current)
    except ValueError:
        return None
    j = (i + 1) % len(portals)
    if portals[j] == current:
        return None
    return portals[j]

if __name__ == "__main__":
    portals = [(0,2), (2,1), (3,0)]
    print(teleportRandom(portals, (0,2)))  # -> (2,1)
    print(teleportRandom(portals, (2,1)))  # -> (3,0)
    print(teleportRandom(portals, (3,0)))  # -> (0,2)
