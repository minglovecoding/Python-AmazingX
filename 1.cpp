#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int main(){
   ios::sync_with_stdio(0);
   cin.tie(nullptr);
   int N,M;
   cin>>N>>M;
   vector<ll>leftcnt(M+1,0);
   vector<ll>rightcnt(M+1,0);
   vector<ll>diff(2*M+2,0);
   //leftcnt,rightcnt
   for(int i=0;i<N;i++){
      int a,b;
      cin>>a>>b;
      leftcnt[a]++;
      rightcnt[b]++;
   }
   //leftnode++ and rightnode--
   for(int x=0;x<=M;x++){
      for(int y=0;y<=M;y++){
         diff[x+y]+=leftcnt[x]*leftcnt[y];
         diff[x+y+1]-=rightcnt[x]*rightcnt[y];
      }
   }
   ll ans=0;
   for(int k=0;k<=2*M;k++){
      ans+=diff[k];
      cout<<ans<<"\n";
   }
   return 0;
}