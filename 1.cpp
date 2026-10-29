#include <bits/stdc++.h>
using namespace std;
struct Cow{int s,t,c;}cows[25];
struct Conditioner{int a,b,p,m;}machines[15];
int ans=INT_MAX;
int need[105];
int actual[105];
int N,M;
void dfs(int machine,int cost){
    if(cost>=ans) return;
    if(machine==M){
        for(int i=1;i<=100;i++){
            if(actual[i]<need[i]) return;
        }
        ans=min(ans,cost);
        return;
    }
    //不选
    dfs(machine+1,cost);
    //选
    for(int i=machines[machine].a;i<=machines[machine].b;i++){actual[i]+=machines[machine].p;}
    dfs(machine+1,cost+machines[machine].m);
    for(int i=machines[machine].a;i<=machines[machine].b;i++){actual[i]-=machines[machine].p;}
}
int main(){
    cin>>N>>M;
    fill(need,need+105,0);
    fill(actual,actual+105,0);
    for(int i=0;i<N;i++){
        cin>>cows[i].s>>cows[i].t>>cows[i].c;
        for(int j=cows[i].s;j<=cows[i].t;j++){
            need[j]=cows[i].c;
        }
    }
    for(int i=0;i<M;i++){
        cin>>machines[i].a>>machines[i].b>>machines[i].p>>machines[i].m;
    }
    dfs(0,0);
    cout<<ans<<endl;
    return 0;
}