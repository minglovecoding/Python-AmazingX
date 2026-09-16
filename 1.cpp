#include<bits/stdc++.h>
using namespace std;
const int Nmax=5e4+5;
const int Kmax=55;
const int INF=0x3f3f3f3f;
int N,K;
int breed[Nmax];
char Kmap[Kmax][Kmax];
int dist[Nmax][Kmax];
deque<pair<int,int>>dq;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>N>>K;
    memset(dist,0x3f,sizeof(dist));
    for(int i=1;i<=N;i++){
        cin>>breed[i];
    }
    for(int i=1;i<=K;i++){
        for(int j=1;j<=K;j++){
            cin>>Kmap[i][j];
        }
    }

    dist[1][breed[1]]=0;
    dq.push_front({1,breed[1]});

    while(!dq.empty()){
        auto [pos,type]=dq.front();
        dq.pop_front();
        int currentDist=dist[pos][type];
        //1.传递给当前牛
        int nextType=breed[pos];
        if(Kmap[type][nextType]=='1'&&dist[pos][nextType]>currentDist){
            dist[pos][nextType]=currentDist;
            dq.push_front({pos,nextType});
        } 
        //2.向右传递
        if(pos>1&&dist[pos-1][type]>currentDist+1){
            dist[pos-1][type]=currentDist+1;
            dq.push_back({pos-1,type});
        }
        //3.向左传递
        if(pos<N&&dist[pos+1][type]>currentDist+1){
            dist[pos+1][type]=currentDist+1;
            dq.push_back({pos+1,type});
        }
    }

    if(dist[N][breed[N]]==INF) cout<<-1<<endl;
    else cout<<dist[N][breed[N]]<<endl;
    return 0;
}