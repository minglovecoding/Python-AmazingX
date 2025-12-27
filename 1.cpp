#include<iostream>
#include<list>
using namespace std;
int main(){
   list<int>prime={1,3,5,7};
   prime.pop_back();
   prime.push_back(9);
   for(auto iter=prime.begin();iter!=prime.end();iter++){
      cout<<*iter<<endl;
   }
}