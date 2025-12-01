# Day 25 — Part 4: The Lost Player IDs

Observation: Swaps only permute IDs; removing a single ID M changes the XOR of all held IDs from XOR(1..n) to XOR(1..n) XOR M.

Trick: The XOR of players who participate an odd number of times equals the XOR difference induced by the swap permutation. Therefore:

missing = XOR(1..n) XOR XOR(players with odd participation count).

This matches the sample: odd participants are 1 and 4 → 1 XOR 4 = 5.

Files:
- lost_player_ids.py — Python implementation.
- lost_player_ids.cpp — C++17 implementation.
