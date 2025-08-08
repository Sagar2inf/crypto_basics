#include<bits/stdc++.h>

using namespace std;

int char_to_int(char c){
	int x;
	if(c >= '0' && c <= '9'){
		x = (c - '0');
	}else if(c >= 'a' && c <= 'z') {
		x = (c - 'a' + 10);
	}else{
		x = (c - 'A' + 10);
	}	
	return x;
}
string xor_of_hex(string s1, string s2){
	int n = s1.size();
	string res = "";
	for(int i = 0; i < n; i++){
		int z = (char_to_int(s1[i]) ^ char_to_int(s2[i]));
		char c = '0';
		if(z < 10){
			c += z;
		}else{
			c = ('a' + z - 10);
		}
		res += c;
	}
	return res;
}

int main(){
	string s1, s2;
	cout << "Enter the first HEX number" << endl;
	cin >> s1;
	cout << "Enter the Second HEX number" << endl;
	cin >> s2;
	cout << "The Xor of two hex numbers: " << xor_of_hex(s1, s2) << endl;
	return 0;
}