#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Move {
    long long w, v; // w = cost - drain, v = drain
};

long long S, E;
int P;
vector<Move> moves;
vector<Move> hull;

// Cross product of (b-a) and (c-a)
long long cross_product(Move a, Move b, Move c) {
    return (b.w - a.w) * (c.v - a.v) - (b.v - a.v) * (c.w - a.w);
}

void build_hull() {
    sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
        if (a.w != b.w) return a.w < b.w;
        return a.v > b.v;
    });
    
    vector<Move> unique_moves;
    for (auto m : moves) {
        if (unique_moves.empty()) {
            unique_moves.push_back(m);
        } else {
            // If same w, we already have better v (due to sort)
            if (unique_moves.back().w == m.w) continue;
            // If new move has lower v than previous (lower w), it's dominated
            // Because we want MAX v for given w.
            // Wait, lower w is better (less cost).
            // So if we have (w1, v1) and (w2, v2) with w2 > w1.
            // If v2 <= v1, then w2 is strictly worse (more cost, less/same val).
            // So we keep increasing v.
            if (m.v > unique_moves.back().v) {
                unique_moves.push_back(m);
            }
        }
    }
    
    // Build Upper Hull
    // We want concave shape (slopes decreasing).
    // (w, v).
    for (auto m : unique_moves) {
        while (hull.size() >= 2) {
            if (cross_product(hull[hull.size()-2], hull.back(), m) >= 0) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(m);
    }
}

long long get_total_drain(long long K) {
    if (K <= 0) return 0;
    double w_target = (double)S / K;
    
    if (w_target < hull[0].w) return -1; // Impossible
    if (w_target >= hull.back().w) {
        return K * hull.back().v;
    }
    
    auto it = lower_bound(hull.begin(), hull.end(), w_target, [](const Move& m, double val) {
        return m.w < val;
    });
    
    Move p2 = *it;
    Move p1 = *(it - 1);
    
    double v_mix = p1.v + (double)(p2.v - p1.v) * (w_target - p1.w) / (p2.w - p1.w);
    return (long long)(K * v_mix);
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> S >> E >> P)) return 0;
    
    for (int i = 0; i < P; ++i) {
        long long c, d, del;
        cin >> c >> d >> del;
        if (d <= 0) continue;
        moves.push_back({c - d, d});
    }
    
    if (moves.empty()) {
        cout << -1 << endl;
        return 0;
    }
    
    build_hull();
    
    if (hull.empty()) {
        cout << -1 << endl;
        return 0;
    }
    
    long long min_w = hull[0].w;
    long long high = 2000000000LL;
    if (min_w > 0) {
        high = S / min_w;
        if (high == 0) {
            cout << -1 << endl;
            return 0;
        }
    }
    
    long long low = 1;
    long long ans = -1;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long val = get_total_drain(mid);
        
        if (val >= E) {
            ans = mid;
            high = mid - 1;
        } else {
            if (mid == high) break;
            long long val_next = get_total_drain(mid + 1);
            if (val_next > val) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
