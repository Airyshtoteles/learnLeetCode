"""
LeetCode 121 - Best Time to Buy and Sell Stock
Tingkat: Easy

Diberikan array prices, di mana prices[i] adalah harga saham pada hari ke-i.
Cari profit maksimum dari 1 transaksi (beli sekali, jual sekali). Jika tidak ada profit positif, kembalikan 0.

Strategi:
- Lacak harga minimum sejauh ini (min_price)
- Untuk setiap harga, hitung potensi profit: price - min_price
- Simpan profit maksimum

Kompleksitas:
Waktu  : O(n)
Memori : O(1)

Contoh:
Input : [7,1,5,3,6,4]
Langkah: min=7 ->1 -> (profit 4) -> (profit 2) -> (profit 5) -> (profit 3)
Output: 5 (beli 1, jual 6)

Edge cases:
- [] atau [x] -> 0
- Harga selalu turun -> 0

Jalankan file ini langsung untuk uji cepat.
"""
from __future__ import annotations
from typing import List

def maxProfit(prices: List[int]) -> int:
    """Hitung profit maksimum dari satu transaksi beli-jual.

    Args:
        prices: List harga saham per hari.
    Returns:
        Profit maksimum (0 jika tidak ada keuntungan).
    """
    min_price = float('inf')
    max_profit = 0

    for price in prices:
        if price < min_price:
            min_price = price  # kandidat beli baru
        else:
            profit = price - min_price
            if profit > max_profit:
                max_profit = profit
    return max_profit

def _run_tests():
    cases = [
        ([7,1,5,3,6,4], 5),
        ([7,6,4,3,1], 0),
        ([2,4,1], 2),
        ([1], 0),
        ([], 0),
        ([3,3,3], 0),
    ]
    for prices, expected in cases:
        got = maxProfit(prices)
        status = "OK" if got == expected else f"FAIL (expected {expected}, got {got})"
        print(f"prices={prices} -> {got} {status}")

if __name__ == "__main__":
    _run_tests()
