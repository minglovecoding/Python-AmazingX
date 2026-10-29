#include <bits/stdc++.h>
using namespace std;
int N,M;
struct Cow{int s,t,c;}cow[25];
struct AC{int a,b,p,m;}ac[15];
int need[105];
int cool[105];
int ans=1e9;

void dfs(int pos, int cost){
    if(pos == M){
        bool ok=true;
        for(int i=1;i<=100;i++){
            if(cool[i] < need[i]) ok=false;
        }
        if(ok) ans=min(ans,cost);
        return;
    }

    dfs(pos+1, cost);
    for(int i=ac[pos].a; i<=ac[pos].b; i++) cool[i] += ac[pos].p;
    dfs(pos+1, cost + ac[pos].m);
    for(int i=ac[pos].a; i<=ac[pos].b; i++) cool[i] -= ac[pos].p;
}

int main(){
    cin>>N>>M;
    memset(need,0,sizeof(need));
    for(int i=0;i<N;i++){
        cin>>cow[i].s>>cow[i].t>>cow[i].c;
        for(int j=cow[i].s;j<=cow[i].t;j++) need[j]=cow[i].c;
    }
    for(int i=0;i<M;i++){
        cin>>ac[i].a>>ac[i].b>>ac[i].p>>ac[i].m;
    }
    dfs(0,0);
    cout<<ans<<endl;
    return 0;
}