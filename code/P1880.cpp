#include<bits/stdc++.h>
using namespace std;   
int num[305];  
int dp1[305][305],dp2[305][305];
int pre[305];  
int main()  
{   
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>num[i];
        num[i+n]=num[i];
    }
    for(int i=1;i<=2*n;i++){
        pre[i]=pre[i-1]+num[i];
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=2*n;l++){
            int r=l+len-1;
            dp1[l][r]=1e9;
            dp2[l][r]=0;
            for(int k=l;k<r;k++){
                int cost1=dp1[l][k]+dp1[k+1][r]+pre[r]-pre[l-1];
                int cost2=dp2[l][k]+dp2[k+1][r]+pre[r]-pre[l-1];
                dp1[l][r]=min(dp1[l][r],cost1);
                dp2[l][r]=max(dp2[l][r],cost2);
            }
        }
    }
    int ans1=1e9;
    int ans2=0;

    for(int i=1;i<=n;i++){
        ans1=min(ans1,dp1[i][i+n-1]);
        ans2=max(ans2,dp2[i][i+n-1]);
    }

    cout<<ans1<<"\n"<<ans2<<"\n";
    return 0;  
}