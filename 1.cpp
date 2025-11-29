#include <iostream>
using namespace std;
#define ll long long 
ll n,x,nm,N[100005];
int main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>N[i];
    }
    //vector<long long> a(n + 1); 
    ll cnt=0;
    if(N[1]>x){
        cnt+=N[1]-x;
        N[1]=x;
    }
    for(int i=2;i<=n;i++){
        if(N[i]+N[i-1]>x){
            cnt+=N[i]+N[i-1]-x;
            N[i]-=N[i-1]+N[i]-x;
        }
    }
    cout<<cnt;
    return 0;
}