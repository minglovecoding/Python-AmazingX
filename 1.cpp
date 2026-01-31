//最大堆
#include<iostream>
#include<queue>
using namespace std;
int main(){
   priority_queue<int>pq;
   pq.push(4);
   pq.push(3);
   pq.push(2);
   pq.push(1);
   cout<<pq.top()<<endl;
   pq.pop();
   cout<<pq.top()<<endl;
   return 0;
}