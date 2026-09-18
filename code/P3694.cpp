#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int Nmax=1e5+5;
const int Mmax=20;
int Q[Nmax];
int pre[21][Nmax];
int band[Mmax+1];
int dp[1<<Mmax]; //dp[mask]
int len[1<<Mmax];  //length[mask]
int main(){
    int n,m;
    cin>>n>>m;
    memset(pre,0,sizeof(pre));
    memset(dp,0x3f,sizeof(dp));// 4. 初始化 dp[0] = 0，其余为 INF
    // 1. 输入并统计每支乐队i的人数 band[i]
    for(int i=1;i<=n;i++){
        cin>>Q[i];
        pre[Q[i]][i]=1; 
        band[Q[i]]++;
    }
    // 2. 建立前缀和 prefix[i][j]
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            pre[i][j]+=pre[i][j-1];
        }
    }
    // 3. 计算每个 mask 已经安排的总人数 length[mask]
    dp[0]=0;
    for(int mask=0;mask<(1<<m);mask++){
        len[mask]=0;
        for(int i=1;i<=m;i++){//选band
            if(mask&(1<<(i-1))){
                len[mask]+=band[i];
            }
        }
    }
    //state convert
    // 5. 枚举 mask 和尚未安排的乐队 j
    for(int mask=0;mask<(1<<m);mask++){
        if(dp[mask]==INF) continue;
        for(int i=1;i<=m;i++){
            if(mask&(1<<(i-1))) continue;
            // 6. 计算乐队 j 对应的目标区间 [left, right]
            //[left,right]为band i在的地方
            //计算left到right有几个band i:correct=pre[i][right]-pre[i][left-1]
            int left=len[mask]+1;
            int right=len[mask]+band[i];
            int correct=pre[i][right]-pre[i][left-1];// 7. 用前缀和计算 correct，完成转移
            int move=band[i]-correct;
            int newMask=mask|(1<<(i-1));
            dp[newMask]=min(dp[newMask],dp[mask]+move);
        }
    }
    cout<<dp[(1<<m)-1]<<'\n';// 8. 输出 dp[(1 << M) - 1]
    return 0;
}
