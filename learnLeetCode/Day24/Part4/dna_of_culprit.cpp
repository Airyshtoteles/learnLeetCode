#include <bits/stdc++.h>
using namespace std;

// DNA of the Culprit: minimal Hamming distance within threshold k; return index or -1.

int dna_match_index(const string& dna_scene, const vector<string>& candidates, int k){
    int best=-1, bestdiff=INT_MAX; int m=dna_scene.size();
    for(int i=0;i<(int)candidates.size();++i){
        const string &c = candidates[i]; if((int)c.size()!=m) continue;
        int diff=0; for(int j=0;j<m;++j) if(dna_scene[j]!=c[j]) ++diff;
        if(diff<=k && diff<bestdiff){ bestdiff=diff; best=i; }
    }
    return best;
}

int main(){
    string dna_scene="ATGCC"; vector<string> candidates={"ATGCA","ATACC","TTGCC"};
    cout << dna_match_index(dna_scene, candidates, 1) << "\n"; // 0
    return 0;
}
