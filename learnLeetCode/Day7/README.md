# Day 7 — Longest Substring Without Repeating Characters

Temukan panjang substring terpanjang tanpa karakter berulang.

## Contoh

- Input: "abcabcbb" → Output: 3 ("abc")
- Input: "bbbbb" → Output: 1 ("b")
- Input: "pwwkew" → Output: 3 ("wke")

## Kendala

- 0 <= s.length <= 5 × 10⁴
- s berisi huruf, angka, simbol, dan spasi

## Pendekatan

- Sliding Window + Hash Set
- Expand `right`, jika duplikat: geser `left` dan hapus karakter sampai window valid
- Update panjang maksimum di setiap langkah

Kompleksitas:
- Waktu: O(n)
- Ruang: O(min(m, n))

## File

- Python: `longest_substring.py`
- C++: `longest_substring.cpp`

## Cara Menjalankan

Python:
```powershell
python .\Day7\longest_substring.py
```

C++ (g++ MinGW):
```powershell
g++ .\Day7\longest_substring.cpp -std=c++17 -O2 -o .\Day7\longest_substring.exe
.\Day7\longest_substring.exe
```

C++ (MSVC):
```powershell
cl /EHsc /O2 /std:c++17 .\Day7\longest_substring.cpp && .\longest_substring.exe
```

---

# Day 7 — Swim in Rising Water (LeetCode #778, Hard)

Cari waktu minimum `t` agar bisa mencapai `(n-1, n-1)` dari `(0, 0)` pada grid `n x n` dengan ketinggian unik `0..n^2-1`,
ketika air naik 1 unit tiap waktu dan hanya bisa melewati sel `height <= t`.

## Pendekatan (Optimal)

- Dijkstra-style dengan min-heap (priority queue): cost sebuah path adalah `max(height)` di sepanjang path.
- Selalu expand sel dengan `cost` paling kecil. Saat kita pop tujuan, itu jawaban optimal.
- Kompleksitas: Waktu O(n^2 log n), Ruang O(n^2)

## File

- C++: `swim_in_rising_water.cpp`

## Cara Menjalankan

C++ (g++ MinGW):
```powershell
g++ .\Day7\swim_in_rising_water.cpp -std=c++17 -O2 -o .\Day7\swim_in_rising_water.exe
.\Day7\swim_in_rising_water.exe
```

C++ (MSVC):
```powershell
cl /EHsc /O2 /std:c++17 .\Day7\swim_in_rising_water.cpp && .\swim_in_rising_water.exe
```