#include<bits/stdc++.h>
using namespace std;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
set<pair<int,int>>cows;
queue<pair<int,int>>q;
int cnt=0;
bool hasCow(int x,int y){
    return cows.count({x,y})>0;
}

void addCow(int x,int y){
    if(hasCow(x,y)) return;
    cows.insert({x,y});
    cnt++;
    q.push({x,y});
}

void checkStatus(int x,int y){
    if(!hasCow(x,y)) return;
    int num=0;
    int emptyX=0;
    int emptyY=0;
    for(int i=0;i<4;i++){
        int nx=x+dx[i];
        int ny=y+dy[i];
        if(hasCow(nx,ny)) num++;
        else{
            emptyX=nx;
            emptyY=ny;
        }
    }
    if(num==3) addCow(emptyX,emptyY);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin>>N;

    for(int i=1;i<=N;i++){
        int x,y;
        cin>>x>>y;
        addCow(x,y);
        while(!q.empty()){
            auto [x,y]=q.front();
            q.pop();

            checkStatus(x,y);
            for(int i=0;i<4;i++){
                int nx=x+dx[i];
                int ny=y+dy[i];
                checkStatus(nx,ny);
            }
        }
        cout<<cnt-i<<"\n";
    }
    return 0;
}