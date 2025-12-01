# Battle of Territories

Grid n x m with 'A', 'B', and '.'. Each turn, both sides expand simultaneously into adjacent empty cells. A cell is claimed only if it touches exactly one side that turn; cells reached at the same time by both are contested forever and do not expand further. Who owns more cells when expansion stops? Count initial A/B cells plus claimed cells; contested cells remain neutral.

## Approach (Multi-source BFS)
- Initialize all 'A' and 'B' positions as sources at time 0 with type = A(1) or B(2)
- Maintain `dist[x][y]` = earliest time a side reached the cell, and `owner[x][y]` in {-1=unreached, 0=contested, 1=A, 2=B}
- From a source/pop (x,y,t,type), try to claim neighbors that are base '.'
  - If neighbor not reached: set dist=t+1, owner=type, enqueue
  - If neighbor already reached with the same dist and owner!=type: mark contested (owner=0); do not enqueue further from it
  - If neighbor already owned earlier (smaller dist): ignore
- Do not expand from contested cells.
- Answer: count initial 'A' + cells with owner=1 vs initial 'B' + cells with owner=2; compare.

This simulates simultaneous front expansion with tie resolution.

## Files
- `battle_territories.py` — Python implementation with example
- `battle_territories.cpp` — C++17 implementation
