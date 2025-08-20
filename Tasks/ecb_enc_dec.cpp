#include<bits/stdc++.h>
#include "cppcodec_1/cppcodec/base64_default_rfc4648.hpp"

using namespace std;

typedef vector<uint8_t> byte_vec;
typedef unsigned char uchar;
using base64 = cppcodec::base64_rfc4648;

vector<uchar> inv_S_BOX;
vector<uchar> S_BOX = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
    0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
    0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
    0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
    0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
    0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
    0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
    0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
    0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
    0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
    0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

void generate_inv_S_BOX(){
    inv_S_BOX.assign(256, 0);
    for(int i = 0; i < S_BOX.size(); i++){
        inv_S_BOX[S_BOX[i]] = i;
    }
}

void shift(vector<uchar> & s, int round){
    while(round--){
        uchar c = s[0];
        s.erase(s.begin(), s.begin() + 1);
        s.push_back(c);
    }
}

vector<uchar> g_fn(vector<uchar> s, int round){
    // rotate left by one position
    uchar c = s[0];
    s.erase(s.begin());
    s.push_back(c);

    // substitute using S_BOX
    vector<uchar> ss;
    for(auto & it: s){
        uchar val = it;
        val = S_BOX[val]; 
        ss.push_back(val);
    }

    // Rcon
    uchar rcon;
    if(round == 9){
        rcon = 0x1B;
    } else if(round == 10){
        rcon = 0x36;
    } else {
        rcon = 1 << (round - 1);
    }
    ss[0] = ((uchar)ss[0] ^ rcon);
    return ss;
}

vector<vector<uchar>> generate_round_key(vector<uchar> key){
    vector<vector<uchar>> keys;
    keys.push_back(key);
    for(int i = 1; i <= 10; i++){
        vector<uchar> s;
        vector<uchar> last_key;
        for(int j = 12; j < 16; j++){
            last_key.push_back(keys[i - 1][j]);
        }
        last_key = g_fn(last_key, i);
        for(int j = 0; j < 16; j++){
            if(j < 4){
                s.push_back((keys[i - 1][j] ^ last_key[j]));
            }else{
                s.push_back((keys[i - 1][j] ^ s[j - 4]));
            }
        }
        keys.push_back(s);
    }  
    
    return keys;
}


uchar gf_mul(uchar a, uchar b) {
    uchar result = 0;
    while (b) {
        if (b & 1)
            result ^= a;             
        bool high_bit = a & 0x80;   
        a <<= 1;                    
        if (high_bit)
            a ^= 0x1B;               
        b >>= 1;                    
    }
    return result;
}

vector<uchar> subbytes(vector<uchar> s, bool inv = false){
    vector<uchar> res;
    generate_inv_S_BOX();
    for(auto & it: s){
        uchar val = it;
        if(inv){
            val = inv_S_BOX[val];
        } else {
            val = S_BOX[val];
        }
        res.push_back(val);
    }
    return res;
}

vector<uchar> shift_rows(vector<uchar> s, bool inv = false){
    for(int i = 0; i < 4; i++){
        vector<uchar> temp;
        for(int j = 0; j < 4; j++){
            temp.push_back(s[4 * j + i]);
        }
        if(inv){
            shift(temp, 4 - i);
        } else {
            shift(temp, i);
        }
        for(int j = 0; j < 4; j++){
            s[4 * j + i] = temp[j];
        }
    }
    return s;
}

vector<uchar> mix_columns(vector<uchar> state, bool inv = false){
    auto mix_col = [&](vector<uchar> &s){
        vector<uchar> res;
        res.push_back(gf_mul(s[0], 2) ^ gf_mul(s[1], 3) ^ s[2] ^ s[3]);
        res.push_back(s[0] ^ gf_mul(s[1], 2) ^ gf_mul(s[2], 3) ^ s[3]);
        res.push_back(s[0] ^ s[1] ^ gf_mul(s[2], 2) ^ gf_mul(s[3], 3));
        res.push_back(gf_mul(s[0], 3) ^ s[1] ^ s[2] ^ gf_mul(s[3], 2)); 
        return res;
    }; 
    auto invmix_col = [&](vector<uchar> &s){
        vector<uchar> res;
        res.push_back(gf_mul(s[0], 14) ^ gf_mul(s[1], 11) ^ gf_mul(s[2], 13) ^ gf_mul(s[3], 9));
        res.push_back(gf_mul(s[0], 9) ^ gf_mul(s[1], 14) ^ gf_mul(s[2], 11) ^ gf_mul(s[3], 13));
        res.push_back(gf_mul(s[0], 13) ^ gf_mul(s[1], 9) ^ gf_mul(s[2], 14) ^ gf_mul(s[3], 11));
        res.push_back(gf_mul(s[0], 11) ^ gf_mul(s[1], 13) ^ gf_mul(s[2], 9) ^ gf_mul(s[3], 14));
        return res;
    };
    for(int k = 0; k < 4; k++){
        vector<uchar> s;
        for(int j =0; j < 4; j++){
            s.push_back(state[4 * j + k]);
        }
        if(inv){
            s = invmix_col(s);
        } else {
            s = mix_col(s);
        }
        for(int j = 0; j < 4; j++){
            state[4 * j + k] = s[j];
        }
    } 
    return state;
}
vector<uchar> aes_enc(vector<uchar> text, vector<uchar> pre_cf, vector<uchar> key, int mode){
    // generate round keys for all rounds
    vector<vector<uchar>> round_keys = generate_round_key(key);
    
    // step 0
    // add IV
    if(mode == 1) pre_cf = vector<uchar>(16, '\0'); // for ECB mode
    
    vector<uchar> state;
    for(int i = 0; i < 16; i++){
        state.push_back((text[i] ^ pre_cf[i]));
    }

    // add roundkey
    for(int i = 0; i < 16; i++){
        state[i] = (state[i] ^ round_keys[0][i]);
    }

    // STEP 1 - 10 
    for(int i = 1; i <= 10; i++){
        // subbytes
        state = subbytes(state);

        // shiftrows
        state = shift_rows(state); 

        // Mixcolumns
        if(i < 10){
            state = mix_columns(state);
        }

        // add roundkey
        for(int k = 0; k < 16; k++){
            state[k] = (state[k] ^ round_keys[i][k]);
        }
    }
    return state;
}

vector<uchar> aes_dec(vector<uchar> text, vector<uchar> pre_cf, vector<uchar> key, int mode){
    vector<vector<uchar>> round_keys = generate_round_key(key);
    generate_inv_S_BOX();
    // 10th step
    // add roundkey
    for(int k = 0; k < 16; k++){
        text[k] = (text[k] ^ round_keys[10][k]);
    }
    // 9 - 1 steps
    for(int i = 9; i >= 0; i--){
        // invshiftrows
        text = shift_rows(text, true);

        // invSubbytes
        text = subbytes(text, true);

        // add roundkey
        for(int k = 0; k < 16; k++){
            text[k] = (text[k] ^ round_keys[i][k]);
        }

        // invMixColumns
        if(i > 0){
            text = mix_columns(text, true); 
        }
    }

    // inv add IV
    if(mode == 1) pre_cf = vector<uchar>(16, '\0'); // for ECB mode;

    for(int i = 0; i < 16; i++){
        text[i] = (text[i] ^ pre_cf[i]);
    }
    return text;
}

vector<uchar> pad_text(vector<uchar> s, int block_size = 16){
    int pad_size = block_size - (s.size() % block_size);
    for(int i = 0; i < pad_size; i++){
        s.push_back((pad_size)); 
    }
    return s;
}

vector<uchar> unpad_text(vector<uchar> s, int block_size = 16) {
    if (s.empty()) {
        cout << "Bad padding: empty input" << endl;
        return {};
    }

    int pad_size = (int)s.back();

    if (pad_size <= 0 || pad_size > block_size || (int)s.size() < pad_size) {
        cout << "Bad padding: invalid pad size" << endl;
        return {};
    }

    for (int i = s.size() - pad_size; i < s.size(); ++i) {
        if (s[i] != pad_size) {
            cout << "Bad padding: mismatched values" << endl;
            return {};
        }
    }

    s.resize(s.size() - pad_size);
    return s;
}
int test(int x, int y){
    return x * y;
}

// int main(){
//     string key = "YELLOW SUBMARINE";
//     vector<uchar> key_vec(key.begin(), key.end());
//     for(auto & it: key_vec){
//         cout << it << " ";
//     } 
//     cout << endl;
//     ifstream text("10.txt", ios::binary);
//     vector<uchar> cipher((istreambuf_iterator<char>(text)), istreambuf_iterator<char>());
//     vector<uchar> chk;
//     for(auto & it: cipher){
//         if(it == '\n') continue;
//         chk.push_back(it);
//     }
    
//     chk = base64::decode(chk);
//     cipher = chk;
//     vector<uchar> dec;
//     vector<uchar> IV(16, '\0');
//     chk.clear();
//     for(int i = 0; i < 16; i++){
//         chk.push_back(cipher[i]);
//     }
//     dec = aes_dec(chk, IV, key_vec, 2);
//     for(auto & it: dec){
//         cout << it << " ";
//     }
//     cout << endl;

//     return 0;
// }