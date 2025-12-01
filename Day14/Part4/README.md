# Day 14 — Part 4: Optimized BFS State

To handle moving portals every `t` steps without revisiting equivalent states too often, we key visited by `(x,y, steps % t)`.

- When `steps % t == 0`, the layout can change on the next step window.
- We deterministically compute the set of `pcount` portal positions for the current phase: `phase = steps // t`.
- Stepping onto a portal teleports instantly to the next portal in the ordered list.

This reduces redundant enqueues and ensures correctness with time-dependent transitions.
