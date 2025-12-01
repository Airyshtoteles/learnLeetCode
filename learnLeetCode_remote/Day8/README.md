# Day 8 — Minimum Number of Taps to Open to Water a Garden (#1326)

Tentukan jumlah minimum keran (taps) yang dibuka untuk menyiram taman [0, n].
Keran ke-i menyiram interval `[i - ranges[i], i + ranges[i]]`.
Jika tidak bisa menutupi seluruh [0, n], kembalikan -1.

## Intuisi

- Mirip Jump Game II: kita ingin minimalkan "lompatan" untuk menutupi interval hingga n.
- Ubah ke bentuk greedy coverage:
  - Untuk setiap titik awal `left`, simpan sejauh mana bisa dicapai (`maxReach[left]`).
  - Sweep dari kiri ke kanan, perluas `farthest` dengan `maxReach[i]`.
  - Jika `i == currEnd`, kita butuh membuka keran baru: `taps += 1`, `currEnd = farthest`.
  - Jika `farthest == currEnd`, artinya terjebak → return -1.

## Kompleksitas

- Waktu: O(n)
- Ruang: O(n)

## File

- Python: `min_taps.py`
- C++: `min_taps.cpp`

## Cara Menjalankan

Python:
```powershell
python .\Day8\min_taps.py
```

C++ (g++ MinGW):
```powershell
g++ .\Day8\min_taps.cpp -std=c++17 -O2 -o .\Day8\min_taps.exe
.\Day8\min_taps.exe
```

C++ (MSVC):
```powershell
cl /EHsc /O2 /std:c++17 .\Day8\min_taps.cpp && .\min_taps.exe
```