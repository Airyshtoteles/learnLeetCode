#include <bits/stdc++.h>
using namespace std;

// LC 2296 — Design a Text Editor
// Two stacks: left of cursor, right of cursor

class TextEditor {
    vector<char> left, right; // right.back() is next char to the right
public:
    TextEditor() {}

    void addText(string text){
        for(char c: text) left.push_back(c);
    }

    int deleteText(int k){
        int cnt = 0;
        while(!left.empty() && k>0){ left.pop_back(); --k; ++cnt; }
        return cnt;
    }

    string last10(){
        int L = (int)left.size();
        int start = max(0, L-10);
        string out; out.reserve(min(10, L));
        for(int i=start;i<L;++i) out.push_back(left[i]);
        return out;
    }

    string cursorLeft(int k){
        while(k>0 && !left.empty()){
            right.push_back(left.back()); left.pop_back(); --k;
        }
        return last10();
    }

    string cursorRight(int k){
        while(k>0 && !right.empty()){
            left.push_back(right.back()); right.pop_back(); --k;
        }
        return last10();
    }
};

int main(){
    TextEditor ed;
    ed.addText("leetcode");
    cout << ed.deleteText(4) << "\n"; // 4
    ed.addText("practice");
    cout << ed.cursorRight(3) << "\n"; // etpractice
    cout << ed.cursorLeft(8) << "\n";  // leet
    cout << ed.deleteText(10) << "\n"; // 4
    return 0;
}
