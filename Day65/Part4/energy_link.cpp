#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int N;
    long long K;
    if (cin >> N >> K) {
        map<long long, int> counts;
        for (int i = 0; i < N; ++i) {
            long long v;
            cin >> v;
            counts[v]++;
        }

        long long total_pairs = 0;

        if (K == 0) {
            for (auto const& [val, count] : counts) {
                total_pairs += count / 2;
            }
        } else {
            for (auto it = counts.begin(); it != counts.end(); ++it) {
                long long val = it->first;
                int count = it->second;

                if (count > 0) {
                    if (counts.count(val + K)) {
                        int next_count = counts[val + K];
                        int pairs = min(count, next_count);
                        total_pairs += pairs;
                        counts[val + K] -= pairs;
                    }
                }
            }
        }

        cout << total_pairs << endl;
    }
    return 0;
}
