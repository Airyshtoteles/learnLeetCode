# Day 54: The Gauntlet of Logic

## Part 1: The Game of Echoing Corridors
**Problem:**
You are in a grid-based dungeon. Some cells are empty (`.`), some are walls (`#`), and some are portals (`P`).
- You start at `S` and must reach `E`.
- Movement is Up, Down, Left, Right (1 step).
- If you step on a Portal `P`, you are *instantly* teleported to the *farthest* other Portal on the map (Manhattan Distance). If multiple are equally far, any one of them is fine (assume deterministic tie-breaking, e.g., smallest row, then smallest col).
- Teleportation takes 0 time but happens immediately upon entering the cell. You continue your move from the destination portal.
- Find the minimum steps to reach `E`. If unreachable, return -1.

**Example:**
```
S . .
# P #
. . E
```
Portals at (1,1). Farthest from (1,1) is itself (distance 0) if only 1 portal exists? No, usually implies >1 portal. If only 1 portal, teleportation might not happen or stays in place. Let's assume >1 portals for interesting cases, or if 1, stay put.

## Part 2: The Tower of Attrition
**Problem:**
A tower defense grid. You move S to E.
- Each cell has a "danger level" $D_{i,j}$.
- Moving to a cell costs 1 second.
- While in a cell $(i,j)$, you take $D_{i,j}$ damage per second.
- You want to minimize the *total damage* taken.
- Total Damage = Sum of danger levels of all cells visited (including S and E).
- Use Dijkstra.

## Part 3: The Fragmented Realms
**Problem:**
You are given a string $S$ of lowercase letters.
- You can swap any two characters at indices $i$ and $j$ if $i \equiv j \pmod 2$ (same parity).
- Can you rearrange the string to form a Palindrome?
- Return "YES" or "NO".

## Part 4: The Last Warrior's Path
**Problem:**
Simulation. A warrior starts at (0,0) with HP $H$.
- A string of moves "UDLR".
- Each move consumes 1 HP.
- Some cells have health potions (restore 5 HP). Potions are consumed upon use.
- If HP drops to 0, warrior dies.
- Return "Survive" or "Die" and final position.

## Part 5: The Rune Forging
**Problem:**
You have $N$ runes. Some runes can be combined to form a more powerful rune.
- Given a list of combinations: `(Rune A, Rune B) -> Rune C`.
- You start with a set of basic runes.
- You want to craft a specific Target Rune.
- Determine if it's possible.
- (This is a reachability problem in a DAG or simple BFS/DFS).
