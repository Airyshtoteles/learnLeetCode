# Day 24 — Part 3: Detective’s Timeline

Interpretation: Each suspect’s timestamps indicate sightings elsewhere (alibis). If a suspect has any timestamp within [t_start, t_end], they cannot be guilty.

Approach:
- For each suspect’s sorted time list, binary search the in-window segment using lower_bound/upper_bound (bisect_left/right).
- If there exists at least one timestamp within the interval, add the suspect to the result.

Complexity: O(S log T) where S is number of suspects and T is max timestamps per suspect.

Files:
- detectives_timeline.py — Python implementation.
- detectives_timeline.cpp — C++17 implementation.
