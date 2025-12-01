#include <bits/stdc++.h>
using namespace std;

// LC 4 — Median of Two Sorted Arrays
// Binary search partition on smaller array

double findMedianSortedArrays(vector<int>& A, vector<int>& B){
    if (A.size() > B.size()) return findMedianSortedArrays(B, A);
    int m = (int)A.size(), n = (int)B.size();
    int total = m + n;
    int half = total / 2;
    int lo = 0, hi = m;
    while(true){
        int i = (lo + hi) / 2;
        int j = half - i;
        int Aleft = (i > 0 ? A[i-1] : INT_MIN);
        int Aright = (i < m ? A[i] : INT_MAX);
        int Bleft = (j > 0 ? B[j-1] : INT_MIN);
        int Bright = (j < n ? B[j] : INT_MAX);
        if (Aleft <= Bright && Bleft <= Aright){
            if (total % 2) return min(Aright, Bright);
            return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0;
        } else if (Aleft > Bright){
            hi = i - 1;
        } else {
            lo = i + 1;
        }
    }
}

int main(){
    vector<int> a = {1,3}, b = {2};
    cout << fixed << setprecision(1) << findMedianSortedArrays(a,b) << "\n"; // 2.0
    return 0;
}
