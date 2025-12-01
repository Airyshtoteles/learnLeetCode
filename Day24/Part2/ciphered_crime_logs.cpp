#include <bits/stdc++.h>
using namespace std;

// Ciphered Crime Logs: ASCII XOR decode then longest palindromic substring via expand-around-center.

string xor_decode(const string& s, int k){
    string t; t.reserve(s.size());
    for(char c: s) t.push_back(char((unsigned char)c ^ (unsigned char)k));
    return t;
}

string longest_palindrome(const string& s){
    int n = (int)s.size(); if(n==0) return string();
    int best=1, start=0;
    auto expand = [&](int l, int r){
        while(l>=0 && r<n && s[l]==s[r]){ --l; ++r; }
        int len = r-(l+1);
        if(len > best){ best=len; start=l+1; }
    };
    for(int i=0;i<n;++i){ expand(i,i); expand(i,i+1); }
    return s.substr(start, best);
}

string ciphered_crime_logs(const string& s, int k){
    string dec = xor_decode(s,k);
    return longest_palindrome(dec);
}

int main(){
    cout << ciphered_crime_logs("jyfwf", 7) << "\n";
    return 0;
}
