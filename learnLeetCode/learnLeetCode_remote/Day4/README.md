# Day 4 — Move Zeroes to End (Optimized)

Pindahkan semua elemen 0 ke akhir array sambil mempertahankan urutan relatif elemen non-zero. Lakukan in-place tanpa membuat salinan array baru.

## Contoh

- Input: `[0, 1, 0, 3, 12]` → Output: `[1, 3, 12, 0, 0]`
- Input: `[0, 0, 1]` → Output: `[1, 0, 0]`

## Batasan

- 1 <= nums.length <= 1e5
- -1e4 <= nums[i] <= 1e4

## Pendekatan

- Two pointers (single pass): pointer `read` untuk scanning, `write` untuk posisi tulis elemen non-zero berikutnya.
- Saat `nums[read] != 0`, tukar `nums[write]` dan `nums[read]` hanya jika `read != write` (mengurangi jumlah penulisan), lalu `write += 1`.
- Kompleksitas: Waktu O(n), Ruang O(1).

## File

- Python: `move_zeroes.py`
- C++: `move_zeroes.cpp`

## Cara Menjalankan

Python:

```powershell
python .\Day4\move_zeroes.py
```

C++ (g++ MinGW):

```powershell
g++ .\Day4\move_zeroes.cpp -std=c++17 -O2 -o .\Day4\move_zeroes.exe
.\Day4\move_zeroes.exe
```

C++ (MSVC Developer PowerShell):

```powershell
cl /EHsc /O2 /std:c++17 .\Day4\move_zeroes.cpp && .\move_zeroes.exe
```
