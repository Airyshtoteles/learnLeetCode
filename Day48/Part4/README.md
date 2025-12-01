# Part 4: Arcane Forge Production Line

## Problem Description

You manage a magical factory with `K` machines.
Each machine `i` has:
*   `craft[i]`: Time to produce 1 item.
*   `cd[i]`: Cooldown time after producing an item.
*   `value[i]`: Value of the item produced.

**Constraints:**
*   Total operation time: `T`.
*   Machines work in **parallel**.
*   Each machine can only produce one item at a time.
*   After finishing an item (taking `craft[i]`), the machine MUST wait `cd[i]` before starting the next one.

**Goal:** Maximize the total value of items produced within time `T`.

**Logic:**
Since machines are independent and parallel, we can calculate the maximum value produced by each machine individually and sum them up.

For a single machine `i`:
*   Cycle time = `craft[i] + cd[i]`.
*   In time `T`, how many full cycles? `count = T // (craft[i] + cd[i])`.
*   Remaining time: `rem = T % (craft[i] + cd[i])`.
*   If `rem >= craft[i]`, we can produce one more item (the cooldown doesn't need to finish if time `T` ends, as long as the item is done).
*   Total items = `count + (1 if rem >= craft[i] else 0)`.
*   Total Value = `Total items * value[i]`.

**Input:**
*   `T`: Total time.
*   `Machines`: List of `[craft, cd, value]`.

**Output:**
*   Maximum Total Value.

### Example

**Input:**
```text
T = 10
Machines = [
  [2, 1, 5],  # M1: Craft 2, CD 1, Val 5. Cycle 3.
  [5, 2, 20]  # M2: Craft 5, CD 2, Val 20. Cycle 7.
]
```

**Calculation:**
*   **M1:** Cycle = 2+1=3.
    *   T=10. 10 // 3 = 3 full cycles. (Time used: 3*3=9).
    *   Rem = 1.
    *   Can we craft one more? Need 2. Rem 1 < 2. No.
    *   Items = 3. Value = 3 * 5 = 15.
*   **M2:** Cycle = 5+2=7.
    *   T=10. 10 // 7 = 1 full cycle. (Time used: 7).
    *   Rem = 3.
    *   Can we craft one more? Need 5. Rem 3 < 5. No.
    *   Items = 1. Value = 1 * 20 = 20.
*   **Total:** 15 + 20 = 35.

**Output:**
```text
35
```
