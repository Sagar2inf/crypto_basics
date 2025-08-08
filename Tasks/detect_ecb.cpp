#include<bits/stdc++.h>

using namespace std;

int main(){
    ifstream text("8.txt");
    string line;
    map<string, int> blocks;
    vector<map<string, int>> block_counts;
    string ecb;
    while(getline(text, line)){
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        for(size_t i = 0; i < line.size(); i += 32){
            string block = line.substr(i, 32);
            blocks[block]++;
        }
        for(auto & it: blocks){
            if(it.second != 1){
                ecb = line;
            }
        }

        blocks.clear();
    }
    

    return 0;
}