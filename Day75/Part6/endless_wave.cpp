#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, K;
    long long S;
    if (cin >> n >> K >> S) {
        if (n == 0) {
            cout << "1" << endl;
            return 0;
        }
        vector<long long> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];

        long long active_power = 0;
        bool possible = true;
        
        for (int i = 0; i < n; ++i) {
            active_power += p[i];
            
            // Can defeat K enemies per unit time
            // So we can reduce active_power by K (defeating strongest or any K)
            long long defeated = min((long long)K, active_power);
            active_power -= defeated;
            
            if (active_power > S) {
                possible = false;
                break;
            }
        }

        cout << (possible ? "1" : "0") << endl;
    }
    return 0;
}
