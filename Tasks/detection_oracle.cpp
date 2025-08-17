#include<bits/stdc++.h>
#include "process.h"

using namespace std;

int main(){
    string s; cin >> s;
    vector<uchar> encrypted_text = enc(s); // uchar -> unsigned char
    map<vector<uchar>, int> blocks;
    for(int i = 0; i < encrypted_text.size(); i += 16){
        vector<uchar> block(encrypted_text.begin() + i, encrypted_text.begin() + min(i + 16, (int)encrypted_text.size()));
        blocks[block]++;
    }
    bool f = 0;
    for(auto & it: blocks){
        if(it.second != 1){
            f = 1; break;
        }
    }
    if(f){
        cout << "ECB detected" << endl;
    }else{
        cout << "CBC detected" << endl;
    }
    return 0;
}