#include <bits/stdc++.h>
using namespace std;

// LC 2390 — Maximum Number of Robots Within Budget

int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget){
    int n = chargeTimes.size();
    deque<int> dq;
    int left = 0;
    long long totalRun = 0;
    int best = 0;
    for (int right = 0; right < n; ++right){
        totalRun += runningCosts[right];
        while(!dq.empty() && chargeTimes[dq.back()] <= chargeTimes[right]) dq.pop_back();
        dq.push_back(right);
        while(left <= right && (long long)chargeTimes[dq.front()] + (right - left + 1) * totalRun > budget){
            if (!dq.empty() && dq.front() == left) dq.pop_front();
            totalRun -= runningCosts[left];
            ++left;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

int main(){
    vector<int> c = {3,6,1,3,4};
    vector<int> r = {2,1,3,4,5};
    cout << maximumRobots(c, r, 25) << "\n"; // 3
    return 0;
}
