#include <iostream>
using namespace std;
 
int sum(int a, int b)
{
  int result1;
 
  result1 = a + b;
  
  return result1;
}
 
int main ()
{
   // 局部变量声明
   int a = 100;
   int b = 200;
   int result;
 
   // 调用函数来添加值
   result = sum(a, b);
   cout << "Total value is :" << result << endl;
 
   // 再次调用函数
   //result = sum(a);
   //cout << "Total value is :" << result << endl;
 
   return 0;
}