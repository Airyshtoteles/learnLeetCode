# Day 20 — Part 1: Design a Text Editor (LC 2296)

Implement a simple text editor with a cursor, supporting:
- addText(text): insert at cursor
- deleteText(k): delete up to k chars to the left; return count deleted
- cursorLeft(k), cursorRight(k): move cursor and return up to the last 10 chars to the left of cursor

Approach:
- Maintain two stacks (vectors): `left` holds text left of cursor, `right` holds text right of cursor (top is nearest).
- addText pushes into `left`.
- deleteText pops from `left` up to k.
- cursorLeft pops from `left` to `right` k times; cursorRight pops from `right` to `left` k times.
- The last 10 chars are the suffix of `left`.

Complexity:
- Each operation is O(len) for the movement amount; overall amortized O(1) per character moved/added/deleted.

Files:
- text_editor.py — Python implementation with small example.
- text_editor.cpp — C++ implementation with small example in main().
