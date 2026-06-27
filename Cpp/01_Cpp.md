### 📌 Lambda函数与表达式

Lambda 表达式本质上与函数声明非常类似。Lambda 表达式具体形式如下:

```c++
#1
[](int x, int y){ return x < y ; }
#2
[](int x, int y) -> int { int z = x + y; return z + x; }
#3
[]      // 沒有定义任何变量。使用未定义变量会引发错误。
[x, &y] // x以传值方式传入（默认），y以引用方式传入。
[&]     // 任何被使用到的外部变量都隐式地以引用方式加以引用。
[=]     // 任何被使用到的外部变量都隐式地以传值方式加以引用。
[&, x]  // x显式地以传值方式加以引用。其余变量以引用方式加以引用。
[=, &z] // z显式地以引用方式加以引用。其余变量以传值方式加以引用。
```

```c++
#include <iostream>
using namespace std;
/*int add(int a,int b){
  return a+b;
}*/
int main() {
    auto add = [](int a, int b) {
        return a + b;
    };
    int c=add(3, 5);
    cout << c << endl;  // 输出 8
}
```

### 📌 C++数字

```c++
#include <iostream>
using namespace std;
 
int main ()
{
   // 数字定义
   int    i;
   long   l;
   float  f;
   double d;
   
   // 数字赋值  
   i = 1000;
   l = 1000000; 
   f = 230.47;  
   d = 30949.374;
   
   // 数字输出
   cout << "int    i :" << i << endl;
   cout << "long   l :" << l << endl;
   cout << "float  f :" << f << endl;
   cout << "double d :" << d << endl;
 
   return 0;
}
```

| No.  | **函数 & 描述**                                              |
| :--- | :----------------------------------------------------------- |
| 1    | **double cos(double);** 该函数返回弧度角（double 型）的余弦。 |
| 2    | **double sin(double);** 该函数返回弧度角（double 型）的正弦。 |
| 3    | **double tan(double);** 该函数返回弧度角（double 型）的正切。 |
| 4    | **double log(double);** 该函数返回参数的自然对数。           |
| 5    | **double pow(double, double);** 假设第一个参数为 x，第二个参数为 y，则该函数返回 x 的 y 次方。 |
| 6    | **double hypot(double, double);** 该函数返回两个参数的平方总和的平方根，也就是说，参数为一个直角三角形的两个直角边，函数会返回斜边的长度。 |
| 7    | **double sqrt(double);** 该函数返回参数的平方根。            |
| 8    | **int abs(int);** 该函数返回整数的绝对值。                   |
| 9    | **double fabs(double);** 该函数返回任意一个浮点数的绝对值。  |
| 10   | **double floor(double);** 该函数返回一个小于或等于传入参数的最大整数。 |

```c++
#include <iostream>
#include <cmath>
using namespace std;
 
int main ()
{
   // 数字定义
   short  s = 10;
   int    i = -1000;
   long   l = 100000;
   float  f = 230.47;
   double d = 200.374;
 
   // 数学运算
   cout << "sin(d) :" << sin(d) << endl;
   cout << "abs(i)  :" << abs(i) << endl;
   cout << "floor(d) :" << floor(d) << endl;
   cout << "sqrt(f) :" << sqrt(f) << endl;
   cout << "pow( d, 2) :" << pow(d, 2) << endl;
 
   return 0;
}
```

### 📌 C++随机数

关于随机数生成器，有两个相关的函数。一个是 **rand()**，该函数只返回一个伪随机数。生成随机数之前必须先调用 **srand()** 函数。

下面实例使用了 **time()** 函数来获取系统时间的秒数，通过调用 rand() 函数来生成随机数：

```c++
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main ()
{
   int i,j;
   // 设置种子
   srand(time(0));
   /* 生成 10 个随机数 */
   for( i = 0; i < 10; i++ )
   {
      // 生成实际的随机数
      j= rand();
      cout <<"随机数： " << j << endl;
   }
  //比如生成 [a, b] 范围的随机整数：
  //int x = a + rand() % (b - a + 1);
   return 0;
}
```

### 📌 C++数学常数

```c++
#include <iostream>
#include <cmath>
#include <numbers>
using namespace std;
constexpr double PI  = 3.14159265358979323846;
constexpr double E   = 2.71828182845904523536;
constexpr double PHI = 1.61803398874989484820;
int main() {
	cout<<PI<<endl;
	cout<<E<<endl;
	cout<<PHI<<endl;
  return 0;
}
```

### 📌 C++多维数组

1. 二维数组

```c++
#include <iostream>
#include <cmath>
#include <numbers>
using namespace std;
int main() {
	//int a=10;
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int b[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	for(int i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
    cout<<endl;
    for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
    return 0;
}
```

2. C++指向数组的指针

```c++
#include <iostream>
using namespace std;
 
int main ()
{
   // 带有 5 个元素的双精度浮点型数组
   double runoobAarray[5] = {1000.0, 2.0, 3.4, 17.0, 50.0};
   double *p;
 
   p = runoobAarray;
 
   // 输出数组中每个元素的值
   cout << "使用指针的数组值 " << endl; 
   for ( int i = 0; i < 5; i++ )
   {
       cout << "*(p + " << i << ") : ";
       cout << *(p + i) << endl;
   }
 
   cout << "使用 runoobAarray 作为地址的数组值 " << endl;
   for ( int i = 0; i < 5; i++ )
   {
       cout << "*(runoobAarray + " << i << ") : ";
       cout << *(runoobAarray + i) << endl;
   }
 
   return 0;
}
```

3. C++传递数组给函数

```c++
//1
//void myFunction(int *param){}
//2
//void myFunction(int param[10])
//3
//void myFunction(int param[]){}

#include <iostream>
using namespace std;
// 函数声明
double getAverage(int arr[], int size)
{
  int    i, sum = 0;       
  double avg;          
 
  for (i = 0; i < size; ++i)
  {
    sum += arr[i];
   }
 
  avg = double(sum) / size;
 
  return avg;
}
int main ()
{
   // 带有 5 个元素的整型数组
   int balance[5] = {1000, 2, 3, 17, 50};
   double avg;
 
   // 传递一个指向数组的指针作为参数
   avg = getAverage( balance, 5 ) ;
 
   // 输出返回值
   cout << "平均值是：" << avg << endl; 
    
   return 0;
}
```

4. C++从函数返回数组

   C++ 不支持在函数外返回局部变量的地址，除非定义局部变量为 **static** 变量。

   为了避免以上情况，可以使用静态数组或者动态分配数组。静态数组需要在函数内部创建一个静态数组，并将其地址返回，例如：

```c++
int* myFunction()
{
   static int myArray[3] = {1, 2, 3};
   return myArray;
}
```

```c++
#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
// 要生成和返回随机数的函数
int * getRandom( )
{
  static int  r[10];
 
  // 设置种子
  srand( (unsigned)time( NULL ) );
  for (int i = 0; i < 10; ++i)
  {
    r[i] = rand();
    cout << r[i] << endl;
  }
 
  return r;
}
 
// 要调用上面定义函数的主函数
int main ()
{
   // 一个指向整数的指针
   int *p;
 
   p = getRandom();
   for ( int i = 0; i < 10; i++ )
   {
       cout << "*(p + " << i << ") : ";
       cout << *(p + i) << endl;
   }
 
   return 0;
}
```

2. 或者使用动态分配数组，动态分配数组需要在函数内部使用 new 运算符来分配一个数组，并在函数结束时使用 delete 运算符释放该数组。

```c++
#include <iostream>
using namespace std;

int* createArray(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

int main() {
    int* myArray = createArray(5);
    for (int i = 0; i < 5; i++) {
        cout << myArray[i] << " ";
    }
    cout << endl;
    delete[] myArray; // 释放内存
    return 0;
}		
```

### 📌 C++字符串

1. C风格字符串

```c++
#include <iostream>
#include <cstring>
 
using namespace std;
 
int main ()
{
   char str1[13] = "runoob";
   char str2[13] = "google";
   char str3[13];
   int  len ;
 
   // 复制 str1 到 str3
   strcpy( str3, str1);
   cout << "strcpy( str3, str1) : " << str3 << endl;
 
   // 连接 str1 和 str2
   strcat( str1, str2);
   cout << "strcat( str1, str2): " << str1 << endl;
 
   // 连接后，str1 的总长度
   len = strlen(str1);
   cout << "strlen(str1) : " << len << endl;
 
   return 0;
}
```

2. C++的String

```c++
#include<bits/stdc++.h>
using namespace std;
 
int main ()
{
   string str1 = "runoob";
   string str2 = "google";
   string str3;
   int  len ;
 
   // 复制 str1 到 str3
   str3 = str1;
   cout << "str3 : " << str3 << endl;
 
   // 连接 str1 和 str2
   str3 = str1 + str2;
   cout << "str1 + str2 : " << str3 << endl;
 
   // 连接后，str3 的总长度
   len = str3.size();
   cout << "str3.size() :  " << len << endl;
 
   return 0;
}
```

### 📌 C++指针

每一个变量都有一个内存位置，每一个内存位置都定义了可使用连字号（&）运算符访问的地址，它表示了在内存中的一个地址。

```c++
#include <iostream>
using namespace std;
int main ()
{
   int  var1;
   char var2[10];
   cout << "var1 变量的地址： ";
   cout << &var1 << endl;
   cout << "var2 变量的地址： ";
   cout << &var2 << endl;
   return 0;
}
```

```c++
#include <iostream>
using namespace std;
int main ()
{
   int  var = 20;   // 实际变量的声明
   int  *ip;        // 指针变量的声明
 
   ip = &var;       // 在指针变量中存储 var 的地址
 
   cout << "Value of var variable: ";
   cout << var << endl;
 
   // 输出在指针变量中存储的地址
   cout << "Address stored in ip variable: ";
   cout << ip << endl;
 
   // 访问指针中地址的值
   cout << "Value of *ip variable: ";
   cout << *ip << endl;
 
   return 0;
}
```

1. Null指针

在变量声明的时候，如果没有确切的地址可以赋值。赋为 NULL 值的指针被称为**空**指针。

```c++
#include <iostream>
using namespace std;
int main ()
{
   int  *ptr = NULL;
   cout << "ptr 的值是 " << ptr ;
   return 0;
}
```

2. 指针算术运算

```c++
#include <iostream>
using namespace std;
int main() {
    // 定义一个数组
    int arr[5] = {10, 20, 30, 40, 50};
 
    // 定义一个指向数组第一个元素的指针
    int* ptr = arr;
    
    // 输出指针指向的元素
    cout << "指针当前指向的元素: " << *ptr << endl;
    
    // 递增指针
    ptr++;
    
    // 输出指针指向的元素
    cout << "递增指针后指向的元素: " << *ptr << endl;
    
    return 0;
}
```

3. 指针与数组关系

```c++
#include <iostream>
 
int main() {
    // 定义一个数组
    int arr[5] = {10, 20, 30, 40, 50};
    
    // 定义一个指向数组第一个元素的指针
    int* ptr = arr;
    
    // 输出指针指向的元素
    std::cout << "指针当前指向的元素: " << *ptr << std::endl;
    
    // 递增指针
    ptr++;
    
    // 输出指针指向的元素
    std::cout << "递增指针后指向的元素: " << *ptr << std::endl;
    
    return 0;
}		
```

4. 指针数组

```c++
#include <iostream>
 
using namespace std;
const int MAX = 3;
 
int main ()
{
   int  var[MAX] = {10, 100, 200};
   int *ptr[MAX];
 
   for (int i = 0; i < MAX; i++)
   {
      ptr[i] = &var[i]; // 赋值为整数的地址
   }
   for (int i = 0; i < MAX; i++)
   {
      cout << "Value of var[" << i << "] = ";
      cout << *ptr[i] << endl;
   }
   return 0;
}
```

5. 指向指针的指针

指向指针的指针是一种多级间接寻址的形式，或者说是一个指针链。

<img src="/Users/zhoumingzhao/Desktop/Python-AmazingX/images/pointer.png" alt="pointer" style="zoom:150%;" />

一个指针包含一个变量的地址。当我们定义一个指向指针的指针时，第一个指针包含了第二个指针的地址，第二个指针指向包含实际值的位置。

```c++
#include <iostream>
using namespace std;
int main ()
{
    int  var; 
    int  *ptr;
    int  **pptr;
    var = 3000;
    // 获取 var 的地址
    ptr = &var;
    // 使用运算符 & 获取 ptr 的地址
    pptr = &ptr;
    // 使用 pptr 获取值
    cout << "var 值为 :" << var << endl;
    cout << "*ptr 值为:" << *ptr << endl;
    cout << "**pptr 值为:" << **pptr << endl;
    return 0;
}
```

6. C++传递指针给函数

```c++
//case 1
#include <iostream>
#include <ctime>
using namespace std;
// 在写函数时应习惯性的先声明函数，然后在定义函数
void getSeconds(unsigned long *par)
{
   // 获取当前的秒数
   *par = time( NULL );
   return;
}

int main ()
{
   unsigned long sec;
 
   getSeconds( &sec );
 
   // 输出实际值
   cout << "Number of seconds :" << sec << endl;
 
   return 0;
}
```

```c++
//case 2
#include <iostream>
using namespace std;
 
// 函数声明
double getAverage(int *arr, int size)
{
  int i,sum = 0;       
  double avg;          
 
  for (i = 0; i < size; ++i)
  {
    sum += arr[i];
   }
 
  avg = double(sum) / size;
 
  return avg;
}
 
int main ()
{
   // 带有 5 个元素的整型数组
   int balance[5] = {1000, 2, 3, 17, 50};
   double avg;
 
   // 传递一个指向数组的指针作为参数
   avg = getAverage( balance, 5 ) ;
 
   // 输出返回值
   cout << "Average value is: " << avg << endl; 
    
   return 0;
}
 

```

7. 从函数返回指针

```c++
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
// 要生成和返回随机数的函数
int *getRandom( )
{
  static int  r[10];
  // 设置种子
  srand( (unsigned)time( NULL ) );
  for (int i = 0; i < 10; ++i)
  {
    r[i] = rand();
    cout << r[i] << endl;
  }
  return r;
}
// 要调用上面定义函数的主函数
int main ()
{
   // 一个指向整数的指针
   int *p;
 
   p = getRandom();
   for ( int i = 0; i < 10; i++ )
   {
       cout << "*(p + " << i << ") : ";
       cout << *(p + i) << endl;
   }
   return 0;
}
```

### 📌 C++引用

```c++
int a = 10;
int &ref = a;  // ref 是 a 的引用
```

- `int &ref` 表示 `ref` 是一个 `int` 类型的引用。
- `ref` 是 `a` 的别名，对 `ref` 的操作会直接作用于 `a`。

| **特性**                | **引用**                                                     | **指针**                                                     |
| :---------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| **定义与初始化**        | 必须初始化，且不能为 `null`。                                | 可以不初始化，可以在后续代码中指向其他对象，可以为 `null`。  |
| **语法**                | 使用 `&` 声明，例如：`int &ref = a;`                         | 使用 `*` 声明，例如：`int *ptr = &a;`                        |
| **重新绑定**            | 不能重新绑定，一旦初始化后始终引用同一个对象。               | 可以重新指向其他对象，例如：`ptr = &b;`                      |
| **空值（Nullability）** | 不能为 `null`，必须绑定到有效的对象。                        | 可以为 `null`，表示不指向任何对象。                          |
| **内存占用**            | 不占用额外内存（编译器通常将其优化为直接操作所引用的对象）。 | 占用额外内存（存储地址，通常是一个机器字长，如4字节或8字节）。 |
| **访问方式**            | 直接使用，无需解引用操作符，例如：`ref = 10;`                | 需要使用 `*` 解引用操作符访问或修改所指向的对象，例如：`*ptr = 10;` |
| **多级间接访问**        | 不支持多级间接访问（不能有引用的引用）。                     | 支持多级间接访问（如指针的指针：`int **pptr;`）。            |
| **函数参数传递**        | 常用于函数参数传递，语法简洁，例如：`void func(int &x) { x = 10; }` | 也可以用于函数参数传递，但需要使用解引用操作符，例如：`void func(int *x) { *x = 10; }` |
| **数组与引用**          | 不能直接创建引用数组，但可以创建数组的引用，例如：`int (&ref)[10] = arr;` | 可以创建指针数组，也可以创建指向数组的指针，例如：`int *ptrArr[10];` |
| **安全性**              | 更安全，不能为 `null`，且语法更直观。                        | 更灵活，但容易出错（如空指针、野指针等）。                   |
| **底层实现**            | 通常通过指针实现，但编译器会优化为直接操作所引用的对象。     | 直接存储目标对象的内存地址。                                 |

```c++
#include <iostream>
 
using namespace std;
 
int main ()
{
   // 声明简单的变量
   int    i;
   double d;
 
   // 声明引用变量
   int&    r = i;
   double& s = d;
   
   i = 5;
   cout << "Value of i : " << i << endl;
   cout << "Value of i reference : " << r  << endl;
 
   d = 11.7;
   cout << "Value of d : " << d << endl;
   cout << "Value of d reference : " << s  << endl;
   
   return 0;
}
```

1.把引用作为参数

```c++
#include <iostream>
using namespace std;
void swap(int &a,int &b){
	int temp=a;
	a=b;
	b=temp;
	return;
}
int main() {
	int a=10,b=20;
	swap(a,b);
	cout<<a<<" "<<b<<endl;
	return 0;
}
```

2.把引用作为返回值

```c++
#include <iostream>
 
using namespace std;
 
double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};
 
double& setValues(int i) {  
   double& ref = vals[i];    
   return ref;   // 返回第 i 个元素的引用，ref 是一个引用变量，ref 引用 vals[i]
}
 
// 要调用上面定义函数的主函数
int main ()
{
 
   cout << "改变前的值" << endl;
   for ( int i = 0; i < 5; i++ )
   {
       cout << "vals[" << i << "] = ";
       cout << vals[i] << endl;
   }
 
   setValues(1) = 20.23; // 改变第 2 个元素
   setValues(3) = 70.8;  // 改变第 4 个元素
 
   cout << "改变后的值" << endl;
   for ( int i = 0; i < 5; i++ )
   {
       cout << "vals[" << i << "] = ";
       cout << vals[i] << endl;
   }
   return 0;
}
```

### 📌 C++日期&时间

```c++
#include <iostream>
#include <ctime>
 
using namespace std;
 
int main( )
{
   // 基于当前系统的当前日期/时间
   time_t now = time(0);
   
   // 把 now 转换为字符串形式
   char* dt = ctime(&now);
 
   cout << "本地日期和时间：" << dt << endl;
 
   // 把 now 转换为 tm 结构
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   cout << "UTC 日期和时间："<< dt << endl;
}
```

### 📌 C++ 基本的输入输出

1.输入输出

```c++
#include <iostream>
using namespace std;
 
int main( )
{
   char name[50];
   cout << "请输入您的名称： ";
   cin >> name;
   cout << "您的名称是： " << name << endl;
 
}
```

2.减少输入输出时间

```c++
ios_base::sync_with_stdio(0); 
cin.tie(0);
```

**`ios_base::sync_with_stdio(false);`**

- 作用：关闭 `iostream`（`cin/cout`）与 `stdio`（`scanf/printf`）之间的同步。
- 默认情况下，C++ 的输入输出和 C 的输入输出是同步的，这样你可以混用 `cin` 和 `printf`。
- 但是同步会增加开销，关掉后可以提升 `cin/cout` 的性能。
- 关闭后 **不要混用 `cin/cout` 和 `scanf/printf`**，否则可能出错。

**`cin.tie(0);`**

- 作用：解除 `cin` 与 `cout` 的绑定关系。
- 默认情况下，每次执行 `cin` 之前，`cout` 会自动刷新缓冲区（保证提示信息立即输出）。
- 解除绑定后，`cin` 不再强制刷新 `cout`，从而提高性能。
- 如果需要输出立即显示，可以手动调用 `cout.flush()`。

### 📌 C++ 结构体

```C++
#include<bits/stdc++.h>
using namespace std;
struct Person{
	char name[10];
	int age;
	char sex[5];
	int height;
	string school;
}; 
int main()
{
   Person Johnson;
   strcpy(Johnson.name,"Johnson");
   Johnson.age=18;
   strcpy(Johnson.sex,"male");
   Johnson.height=175;
   Johnson.school="shenzhen middle school";
   cout<<Johnson.name<<" "<<Johnson.age<<" "<<Johnson.school<<endl;
   return 0;
}
```

***

