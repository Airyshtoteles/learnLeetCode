# Day 5 — Longest Substring Without Repeating Characters

Cari panjang substring terpanjang yang tidak memiliki karakter yang berulang.

## Contoh

- Input: `"abcabcbb"` → Output: `3` (substring "abc")
- Input: `"bbbbb"` → Output: `1` (substring "b")  
- Input: `"pwwkew"` → Output: `3` (substring "wke")

## Kendala

- 0 <= s.length <= 5 × 10⁴
- s terdiri dari karakter huruf Inggris, angka, simbol, dan spasi

## Pendekatan

**Sliding Window dengan Hash Set:**
1. Gunakan dua pointer (`left` dan `right`) untuk menentukan window
2. Expand window dengan menggeser `right`, tambahkan karakter ke set
3. Jika karakter sudah ada di set (duplikat), shrink window dari `left` sampai duplikat hilang
4. Update panjang maksimum setiap kali window valid

**Kompleksitas:**
- Waktu: O(n) - setiap karakter dikunjungi maksimal 2 kali
- Ruang: O(min(m,n)) - m adalah ukuran character set, n adalah panjang string

## File

- Python: `longest_substring.py`
- C++: `longest_substring.cpp`

## Cara Menjalankan

Python:

```powershell
python .\Day5\longest_substring.py
```

C++ (g++ MinGW):

```powershell
g++ .\Day5\longest_substring.cpp -std=c++17 -O2 -o .\Day5\longest_substring.exe
.\Day5\longest_substring.exe
```

C++ (MSVC Developer PowerShell):

```powershell
cl /EHsc /O2 /std:c++17 .\Day5\longest_substring.cpp && .\longest_substring.exe
```

## Penjelasan Algoritma

Sliding window adalah teknik efektif untuk substring problems:

1. **Expand:** Geser `right` pointer, tambahkan `s[right]` ke window
2. **Contract:** Jika ada duplikat, geser `left` pointer sampai duplikat hilang
3. **Track:** Simpan panjang window maksimum yang pernah dicapai

Contoh trace untuk `"abcabcbb"`:
- Window: [a] → [ab] → [abc] → [bc] (duplikat 'a') → [bca] (duplikat 'b') → [cab] → [cab] (duplikat 'b') → [ab] → [b]
- Panjang max: 3 (dari "abc")