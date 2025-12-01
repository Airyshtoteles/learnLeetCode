# 🧩 Day 1 — Single Number (7 Oktober 2025)

## 📘 Deskripsi Soal
Diberikan sebuah array `nums` yang berisi bilangan bulat. Setiap elemen muncul **tepat dua kali**, kecuali **satu elemen** yang muncul **sekali saja**. Temukan elemen unik tersebut.

Syarat:
- Waktu: `O(n)` (hanya satu pass atau linear scan diperbolehkan)
- Ruang tambahan: `O(1)` (tidak boleh pakai struktur data ekstra seperti map / unordered_map / vector frekuensi)

Contoh:
```
Input : [4, 1, 2, 1, 2]
Output: 4

Input : [2, 2, 3]
Output: 3
```

## 💡 Intuisi & Ide Utama
Karena semua angka selain satu muncul **dua kali**, kita butuh operasi yang bisa "meniadakan" pasangan angka yang sama dan hanya menyisakan yang tunggal. Operasi **bitwise XOR (^)** punya sifat yang *pas* untuk ini.

## 🔐 Sifat Penting XOR
| Sifat | Penjelasan |
|-------|------------|
| `a ^ a = 0` | Angka yang sama saling menetralkan |
| `a ^ 0 = a` | Identitas (zero tidak mengubah hasil) |
| Komutatif | `a ^ b = b ^ a` |
| Asosiatif | `(a ^ b) ^ c = a ^ (b ^ c)` |

Karena komutatif dan asosiatif, urutan tidak penting—semua pasangan akan lenyap jadi 0. Hanya angka tanpa pasangan yang bertahan.

Contoh langkah XOR:
```
4 ^ 1 ^ 2 ^ 1 ^ 2
= (1 ^ 1) ^ (2 ^ 2) ^ 4
= 0 ^ 0 ^ 4
= 4
```

## ✅ Implementasi (C++)
File: `find_unique_improve.cpp`
```cpp
#include <bits/stdc++.h>
using namespace std;

int singleNumber(const vector<int>& nums) {
    int acc = 0;
    for (int v : nums) acc ^= v; // XOR semua elemen
    return acc; // tersisa elemen unik
}

int main() {
    cout << singleNumber({4,1,2,1,2}) << '\n'; // 4
    cout << singleNumber({2,2,3}) << '\n';     // 3
}
```

### 🛠️ Cara Kompilasi & Jalan (Windows / PowerShell)
Pastikan sudah menginstall g++ (MinGW).
```powershell
g++ -std=c++17 -O2 -Wall -Wextra -pedantic find_unique_improve.cpp -o single_number
./single_number
```

## ⏱️ Kompleksitas
- Waktu: `O(n)` — satu loop melalui array
- Ruang tambahan: `O(1)` — hanya 1 accumulator (tanpa struktur tambahan)

## 🧪 Tambahan Kasus Uji (Manual)
| Input | Output | Catatan |
|-------|--------|--------|
| `[1]` | 1 | Kasus minimum |
| `[1,2,1]` | 2 | Unik di tengah |
| `[0,5,0]` | 5 | Termasuk nol |
| `[-1,4,4]` | -1 | Bilangan negatif valid |
| `[9,9,9,7,7,7,3]` | 3 | Semua tripel kecuali satu? (Tidak sesuai constraint asli; algoritma masih kembalikan 3, tapi problem mendefinisikan setiap elemen selain satu muncul dua kali) |

Catatan: Jika constraint berubah (misal ada elemen muncul 3 kali), solusi XOR tidak lagi cukup dan butuh bit counting khusus (seperti pada "Single Number II").

## 🧠 Validasi & Why It Works
Misalkan himpunan angka adalah: `{x, a1, a1, a2, a2, ..., ak, ak}` di mana `x` unik.
\[
(((x \oplus a_1) \oplus a_1) \oplus a_2) \oplus a_2 ... = x \oplus 0 \oplus 0 ... = x
\]
Semua pasangan menjadi 0 karena `a_i ^ a_i = 0`.

## 🚫 Pendekatan yang Tidak Dipakai (dan Kenapa)
| Pendekatan | Alasan Ditolak |
|------------|----------------|
| Hash map / frequency count | Butuh `O(n)` ruang tambahan |
| Sorting lalu scan | Sorting `O(n log n)` (tidak memenuhi syarat waktu) |
| Brute force nested loop | `O(n^2)` terlalu lambat |

## 📚 Catatan Belajar Hari Ini
- Memahami operasi bitwise XOR & sifat matematisnya
- Menghargai pentingnya batasan kompleksitas waktu & ruang
- Melihat contoh klasik optimal minimalis (1 variabel, 1 loop)
- Mulai membangun intuisi: gunakan sifat aljabar/bit untuk mengeliminasi pasangan/pola

## 🧾 Edge Cases (Secara Teoretis)
| Kasus | Status |
|-------|--------|
| Array kosong | Tidak valid sesuai deskripsi (anggap selalu ada 1 unik) |
| Semua elemen sama | Tidak valid karena harus ada tepat 1 unik |
| Angka negatif | Tetap jalan (XOR bekerja di representasi bit) |
| Nilai besar (int batas) | Aman selama dalam range `int` |

## 🧪 (Opsional) Versi dengan Input Dinamis
```cpp

int n; cin >> n; vector<int> arr(n); for (int i=0;i<n;++i) cin >> arr[i];
cout << singleNumber(arr) << '\n';
```

## 🔍 Checklist Internal
- [x] O(n) waktu
- [x] O(1) ruang tambahan
- [x] Tidak pakai struktur tambahan
- [x] Kompilasi bersih dengan flags ketat

## 📅 Log Harian
- Hari: 1 / 100
- Topik: Bit Manipulation Basics
- Status: ✅ Selesai
- Mood: 🔥 Start strong!

## 🎯 Next Steps (Rencana Hari Berikutnya)
1. Single Number II (setiap elemen muncul 3 kali kecuali 1) → gunakan bit counting / mod 3
2. Missing Number (0..n, satu hilang) → XOR atau rumus sigma
3. Bit Count / Hamming Weight untuk pemanasan sebelum variasi lanjutan

## 🏁 Penutup
Soal ini contoh bagus bahwa: *"Kadang solusi paling elegan bukan menghitung semuanya, tapi menghapus yang tidak perlu."* XOR = sapu ajaib untuk pasangan duplikat.

> Konsistensi kecil hari ini = lompatan besar di hari ke-30, 60, 100.

Selamat lanjut! 🚀
