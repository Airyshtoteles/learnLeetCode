# LeetCode 121 - Best Time to Buy and Sell Stock (Easy)

## Deskripsi
Diberikan array `prices` di mana `prices[i]` adalah harga saham pada hari ke-`i`.
Tugas: Temukan profit maksimum dari **tepat satu transaksi** (beli sekali, lalu jual sekali di hari setelahnya). Jika tidak ada profit positif, hasilkan `0`.

Contoh:
```
Input  : [7,1,5,3,6,4]
Output : 5
Penjelasan: Beli di 1, jual di 6 → profit = 6 - 1 = 5
```

## Intuisi Solusi
Kita ingin mencari `prices[j] - prices[i]` dengan `j > i` yang maksimum.
Alih-alih mencoba semua pasangan (O(n²)), kita:
1. Lacak harga minimum sejauh ini (`min_price`).
2. Untuk tiap harga sekarang (`price`), hitung profit jika jual hari ini: `price - min_price`.
3. Simpan profit maksimum (`max_profit`).
4. Jika menemukan harga lebih rendah, perbarui `min_price` (anggap kita beli ulang di situ).

## Algoritma (Pseudo)
```
min_price = +∞
max_profit = 0
for price in prices:
    if price < min_price:
        min_price = price
    else:
        profit = price - min_price
        if profit > max_profit:
            max_profit = profit
return max_profit
```

## Kompleksitas
- Waktu: `O(n)` (satu pass)
- Memori: `O(1)`

## Edge Cases
| Input                | Output | Alasan                              |
|----------------------|--------|-------------------------------------|
| []                   | 0      | Tidak ada transaksi                 |
| [5]                  | 0      | Perlu minimal 2 hari                |
| [7,6,4,3,1]          | 0      | Harga selalu turun                  |
| [3,3,3]              | 0      | Tidak ada selisih positif           |
| [2,4,1]              | 2      | Beli 2 jual 4                       |

## Implementasi
### Python (`max_profit.py`)
Jalankan untuk uji mandiri:
```bash
python max_profit.py
```

### JavaScript (`max_profit.js`)
```bash
node max_profit.js
```

### C++ (`max_profit.cpp`)
Compile & run (g++):
```bash
g++ -std=c++17 -O2 -Wall -o max_profit max_profit.cpp
./max_profit
```

## Cuplikan Kode
### Python
```python
def maxProfit(prices):
    min_price = float('inf')
    max_profit = 0
    for price in prices:
        if price < min_price:
            min_price = price
        else:
            profit = price - min_price
            if profit > max_profit:
                max_profit = profit
    return max_profit
```

### JavaScript
```javascript
function maxProfit(prices) {
  let minPrice = Infinity;
  let maxProfit = 0;
  for (const price of prices) {
    if (price < minPrice) {
      minPrice = price;
    } else {
      const profit = price - minPrice;
      if (profit > maxProfit) maxProfit = profit;
    }
  }
  return maxProfit;
}
```

### C++
```cpp
int maxProfit(const std::vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    for (int price : prices) {
        if (price < minPrice) {
            minPrice = price;
        } else {
            int profit = price - minPrice;
            if (profit > maxProfit) maxProfit = profit;
        }
    }
    return maxProfit;
}
```

## Bonus (Lanjutan)
- Multi transaksi: LeetCode 122 (jumlahkan semua kenaikan lokal)
- Dengan biaya transaksi: LeetCode 714
- Dengan cooldown: LeetCode 309
- Dua transaksi: LeetCode 123
- K transaksi: LeetCode 188

  
