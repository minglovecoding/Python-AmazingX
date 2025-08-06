#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int A[N],v[N],c[N];
int T,n,m,K;
struct Rule{
    int l,r,t;
    bool operator<(const Rule &demo) const{
        return l>demo.l;
    }
}rule[N];
//树状数组
void add(int x){
    if(x<=0) return;
    for(;x<=m;x+=x&-x) c[x]++;
}
int getsum(int x){
    if(x<=0) return 0;
    int res=0;
    for(;x;x-=x& -x) res+=c[x];
    return res;
}
int getsum(int l,int r){
    return getsum(r)-getsum(l-1);
}
int solve(){
    for(int i=1;i<=n;i++) v[i]=A[i];
    sort(v+1,v+n+1);
    m=unique(v+1,v+n+1)-v-1;
    for(int i=0;i<=m;i++) c[i]=0;
    multiset<int>se;
    for(int i=1;i<=n;i++){
        A[i]=lower_bound(v+1,v+m+1,A[i])-v;
        se.insert(A[i]);
    }
    for(int i=1;i<=K;i++){
        rule[i].l=lower_bound(v+1,v+m+1,rule[i].l)-v;
        rule[i].r=upper_bound(v+1,v+m+1,rule[i].r)-v-1;
    }
    sort(rule+1,rule+K+1);
    int ans=0;
    for(int i=1;i<=K;i++){
        if(rule[i].t<=0) continue;
        int cur=getsum(rule[i].l,rule[i].r);
        if(cur>=rule[i].t) continue;
        ans+=rule[i].t-cur;
        auto it=se.lower_bound(rule[i].l);
        while(cur!=rule[i].t){
            cur++;
            auto it2=it;
            add(*it);
            ++it;
            se.erase(it2);
        }
    }
    return ans;
}
int main(){
    cin>>T;
    while(T){
        T--;
        cin>>n>>K;
        for(int i=1;i<=n;i++) cin>>A[i];
        for(int i=1;i<=K;i++) cin>>rule[i].l>>rule[i].r>>rule[i].t;
        cout<<n-solve()<<endl;
    }
    return 0;
}