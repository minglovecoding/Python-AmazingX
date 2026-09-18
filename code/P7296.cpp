//记录所有出现的字母，个数K一定小于或等于20
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int Kmax=20;
int cnt[Kmax][Kmax];  //记录Nhoj听到字符里相邻字符出现的链接次数
vector<int>id(26,-1); //记录出现字符的id
int addCost[Kmax][1<<Kmax];
int dp[1<<Kmax];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin>>s;
    //c -> index
    int K=0;
    for(auto c:s){
        int index=c-'a';
        if(id[index]==-1){
            id[index]=K++;
        }
    }
    //统计cnt[i][j] 
    for(int i=0;i<s.size()-1;i++){
        int a=id[s[i]-'a'];
        int b=id[s[i+1]-'a'];
        cnt[a][b]++;
    }
    int totalState=1<<K;  //K个字符的排列状态
    memset(addCost,0,sizeof(addCost));
    //计算j放在mask后的新代价
    for(int j=0;j<K;j++){
        for(int mask=1;mask<totalState;mask++){
            //找到mask最低的位1
            int lowBit=__builtin_ctz(mask);
            //找到去除这个位的mask
            int previousMask=mask^(1<<lowBit);
            addCost[j][mask]=addCost[j][previousMask]+cnt[j][lowBit];
        }
    }
    memset(dp,0x3f,sizeof(dp));
    dp[0]=0;
    for(int mask=0;mask<totalState;mask++){
        for(int j=0;j<K;j++){
            if(mask&(1<<j)) continue;
            int newMask=mask|(1<<j);
            dp[newMask]=min(dp[newMask],dp[mask]+addCost[j][mask]);
        }
    }
    //+第一遍
    int res=1+dp[totalState-1];
    //相同字符
    for(int i=0;i<K;i++){
        res+=cnt[i][i];
    }
    cout<<res<<'\n';
    return 0;
}