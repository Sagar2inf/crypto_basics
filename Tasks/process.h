#ifndef process
#define process
#include<bits/stdc++.h>

using namespace std;
typedef unsigned char uchar;

vector<uchar> process_plaintext(string s);
vector<uchar> random_key();
vector<uchar> random_IV();
vector<uchar> enc(string s);


#endif