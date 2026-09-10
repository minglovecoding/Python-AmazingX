//1.实时模拟这个过程太复杂，不可取。结合题目多个起点，可采用多源BFS。
//2.曼哈顿菱形的性质：｜xn-x|+｜yn-y｜<= r,因此从菱形半径一定小于该点到周围最近石头的距离
//3.求所有可能到达的空格，可由所有可到达中心扩张而成。time / D < rockDist[x][y]，半径为多大最终受限于到最近石头距离。
//4.求空格到石头的最短距离可以反推成多源BFS从石头到空格的位置。
//5.对所有可达中心枚举扩张时间复杂度过高，所以优化用最大能力优先的多源BFS，从中心散发能量，中心点记录的是最大安全能量rockDist[x][y] - 1（考虑来回踱步可能会增加半径），每个grid记录最大的能量值。
//6.最后统计有多少个空格有能量（包含0，0没有扩张能力，但到过该点）。
#include<bits/stdc++.h>
using namespace std;
const int Nmax=1005;
int N,D;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int rockDist[Nmax][Nmax];
int firstArrive[Nmax][Nmax];
int maxPower[Nmax][Nmax];
queue<pair<int,int>>q1;
queue<pair<int,int>>q2;
priority_queue<tuple<int,int,int>>pq3;
bool border(int x,int y){
    return x>=0&&x<N&&y>=0&&y<N;
}
int main(){
    string grid[Nmax];
    cin>>N>>D;
    for(int i=0;i<N;i++){
        cin>>grid[i];
    }
    //Stage 1
    memset(rockDist,-1,sizeof(rockDist));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(grid[i][j]=='#'){
                rockDist[i][j]=0;
                q1.push({i,j});
            }
        }
    }
    while(!q1.empty()){
        auto [x,y]=q1.front();
        q1.pop();
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(!border(nx,ny)) continue;
            if(rockDist[nx][ny]!=-1) continue;
            rockDist[nx][ny]=rockDist[x][y]+1;
            q1.push({nx,ny});
        }
    }
    //Stage 2
    memset(firstArrive,-1,sizeof(firstArrive));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(grid[i][j]=='S'){
                firstArrive[i][j]=0;
                q2.push({i,j});
            }
        }
    }
    while(!q2.empty()){
        auto [x,y]=q2.front();
        q2.pop();
        //power
        int time=firstArrive[x][y];
        if(time/D>rockDist[x][y]-1) continue;
        pq3.push({rockDist[x][y]-1,x,y});
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(!border(nx,ny)) continue;
            if(grid[nx][ny]=='#') continue;
            if(firstArrive[nx][ny]!=-1) continue;
            firstArrive[nx][ny]=firstArrive[x][y]+1;
            q2.push({nx,ny});
        }
    }
    //stage3
    memset(maxPower,-1,sizeof(maxPower));
    while(!pq3.empty()){
        auto [power,x,y] = pq3.top();
        pq3.pop();
        if(maxPower[x][y]>=power) continue;
        maxPower[x][y]=power;
        if(power==0) continue;
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(!border(nx,ny)) continue;
            if(grid[nx][ny]=='#') continue;
            int nextPower=power-1;
            if(maxPower[nx][ny]<nextPower){
                pq3.push({nextPower,nx,ny});
            }
        }
    }
    //Output
    int ans=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(maxPower[i][j]!=-1) ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}