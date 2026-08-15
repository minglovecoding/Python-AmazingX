#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int>arr={1,2,3,1,2,3,4,5,3};
    map<int,int>cnt;
    for(int num:arr) cnt[num]++;
    for(auto &pair:cnt){
        cout << pair.first << ": " << pair.second << endl;
    }
}