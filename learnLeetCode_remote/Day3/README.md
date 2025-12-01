# Day 3 — Two Pointers & In-Place Array Patterns

This folder contains solutions for classic array/two-pointer problems in Python and C++, each with brief docs and simple self-tests.

Problems included:

- Two Sum II — Input array is sorted (Easy): `two_sum_ii.py`, `two_sum_ii.cpp`
- Remove Duplicates from Sorted Array (Easy): `remove_duplicates_sorted_array.py`, `remove_duplicates_sorted_array.cpp`
- Move Zeroes (Easy): `move_zeroes.py`, `move_zeroes.cpp`
- Bonus (Medium): Container With Most Water: `container_with_most_water.py`, `container_with_most_water.cpp`

## Approaches at a Glance

- Two Sum II: Two pointers from both ends; adjust by comparing sum vs target. O(n) time, O(1) space.
- Remove Duplicates: Two pointers (read/write). Overwrite when encountering new unique value. O(n) time, O(1) space.
- Move Zeroes: Compact non-zeros forward, then fill trailing with zeros. Minimal writes. O(n) time, O(1) space.
- Container With Most Water: Two pointers; move the shorter side inward to potentially find a taller line. O(n) time, O(1) space.

## Quick Run

Each Python file can be run directly to execute a small smoke test. From the repo root:

```powershell
python .\Day3\two_sum_ii.py
python .\Day3\remove_duplicates_sorted_array.py
python .\Day3\move_zeroes.py
python .\Day3\container_with_most_water.py
```

Or run the combined Python demo:

```powershell
python .\Day3\main.py
```

### C++ quick compile/run

Using g++ (MinGW) in PowerShell:

```powershell
g++ .\Day3\two_sum_ii.cpp -std=c++17 -O2 -o .\Day3\two_sum_ii.exe; .\Day3\two_sum_ii.exe
g++ .\Day3\remove_duplicates_sorted_array.cpp -std=c++17 -O2 -o .\Day3\remove_duplicates_sorted_array.exe; .\Day3\remove_duplicates_sorted_array.exe
g++ .\Day3\move_zeroes.cpp -std=c++17 -O2 -o .\Day3\move_zeroes.exe; .\Day3\move_zeroes.exe
g++ .\Day3\container_with_most_water.cpp -std=c++17 -O2 -o .\Day3\container_with_most_water.exe; .\Day3\container_with_most_water.exe
```

Using MSVC (Developer PowerShell for VS):

```powershell
cl /EHsc /O2 /std:c++17 .\Day3\two_sum_ii.cpp && .\two_sum_ii.exe
cl /EHsc /O2 /std:c++17 .\Day3\remove_duplicates_sorted_array.cpp && .\remove_duplicates_sorted_array.exe
cl /EHsc /O2 /std:c++17 .\Day3\move_zeroes.cpp && .\move_zeroes.exe
cl /EHsc /O2 /std:c++17 .\Day3\container_with_most_water.cpp && .\container_with_most_water.exe
```

## Notes

- Implementations are iterative and avoid extra allocations.
- Function names follow LeetCode style for easy copy-paste into the judge.
- Add more tests as desired—see `main.py` for examples.
