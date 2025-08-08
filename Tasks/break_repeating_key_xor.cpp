#include<bits/stdc++.h>
#include "cppcodec_1\base64_rfc4648.hpp"

using namespace std;
using base64 = cppcodec::base64_rfc4648;

unordered_map<char, double> english_freq = {
    {'a', 0.0651738}, {'b', 0.0124248}, {'c', 0.0217339},
    {'d', 0.0349835}, {'e', 0.1041442}, {'f', 0.0197881},
    {'g', 0.0158610}, {'h', 0.0492888}, {'i', 0.0558094},
    {'j', 0.0009033}, {'k', 0.0050529}, {'l', 0.0331490},
    {'m', 0.0202124}, {'n', 0.0564513}, {'o', 0.0596302},
    {'p', 0.0137645}, {'q', 0.0008606}, {'r', 0.0497563},
    {'s', 0.0515760}, {'t', 0.0729357}, {'u', 0.0225134},
    {'v', 0.0082903}, {'w', 0.0171272}, {'x', 0.0013692},
    {'y', 0.0145984}, {'z', 0.0007836}, {' ', 0.1918182}
};

double score_of_text(string s){
    double scr = 0;
    for(auto & it: s){
        char c = it;
        if(c >= 'A' && c <= 'Z'){
            c += 32;
        }
        if(english_freq.find(c) != english_freq.end()){
            scr += english_freq[c];
        }
    }
    return scr;
}

int main(){
    ifstream text("6.txt");
    string line;
    string base64_test = "";
    while(getline(text, line)){
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        base64_test += line;
    }
    vector<uint8_t> decoded_bytes = base64::decode(base64_test);
    string test(decoded_bytes.begin(), decoded_bytes.end());
    cout << "Total characters: " << test.size()<< endl;
    double keysize = 0.0, score = 100.0;
    for(int size = 2; size <= 40; size++){
        double h_dist = 0.0, cnt = 0.0;
        for(int i = 0; i < test.size() - size - 50; i+= size){
            string s1 = test.substr(i, size);
            string s2 = test.substr(i + size, size);
            for(int j = 0; j < size; j++){
                h_dist += (__builtin_popcount(s1[j] ^ s2[j]));
            }
            cnt += 1.0; 
        }
        h_dist /= cnt;
        h_dist /= size;
        if(h_dist < score){
            score = h_dist;
            keysize = size;
        }
    }
    cout << "Length of the Key: " << keysize << endl; 
    vector<string> texts(keysize);
    for(int i = 0; i < test.size(); i+= keysize){
        for(int j = i; j < i + keysize && j < test.size(); j++){
            texts[j % int(keysize)] += (char)test[j];
        }
    }
    string final_key = "";
    for(int i = 0; i < keysize; i++){
        string s = texts[i];
        double max_score = 0;
        char key = 0;
        for(int j = 0; j < 128; j++){
            string decrypted = "";
            for(char c : s){
                decrypted += (char)(c ^ j);
            }
            double current_score = score_of_text(decrypted);
            if(current_score > max_score){
                max_score = current_score;
                key = j;
            }
        }
        final_key += key;
    }
    cout << "The Key is: " << final_key << endl;
    int j = 0;
    for(char c: test){
        cout << char(c ^ final_key[j % final_key.size()]);
        j += 1;
    }
}