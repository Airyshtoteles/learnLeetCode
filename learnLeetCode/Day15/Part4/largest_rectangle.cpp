#include <bits/stdc++.h>
using namespace std;

// LeetCode 84 — Largest Rectangle in Histogram

int largestRectangleArea(vector<int>& heights){
    vector<int> h = heights; h.push_back(0);
    vector<int> st; long long ans=0;
    for (int i=0;i<(int)h.size();++i){
        while (!st.empty() && h[st.back()] > h[i]){
            int idx = st.back(); st.pop_back();
            int L = st.empty() ? -1 : st.back();
            long long width = i - L - 1;
            ans = max(ans, 1LL*h[idx]*width);
        }
        st.push_back(i);
    }
    return (int)ans;
}

int main(){
    vector<int> a = {2,1,5,6,2,3};
    cout << largestRectangleArea(a) << "\n"; // 10
    return 0;
}
