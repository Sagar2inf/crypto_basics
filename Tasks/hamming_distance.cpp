#include<bits/stdc++.h>

using namespace std;


int main(){
    string s1 = "this is a test", s2 = "wokka wokka!!!";
    int h_dist = 0;
    for(int i = 0; i < s1.size(); i++){
        h_dist += (__builtin_popcount(s1[i] ^ s2[i]));
    }
    cout << h_dist << endl;
    return 0;
}