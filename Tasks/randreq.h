#ifndef randreq
#define randreq
#include<bits/stdc++.h>
#include <random>

using namespace std;
typedef unsigned char uchar;

vector<uchar> rand_key(int len = 16);
vector<uchar> rand_pre_pad();
vector<uchar> rand_post_pad();
vector<uchar> rand_IV(int len = 16);

#endif