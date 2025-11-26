#include <iostream>
#include <vector>

using namespace std;

struct Machine {
    long long craft;
    long long cd;
    long long value;
};

long long solveArcaneForge(long long t, const vector<Machine>& machines) {
    long long total_value = 0;

    for (const auto& m : machines) {
        long long cycle_time = m.craft + m.cd;
        long long count = t / cycle_time;
        long long rem = t % cycle_time;

        if (rem >= m.craft) {
            count++;
        }

        total_value += count * m.value;
    }

    return total_value;
}

int main() {
    long long T = 10;
    vector<Machine> Machines = {
        {2, 1, 5},
        {5, 2, 20}
    };

    long long result = solveArcaneForge(T, Machines);
    cout << "Maximum Value: " << result << endl;

    return 0;
}
