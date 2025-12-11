#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

bool canComplete(int k, vector<int>& tasks, vector<int>& workers, int pills, int strength) {
    if (k == 0) return true;
    multiset<int> w_set;
    // Take k strongest workers
    for(int i = workers.size() - k; i < workers.size(); ++i) {
        w_set.insert(workers[i]);
    }
    
    // Try to complete k smallest tasks, starting from the largest of them
    for(int i = k - 1; i >= 0; --i) {
        int task = tasks[i];
        
        // Try to use strongest worker without pill
        if (!w_set.empty() && *w_set.rbegin() >= task) {
            w_set.erase(prev(w_set.end()));
        } else if (pills > 0) {
            // Try to use weakest worker with pill
            auto it = w_set.lower_bound(task - strength);
            if (it != w_set.end()) {
                w_set.erase(it);
                pills--;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    int n_tasks, n_workers, pills, strength;
    if (!(cin >> n_tasks)) return 0;
    vector<int> tasks(n_tasks);
    for(int i=0; i<n_tasks; ++i) cin >> tasks[i];
    
    cin >> n_workers;
    vector<int> workers(n_workers);
    for(int i=0; i<n_workers; ++i) cin >> workers[i];
    
    cin >> pills >> strength;
    
    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());
    
    int low = 0, high = min((int)tasks.size(), (int)workers.size());
    int ans = 0;
    
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if (canComplete(mid, tasks, workers, pills, strength)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
