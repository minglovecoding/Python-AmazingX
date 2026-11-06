#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--){
        int N,K;
        cin>>N>>K;
        vector<vector<int>>dp(N+1,vector<int>(N+1,1));
        vector<int>sequence(N+1);
        for(int i=1;i<=N;i++){
            cin>>sequence[i];
        }
        // REP可以无限，1≤K≤3，每个正整数都不超过 K
        for(int len=2;len<=N;len++){
            for(int left=1;left+len-1<=N;left++){
                int right=left+len-1;
                dp[left][right]=right-left+1;
                //1.拆分区间
                for(int k=left;k<right;k++){
                    int step=dp[left][k]+dp[k+1][right];
                    dp[left][right]=min(dp[left][right],step);
                }
                //2.REP重复
                for(int p=1;p<len;p++){
                    if(len%p!=0) continue;
                    //用lcp优化时：lcp[left][left+p] >= len-p
                    if(equal(sequence.begin()+left,sequence.begin()+right-p+1,sequence.begin()+left+p)){
                            dp[left][right]=min(dp[left][right],dp[left][left+p-1]);
                    }
                }
            }
        }
        cout<<(dp[1][N]<=K?"YES":"NO")<<"\n";
    }
    return 0;
}
/* 可以用LCP最长公共前缀优化，lcp[i][j]=从位置i和j开始，连续相同的元素。
vector<vector<int>> lcp(N+2, vector<int>(N+2, 0));
for (int i = N; i >= 1; i--) {
    for (int j = N; j >= 1; j--) {
        if (sequence[i] == sequence[j]) {
            lcp[i][j] = lcp[i+1][j+1] + 1;
        }
    }
}
*/