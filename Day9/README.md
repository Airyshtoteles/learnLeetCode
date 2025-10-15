# Day 9 — LeetCode 135: Candy

Diberikan array `ratings` yang berisi rating untuk setiap anak dalam barisan.
Aturan membagikan permen:
- Setiap anak minimal mendapat 1 permen.
- Anak dengan rating lebih tinggi daripada tetangganya harus mendapat lebih banyak permen dari tetangganya itu.

Tugas: Kembalikan jumlah minimum permen yang harus dibagikan.

Contoh
- Input: ratings = [1,0,2] → Output: 5
- Input: ratings = [1,2,2] → Output: 4

Pendekatan (Greedy, 2-pass)
1) Inisialisasi semua anak dengan 1 permen.
2) Scan kiri → kanan: jika `ratings[i] > ratings[i-1]`, set `candies[i] = candies[i-1] + 1`.
3) Scan kanan → kiri: jika `ratings[i] > ratings[i+1]`, set `candies[i] = max(candies[i], candies[i+1] + 1)`.
4) Jawaban adalah jumlah seluruh elemen `candies`.

Kompleksitas
- Waktu: O(n)
- Ruang: O(n)

Files
- candy.py — Implementasi Python + assertions untuk contoh.
- candy.cpp — Implementasi C++17 + sanity checks di `main`.

Cara Menjalankan
- Python (dari folder Day9):
  ```powershell
  python .\candy.py
  ```
- C++ (PowerShell, MinGW g++):
  ```powershell
  g++ -std=c++17 -O2 .\candy.cpp -o .\candy.exe ; if ($?) { .\candy.exe }
  ```
