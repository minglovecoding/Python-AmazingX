#include <bits/stdc++.h>
using namespace std;
//1.加牛可能会有连锁反应，因此加牛时候也要check四周的牛状态。
//2.对新加入的牛用队列存储并依次弹出判断。
//3.要考虑到新加的牛覆盖补掉的牛，因此每次加的图里有的牛等于总共牛减去i。
//4.必须写一个函数判断四周是否有牛，并用计数器num，当num==3时，触发加牛操作。
set<pair<int,int>>cows;
queue<pair<int,int>>q;
int cnt=0;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
bool has_cow(int x,int y){
   return cows.count({x,y})>0;
}
void add_cow(int x,int y){
   if(has_cow(x,y)) return;
   cows.insert({x,y});
   q.push({x,y});
   cnt++;
}
void check_status(int x,int y){
   if(!has_cow(x,y)) return;
   int num=0;
   int anotherX=0;
   int anotherY=0;
   for(int i=0;i<4;i++){
      int nx=x+dx[i];
      int ny=y+dy[i];
      if(has_cow(nx,ny)) num++;
      else{
         anotherX=nx;
         anotherY=ny;
      } 
   }
   if(num==3) add_cow(anotherX,anotherY);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin>>N;

    for(int i=0;i<N;i++){
      int x,y;
      cin>>x>>y;
      add_cow(x,y);
      while(!q.empty()){
         auto [x,y]=q.front();
         q.pop();

         check_status(x,y);
         for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            check_status(nx,ny);
         }
      }
      cout<<cnt-i-1<<"\n";
    }
    return 0;
}