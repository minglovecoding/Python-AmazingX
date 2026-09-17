//1.TSP旅行商问题
//2.先算出不同点的cost，再套用旅行商问题
/*
4
1 1
1 -1
-1 1
-1 -1
*/
#include<bits/stdc++.h>
using namespace std;
const int Nmax=15;
int n;
double cost[Nmax][Nmax];
struct cream{
    double x;
    double y;
}creams[Nmax];
double dp[1<<Nmax][Nmax];
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>creams[i].x>>creams[i].y;
    }
    //cost
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            double dx=creams[i].x-creams[j].x;
            double dy=creams[i].y-creams[j].y;
            cost[i][j]=sqrt(dx*dx+dy*dy);
        }
    }
    //initialize
    for(int mask=0;mask<(1<<n);mask++){
        for(int i=0;i<n;i++){
            dp[mask][i]=1e18;
        }
    }
    for(int i=0;i<n;i++){//只吃了第 i 块奶酪，并且当前停在 i，距离就是原点到 i 的距离。
        dp[1<<i][i]=sqrt(creams[i].x*creams[i].x+creams[i].y*creams[i].y); 
    }
    //state convert
    for(int mask=0;mask<(1<<n);mask++){
        for(int i=0;i<n;i++){
            if(!(mask&(1<<i))) continue;
            if(dp[mask][i]>=1e18) continue;
            for(int j=0;j<n;j++){
                if(mask&(1<<j)) continue;
                int newMask=mask | (1<<j);
                dp[newMask][j]=min(dp[newMask][j],dp[mask][i]+cost[i][j]);
            }
        }
    }
    //printf
    double res=1e18;
    for(int i=0;i<n;i++){
        res=min(res,dp[(1<<n)-1][i]);
    }
    printf("%.2f\n",res);
    return 0;
}