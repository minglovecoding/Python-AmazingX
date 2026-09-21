#include<iostream>
#include<cmath>
using namespace std;
const int Nmax=305;
int a[Nmax];
int dp[Nmax][Nmax];
int main(){
    int n;
    cin>>n;
    //initialize
    for(int i=0;i<n;i++){
        cin>>a[i];
        dp[i][i]=1;
    }
    //Interval DP
    for(int i=2;i<=n;i++){
        for(int l=0;l+i-1<n;l++){
            int r=l+i-1;
            //case 1
            dp[l][r]=1+dp[l+1][r];
            //case 2 
            for(int k=l+1;k<=r;k++){
                if(a[l]==a[k]){
                //1
                if(l+1==k){
                    dp[l][r]=min(dp[l][r],dp[k][r]);
                }//2
                else{
                    dp[l][r]=min(dp[l][r],dp[l+1][k-1]+dp[k][r]);
                }
                }
            }
        }
    }
    cout<<dp[0][n-1]<<"\n";
    return 0;
}