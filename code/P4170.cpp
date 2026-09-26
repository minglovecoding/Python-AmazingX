//区间DP
//相同色的可以合并
//默认dp[l][r]=dp[l+1][r]+1
//遍历k，如果s[l]等于s[k],result=dp[l+1][k-1]+dp[k][r]，如果k=l+1，同色的跳过。
//输出dp[0][n-1]
#include <bits/stdc++.h>
using namespace std;
const int Nmax = 55;
int dp[Nmax][Nmax];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = s.size();
    // initialize
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    // Interval DP
    for(int len=2;len<=n;len++){
        for(int l=0;l+len-1<n;l++){
            int r=l+len-1;
            //case 1:
            dp[l][r]=1+dp[l+1][r];
            for(int k=l+1;k<=r;k++){
                if(s[l]==s[k]){
                    if(k==l+1){
                        dp[l][r]=min(dp[l][r],dp[k][r]);
                    }else{
                        dp[l][r]=min(dp[l][r],dp[l+1][k-1]+dp[k][r]);
                    }
                }
            }            
        }
    }
    cout << dp[0][n - 1] << '\n';
    return 0;
}