#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>

using namespace std;

struct BitSet {
    int n;
    int num_words;
    vector<uint64_t> words;

    BitSet(int size) : n(size) {
        num_words = (n + 63) / 64;
        words.resize(num_words, 0);
    }

    void set(int idx) {
        if (idx < 0 || idx >= n) return;
        words[idx / 64] |= (1ULL << (idx % 64));
    }

    void set_range(int l, int r) {
        if (l > r) return;
        l = max(0, l);
        r = min(n - 1, r);
        
        int start_word = l / 64;
        int end_word = r / 64;
        
        if (start_word == end_word) {
            uint64_t mask = (~0ULL << (l % 64)) & (~0ULL >> (63 - (r % 64)));
            words[start_word] |= mask;
        } else {
            words[start_word] |= (~0ULL << (l % 64));
            for (int i = start_word + 1; i < end_word; ++i) {
                words[i] = ~0ULL;
            }
            words[end_word] |= (~0ULL >> (63 - (r % 64)));
        }
    }

    void shift_left() {
        for (int i = num_words - 1; i > 0; --i) {
            words[i] = (words[i] << 1) | (words[i - 1] >> 63);
        }
        words[0] <<= 1;
        int unused_bits = num_words * 64 - n;
        if (unused_bits > 0) {
            words[num_words - 1] &= (~0ULL >> unused_bits);
        }
    }

    void shift_right() {
        for (int i = 0; i < num_words - 1; ++i) {
            words[i] = (words[i] >> 1) | (words[i + 1] << 63);
        }
        words[num_words - 1] >>= 1;
    }

    int count() const {
        int cnt = 0;
        for (uint64_t w : words) {
            #ifdef __GNUC__
                cnt += __builtin_popcountll(w);
            #else
                uint64_t v = w;
                while (v) {
                    v &= (v - 1);
                    cnt++;
                }
            #endif
        }
        return cnt;
    }

    void bitwise_or(const BitSet& other) {
        for (int i = 0; i < num_words; ++i) {
            words[i] |= other.words[i];
        }
    }
    
    void reset() {
        fill(words.begin(), words.end(), 0);
    }
};

struct King {
    char type;
    int r, c, R;
};

long long solve_elemental_chess(int N, vector<King>& kings) {
    vector<bool> fire_rows(N, false);
    BitSet water_mask(N);
    BitSet diag1_mask(N); 
    BitSet diag2_mask(N); 
    
    vector<King> air_kings;
    vector<vector<int>> diag1_entries(N);
    vector<vector<int>> diag2_entries(N);
    
    for (const auto& k : kings) {
        if (k.type == 'F') {
            fire_rows[k.r] = true;
        } else if (k.type == 'W') {
            water_mask.set(k.c);
        } else if (k.type == 'E') {
            int sum = k.c + k.r;
            int diff = k.c - k.r;
            
            if (sum >= 0 && sum < N) {
                diag1_mask.set(sum);
            } else if (sum >= N) {
                int r_entry = sum - (N - 1);
                if (r_entry > 0 && r_entry < N) {
                    diag1_entries[r_entry].push_back(N - 1);
                }
            }
            
            if (diff >= 0 && diff < N) {
                diag2_mask.set(diff);
            } else if (diff < 0) {
                int r_entry = -diff;
                if (r_entry > 0 && r_entry < N) {
                    diag2_entries[r_entry].push_back(0);
                }
            }
        } else if (k.type == 'A') {
            air_kings.push_back(k);
        }
    }
    
    long long safe_cells = 0;
    BitSet row_mask(N);
    
    for (int r = 0; r < N; ++r) {
        if (r > 0) {
            diag1_mask.shift_right();
            diag2_mask.shift_left();
            
            if (!diag1_entries[r].empty()) {
                diag1_mask.set(N - 1);
            }
            if (!diag2_entries[r].empty()) {
                diag2_mask.set(0);
            }
        }
        
        if (fire_rows[r]) continue;
        
        row_mask.reset();
        row_mask.bitwise_or(water_mask);
        row_mask.bitwise_or(diag1_mask);
        row_mask.bitwise_or(diag2_mask);
        
        for (const auto& k : air_kings) {
            int dy = abs(r - k.r);
            if (dy <= k.R) {
                int dx = sqrt((long long)k.R * k.R - (long long)dy * dy);
                row_mask.set_range(k.c - dx, k.c + dx);
            }
        }
        
        safe_cells += (N - row_mask.count());
    }
    
    return safe_cells;
}

int main() {
    vector<King> kings;
    kings.push_back({'F', 0, 0, 0});
    kings.push_back({'W', 0, 0, 0});
    kings.push_back({'E', 2, 2, 0});
    kings.push_back({'A', 4, 4, 1});
    
    cout << "Test 1: " << solve_elemental_chess(5, kings) << endl;
    
    return 0;
}
