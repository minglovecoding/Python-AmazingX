#include<iostream>
#include<list>
using namespace std;
int main(){
   list<int>l1;
   list<int>l2={8,6,5,9};
   l1.push_back(1);
   l1.push_back(4);
   l1.push_back(3);
   l1.push_back(3);

   l1.sort();
   l1.unique();
   for(list<int>::iterator iter=l1.begin();iter!=l1.end();iter++){
      cout<<*iter<<" ";
   }
   cout<<endl;
   l1.merge(l2);
   for(list<int>::iterator iter=l1.begin();iter!=l1.end();iter++){
      cout<<*iter<<" ";
   }
   cout<<endl;
   l1.reverse();
   for(list<int>::iterator iter=l1.begin();iter!=l1.end();iter++){
      cout<<*iter<<" ";
   }
   return 0;
}