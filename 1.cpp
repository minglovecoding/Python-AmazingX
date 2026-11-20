#include<bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int>parent;

    explicit DSU(int n):parent(n+1,-1){}

    int find(int x){
        if(parent[x]<0) return x;
        return parent[x]=find(parent[x]);
    }

    bool unite(int a,int b){
        a=find(a);
        b=find(b);

        if(a==b) return false;
        if(parent[a]>parent[b]) swap(a,b);

        parent[a]+=parent[b];
        parent[b]=a;
        
        return true;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("closing.in","r",stdin);
    freopen("closing.out","w",stdout);

    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n+1);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int>order(n+1);
    for(int i=1;i<=n;i++) cin>>order[i];

    DSU dsu(n);
    vector<bool>active(n+1,false);
    vector<bool>answer(n+1,false);

    int activeC=0;

    for(int i=n;i>=1;i--){
        int u=order[i];
        active[u]=true;
        activeC++;

        for(int v:adj[u]){
            if(active[v]&&dsu.unite(u,v)) activeC--;
        }
        answer[i]=(activeC==1);
    }

    for(int i=1;i<=n;i++){
        cout<<(answer[i]?"YES":"NO")<<"\n";
    }
    return 0;
}