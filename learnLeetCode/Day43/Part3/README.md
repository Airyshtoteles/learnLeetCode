# Spirit Link Battle Arena

Level: Hard

N spirits in a circle (0..N-1).
Events:
1. `link a b`: Connect spirits a and b. If connected, they form a clan (connected component).
2. `battle x`: The clan containing spirit x attacks the neighbor clan in clockwise direction.
   - Neighbor clan: The clan of the spirit immediately clockwise to the "rightmost" spirit of x's clan?
   - Or simply: Find the next spirit in circle (x+1, x+2...) that belongs to a DIFFERENT clan. That clan is the target.
   - Battle: Larger total power absorbs smaller. If equal? Assume attacker wins or nothing happens? Problem says "absorbs weak". Let's assume strict > wins, <= loses/absorbed? Or simply sum powers and merge? "clan dengan total power lebih besar menyerap clan lemah".
   - If merge happens, the two clans become one.

Task: Count remaining clans after all events.

## Twist: Reverse Processing?
The problem description mentions "Event harus diproses reverse menggunakan union-find + rollback, karena battle menyebabkan merging irreversibly."
Wait.
If we process forward:
- Link: Merge sets. Easy.
- Battle: Check neighbors, compare sums, merge if condition met.
This seems doable forward with DSU + maintaining "next clan" pointers.
Why reverse?
Maybe "battle" destroys a clan (removes it)?
If A absorbs B, B is gone.
If we process reverse:
- We start with the final state? But we don't know the final state.
- Maybe the "battle" is a query "who is alive?"
- Actually, if "battle" is deterministic merging, forward simulation is fine IF we can efficiently find the neighbor clan.
- Since spirits are circular, we can maintain a circular linked list of *active* clans or segments.
- DSU maintains clan membership and total power.
- "Neighbor clan clockwise": For a clan C, its clockwise neighbor is the clan of `(max_index_in_C + 1) % N`? No, indices are interleaved.
- Better: The "neighbor" is the clan of the next spirit in the circle.
- If we use DSU, we can find the clan ID of `(i+1)%N`. If it's same as `i`, continue.
- To do this efficiently:
  - DSU for sets.
  - Each set maintains a "rightmost" or "clockwise-most" boundary? No, sets can be interleaved (e.g. 0 and 2 linked, 1 separate).
  - "Link a b" connects arbitrary spirits.
  - "Battle x": Clan X attacks "neighbor clan".
  - Definition of neighbor clan needs care. If topology is strictly circular and links only happen between adjacent? "Link a b" usually implies adjacency in many problems, but here "Connect spirits a and b" might be arbitrary.
  - IF links are arbitrary, "clockwise neighbor" is ill-defined unless we iterate `(x+1)%N, (x+2)%N...` until we find a node in a different clan.
  - If N is large, iterating is slow.
  - However, if we maintain for each clan a set of "adjacent spirits in circle that are NOT in clan", it's hard.

Let's assume "Link a b" connects arbitrary nodes.
But "Battle" implies spatial locality.
If links are arbitrary, the concept of "neighbor clan" is tricky.
Maybe "neighbor" means the clan of the spirit at `(x's position + 1)`?
If `x` is at `pos`, and `pos+1` is in same clan, we look at `pos+2`?
Yes, "neighbor clan clockwise" usually means the first clan encountered when traversing the circle from any member of current clan?
Or specifically from `x`? "Clan tempat spirit x berada akan menyerang...".
Let's assume: Find `y = (x+1)%N`. If `find(y) == find(x)`, try `y+1`, etc.
To speed this up, we can use a DSU-like structure on the *indices* 0..N-1 to skip over members of the same clan.
Let `Next[i]` be the next index `j` such that `find(j) != find(i)`.
Initially `Next[i] = (i+1)%N`.
When `i` and `(i+1)%N` merge into same clan, `Next[i]` becomes `Next[(i+1)%N]`.
This is exactly DSU on the linear/circular array of spirits!
So we need TWO DSUs:
1. `ClanDSU`: Manages power and logical grouping of spirits (for "Link" and "Battle" merges).
2. `NextDSU`: Manages the "skip same clan" logic on the circle. `find_next(i)` gives the next spirit index that *might* be in a different clan.
   - Actually, `NextDSU` should link `i` to `(i+1)%N` if they are in the same `ClanDSU`.
   - When `Link a b` happens: `ClanDSU.union(a, b)`. This might not make them adjacent in circle.
   - When `Battle x` happens:
     - Identify `rootX = ClanDSU.find(x)`.
     - We need a member of `rootX`? No, we scan from `x`? Or from "rightmost"?
     - "Clan ... menyerang clan tetangga terdekat searah jarum jam".
     - If the clan is scattered (e.g. {0, 5, 10}), "neighbor" is ambiguous.
     - **Assumption**: Links are only between adjacent spirits `(i, i+1)`.
     - If links are arbitrary, the problem is likely "Link adjacent".
     - If arbitrary, "neighbor clan" is hard to define.
     - Given "Reverse Processing" hint, it suggests "Link" might be edge removal? No, "Link" adds edge.
     - Reverse processing is useful if we have "Destroy/Split". Here we have "Merge".
     - Wait, "Battle" causes merge (absorb). "Link" causes merge.
     - Both are merges. Forward is fine.
     - Unless... "Battle" removes the LOSER?
     - If Loser is removed, it's gone.
     - If Forward:
       - Link: Merge.
       - Battle: Compare power. If X > Y, Y is removed (or merged into X). If X <= Y, X is removed?
       - If removed, the circle shrinks? Or just empty spots?
       - "Menyerap" -> Merges.
       - So it's always merging.
       - Why reverse?
       - Maybe to handle "Link" queries efficiently if they were "Unlink"? But they are "Link".
       - Maybe the problem is: "At time T, what is the state?"
       - Let's stick to Forward Simulation with `NextDSU` optimization.
       - Assumption: Links are arbitrary, but "neighbor" search starts from `x` clockwise? Or `x`'s clan is treated as a contiguous block?
       - If arbitrary links, "neighbor" is likely "scan from x clockwise until node not in x's clan".
       - `NextDSU` helps skip nodes in same clan.
       - `NextDSU` links `i` -> `(i+1)%N` if `ClanDSU.find(i) == ClanDSU.find((i+1)%N)`.
       - We update `NextDSU` lazily or upon Link/Battle.

Implementation:
- `parent`: Clan DSU.
- `power`: Clan power.
- `next_spirit`: DSU for skipping. `next_spirit[i]` points to `i+1`. If `i` and `i+1` in same clan, `union_next(i, i+1)`.
- `find_next(i)` returns the representative in `next_spirit` structure, which should map to the "last" element of the contiguous block starting at `i`?
- Actually, `NextDSU` on indices: `parent_next[i]`. If `i` and `(i+1)%N` are same clan, `union_next(i, (i+1)%N)`.
- `find_next_target(i)`: `j = (i+1)%N`. While `ClanDSU.find(j) == ClanDSU.find(i)`, `j = (j+1)%N`.
- Optimization: `NextDSU` maintains segments of *consecutive* spirits that belong to the *same* clan.
- When `Link a b` merges two clans, we might merge multiple segments in `NextDSU`?
- No, `Link a b` (arbitrary) might make `0` and `10` same clan, but `1..9` are different. `NextDSU` shouldn't jump 0->10.
- Only `Battle` merges adjacent clans?
- If `Link` is arbitrary, `NextDSU` only merges `i` and `i+1` if they become same clan.
- We can check `i` and `i+1` (and `a` and `a+1` etc?) upon Link?
- Too slow to check all.
- **Hypothesis**: Links are only between adjacent nodes `(i, (i+1)%N)`.
- If so, clans are always contiguous segments.
- Then `NextDSU` is perfect.
- If links are arbitrary, the problem is very weird for "Battle".
- I will assume **Links are arbitrary**, and "Neighbor" means "scan clockwise from x".
- Optimization: `NextDSU` stores `jump[i]`. Initially `(i+1)%N`.
- When scanning, path compress `jump`.
- `get_target(x)`:
  - `curr = x`
  - `root = find_clan(x)`
  - `while find_clan(curr) == root`:
    - `curr = jump[curr]` (with path compression logic?)
    - Actually, just `curr = (curr + 1)%N` is slow.
    - We need `jump[i]` to point to the next index that is *likely* different clan.
    - When we find `find_clan(i) == find_clan(jump[i])`, we update `jump[i] = jump[jump[i]]`.
    - This is "Path Halving" on the linked list of indices.

Complexity: Amortized O((N+Q) alpha N).

