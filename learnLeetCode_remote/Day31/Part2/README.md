# Day 31 — Part 2: Dungeon Duel

Two players A and B start with HP=100, each has M mana. On a turn, a player may:
- attack: deal X damage to the opponent (HP -= X)
- heal: restore Y HP to self, capped at 100 (HP = min(100, HP+Y))
Every action costs 1 mana. A takes the first turn. Determine whether A has a forced win assuming optimal play.

State:
(hpA, hpB, manaA, manaB, turn) where turn=0 for A, 1 for B.
Terminal:
- If hpA <= 0 and hpB <= 0: last mover wins → treat as loss for current player whose turn cannot happen; we can resolve ties as opponent win.
- If hpA <= 0: A lost; return False.
- If hpB <= 0: A won; return True.
- If both manas are zero and both alive: no further actions → compare hpA and hpB; A wins iff hpA > hpB.

Transition:
- On A's turn: Can choose attack (if manaA>0) or heal (if manaA>0). If no manaA, skip to B (turn=1) with same HPs.
- On B's turn: symmetric. If no manaB, skip to A (turn=0).

Use DFS + memo (minimax): current player aims to make AWin state True if possible; the opponent tries to avoid it.

Files:
- dungeon_duel.py — Python DFS + memo.
- dungeon_duel.cpp — C++17 DFS + memo.
