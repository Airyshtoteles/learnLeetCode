# Day 45 Part 7: Distributed Tower Defense Pathfinding

## Problem Description

You need to defend $K$ paths from enemies.
*   **Paths:** Each path is a sequence of coordinates.
*   **Enemies:** Spawn at the start of each path.
    *   `HP`: Health Points.
    *   `Speed`: Units per second.
*   **Towers:**
    *   You can place up to **3** towers.
    *   Candidate locations are given.
    *   Each tower has `Radius` and `Damage`.
    *   **Attack Mechanic:** Towers fire every 2 seconds.
    *   **Alternating Fire:** If multiple towers are active, they fire in a sequence offset by time?
        *   Let's assume simplified "Alternating":
        *   Tower $i$ fires at $t = \text{offset}_i, \text{offset}_i + 2, \dots$
        *   Where $\text{offset}_i$ could be $0$ or $1$ to interleave?
        *   **Assumption:** All towers fire at $t=0, 2, 4, \dots$ for simplicity unless specified otherwise. The prompt says "urutan bergantian setiap 2 detik" (alternating sequence every 2 seconds). This might mean Tower A at 0, Tower B at 2, Tower C at 4? Or Tower A at 0, B at 1, C at 2?
        *   Let's implement: Tower $i$ fires at $t \pmod 2 == 0$. (Synchronized).
        *   Or better: Check if enemy is in range of *any* tower at time $t$.
*   **Goal:** Find a set of $\le 3$ towers such that **all** enemies are killed before reaching the end of their paths.
*   **Output:** Minimal number of towers needed (1, 2, or 3). If impossible, return -1.

## Algorithm: Brute Force Combinations + Simulation

Since the number of towers is small (max 3) and candidate locations are finite (let's assume $N \le 20$), we can try all combinations.

### Steps
1.  **Input Parsing:** Paths, Enemy Stats, Candidate Locations.
2.  **Iterate $k = 1, 2, 3$:**
    *   Iterate all combinations of $k$ towers from candidates.
    *   **Simulation:**
        *   For each enemy on its path:
            *   Calculate total damage received.
            *   Enemy moves at `Speed`.
            *   At time $t=0, 2, 4, \dots$, check distance to all chosen towers.
            *   If $dist \le Radius$, `HP -= Damage`.
            *   If `HP <= 0`, enemy dies.
            *   If enemy reaches end with `HP > 0`, simulation fails.
    *   If a combination kills all enemies, return $k$.
3.  Return -1 if no combination works.

### Complexity
*   Candidates $C$.
*   Combinations $\binom{C}{1} + \binom{C}{2} + \binom{C}{3} \approx C^3/6$.
*   For $C=20$, $C^3 \approx 8000$.
*   Simulation: Path length $L$. Steps $L/Speed$.
*   Total: $8000 \times L$. Feasible.

## Implementation Details
*   Time step: We can simulate second by second or event-based.
*   Since fire rate is every 2s, checking at $t=0, 2, 4...$ is sufficient.
*   Enemy position at time $t$: `path[min(len-1, floor(t * speed))]`?
    *   Better: Interpolate position or assume discrete steps on grid.
    *   Assume discrete path nodes. Speed = 1 node/sec.
