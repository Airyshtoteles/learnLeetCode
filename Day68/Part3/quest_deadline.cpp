#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Quest {
    int reward;
    int deadline;
};

bool compareQuests(const Quest& a, const Quest& b) {
    return a.deadline < b.deadline;
}

int main() {
    int n;
    if (cin >> n) {
        vector<Quest> quests(n);
        for (int i = 0; i < n; ++i) {
            cin >> quests[i].reward >> quests[i].deadline;
        }

        sort(quests.begin(), quests.end(), compareQuests);

        priority_queue<int, vector<int>, greater<int>> pq;
        long long total_reward = 0;

        for (const auto& q : quests) {
            pq.push(q.reward);
            total_reward += q.reward;

            if (pq.size() > q.deadline) {
                int min_reward = pq.top();
                pq.pop();
                total_reward -= min_reward;
            }
        }

        cout << total_reward << endl;
    }
    return 0;
}
