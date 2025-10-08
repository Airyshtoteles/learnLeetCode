// LeetCode 121 - Best Time to Buy and Sell Stock (Easy)
// Strategi: Single pass, simpan harga minimum sejauh ini & hitung profit maksimum.
// Waktu: O(n), Memori: O(1)

#include <bits/stdc++.h>
using namespace std;

int maxProfit(const vector<int>& prices) {
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

struct Case { vector<int> prices; int expected; };

int main() {
    vector<Case> cases = {
        {{7,1,5,3,6,4}, 5},
        {{7,6,4,3,1}, 0},
        {{2,4,1}, 2},
        {{1}, 0},
        {{}, 0},
        {{3,3,3}, 0},
    };

    for (auto& c : cases) {
        int got = maxProfit(c.prices);
        cout << "prices=[";
        for (size_t i = 0; i < c.prices.size(); ++i) {
            if (i) cout << ',';
            cout << c.prices[i];
        }
        cout << "] -> " << got << (got == c.expected ? " OK" : " FAIL (expected " + to_string(c.expected) + ")") << '\n';
    }
    return 0;
}
