#include <bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int>parent;
    int components;

    explicit DSU(int n):parent(n+1,-1),components(n){}

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
        components--;
        return true;
    }

    bool same(int a,int b){
        return find(a)==find(b);
    }

    int size(int x){
        return -parent[find(x)];
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    DSU dsu(n);
    while(m--){
        int z,x,y;
        cin>>z>>x>>y;
        if(z==1) dsu.unite(x,y);
        else cout<<(dsu.same(x,y)?"Y":"N")<<"\n";
    }
    return 0;
}