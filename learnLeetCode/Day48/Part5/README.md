# Part 5: Spirit-Link Guardians

## Problem Description

You have `N` guardians on a 2D field.
Each guardian `i` has:
*   Position `(x, y)`.
*   Base Power `p`.
*   Buff Radius `r`.

**Mechanics:**
*   You must choose exactly `K` guardians to activate.
*   You must determine the **Activation Order**.
*   When guardian `A` is activated:
    *   It checks all **already activated** guardians.
    *   Wait, the problem says: "guardian yang menerima buff dapat men-trigger buff ke guardian lain saat nanti diaktifkan".
    *   This implies: If `A` is activated *before* `B`, and `A` is in range of `B` (or `B` in range of `A`?), then `B` gets a buff?
    *   Let's re-read: "Jika guardian i diaktifkan, maka setiap guardian j dengan jarak <= r[i] akan menerima buff dan p[j] meningkat +1."
    *   So `i` buffs `j`. `j` must be in range of `i`.
    *   Does `j` need to be active? "p[j] meningkat". Usually `p` is a property of the unit.
    *   "Buff bersifat chain: guardian yang menerima buff dapat men-trigger buff ke guardian lain saat nanti diaktifkan."
    *   This implies the buff increases `p[j]`. When `j` is later activated, does its *buffing power* increase? No, usually "p" is the score.
    *   Does the buff increase the *radius*? No.
    *   Does the buff increase the *amount* `j` buffs others? "p[j] meningkat +1". Usually `p` is the score contribution.
    *   Let's assume `p` is the score.
    *   So: `i` activates. For all `j` (active or inactive?) in range `r[i]`, `p[j] += 1`.
    *   Goal: "total sum power akhir maksimal".
    *   This implies we sum the *final* `p` of all **activated** guardians? Or all guardians?
    *   "pilih urutan aktivasi k guardian". Usually we only care about the `K` active ones.
    *   Let's assume we sum the final power of the `K` chosen guardians.
    *   If `i` buffs `j`, and both are chosen:
        *   If `i` activates before `j`: `j` gets +1.
        *   If `j` activates before `i`: `i` gets +1 (if `j` buffs `i`).
    *   Wait, "guardian i diaktifkan... j menerima buff".
    *   If `j` is not yet active, it gets +1. When it activates later, it has `p+1`.
    *   If `j` is already active, does it get +1? Yes, `p[j]` increases.
    *   So the order doesn't matter for the *sum* if the buff applies regardless of state?
    *   BUT: "Buff bersifat chain". This usually implies `A -> B -> C`.
    *   If `A` buffs `B`, `B`'s power increases. Does `B`'s *buffing ability* increase?
    *   "guardian yang menerima buff dapat men-trigger buff ke guardian lain".
    *   This phrasing suggests that `B` *passes on* the buff?
    *   Interpretation 1: Standard +1. `A` buffs `B`. `B` gets +1. `B` buffs `C`. `C` gets +1. Total +2.
    *   Interpretation 2: Chain. `A` buffs `B`. `B` gets +1. Now `B` has "extra charge". When `B` activates, it gives +1 (base) + 1 (extra) to `C`?
    *   "p[j] meningkat +1". This modifies `p`.
    *   If `p` is just score, then it's Interpretation 1.
    *   If `p` affects the buff strength, the problem would say "buff strength increases".
    *   "Buff bersifat chain" might just mean "A buffs B, then B buffs C" is a valid sequence of events.
    *   Let's assume Interpretation 1 (Simple +1 to score).
    *   Total Score = Sum of Base Powers of K guardians + Sum of Buffs.
    *   Buffs occur if `i` activates and `j` is in range.
    *   Does `j` need to be in the set K?
        *   If `j` is not in K, its power increases, but does it contribute to the final sum? "total sum power akhir". Usually implies sum of the *team*.
        *   Let's assume we only care about the power of the K guardians.
    *   Does `i` buff `j` if `j` is already active?
        *   "Jika guardian i diaktifkan... j... menerima buff". Yes.
    *   So if we pick a set K, the total buffs = Number of ordered pairs `(i, j)` in K such that `dist(i, j) <= r[i]`.
    *   Wait, if order doesn't matter (everyone buffs everyone eventually), then we just maximize edges in the subgraph of K?
    *   BUT: "pilih urutan aktivasi". This implies order MATTERS.
    *   Why would order matter?
        *   Maybe `j` only receives buff if it is *already* active? Or *not yet* active?
        *   "guardian yang menerima buff dapat men-trigger buff ke guardian lain **saat nanti diaktifkan**."
        *   This strongly implies `B` must receive the buff *before* `B` activates to pass it on?
        *   This supports Interpretation 2 (Chain/Viral Buff).
        *   Let's assume:
            *   Each guardian has `buff_strength` (initially 1? or 0? or related to p?).
            *   Actually, "p[j] meningkat +1".
            *   Maybe the buff strength is related to `p`?
            *   Or maybe "trigger buff" just means "perform its own buff action".
            *   If it's just "perform own action", then order doesn't matter for the *existence* of the action.
            *   UNLESS: `j` only buffs others if `j` has received a buff? No, that's too restrictive.
    *   Let's go with the most complex interpretation that fits "Chain" and "Order matters":
        *   **Viral Buff:** When `i` activates, it gives `current_buff_power` to neighbors.
        *   Neighbors `j` receive this. Their `p` increases. Their `current_buff_power` might increase?
        *   Let's stick to the text: "p[j] meningkat +1".
        *   Maybe the "Chain" just means `A` buffs `B`, and `B` (later) buffs `C`.
        *   If `B` activates *before* `A`, `B` buffs `C`. Then `A` activates and buffs `B`. `B` has +1. `C` has +1.
        *   If `A` activates *before* `B`. `A` buffs `B`. `B` has +1. Then `B` activates. Does `B` give more to `C`?
        *   If no, then order doesn't matter for the sum.
        *   If yes (e.g. `B` gives `1 + received_buffs`), then order matters.
        *   Given "Hard" and "Order dependency", let's assume **Viral Buff**:
            *   When `i` activates, it adds `1 + (buffs i received so far)` to `p[j]` for all `j` in range?
            *   Or maybe just `1`?
            *   If it's just `1`, and order matters, maybe "j menerima buff" only happens if `j` is *active*? Or *inactive*?
            *   Let's assume the "Chain" comment is flavor text for "A buffs B, B buffs C".
            *   Let's assume the constraint is: **A guardian only buffs others when it activates.**
            *   And maybe: **A guardian only RECEIVES buffs if it is...**?
            *   Actually, if `A` buffs `B` (inactive), `B`'s power goes up. When `B` activates, it buffs `C`.
            *   If `B` activates first, it buffs `C`. Then `A` activates, buffs `B`.
            *   Result is same.
            *   There must be a condition where order changes the result.
            *   Maybe: **"Guardian i buffs j ONLY IF j is currently active?"**
                *   Then we want to activate receivers *first*?
            *   Maybe: **"Guardian i buffs j ONLY IF j is NOT yet active?"** (Buffs prepare them).
                *   Then we want to activate buffers *first*.
            *   Let's guess: **"Guardian i buffs j. If j activates LATER, j carries that buff?"**
            *   Let's assume the simplest "Order Matters" mechanic:
                *   **Score = Sum of P of activated guardians.**
                *   **Rule:** `i` buffs `j` (adds +1 to `p[j]`) **only if `j` is already active** (or vice versa).
                *   Let's assume **"Only if `j` is NOT yet active"** (Preparation).
                *   So `A` (active) -> buffs `B` (inactive). `B` gets +1.
                *   Later `B` activates. `B` starts with `P+1`.
                *   If `B` activates before `A`, `B` is active. `A` activates. `A` tries to buff `B`. `B` is active. Buff fails?
                *   This makes it an ordering problem.
                *   Let's assume: **Buffs only apply to INACTIVE guardians.**
                *   Goal: Maximize final sum of P.
                *   This encourages activating buffers early.

**Input:**
*   `N`, `K`.
*   `Guardians`: `[x, y, p, r]`.

**Output:**
*   Max Total Power.

### Example

**Input:**
```text
N = 3, K = 3
G0: 0,0, p=10, r=10 (Covers G1, G2)
G1: 1,0, p=10, r=0  (Covers none)
G2: 2,0, p=10, r=0  (Covers none)
```

**Logic (Assumption: Buffs apply to inactive only):**
*   Order G0, G1, G2:
    *   Activate G0. Buffs G1 (inactive), G2 (inactive).
    *   G1 p=11. G2 p=11.
    *   Activate G1. Buffs nothing.
    *   Activate G2. Buffs nothing.
    *   Total: 10 + 11 + 11 = 32.
*   Order G1, G2, G0:
    *   Activate G1.
    *   Activate G2.
    *   Activate G0. Buffs G1 (Active - Fail), G2 (Active - Fail).
    *   Total: 10 + 10 + 10 = 30.

**Output:**
```text
32
```
