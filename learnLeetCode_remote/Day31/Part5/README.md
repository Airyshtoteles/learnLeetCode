# Day 31 — Part 5: Mirror Realm

We move from (0,0) to (n,n) in exactly 2n steps. Normal mode moves: Right=(x+1,y), Up=(x,y+1).
A mirror mode flips directions: attempting Right becomes Up; attempting Up becomes Right.
Mirror activates every 2 steps, i.e., steps are grouped in pairs: [normal, normal, mirror, mirror, normal, normal, ...].
Given a set of forbidden coordinates, count the number of distinct paths avoiding any forbidden cell along the way.

Approach:
- DP over step index t from 0..2n and coordinates (x,y) with parity block p in {0,1,2,3} meaning t%4:
  - p in {0,1}: normal; p in {2,3}: mirror.
- At each step, choose intended move (Right or Up), then apply mirror flip if p in {2,3}. If next cell is forbidden or out-of-bounds (x>n or y>n), skip.
- dp[t+1][nx][ny] += dp[t][x][y]. Answer is sum over dp[2n][n][n].

Complexity: O(n^3).

Files:
- mirror_realm.py — Python DP.
- mirror_realm.cpp — C++17 DP.
