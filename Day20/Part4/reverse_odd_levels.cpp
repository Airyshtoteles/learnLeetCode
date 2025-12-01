#include <bits/stdc++.h>
using namespace std;

// LC 2415 — Reverse Odd Levels of Binary Tree

struct TreeNode{
    int val; TreeNode* left; TreeNode* right;
    TreeNode(int v=0, TreeNode* l=nullptr, TreeNode* r=nullptr): val(v), left(l), right(r) {}
};

TreeNode* reverseOddLevels(TreeNode* root){
    if (!root) return root;
    queue<TreeNode*> q; q.push(root);
    int level = 0;
    while(!q.empty()){
        int sz = q.size();
        vector<TreeNode*> nodes; nodes.reserve(sz);
        for(int i=0;i<sz;++i){
            TreeNode* node=q.front(); q.pop(); nodes.push_back(node);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        if (level % 2 == 1){
            int i=0, j=(int)nodes.size()-1;
            while(i<j){ swap(nodes[i]->val, nodes[j]->val); ++i; --j; }
        }
        ++level;
    }
    return root;
}

int main(){
    TreeNode* n8=new TreeNode(8); TreeNode* n13=new TreeNode(13);
    TreeNode* n21=new TreeNode(21); TreeNode* n34=new TreeNode(34);
    TreeNode* n3=new TreeNode(3, n8, n13); TreeNode* n5=new TreeNode(5, n21, n34);
    TreeNode* root=new TreeNode(2, n3, n5);
    reverseOddLevels(root);
    cout << root->left->val << " " << root->right->val << "\n"; // 5 3
    return 0;
}
