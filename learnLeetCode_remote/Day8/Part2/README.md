# Day 8 — Part 2: 3Sum

Kembalikan semua triplet unik `[a,b,c]` sehingga `a + b + c = 0`.

## Pendekatan

- Sort array terlebih dahulu
- Iterasi anchor i dari kiri ke kanan
  - Skip duplikat untuk `i`
  - Two-pointers di segmen `(i+1 .. n-1)`
  - Jika `sum == 0`: tambahkan triplet, lalu geser `l` dan `r` melewati duplikat
  - Jika `sum < 0`: `l++`
  - Jika `sum > 0`: `r--`

Kompleksitas: O(n^2) waktu, O(1) ruang tambahan (tidak termasuk output)

## File

- Python: `three_sum.py`
- C++: `three_sum.cpp`

## Cara Menjalankan

Python:
```powershell
python .\Day8\Part2\three_sum.py
```

C++ (g++ MinGW):
```powershell
g++ .\Day8\Part2\three_sum.cpp -std=c++17 -O2 -o .\Day8\Part2\three_sum.exe
.\Day8\Part2\three_sum.exe
```

C++ (MSVC):
```powershell
cl /EHsc /O2 /std:c++17 .\Day8\Part2\three_sum.cpp && .\three_sum.exe
```