#include<bits/stdc++.h>
#include<fstream>

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
        if(english_freq.find(it) != english_freq.end()){
            scr += english_freq[it];
        }
    }
    return scr;
}

int main(){
	ifstream inFile("4.txt");
	string s;
	string res = "NO Valid Cipher found!";
    double score = 0;
    int x = -1, y = 1;
	if(inFile.is_open()){
		while(getline(inFile, s)){
			int n = s.size();
		    vector<int> chk;
		    for(int i = 1; i < n; i+=2){
		        int x = 0, y = 16, mul = 1; 
		        for(int j = i; j >= i - 1; j--){
		            if(s[j] >= '0' && s[j] <= '9'){
		                x += mul * (s[j] - '0');
		            }else{
		                x += mul * (s[j] - 'a' + 10);
		            }
		            mul *= 16;
		        }
		        chk.push_back(x);
		    }

			for(int i = 0; i < 128; i++){
		        int f = 0;
		        string s = "";
		        for(int j = 0; j < chk.size(); j++){
		            if((i ^ chk[j]) < 128) s += char((i ^ chk[j]));
		            else f = 1;
		        }
		        if(f) continue;
		        if(score < score_of_text(s)){
		            score = score_of_text(s);
		            res = s;
		            x = y;
		        }
		    } 
		    y += 1;
		}
		inFile.close();
	}else{
		cout << "Error while opening the file" << endl;
	}
	cout << x << " " << res << '\n';
	return 0;
}