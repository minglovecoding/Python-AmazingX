#include <bits/stdc++.h>
using namespace std;

int N,K;
int A[200001],B[200001]; //input
int P[100001]; //as described in analysis
vector<int>S[100001]; //as described in analysis
int from[100001]; //from[i] = where the cow in position i originated from
int cnt[100001]; //array to keep track of uniquePos
int uniquePos; //# of unique reachable positions

//add in S_node
void add(int node){
  for (int x:S[node]){
    if (cnt[x]==0)
      uniquePos++;
    cnt[x]++;
  }
}

//remove S_node
void remove(int node){
  for (int x:S[node]){
    if (cnt[x]==1)
      uniquePos--;
    cnt[x]--;
  }
}

bool vis[100001];
queue<int>q; //stores all nodes in current cycle

void dfs(int node){
  vis[node]=true;
  add(node);
  q.push(node);
  if (!vis[P[node]])
    dfs(P[node]);
}

int main(){
  cin>>N>>K;
  for (int i=0;i<K;i++)
    cin>>A[i]>>B[i];
  //initialize from and S
  for (int i=1;i<=N;i++){
    from[i]=i;
    S[i].push_back(i);
  }
  //simulate the first K swaps, keeping track of where each position can reach
  for (int i=0;i<K;i++){
    S[from[A[i]]].push_back(B[i]);
    S[from[B[i]]].push_back(A[i]);
    swap(from[A[i]],from[B[i]]);
  }
  //compute array P after first K swaps
  for (int i=1;i<=N;i++)
    P[from[i]]=i;
  int ans[100001];
  //run a DFS on each cycle
  for (int i=1;i<=N;i++)
    if (!vis[i]){
      dfs(i);
      int tempAns=uniquePos; //the answer 
      //assign the answer for all nodes in the cycle, which we've stored in this queue
      while (!q.empty()){
	remove(q.front());
	ans[q.front()]=tempAns;
	q.pop();
      }
    }
  for (int i=1;i<=N;i++)
    cout<<ans[i]<<endl;
  return 0;
}