#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
   vector<int> a = {1, 2, 2, 2, 4, 6};
   auto left = lower_bound(a.begin(), a.end(), 2);
   auto right = upper_bound(a.begin(),a.end(),2);
   while(left!=right){
      cout<<*left<<" ";
      left++;
   }
   cout<<endl;
}