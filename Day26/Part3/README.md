# The Temporal Switch

There are n switches and m lamps. Each lamp is connected to a subset of switches. Pressing a switch flips (toggles) all connected lamps. Initially all lamps are off. Find the minimum number of switches to press (order arbitrary) so that all lamps are on. If impossible, return -1.

- State: lamps' on/off statuses as an m-bit bitmask (0=off, 1=on)
- Move: press switch i → XOR current mask with mask[i]
- Goal: reach (1<<m)-1

## Approach
BFS in the bitmask space (size up to 2^m):
- Precompute `mask[i]` for each switch i
- Start from 0, push neighbors `state ^ mask[i]`
- Distance (number of presses) gives the minimum

This works because each press cost is 1 and the graph is unweighted.

## Example
```
n = 3, m = 3
connections = [
  [0, 1],   # switch 0 affects lamp 0,1
  [1, 2],   # switch 1 affects lamp 1,2
  [0, 2]    # switch 2 affects lamp 0,2
]
```
Output: `3`

## Files
- `temporal_switch.py` — Python BFS solution with a demo
- `temporal_switch.cpp` — C++17 BFS solution
