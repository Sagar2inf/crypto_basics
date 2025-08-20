#include<bits/stdc++.h>
#include "randreq.h"
#include "ecb_enc_dec.h"

using namespace std;

typedef unsigned char uchar;

vector<uchar> process_plaintext(string& s){
    vector<uchar> pre_pad = rand_pre_pad(); 
    vector<uchar> res(pre_pad.begin(), pre_pad.end());
    for(auto & it: s){
        uchar c = static_cast<uchar>(it);
        res.push_back(c);
    }
    vector<uchar> post_pad = rand_post_pad();
    for(auto & it: post_pad){
        res.push_back(it);
    }
    res = pad_text(res);
    return res;
}
vector<uchar> random_key(){
    return rand_key();
}
vector<uchar> random_IV(){
    return rand_IV(16);
}

vector<uchar> enc(string s){
    vector<uchar> plain_text = process_plaintext(s);
    vector<uchar> key = random_key();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 2);
    int mode = dist(gen);
    // mode = 1;
    vector<uchar> encrypted_text;
    vector<uchar> IV = random_IV();
    for(int i = 0; i < plain_text.size(); i+=16){
        vector<uchar> block(plain_text.begin() + i, plain_text.begin() + min(i + 16, (int)plain_text.size()));
        if(block.size() < 16){
            cout << "Invalid padding" << endl; exit(1);
        }
        vector<uchar> enc_block = aes_enc(block, IV, key, mode);
        encrypted_text.insert(encrypted_text.end(), enc_block.begin(), enc_block.end());
    }
    cout << (mode == 1?"It is ECB": "It is CBC") << endl;
    return encrypted_text;
}





