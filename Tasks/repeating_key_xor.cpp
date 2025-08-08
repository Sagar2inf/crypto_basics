#include<bits/stdc++.h>

using namespace std;

string encrypt(string s, int j, string key = "ICE"){
	vector<int> chk;
	string ss = "";
	for(auto & it: s){
		int x = it;
		int y = key[j];
		// chk.push_back((x ^ y));
		int z = (x ^ y) / 16;
		int rem = (x ^ y) % 16;
		j = (j + 1) % 3;
		char c = 'a';
		if(rem > 9){
			c = 'a' + rem - 10;
		}else c = '0' + rem;
		ss += '0' + z;
		ss += c;

	}
	return ss;

}
	
int main(){
	string s;
	s = "Burning 'em, if you ain't quick and nimble\n"
        "I go crazy when I hear a cymbal";	
	int j = 0;
	cout << encrypt(s, j) << endl;
	return 0;
}
