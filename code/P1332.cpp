//1.多源BFS题，将多个感染源逐个加入到BFS，
//2.逐个按输入顺序输出，需要保存领主位置，要用到pair函数。
//3.不需要结构体，map用dist存time，坐标用pair函数，队列用queue。
//4.多源BFS要防止位置重复，所以最好加入判断语句。
#include<bits/stdc++.h>
using namespace std;
const int Nmax=505;
int dist[Nmax][Nmax];
int dx[4]={1,0,-1,0};//-> ^ <- v
int dy[4]={0,1,0,-1};
int main(){
    int n,m,a,b;
    cin>>n>>m>>a>>b;
    //initialize dist
    memset(dist,-1,sizeof(dist));
    queue<pair<int,int>>q;
    //put all infected into queue 
    for(int i=0;i<a;i++){
        int x,y;
        cin>>x>>y;
        if(dist[x][y]==-1){
            dist[x][y]=0;
            q.push({x,y});
        }
    }
    //save lord
    vector<pair<int,int>>lord(b);
    for(int i=0;i<b;i++){
        cin>>lord[i].first>>lord[i].second;
    }
    //multiple bfs
    while(!q.empty()){
        auto [x,y]=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx<1||nx>n||ny<1||ny>m) continue;
            if(dist[nx][ny]!=-1) continue;
            dist[nx][ny]=dist[x][y]+1;
            q.push({nx,ny});
         }
    }
    for(auto [x,y]:lord){
        cout<<dist[x][y]<<endl;
    }
    return 0;
}
/*
5 4 2 3 a=2,b=3
1 1
5 4
3 3
5 3
2 4

3
1
3
*/