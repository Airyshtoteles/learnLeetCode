#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    int N;
    long long W;
    if (!(cin >> N >> W)) return 0;

    vector<long long> A(N), B(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];

    vector<long long> max_weights(N);
    for (int i = 0; i < N; ++i) {
        max_weights[i] = max(A[i], B[i]);
    }

    sort(max_weights.begin(), max_weights.end());

    int count = 0;
    long long current_weight = 0;
    for (int i = 0; i < N; ++i) {
        if (current_weight + max_weights[i] <= W) {
            current_weight += max_weights[i];
            count++;
        } else {
            break;
        }
    }

    cout << count << endl;

    return 0;
}
