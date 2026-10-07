#include <iostream>
using namespace std;
int pos[15][25];
int main() {
   int N,K;
   int cow;
   int ans=0;
   bool flag;
   freopen("gymnastics.in", "r", stdin);
   freopen("gymnastics.out", "w", stdout);
   cin>>K>>N;
   for(int i=0;i<K;i++){
      for(int j=0;j<N;j++){
         cin>>cow;
         pos[i][cow]=j+1;
      }
   }

   for(int i=1;i<=N;i++){
      for(int j=1;j<=N;j++){
         flag=true;
         if(i==j) continue;
         for(int k=0;k<K;k++){
            if(pos[k][i]<pos[k][j]){
               flag=false;
               break;
            }
         }
         if(flag) ans++;
      }
   }
   cout<<ans<<endl;
   return 0;
}

//"Hello Xiaoxu"