# Day 24 — Part 1: The Missing Witness

Task: One witness lies completely. Given each witness’s list of people they claim to have seen, identify the liar based on cross-witness consistency.

Heuristic approach:
- Let count_seen[x] be how many witnesses (across all) mention person x.
- For witness i, compute a support score over their claims using counts that exclude i’s own mentions: `score_i = sum(count_seen_except_i[x] for x in statements[i]) + count_seen_except_i[i]` (how many others saw those people, and how many others saw i).
- Choose argmin score; break ties by preferring witnesses whose claims include more zero-supported mentions.

Why this works in practice:
- The liar’s claims tend to point to people few (or no) other witnesses saw, and the liar themselves is typically not corroborated by others. This outlier detection matches the hint.

Files:
- missing_witness.py — Python implementation with sample.
- missing_witness.cpp — C++17 implementation.
