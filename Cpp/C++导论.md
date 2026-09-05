C++ 编程入门课

## 📚 C++可以用来做什么

- USACO、CCC竞赛
- 游戏开发、图形渲染、音视频处理
- 机器人、嵌入式硬件开发（单片机、物联网设备的固件）
- 区块链/密码学 

## 🖥️ 必备软件

- vscode（写代码用的）
- github（开源代码）
- chatgpt （查阅代码） 
- C++[在线编译器](https://www.jyshare.com/compile/12/)

## 🧑🏽‍💻 刷题网站

- [leetcode](https://leetcode.cn/) 力扣
- [usaco](https://usaco.org/index.php) 美国高中信息学竞赛
- codeforces cf
- 洛谷

---

## 🗓️ 课时安排与教学目标

| 课时   | 教学主题                          | 教学目标                                         |
| ------ | :-------------------------------- | ------------------------------------------------ |
| 第1课  | Cpp导论                           | 了解C++编程，安装环境并运行第一个程序            |
| 第2课  | 变量与数据类型                    | 掌握变量定义、字符串、整数、浮点数、布尔值等基础 |
| 第3课  | 输入与输出                        | 使用 cin 和 cout 进行人机交互                    |
| 第4课  | 运算符与表达式                    | 进行基本运算操作（加减乘除、取余、比较等）       |
| 第5课  | 条件语句 if...else                | 学会使用条件判断构造程序逻辑                     |
| 第6课  | 循环语句 for / while              | 理解并应用循环结构处理重复任务                   |
| 第7课  | 列表与字符串操作                  | 掌握基本数据结构及常用方法                       |
| 第8课  | 函数的定义与调用                  | 学会封装功能，使用函数组织代码                   |
| 第9课  | 综合项目：猜数字小游戏            | 实战练习，巩固已学知识                           |
| 第10课 | 总结与扩展：小游戏展示 & 自由创作 | 展示成果，激发兴趣，引导自主探索                 |

---

## 📝 示例代码

### 📌 C++程序结构

```c++
#include <iostream>
using namespace std;
int main()
{
   cout << "Hello, world!" << endl;
    //可以用 "\n" 代替以上代码里的 endl。
    return 0;
}
```

### 📌 编译 & 执行 C++ 程序

```cmd
$ g++ 1.cpp
$ ./a.out
```

### 📌 C++ 中的分号 & 语句块

```cpp
x = y;
y = y+1;
add(x, y);

{
   cout << "Hello World"; // 输出 Hello World
   return 0;
}
```

### 📌 C++ 标识符

C++ 标识符是用来标识变量、函数、类、模块。一个标识符以字母 A-Z 或 a-z 或下划线 _ 开始，后跟零个或多个字母、下划线和数字（0-9）。

C++ 标识符内不允许出现标点字符，比如 @、& 和 %。并且C++ 能区分大小写，**Man** 和 **man** 是两个不同的标识符。

```cpp
int x;
int y;
int move_name(int x,int y);
class a_123{}
int _temp;
int a23b9;      
int retVal;
```

### 📌 C++ 关键字

 C++ 中的关键字是不能作为变量名的。

| if    | else     | new       | this      |
| ----- | -------- | --------- | --------- |
| auto  | enum     | operator  | throw     |
| bool  | explicit | private   | true      |
| break | template | protected | try       |
| case  | do       | public    | typedef   |
| catch | false    | register  | typeid    |
| char  | float    | while     | namespace |
| class | for      | return    | union     |
| const | friend   | short     | unsigned  |
| void  | goto     | signed    | using     |

### 📌 C++ 中的注释、空格

```CPP
//声明变量时候用到
/*
...
*/
int age;
```

### 📌 C++ 数据类型

| 类型     | 关键字 | case                |  |
| :------- | :----- | ------------------- | -------- |
| 布尔型   | bool   | bool A=true;       | 布尔类型，存储值 true 或 false，占用 1 个字节。 |
| 字符型   | char   | char A='a';         | 字符类型，用于存储 ASCII 字符，通常占用 1 个字节。 |
| 整型     | int    | int A=123;          | 整数类型，通常用于存储普通整数，通常占用 4 个字节。 |
| 浮点型   | float  | float A=1.23;       | 单精度浮点值，用于存储单精度浮点数。单精度是这样的格式，1 位符号，8 位指数，23 位小数，通常占用4个字节。![img](https://www.runoob.com/wp-content/uploads/2014/09/v2-749cc641eb4d5dafd085e8c23f8826aa_hd.png) |
| 双浮点型 | double | double A=1.2345678; | 双精度浮点值，用于存储双精度浮点数。双精度是 1 位符号，11 位指数，52 位小数，通常占用 8 个字节。![img](https://www.runoob.com/wp-content/uploads/2014/09/v2-48240f0e1e0dd33ec89100cbe2d30707_hd.png) |
| 无类型   | void   |                     |  |
| `signed` | `signed`   | 表示有符号类型（默认） | `signed int x = -10;`                                      |
| `signed` | `unsigned` | 表示无符号类型         | `unsigned int y = 10;`                                       |
| `short`  | `short`    | 表示短整型             | `short int z = 100;` |

| 数据类型             | 描述                              | 大小（字节） | 范围/取值示例                                           |
| :------------------- | :-------------------------------- | :----------- | :------------------------------------------------------ |
| `bool`               | 布尔类型，表示真或假              | 1            | `true` 或 `false`                                       |
| `char`               | 字符类型，通常用于存储 ASCII 字符 | 1            | -128 到 127 或 0 到 255                                 |
| `signed char`        | 有符号字符类型                    | 1            | -128 到 127                                             |
| `unsigned char`      | 无符号字符类型                    | 1            | 0 到 255                                                |
| `short`              | 短整型                            | 2            | -32,768 到 32,767                                       |
| `unsigned short`     | 无符号短整型                      | 2            | 0 到 65,535                                             |
| `int`                | 整型                              | 4            | -2,147,483,648 到 2,147,483,647                         |
| `unsigned int`       | 无符号整型                        | 4            | 0 到 4,294,967,295                                      |
| `long`               | 长整型                            | 4 或 8       | 取决于平台                                              |
| `unsigned long`      | 无符号长整型                      | 4 或 8       | 取决于平台                                              |
| `long long`          | 长长整型（C++11 引入）            | 8            | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807 |
| `unsigned long long` | 无符号长长整型（C++11 引入）      | 8            | 0 到 18,446,744,073,709,551,615                         |
| `float`              | 单精度浮点数                      | 4            | 约 ±3.4e±38（6-7 位有效数字）                           |
| `double`             | 双精度浮点数                      | 8            | 约 ±1.7e±308（15 位有效数字）                           |
| `long double`        | 扩展精度浮点数                    | 8、12 或 16  | 取决于平台                                              |

### 📌 局部变量与全局变量

```c++
#include <iostream>
using namespace std;
 
// 全局变量
int g = 20;
int main ()
{
  // 局部变量
  //int g = 10;
  cout << g;
  return 0;
}
```

### 📌 C++常量

整数常量可以是十进制、八进制或十六进制的常量。前缀指定基数：0x 或 0X 表示十六进制，0 表示八进制，不带前缀则默认表示十进制。

```c++
int a=85         // 十进制
int a=0213       // 八进制 
int a=0x4b       // 十六进制 
int a=830         // 整数 
```

### 📌 浮点常量

```c++
float a=3.14159       // 合法的 
```

### 📌 字符常量

| 转义序列 | 含义       |
| :------- | :--------- |
| \\       | \ 字符     |
| \'       | ' 字符     |
| \"       | " 字符     |
| \n       | 换行符     |
| \t       | 水平制表符 |

```cpp
#include <iostream>
using namespace std;
int main()
{
   cout << "Hello\tWorld\n\n"<<endl;
   return 0;
}
```

### 📌 字符串常量

字符串字面值或常量是括在双引号 **""** 中的,可以使用 **\** 做分隔符，把一个很长的字符串常量进行分行。

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string greeting = "hello, world";
    cout << greeting;
    cout << "\n";     // 换行符
    string greeting2 = "hello, \
                        world";
    cout << greeting2;
    return 0;
}
```

### 📌 定义常量

```cpp
#include <iostream>
using namespace std;
 
#define LENGTH 10   
#define WIDTH  5
#define NEWLINE '\n'

const int abc=123; //const 定义常量，表示该变量的值不能被修改。
int main()
{
   int area;  
   area = LENGTH * WIDTH;
   cout << area;
   cout << NEWLINE;
   return 0;
}
```

### 📌 auto static extern

```cpp
#include <iostream>
 
// 函数声明 
void func(void);
 
static int count = 10; /* 全局变量 */

int main()
{
    auto f=3.14;      //double
    auto s("hello");  //const char*
    auto z = new auto(9); // int*
    auto x1 = 5, x2 = 5.0, x3='r';//错误，必须是初始化为同一类型
  
    while(count--)
    {
       func();
    }
    return 0;
}

// 函数定义
void func( void )
{
    static int i = 5; // 局部静态变量
    i++;
    std::cout << "变量 i 为 " << i ;
    std::cout << " , 变量 count 为 " << count << std::endl;
}
```

```cpp
//extern 存储类用于提供一个全局变量的引用，全局变量对所有的程序文件都是可见的。
//第一个文件：main.cpp
实例
#include <iostream>
 
int count ;
extern void write_extern();
 
int main()
{
   count = 5;
   write_extern();
}
//第二个文件：support.cpp

实例
#include <iostream>
 
extern int count;
 
void write_extern(void)
{
   std::cout << "Count is " << count << std::endl;
}
```

### 📌 算术运算符

| 运算符 | 描述                                                         | 实例             |
| :----- | :----------------------------------------------------------- | :--------------- |
| +      | 把两个操作数相加                                             | A + B 将得到 30  |
| -      | 从第一个操作数中减去第二个操作数                             | A - B 将得到 -10 |
| *      | 把两个操作数相乘                                             | A * B 将得到 200 |
| /      | 分子除以分母                                                 | B / A 将得到 2   |
| %      | 取模运算符，整除后的余数                                     | B % A 将得到 0   |
| ++     | [自增运算符](https://www.runoob.com/cplusplus/cpp-increment-decrement-operators.html)，整数值增加 1 | A++ 将得到 11    |
| --     | [自减运算符](https://www.runoob.com/cplusplus/cpp-increment-decrement-operators.html)，整数值减少 1 | A-- 将得到 9     |

```cpp
#include <iostream>
using namespace std;
int main()
{
   int a = 21;
   int b = 10;
   int c;
 
   c = a + b;
   cout<< c << endl ;
   c = a - b;
   cout<< c << endl ;
   c = a * b;
   cout<< c << endl ;
   c = a / b;
   cout<< c << endl ;
   c = a % b;
   cout<< c << endl ;
 
   int d = 10;   //  测试自增、自减
   c = d++; //c=10 d=11
   //c = ++d; //c=11 d=11
  
   cout << c << endl ;
 
   d = 10;    // 重新赋值
   c = d--; //c=10 d=9
   cout << "Line 1 - c 的值是 " << c << endl ;
   return 0;
}
```

### 📌 关系运算符 & 逻辑运算符 & 位运算符

| 运算符 | 描述                                                         | 实例                 |
| :----- | :----------------------------------------------------------- | :------------------- |
| ==     | 检查两个操作数的值是否相等，如果相等则条件为真。             | (A == B) 不为真。    |
| !=     | 检查两个操作数的值是否相等，如果不相等则条件为真。           | (A != B) 为真。      |
| >      | 检查左操作数的值是否大于右操作数的值，如果是则条件为真。     | (A > B) 不为真。     |
| <      | 检查左操作数的值是否小于右操作数的值，如果是则条件为真。     | (A < B) 为真。       |
| >=     | 检查左操作数的值是否大于或等于右操作数的值，如果是则条件为真。 | (A >= B) 不为真。    |
| <=     | 检查左操作数的值是否小于或等于右操作数的值，如果是则条件为真。 | (A <= B) 为真。      |
| &&     | 称为逻辑与运算符。如果两个操作数都 true，则条件为 true。     | (A && B) 为 false。  |
| \|\|   | 称为逻辑或运算符。如果两个操作数中有任意一个 true，则条件为 true。 | (A \|\| B) 为 true。 |
| !      | 称为逻辑非运算符。用来逆转操作数的逻辑状态，如果条件为 true 则逻辑非运算符将使其为 false。 | !(A && B) 为 true。  |

```cpp
#include <iostream>
using namespace std;
 
int main()
{
   int a = 21;
   int b = 10;
   int c ;
 
   if( a == b )
   {
      cout << "a 等于 b" << endl ;
   }
   else
   {
      cout << "a 不等于 b" << endl ;
   }
   if ( a < b )
   {
      cout << "a 小于 b" << endl ;
   }
   else
   {
      cout << "a 不小于 b" << endl ;
   }
   if ( a > b )
   {
      cout << "a 大于 b" << endl ;
   }
   else
   {
      cout << "a 不大于 b" << endl ;
   }
   /* 改变 a 和 b 的值 */
   a = 5;
   b = 20;
   if ( a <= b )
   {
      cout << "a 小于或等于 b" << endl ;
   }
   if ( b >= a )
   {
      cout << "b 大于或等于 a" << endl ;
   }
   return 0;
}
```

```c++
#include <iostream>
using namespace std;
 
int main()
{
   int a = 5;
   int b = 20;
   int c ;
 
   if ( a && b )
   {
      cout << "Line 1 - 条件为真"<< endl ;
 
   }
   if ( a || b )
   {
      cout << "Line 2 - 条件为真"<< endl ;
   }
   /* 改变 a 和 b 的值 */
   a = 0;
   b = 10;
   if ( a && b )
   {
      cout << "Line 3 - 条件为真"<< endl ;
   }
   else
   {
      cout << "Line 4 - 条件不为真"<< endl ;
   }
   if ( !(a && b) )
   {
      cout << "Line 5 - 条件为真"<< endl ;
   }
   return 0;
}
```

按位运算符是把数字看作二进制来进行计算的。C++s中的按位运算法则如下：下表中变量 a 为 60，b 为 13，二进制格式如下：

```cpp
#include <iostream>
using namespace std;
 
int main()
{
   int a = 60;      // 60 = 0011 1100 
   int b = 13;      // 13 = 0000 1101
   int c = 0;           
 
   c = a & b;             // 12 = 0000 1100 a与b相同的位进行比较，如果都为1即为1。
   cout << "Line 1 - c 的值是 " << c << endl ;
 
   c = a | b;             // 61 = 0011 1101
   cout << "Line 2 - c 的值是 " << c << endl ;
 
   c = a ^ b;             // 49 = 0011 0001
   cout << "Line 3 - c 的值是 " << c << endl ;
 
   c = ~a;                // 61 = 1100 0011
   cout << "Line 4 - c 的值是 " << c << endl ;
                          
   c = a << 2;            // 240 = 1111 0000 
   cout << "Line 5 - c 的值是 " << c << endl ;
                          
   c = a >> 2;            // 15 = 0000 1111
   cout << "Line 6 - c 的值是 " << c << endl ;
 
   return 0;
}
```

| &    | 按**位与**运算符：参与运算的两个值,如果两个相应位都为1,则该位的结果为1,否则为0 | (a & b) 输出结果 12 ，二进制解释： 0000 1100                 |
| ---- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| \|   | 按位或运算符：只要对应的二个二进位有一个为1时，结果位就为1。 | (a \| b) 输出结果 61 ，二进制解释： 0011 1101                |
| ^    | 按位**异或**运算符：当两对应的二进位相异时，结果为1          | (a ^ b) 输出结果 49 ，二进制解释： 0011 0001                 |
| ~    | 按位取反运算符：将二进制表示中的每一位取反，0 变为 1，1 变为 0。**~x** 类似于 **-x-1** | (~a ) 输出结果 -61 ，二进制解释： 1100 0011 (以补码形式表示)，在一个有符号二进制数的补码形式。 |
| <<   | 左移动运算符：运算数的各二进位全部左移若干位，由 **<<** 右边的数字指定了移动的位数，高位丢弃，低位补0。 | a << 2 输出结果 240 ，二进制解释： 1111 0000                 |
| >>   | 右移动运算符：把">>"左边的运算数的各二进位全部右移若干位，**>>** 右边的数字指定了移动的位数 |                                                              |

### 📌 赋值运算符

| 运算符 | 描述                                                         | 实例                            |
| :----- | :----------------------------------------------------------- | :------------------------------ |
| =      | 简单的赋值运算符，把右边操作数的值赋给左边操作数             | C = A + B 将把 A + B 的值赋给 C |
| +=     | 加且赋值运算符，把右边操作数加上左边操作数的结果赋值给左边操作数 | C += A 相当于 C = C + A         |
| -=     | 减且赋值运算符，把左边操作数减去右边操作数的结果赋值给左边操作数 | C -= A 相当于 C = C - A         |
| *=     | 乘且赋值运算符，把右边操作数乘以左边操作数的结果赋值给左边操作数 | C *= A 相当于 C = C * A         |
| /=     | 除且赋值运算符，把左边操作数除以右边操作数的结果赋值给左边操作数 | C /= A 相当于 C = C / A         |
| %=     | 求模且赋值运算符，求两个操作数的模赋值给左边操作数           | C %= A 相当于 C = C % A         |
| <<=    | 左移且赋值运算符                                             | C <<= 2 等同于 C = C << 2       |
| >>=    | 右移且赋值运算符                                             | C >>= 2 等同于 C = C >> 2       |
| &=     | 按位与且赋值运算符                                           | C &= 2 等同于 C = C & 2         |
| ^=     | 按位异或且赋值运算符                                         | C ^= 2 等同于 C = C ^ 2         |
| \|=    | 按位或且赋值运算符                                           | C \|= 2 等同于 C = C \| 2       |

### 📌 for循环、while、do...while

```cpp
#include <iostream>
using namespace std;
 
int main ()
{
   // for 循环执行
   for( int a = 1; a <= 10; a++ )
   {
       cout << "a 的值：" << a << endl;
   }
   //
   int my_array[5] = {1, 2, 3, 4, 5};
   for( int i = 0;  i < 5; i++ )
   {
       cout << "array的值：" << my_array[i] << endl;
   }
  //
  // 每个数组元素乘于 2
  for (int &x : my_array)
  {
    x *= 2;
    cout << x << endl;  
  }
// auto 类型也是 C++11 新标准中的，用来自动获取变量的类型
  for (auto &x : my_array) {
    x *= 2;
    cout << x << endl;  
  }
   return 0;
}
```

```cpp
#include <iostream>
using namespace std;
 
int main ()
{
   // 局部变量声明
   int a = 10;
   // while 循环执行
   while( a < 20 )
   {
       cout << "a 的值：" << a << endl;
       a++;
   }
   do
   {
       cout << "a 的值：" << a << endl;
       a = a + 1;
   }while( a < 20 );
   return 0;
}
```

```c++
for (int i = 0; i < 10; i++) {
    if (i == 5) break;
    //if (i == 5) continue;
    cout << i << " ";
}
```

### 📌 调用函数

```cpp
#include <iostream>
using namespace std;
 
int sum(int a, int b)
{
  int result;
 
  result = a + b;
  
  return (result);
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
```
