/*
3 5
1 1 R
3 3 L
3 2 D
1 2 L
2 1 U

0
0
0
2
3

RL?
U??
?DL

RLR
URR
LDL
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1000+10;
const int Q=2e5+10;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int tot=0,n,q,ans[Q],g[N][N],s[N][N];
struct Node{
    int x,y,d;
}a[Q];
inline bool inb(int x,int y){
    return 1<=x && x<=n && 1<=y && y<=n;
}
void dfs(int x,int y){
    if(s[x][y]) return;
    bool flag=false;
    if(g[x][y]==-1){
        for(int i=0;i<4;i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(s[nx][ny]) flag=true;
        }
    }else{
        int nx=x+dx[g[x][y]],ny=y+dy[g[x][y]];
        if(s[nx][ny]) flag=true;
    }
    if(!flag) return;
    ++tot;
    s[x][y]=1;
    for(int i=0;i<4;i++){
        int nx=x+dx[i],ny=y+dy[i];
        if(inb(nx,ny)) dfs(nx,ny);
    }
}
int main(){
    cin>>n>>q;
    memset(g,-1,sizeof(g));
    for(int i=1;i<=q;i++){
         char c;
         cin>>a[i].x>>a[i].y>>c;
         if(c=='U') a[i].d=0;
         else if(c=='R') a[i].d=1;
         else if(c=='D') a[i].d=2;
         else a[i].d=3;
         g[a[i].x][a[i].y]=a[i].d;
    }
    for(int i=1;i<=n;i++) s[0][i]=s[n+1][i]=s[i][0]=s[i][n+1]=1;
    for(int i=1;i<=n;i++){
        dfs(1,i);
        dfs(n,i);
        dfs(i,1);
        dfs(i,n);
    }
    ans[q]=tot;
    for(int i=q;i>=2;i--){
        g[a[i].x][a[i].y]=-1;
        dfs(a[i].x,a[i].y);
        ans[i-1]=tot;
    }
    for(int i=1;i<=q;i++){
        cout<<n*n-ans[i]<<endl;
    }
    return 0;
}