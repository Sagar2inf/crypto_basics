#include<bits/stdc++.h>
#include "cppcodec_1/base64_rfc4648.hpp"
#include<sstream>
#include<iomanip>

using namespace std;

using base64 = cppcodec::base64_rfc4648;

int main(){
    string s = "YELLOW SUBMARINE"; //cin >> s;
    int block_size = 20; // cin >> block_size;
    int pad_len = block_size - (s.size() % block_size);
    stringstream ss;
    ss << "0x0" << hex << pad_len;
    cout << ss.str() << endl;
    return 0;
}