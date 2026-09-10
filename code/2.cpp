#include<bits/stdc++.h>
using namespace std;
const int maxN=305;
int danger[maxN][maxN];
int dist[maxN][maxN];
int INF=0x3f3f3f3f;
int dx[5]={0,1,0,-1,0};
int dy[5]={0,0,1,0,-1};
queue<pair<int,int>>q;
int bfs(){
    if(danger[0][0]==INF) return 0;
    if(danger[0][0]==0) return -1;
    dist[0][0]=0;
    q.push({0,0});
    while(!q.empty()){
        auto [x,y]=q.front();
        q.pop();
        for(int i=1;i<5;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx<0||ny<0) continue;
            if(dist[nx][ny]!=-1) continue;
            int newtime=dist[x][y]+1;
            if(newtime>=danger[nx][ny]) continue;
            dist[nx][ny]=newtime; 
            if(danger[nx][ny]==INF) return dist[nx][ny];
            q.push({nx,ny});
        }
    }
    return -1;
}
int main(){
    int M;
    cin>>M;
    memset(danger,0x3f,sizeof(danger));
    memset(dist,-1,sizeof(dist));
    for(int i=0;i<M;i++){
        int x,y,t;
        cin>>x>>y>>t;
        for(int j=0;j<5;j++){
            int nx=x+dx[j];
            int ny=y+dy[j];
            if(nx<0||ny<0) continue;
            danger[nx][ny]=min(danger[nx][ny],t);
        }
        
    }
    cout<<bfs()<<endl;
    return 0;
}