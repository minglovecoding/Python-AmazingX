//用实时模拟的方法需要维护的状态过多，比较复杂。
//1.把流星模拟和人物模拟分开，引入danger时间，即为流星砸下来的时间，初始化为INF，后读入更新。
//2.只要人物走到danger==INF的位置，即说明是安全地方，因为此位置任意时候都不会危险。
//3.如果队列位置为空了，说明无论如何都走不出去了，输出-1。
#include<bits/stdc++.h>
using namespace std;
const int Nmax=305;
const int INF=0x3f3f3f3f;
int danger[Nmax][Nmax];
int dist[Nmax][Nmax];
int dx[5]={0,1,0,-1,0};//-> ^ <- v
int dy[5]={0,0,1,0,-1};
queue<pair<int,int>>q;
int bfs(){ //
    if(danger[0][0]==INF) return 0;
    if(danger[0][0]==0) return -1;
    q.push({0,0});
    dist[0][0]=0;
    while(!q.empty()){
        auto [x,y]=q.front();
        q.pop();

        for(int i=1;i<5;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx<0||ny<0) continue;
            if(dist[nx][ny]!=-1) continue;
            int nexttime=dist[x][y]+1;
            if(nexttime>=danger[nx][ny]) continue;
            dist[nx][ny]=nexttime;
            if(danger[nx][ny]==INF) return nexttime;
            q.push({nx,ny});
        }
    }
    return -1;
}

int main(){
    //输入
    int M;
    cin>>M;
    memset(danger,0x3f,sizeof(danger));
    memset(dist,-1,sizeof(dist));
    for(int i=0;i<M;i++){
        int x,y,t;
        cin>>x>>y>>t;
        for(int i=0;i<5;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx<0||ny<0) continue;
            danger[nx][ny]=min(danger[nx][ny],t);
        }
    }
    cout<<bfs()<<endl;
    return 0;
}
/*
4
0 0 2
2 1 2
1 1 2
0 3 5

5
*/