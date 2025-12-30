# Day 59: Advanced Algorithmic Challenges

## 1. Schrodinger’s Inventory
**Problem:**
Select max items such that total weight $\le W$ regardless of whether each item $i$ collapses to $weightA[i]$ or $weightB[i]$.
**Logic:**
Use effective weight $w_i = \max(weightA[i], weightB[i])$. Greedy sort.

## 2. Turn-Based Combat vs. Yourself
**Problem:**
Simulate combat where at time $t$, you act $A_t$ and clone acts $A_{t-5}$.
**Logic:**
Simulation.

## 3. Infinite Staircase with Memory Reset
**Problem:**
Reach $K$ with $+a, -b$. Minimize steps.
**Logic:**
Solve $n \cdot a - m \cdot b = K$ for minimal $n+m$.
Use Extended Euclidean Algorithm.

## 4. Quantum Card Game
**Problem:**
Assign cards to Odd (Low) or Even (High) slots to maximize score.
**Logic:**
Maximize $\sum low + \sum_{even} (high - low)$. Sort by diff.

## 5. Dungeon Where Moving Changes the Map
**Problem:**
Grid shifts with movement.
**Logic:**
Relative position invariant. Check `initial[0][0]` neighbors.
