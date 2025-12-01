#include <bits/stdc++.h>
using namespace std;

// LC 23 — Merge k Sorted Lists (min-heap)

struct ListNode{
    int val; ListNode* next;
    ListNode(int v=0, ListNode* n=nullptr): val(v), next(n) {}
};

struct Cmp{
    bool operator()(ListNode* a, ListNode* b) const{
        return a->val > b->val; // min-heap
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists){
    priority_queue<ListNode*, vector<ListNode*>, Cmp> pq;
    for (auto node: lists) if (node) pq.push(node);
    ListNode dummy(0); ListNode* cur = &dummy;
    while(!pq.empty()){
        ListNode* node = pq.top(); pq.pop();
        cur->next = node; cur = cur->next;
        if (node->next) pq.push(node->next);
    }
    return dummy.next;
}

// helpers for local test
ListNode* build(const vector<int>& a){
    ListNode* head = new ListNode(0); ListNode* cur=head;
    for(int v: a){ cur->next = new ListNode(v); cur=cur->next; }
    ListNode* res=head->next; delete head; return res;
}

int main(){
    vector<ListNode*> lists = { build({1,4,5}), build({1,3,4}), build({2,6}) };
    ListNode* ans = mergeKLists(lists);
    vector<int> out; while(ans){ out.push_back(ans->val); ans=ans->next; }
    for(size_t i=0;i<out.size();++i){ if(i) cout<<","; cout<<out[i]; }
    cout<<"\n"; // 1,1,2,3,4,4,5,6
    return 0;
}
