#include<bits/stdc++.h>

using namespace std;

string hex_to_raw_byte(string inp){
    string s = "";
    if(inp.size() % 2) s += '0';
    s += inp;
    string res = "";
    for(int i = 1; i < s.size(); i+= 2){
        int x = 0, y = 16, mul = 1;
        for(int j = i; j >= i - 1; j--){
            if(s[j] <= '9' && s[j] >= '0'){
                x += mul * (s[j] - '0');
            }else if(s[j] >= 'A' && s[j] <= 'Z'){
                x += mul * (10 + s[j] - 'A');
            }else{
                x += mul * (10 + s[j] - 'a');
            }
            mul *= y;
        }
        res += char(x);
    }
    return res;
}
string raw_byte_to_base64(string inp){
    string s = "";
    for(int i = 0; i < inp.size(); i++){
        int x = inp[i];
        string tmp = "";
        while(x){
            if(x % 2) tmp += '1';
            else tmp += '0';
            x /= 2;
        }
        while(tmp.size() % 8){
            tmp += '0';
        }
        reverse(tmp.begin(), tmp.end());
        s += tmp;
    }
    while(s.size() % 6){
        s += '0';
    }
    string res = "";
    for(int i = 5; i < s.size(); i+=6){
        int x = 0, y = 2, mul = 1;
        for(int j = i; j >= i - 5; j--){
            x += mul * (s[j] - '0');
            mul *= y;
        }
        if(x >= 0 && x <= 25){
            res += ('A' + x);
        }else if(x > 25 && x <= 51){
            res += ('a' + x - 26);
        }else if(x > 51 && x <= 61){
            res += ('0' + x - 52);
        }else if(x == 62) res += '+';
        else res += '/';
    }
    int x = (4 - (res.size() % 4)) % 4;
    while(x--){
        res += '=';
    }
    return res;
}

int main(){
	cout << "The Hex string" << endl;
	string s; cin >> s;
	cout << "Raw byte string: " << endl << hex_to_raw_byte(s) << endl;
	cout << "Base64 string: " << endl << raw_byte_to_base64(hex_to_raw_byte(s)) << endl;
	return 0;
}