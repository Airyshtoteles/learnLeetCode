#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int N;
    if (!(cin >> N)) return 0;

    set<int> times;
    for (int i = 0; i < N; ++i) {
        int t, l;
        cin >> t >> l;
        times.insert(t);
    }

    // Since we can always make 1 input (hitting 1 or 2 notes) at any time step where notes exist,
    // and skipping notes is allowed, the max combo (inputs) is simply the number of unique time steps.
    cout << times.size() << endl;

    return 0;
}
