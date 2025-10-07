#include<iostream>
using namespace std;
inline int add(int a,int b){
   return a+b;
}
int main(){
   int c=add(10,20);
   int d=add(10,21);
   cout<<c<<endl;
   cout<<d<<endl;
   return 0;
}