# Day 24 — Part 4: DNA of the Culprit

Task: Given a crime scene DNA string and a list of candidate DNA strings, pick the candidate with the fewest character differences (Hamming distance) within a threshold k. Return the index, or -1 if none.

Assumptions:
- All strings compared are of equal length; this matches the sample. If lengths may differ, extend with a sliding-window alignment rather than full edit distance.

Approach:
- For each candidate, count mismatches against `dna_scene`.
- Track the minimal diff that is ≤ k and return its index (tie-breaker by lowest index due to scan order).

Files:
- dna_of_culprit.py — Python implementation with the sample.
- dna_of_culprit.cpp — C++17 implementation.
