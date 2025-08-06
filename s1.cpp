#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int n;
long long a[maxn],pre[maxn],suf[maxn];
int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            pre[i]=pre[i-1]+a[i];
        }
        suf[n+1]=0;
        for(int i=n;i>=1;i--){
            suf[i]=suf[i+1]+a[i];
        }
        long long ans=0;
        for(int i=0;i<=n/2-1;i++){
            ans=max(ans,pre[i]+suf[n+1-(n/2-1-i)]);
        }
        cout<<pre[n]-ans<<" "<<ans<<endl;
    }
    return 0;
}