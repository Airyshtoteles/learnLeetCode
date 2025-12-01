/**
 * LeetCode 121 - Best Time to Buy and Sell Stock (Easy)
 * Satu transaksi: beli sekali, jual sekali.
 * Strategi: lacak harga minimum sejauh ini, tiap hari hitung potensi profit.
 * Waktu: O(n), Memori: O(1)
 * @param {number[]} prices
 * @return {number}
 */
function maxProfit(prices) {
  let minPrice = Infinity;
  let maxProfit = 0;
  for (const price of prices) {
    if (price < minPrice) {
      minPrice = price; // kandidat beli
    } else {
      const profit = price - minPrice;
      if (profit > maxProfit) maxProfit = profit;
    }
  }
  return maxProfit;
}

function runTests() {
  const cases = [
    [[7,1,5,3,6,4], 5],
    [[7,6,4,3,1], 0],
    [[2,4,1], 2],
    [[1], 0],
    [[], 0],
    [[3,3,3], 0],
  ];
  for (const [prices, expected] of cases) {
    const got = maxProfit(prices);
    const status = got === expected ? 'OK' : `FAIL (expected ${expected}, got ${got})`;
    console.log(`prices=${JSON.stringify(prices)} -> ${got} ${status}`);
  }
}

if (require.main === module) {
  runTests();
}

module.exports = { maxProfit };
