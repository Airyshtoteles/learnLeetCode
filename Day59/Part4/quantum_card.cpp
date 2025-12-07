#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Card {
    int low, high;
    int diff; // high - low
};

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    int N;
    if (!(cin >> N)) return 0;

    vector<Card> cards(N);
    for (int i = 0; i < N; ++i) cin >> cards[i].low;
    for (int i = 0; i < N; ++i) cin >> cards[i].high;

    for (int i = 0; i < N; ++i) {
        cards[i].diff = cards[i].high - cards[i].low;
    }

    // Sort by diff descending
    sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
        return a.diff > b.diff;
    });

    // Number of Even slots (High) = floor(N/2)
    int num_high = N / 2;
    
    long long total_score = 0;
    for (int i = 0; i < N; ++i) {
        if (i < num_high) {
            total_score += cards[i].high;
        } else {
            total_score += cards[i].low;
        }
    }

    cout << total_score << endl;

    return 0;
}
