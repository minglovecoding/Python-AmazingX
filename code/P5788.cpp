#include <iostream>
#include <stack>
#include <vector>
using namespace std;
const int Nmax = 3000000 + 5;
int a[Nmax];
int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   int n;
   cin>>n;
   stack<int>st;
   vector<int>ans(n+1,0);
   for(int i=1;i<=n;i++){
      cin>>a[i];
   }
   for(int i=1;i<=n;i++){
      while(!st.empty()&&a[st.top()]<a[i]){
         ans[st.top()]=i;
         st.pop();
      }
      st.push(i);
   }
   for(int i=1;i<=n;i++){
      cout<<ans[i]<<" ";
   }
   cout<<endl;
   return 0;
}
