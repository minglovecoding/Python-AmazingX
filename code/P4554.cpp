#include<bits/stdc++.h>
using namespace std;
const int Nmax=505;
//const int INF=0x3f3f3f3f;
int n,m;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
char chessMap[Nmax][Nmax];
deque<pair<int,int>>dq;
int dist[Nmax][Nmax];
bool border(int x,int y){
    return x>=0&&x<n&&y>=0&&y<m;
}
int main(){
    while(true){
        memset(dist,0x3f,sizeof(dist));
        dq.clear(); //safe protection
        cin>>n>>m;
        if(n==0&&m==0) break;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>chessMap[i][j];
            }
        }
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        
        dist[x1][y1]=0;
        dq.push_front({x1,y1});

        while(!dq.empty()){
            auto [x,y]=dq.front();
            dq.pop_front();

            for(int i=0;i<4;i++){
                int nx=x+dx[i];
                int ny=y+dy[i];
                if(!border(nx,ny)) continue;
                int cost=(chessMap[x][y]!=chessMap[nx][ny]);
                if(dist[nx][ny]>dist[x][y]+cost){
                    dist[nx][ny]=dist[x][y]+cost;
                    if(cost==0){
                        dq.push_front({nx,ny});
                    }
                    else{
                        dq.push_back({nx,ny});
                    }
                }
            } 
        }
        cout<<dist[x2][y2]<<endl;
    }
    return 0;
}