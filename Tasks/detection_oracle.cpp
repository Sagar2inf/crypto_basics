#include<bits/stdc++.h>
#include "process.h"

using namespace std;

int main(){
    string s; //cin >> s;
    // s = "My name is SagarMy name is SagarMy name is SagarMy name is SagarMy name is SagarMy name is SagarMy name is SagarMy name is Sagar";
    s = "aaaaaaaaaaaaaaab";
    vector<uchar> encrypted_text = enc(s); // uchar -> unsigned char
    for(auto & it: encrypted_text){
        cout << hex << int(it);
    }
    cout << endl;
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