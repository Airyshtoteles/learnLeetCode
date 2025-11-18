#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, int> cnt;
        cnt[0] = 1;
        return dfs(root, 0, targetSum, cnt);
    }
private:
    int dfs(TreeNode* node, long long cur, int target, unordered_map<long long,int>& cnt) {
        if (!node) return 0;
        cur += node->val;
        int res = 0;
        auto it = cnt.find(cur - target);
        if (it != cnt.end()) res += it->second;
        cnt[cur]++;
        res += dfs(node->left, cur, target, cnt);
        res += dfs(node->right, cur, target, cnt);
        if (--cnt[cur] == 0) cnt.erase(cur);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Build: [10,5,-3,3,2,null,11,3,-2,null,1], target=8 => 3
    TreeNode* root = new TreeNode(10,
        new TreeNode(5,
            new TreeNode(3, new TreeNode(3), new TreeNode(-2)),
            new TreeNode(2, nullptr, new TreeNode(1))
        ),
        new TreeNode(-3, nullptr, new TreeNode(11))
    );

    Solution sol;
    cout << sol.pathSum(root, 8) << "\n"; // 3
    return 0;
}
