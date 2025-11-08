#include <bits/stdc++.h>
using namespace std;

static const int BITS = 31; // for values up to < 2^31

struct Basis {
    array<int,BITS> b{};
    void insert(int x){
        for(int i=BITS-1;i>=0;--i){
            if(!((x>>i)&1)) continue;
            if(!b[i]){ b[i]=x; return; }
            x ^= b[i];
        }
    }
    void merge(const Basis& other){
        for(int v: other.b) if(v) insert(v);
    }
    int max_xor() const {
        int res=0;
        for(int i=BITS-1;i>=0;--i){
            if(b[i] && (res^b[i])>res) res ^= b[i];
        }
        return res;
    }
};

int k_alternating_max_xor(const vector<int>& nums, int k){
    int n = (int)nums.size();
    vector<Basis> B(n + k + 1); // padding
    for(int i=n-1;i>=0;--i){
        Basis cur = B[i+1]; // skip i
        Basis choose = B[i+k];
        choose.insert(nums[i]);
        cur.merge(choose);
        B[i] = cur;
    }
    return B[0].max_xor();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << k_alternating_max_xor(vector<int>{3,10,5,25,2,8},2) << "\n"; // Expect 26
    return 0;
}
