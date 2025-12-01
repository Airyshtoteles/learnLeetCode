# Day 6 — Jump Game II (Medium)

Tentukan minimum jumlah lompatan untuk mencapai indeks terakhir dari array, dimana setiap elemen menunjukkan jarak maksimum yang bisa dilompat.

## Contoh

- Input: `[2,3,1,1,4]` → Output: `2` 
  - Lompatan: 0→1 (jarak 2), 1→4 (jarak 3)
- Input: `[2,3,0,1,4]` → Output: `2`
  - Lompatan: 0→1 (jarak 2), 1→4 (jarak 3)

## Kriteria Efisiensi

- **Runtime:** O(n) - single pass tanpa nested loop
- **Memory:** O(1) - hanya menggunakan beberapa variabel
- **Approach:** Greedy dengan tracking jangkauan maksimum

## Pendekatan: Greedy vs Dynamic Programming

### ❌ DP Approach (O(n²))
```python
# Terlalu lambat untuk input besar
dp[i] = min(dp[j] + 1) for all j that can reach i
```

### ✅ Greedy Approach (O(n))
**Key Insight:** Kita tidak perlu tahu path optimal yang tepat, cukup tahu kapan harus jump.

**Algoritma:**
1. **Track dua range:** 
   - `current_end`: akhir dari range jump saat ini
   - `farthest_reach`: posisi terjauh yang bisa dicapai sejauh ini

2. **Strategi jump:**
   - Selalu explore semua opsi dalam range saat ini
   - Jump hanya ketika mencapai ujung range (`i == current_end`)
   - Update range baru ke `farthest_reach`

3. **Optimasi:**
   - Early termination jika sudah bisa mencapai akhir
   - Tidak perlu jump dari posisi terakhir

## Trace Contoh

Input: `[2,3,1,1,4]`

```
i=0: nums[0]=2, farthest_reach=2, current_end=0
  -> Jump #1, new range: [0,2]

i=1: nums[1]=3, farthest_reach=4, current_end=2  
i=2: nums[2]=1, farthest_reach=4, current_end=2
  -> Jump #2, new range: [0,4] -> can reach end!

Result: 2 jumps
```

## File

- Python: `jump_game_ii.py` (dengan verbose mode untuk learning)
- C++: `jump_game_ii.cpp` (optimized dengan early termination)

## Cara Menjalankan

Python:

```powershell
python .\Day6\jump_game_ii.py
```

C++ (g++ MinGW):

```powershell
g++ .\Day6\jump_game_ii.cpp -std=c++17 -O2 -o .\Day6\jump_game_ii.exe
.\Day6\jump_game_ii.exe
```

C++ (MSVC Developer PowerShell):

```powershell
cl /EHsc /O2 /std:c++17 .\Day6\jump_game_ii.cpp && .\jump_game_ii.exe
```

## Mengapa Greedy Works?

**Optimal Substructure:** Jika kita bisa mencapai posisi `i` dalam `k` jumps, maka untuk semua posisi yang bisa dicapai dari `i`, kita butuh maksimal `k+1` jumps.

**Greedy Choice:** Pada setiap jump, pilih range yang memberikan jangkauan terjauh. Ini guarantees optimal karena:
1. Kita selalu explore semua opsi sebelum jump
2. Memilih jangkauan terjauh memberikan fleksibilitas maksimum untuk jump berikutnya

**No Backtracking Needed:** Sekali kita memutuskan jump, tidak ada benefit untuk kembali ke pilihan sebelumnya.