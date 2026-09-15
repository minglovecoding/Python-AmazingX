#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using State=tuple<ll,int,int>;
const ll INF=0x3f3f3f3f3f3f3f3fLL;
int n,m,k;
int Start,End;
ll dist[10000+5][15];
int main(){
    ios::sync_with_stdio(false);//不兼入c语言输入输出
    cin.tie(nullptr);//解除cin和cout的绑定

    cin>>n>>m>>k;
    cin>>Start>>End;
    vector<vector<pair<int,int>>>adj(n+1);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    
    //最小堆
    priority_queue<State,vector<State>,greater<State>>pq;
    memset(dist,0x3f,sizeof(dist));
    dist[Start][0]=0;
    pq.push({0,Start,0});

    while(!pq.empty()){
        auto [d,u,used] = pq.top();
        pq.pop();
        if(d!=dist[u][used]) continue;
        for(auto [v,w]:adj[u]){
            //1.正常通行
            if(dist[v][used]>dist[u][used]+w){
                dist[v][used]=dist[u][used]+w;
                pq.push({dist[v][used],v,used});
            }
            //2.免费通过 used<k
            if(used<k&&dist[v][used+1]>dist[u][used]){
                dist[v][used+1]=dist[u][used];
                pq.push({dist[v][used+1],v,used+1});
            }
        }
    }
    ll result=INF;
    for(int i=0;i<=k;i++){
        result=min(result,dist[End][i]);
    }
    cout<<result<<endl;
    return 0;
}