#include<iostream>
#include<set>
using namespace std;
int main(){
   set<int>s1;
   s1.insert(1);
   s1.insert(2);
   s1.insert(3);
   s1.insert(2);
   s1.insert(1);
   for(auto iter=s1.begin();iter!=s1.end();iter++){
      cout<<*iter<<endl;
   }
}