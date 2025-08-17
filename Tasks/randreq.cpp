#include<bits/stdc++.h>
#include <random>

using namespace std;
typedef unsigned char uchar;

int rand_int(int l, int r){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(l, r);
    return dist(gen);
}
vector<uchar> rand_key(int len = 16){
    vector<uchar> key;
    while(len--){
        uchar x = static_cast<uchar>(rand_int(1, 255));
        key.push_back(x);
    }
    return key;
}

vector<uchar> rand_pre_pad(){
    int len = rand_int(5, 10);
    vector<uchar> pre;
    while(len--){
        uchar x = static_cast<uchar>(1, 255);
        pre.push_back(x);
    }
    return pre;
}

vector<uchar> rand_post_pad(){
    int len = rand_int(5, 10);
    vector<uchar> post;
    while(len--){
        uchar x = static_cast<uchar>(rand_int(1, 255));
        post.push_back(x);
    }
    return post;
}

vector<uchar> rand_IV(int len = 16){
    vector<uchar> iv;
    while(len--){
        uchar x = static_cast<uchar>(rand_int(1, 255));
        iv.push_back(x);
    }
    return iv;
}

// int main() {
//     cout << rand_key().size() << endl;
//     cout << rand_pre_pad().size() << endl;
//     cout << rand_post_pad().size() << endl;
//     cout << rand_IV().size() << endl;
// }

