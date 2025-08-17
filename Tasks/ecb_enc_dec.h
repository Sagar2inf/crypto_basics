#ifndef ecb_enc_dec
#define ecb_enc_dec
#include<bits/stdc++.h>
using namespace std;

typedef vector<uint8_t> byte_vec;
typedef unsigned char uchar;

vector<uchar> aes_enc(vector<uchar> text, vector<uchar> pre_cf, vector<uchar> key, int mode);
vector<uchar> aes_dec(vector<uchar> text, vector<uchar> pre_cf, vector<uchar> key, int mode);
vector<uchar> pad_text(vector<uchar> s, int block_size = 16);
vector<uchar> unpad_text(vector<uchar> s, int block_size = 16);
int test(int x, int y);
#endif