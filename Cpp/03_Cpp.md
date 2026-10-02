## C++ STL教程（Standard Template Library）

STL是一套功能强大的 C++ 模板类和函数的集合，它提供了一系列通用的、可复用的算法和数据结构。

STL可分为多个组件，包括容器「向量（vector）、链表（list）、队列（queue）、栈（stack）、集合（set）、映射（map）」、迭代器「迭代器用于遍历容器中的元素」、算法「容器操作算法，例排序、搜索、复制、移动、变换等。」、函数对象「一元函数对象、二元函数对象等」和适配器等。

```c++
#include <iostream>
#include <vector>

using namespace std;

int main()
{
   // 创建一个向量存储 int
   vector<int> vec; 
   int i;
 
   // 显示 vec 的原始大小
   cout << "vector size = " << vec.size() << endl;
 
   // 推入 5 个值到向量中
   for(i = 0; i < 5; i++){
      vec.push_back(i);
   }
 
   // 显示 vec 扩展后的大小
   cout << "extended vector size = " << vec.size() << endl;
 
   // 访问向量中的 5 个值
   for(i = 0; i < 5; i++){
      cout << "value of vec [" << i << "] = " << vec[i] << endl;
   }
 
   // 使用迭代器 iterator 访问值
   vector<int>::iterator v = vec.begin();
   while( v != vec.end()) {
      cout << "value of v = " << *v << endl;
      v++;
   }
   return 0;
}
```

### 📌 C++ 导入标准库

```c++
#include <iostream>  // 导入输入输出流库
#include <vector>    // 导入向量容器库
#include <cmath>     // 导入数学函数库
```

- `<iostream>`：提供了输入输出流的功能，如`std::cout`和`std::cin`。
- `<vector>`：提供了向量容器的实现，用于存储动态数组。
- `<cmath>`：提供了常用的数学函数，如`sqrt()`、`sin()`、`cos()`等。

### 📌 template 模版

函数模板能写出可以处理任意类型的函数。

```cpp
#include <iostream>
using namespace std;

// 定义一个函数模板
template <typename T>
T add(T a, T b) {
    return a + b;
}

int add(){}
float add(){}
double add(){}

int main() {
    cout << add(3, 5) << endl;      // int
    cout << add(3.2, 4.8) << endl;  // double
    cout << add<string>("Hi, ", "C++") << endl; // string
}

```

✅ 好处：不用写 `int add(int,int)`、`double add(double,double)` 等重复代码。

### 📌 C++ 标准库

<iostream>: 标准输入输出流
<fstream>: 文件输入输出流
<sstream>: 字符串流
<array>: 定长数组容器
**<vector>: 动态数组容器**
**<deque>: 双端队列容器**
**<list>: 双向链表容器**
<forward_list>: 单向链表容器
<stack>: 栈容器适配器
<queue>: 队列容器适配器
**<set>: 集合容器（基于平衡二叉树）**
<unordered_set>: 无序集合容器（基于哈希表）
**`<map>`: 映射容器（键值对，基于平衡二叉树）**
**<unordered_map>: 无序映射容器（基于哈希表）  
<bitset>: 二进制位容器**
<algorithm>: 常用算法（如排序、查找等）
<iterator>: 迭代器
<numeric>: 数值操作（如累计、乘积等）
<complex>: 复数运算
<valarray>: 数组类及相关操作
<cmath>: 数学函数
<string>: 标准字符串类
<regex>: 正则表达式

`#include <bits/stdc++.h>`在很多 **竞赛代码（比如 USACO、Codeforces）** 里很常见，它是一次性把 C++ 标准库里几乎所有常用头文件都包含进来，缺点**编译慢**，因为它导入了几乎所有库。

### 📌  `priority_queue`

优先队列是一种特殊的队列，它允许我们快速访问队列中具有最高（或最低）优先级的元素。

```c++
#include <queue>

// 声明一个整型优先队列
priority_queue<int> pq;

// 声明一个自定义类型的优先队列，需要提供比较函数
struct compare {
    bool operator()(int a, int b) {
        return a > b; // 这里定义了最小堆
    }
};
priority_queue<int, vector<int>, compare> pq_min;
```

- `empty()`: 检查队列是否为空。
- `size()`: 返回队列中的元素数量。
- `top()`: 返回队列顶部的元素（不删除它）。
- `push()`: 向队列添加一个元素。
- `pop()`: 移除队列顶部的元素。

```cpp
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
```

```cpp
//最小堆
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
struct compare{
   bool operator()(int a,int b){
      return a>b;
   }
};
int main(){
   priority_queue<int,vector<int>,compare>pq_min;
   pq_min.push(4);
   pq_min.push(3);
   pq_min.push(2);
   pq_min.push(1);
   cout<<pq_min.top()<<endl;
   pq_min.pop();
   cout<<pq_min.top()<<endl;
   return 0;
}
```

### 📌 C++ 标准库 `<iterator>`

```cpp
#include <iostream>
#include <vector>
#include <iterator>

int main() {
    // 创建一个 vector 容器并初始化
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用迭代器遍历 vector
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用 auto 关键字简化迭代器类型
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用 C++11 范围 for 循环
    for (int elem : vec) {
        std::cout << elem << " ";
    }
    //
    std::cout << std::endl;
    return 0;
}
```

### 📌 C++ 标准库 `<cmath>`

| 函数         | 功能                       | 示例                    |
| :----------- | :------------------------- | :---------------------- |
| **`abs(x)`** | 计算整数 `x` 的绝对值      | `abs(-5) // 5`          |
| `fabs(x)`    | 计算浮点数 `x` 的绝对值    | `fabs(-5.5) // 5.5`     |
| `fmod(x, y)` | 计算 `x` 除以 `y` 的余数   | `fmod(5.3, 2) // 1.3`   |
| `fmax(x, y)` | 返回 `x` 和 `y` 中的较大值 | `fmax(3.5, 4.2) // 4.2` |
| `fmin(x, y)` | 返回 `x` 和 `y` 中的较小值 | `fmin(3.5, 4.2) // 3.5` |
| **`sqrt(x)`** | 计算 `x` 的平方根          | `sqrt(16) // 4`         |
| `cbrt(x)`    | 计算 `x` 的立方根          | `cbrt(27) // 3`         |
| `sin(x)` | 计算 `x` 的正弦值，`x` 以弧度为单位 | `sin(3.14159 / 2) // 1` |
| `cos(x)` | 计算 `x` 的余弦值，`x` 以弧度为单位 | `cos(3.14159) // -1`    |
| `tan(x)` | 计算 `x` 的正切值，`x` 以弧度为单位 | `tan(0) // 0`           |
| **`ceil(x)`** | 返回不小于 `x` 的最小整数 | `ceil(2.3) // 3`  |
| **`floor(x)`** | 返回不大于 `x` 的最大整数 | `floor(2.3) // 2` |

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
   int a=-1;
   cout<<abs(a)<<endl;
   int b=4;
   cout<<sqrt(b)<<endl;
   float c=2.3,d=2.4;
   cout<<ceil(2.3)<<" "<<floor(d)<<endl;
   int f=4,g=2;
   cout<<pow(f,g)<<endl;
   return 0;
}
```

### 📌 C++ 标准库 `<deque>`

```c++
#include <iostream>
#include <deque>

int main() {
    std::deque<int> myDeque;

    // 插入元素
    myDeque.push_back(10);
    myDeque.push_back(20);
    myDeque.push_front(5);

    // 访问元素
    std::cout << "Deque contains: ";
    for (int i = 0; i < myDeque.size(); ++i) {
        std::cout << myDeque[i] << " ";
    }
    std::cout << std::endl;

    // 删除元素
    myDeque.pop_back();
    myDeque.pop_front();

    // 再次访问元素
    std::cout << "Deque after popping: ";
    for (int i = 0; i < myDeque.size(); ++i) {
        std::cout << myDeque[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

```c++
#include <iostream>
#include <deque>

int main() {
    std::deque<int> d;

    // 向双端队列中添加元素
    d.push_back(10);
    d.push_back(20);
    d.push_front(5);

    // 访问前端元素
    std::cout << "Front element: " << d.front() << std::endl;

    // 访问后端元素
    std::cout << "Back element: " << d.back() << std::endl;

    // 修改前端元素
    d.front() = 15;

    // 修改后端元素
    d.back() = 25;

    // 再次访问元素
    std::cout << "Modified front element: " << d.front() << std::endl;
    std::cout << "Modified back element: " << d.back() << std::endl;

    return 0;
}
```

### 📌 C++ 标准库 `<list>`

```c++
#include <iostream>
#include <list>

int main() {
    std::list<int> numbers1;                  // 空的list
    std::list<int> numbers2(5);               // 包含5个默认初始化元素的list
    std::list<int> numbers3(5, 10);           // 包含5个元素，每个元素为10
    std::list<int> numbers4 = {1, 2, 3, 4};   // 使用初始化列表
    
    // 创建一个整数类型的列表
    std::list<int> numbers;

    // 向列表中添加元素
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    // 访问并打印列表的第一个元素
    std::cout << "First element: " << numbers.front() << std::endl;

    // 访问并打印列表的最后一个元素
    std::cout << "Last element: " << numbers.back() << std::endl;

    // 遍历列表并打印所有元素
    std::cout << "List elements: ";
    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 删除列表中的最后一个元素
    numbers.pop_back();

    // 再次遍历列表并打印所有元素
    std::cout << "List elements after removing the last element: ";
    for (std::list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

| 函数                        | 说明                      |
| :-------------------------- | :------------------------ |
| `push_back(const T& val)`   | 在链表末尾添加元素        |
| `push_front(const T& val)`  | 在链表头部添加元素        |
| `pop_back()`                | 删除链表末尾的元素        |
| `pop_front()`               | 删除链表头部的元素        |
| `insert(iterator pos, val)` | 在指定位置插入元素        |
| `erase(iterator pos)`       | 删除指定位置的元素        |
| `clear()`                   | 清空所有元素              |
| `size()`                    | 返回链表中的元素数量      |
| `empty()`                   | 检查链表是否为空          |
| `front()`                   | 返回链表第一个元素        |
| `back()`                    | 返回链表最后一个元素      |
| `remove(const T& val)`      | 删除所有等于指定值的元素  |
| `sort()`                    | 对链表中的元素进行排序    |
| `merge(list& other)`        | 合并另一个已排序的链表    |
| `reverse()`                 | 反转链表                  |
| `begin()` / `end()`         | 返回链表的起始/结束迭代器 |

**1、基本操作**

```c++
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {10, 20, 30};

    // 插入和删除元素
    lst.push_front(5);           // 在头部插入5
    lst.push_back(40);           // 在尾部插入40
    lst.pop_front();             // 删除头部元素
    lst.pop_back();              // 删除尾部元素

    // 输出链表内容
    std::cout << "List elements: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**2、插入和删除特定位置的元素**

```c++
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};
    auto it = lst.begin();
    std::advance(it, 2);          // 移动迭代器到第3个元素（值为3）

    lst.insert(it, 10);           // 在第3个元素前插入10
    lst.erase(it);                // 删除第3个元素

    // 输出链表内容
    std::cout << "List elements: ";
    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**3、排序和去重**

```c++
#include<iostream>
#include<list>
using namespace std;
int main(){
   list<int>l1={1,2,3,5,4,4};
   l1.sort();
   l1.unique();
   for(list<int>::iterator iter=l1.begin();iter!=l1.end();iter++){
      cout<<*iter<<" ";
   }
   cout<<endl;
   return 0;
}
```

**4、合并和反转**

```c++
#include <iostream>
#include <list>

int main() {
    std::list<int> lst1 = {1, 3, 5, 7};
    std::list<int> lst2 = {2, 4, 6, 8};

    lst1.merge(lst2);              // 合并两个已排序的链表
    lst1.reverse();                // 反转链表

    // 输出链表内容
    std::cout << "Merged and reversed list: ";
    for (const auto& elem : lst1) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

| 特性              | `std::list`                  | `std::vector`                | `std::deque`                 |
| :---------------- | :--------------------------- | :--------------------------- | :--------------------------- |
| **内存结构**      | 非连续内存，双向链表         | 连续内存                     | 分段连续内存                 |
| **访问性能**      | 顺序访问较快，随机访问慢     | 随机访问快                   | 末尾和头部访问都快           |
| **插入/删除性能** | 任意位置插入、删除快         | 末尾插入快，中间位置慢       | 头尾插入、删除快             |
| **适用场景**      | 频繁在中间插入/删除          | 需要高效随机访问             | 需要在头尾快速插入/删除      |
| **迭代器稳定性**  | 稳定，元素插入或删除不会失效 | 插入、删除可能导致迭代器失效 | 插入、删除可能导致迭代器失效 |

***

Lumos.

### 📌 C++ 标准库 `<map>`

`map` 容器中的元素是按照键的顺序自动排序的，这使得它非常适合需要快速查找和有序数据的场景。

```c++
#include <iostream>#include <map>
#include <string>

int main() {
    // 创建一个 map 容器，存储员工的姓名和年龄
    std::map<std::string, int> employees;

    // 插入员工信息
    employees["Alice"] = 30;
    employees["Bob"] = 25;
    employees["Alicf"] = 30;
    employees["Charlie"] = 35;

    // 遍历 map 并打印员工信息
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        std::cout << it->first << " is " << it->second << " years old." << std::endl;
    }

    return 0;
}
```

map 是 C++ STL 中一个非常有用的容器，特别适合需要快速查找和有序数据的场景。

```c++
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> scores;

    // 插入
    scores["Alice"] = 90;
    scores["Bob"] = 85;
    scores.insert({"Charlie", 92});

    // 遍历
    for (auto &p : scores) {
        std::cout << p.first << " => " << p.second << std::endl;
    }

    // 查找
    auto it = scores.find("Bob");
    if (it != scores.end()) {
        std::cout << "Bob's score: " << it->second << std::endl;
    }

    // 删除
    scores.erase("Alice");

    std::cout << "Size: " << scores.size() << std::endl;

    return 0;
}
```

### 📌 **C++ 标准库 `<bitset>`** 

位集合是一个由位（bit）组成的数组，每个位可以是 0 或 1。

```C++
std::bitset<8> bits1;               // 默认初始化：00000000
std::bitset<8> bits2(42);           // 从整数初始化：00101010 
std::bitset<8> bits3("10101010");   // 从字符串初始化：10101010 

std::bitset<8> bits("00001111");
bits[0] = 1;          // 修改第 0 位：00001111 -> 00001111
bits.set(4);          // 设置第 4 位：00001111 -> 00011111
bits.reset(1);        // 重置第 1 位：00011111 -> 00011101
bits.flip();          // 翻转所有位：00011101 -> 11100010
```

- `count()`：返回 `1` 的个数。
- `size()`：返回位数。
- `test(pos)`：检查某一位是否为 `1`。
- `all()`：检查是否所有位都为 `1`。
- `any()`：检查是否有任何一位为 `1`。
- `none()`：检查是否所有位都为 `0`。

```c++
std::bitset<8> bits("10101010");
std::cout << "Count of 1s: " << bits.count() << std::endl;  // 输出 4
std::cout << "Size: " << bits.size() << std::endl;          // 输出 8
std::cout << "Is bit 3 set? " << bits.test(3) << std::endl; // 输出 1 (true)
std::cout << "All bits set? " << bits.all() << std::endl;   // 输出 0 (false)
```

- `to_ulong()`：将 `std::bitset` 转换为 `unsigned long`。
- `to_ullong()`：将 `std::bitset` 转换为 `unsigned long long`。
- `to_string()`：将 `std::bitset` 转换为字符串。

```c++
std::bitset<8> bits("10101010");
unsigned long num = bits.to_ulong();  // 转换为整数：170
std::string str = bits.to_string();   // 转换为字符串："10101010"
```

### 位操作

- `&`：按位与
- `|`：按位或
- `^`：按位异或
- `~`：按位取反

```c++
std::bitset<8> bits1("10101010");
std::bitset<8> bits2("11110000");

std::bitset<8> result_and = bits1 & bits2;  // 按位与：10100000
std::bitset<8> result_or = bits1 | bits2;   // 按位或：11111010
std::bitset<8> result_xor = bits1 ^ bits2;  // 按位异或：01011010
std::bitset<8> result_not = ~bits1;         // 按位取反：01010101
```

```c++
#include <iostream>
#include <bitset>

int main() {
    std::bitset<8> b("11001010"); // 从字符串初始化
    std::cout << "Initial bitset: " << b << std::endl;

    // 访问特定位置的位
    std::cout << "Bit at position 3: " << b[3] << std::endl;

    // 修改位
    b[3] = 1;
    std::cout << "Modified bitset: " << b << std::endl;

    // 翻转位
    b.flip();
    std::cout << "Flipped bitset: " << b << std::endl;

    return 0;
}
```

```c++
#include <iostream>
#include <bitset>

int main() {
    std::bitset<8> b("10101010");

    // 循环遍历bitset中的位
    for (auto i = 0; i < b.size(); ++i) {
        std::cout << b[i];
    }
    std::cout << std::endl;

    return 0;
}
```

### 📌 C++ 标准库 `<string>`

## 常用成员函数

`std::string` 类提供了许多成员函数来操作字符串，以下是一些常用的成员函数：

- `size()`：返回字符串的长度。
- `empty()`：检查字符串是否为空。
- `operator[]`：通过索引访问字符串中的字符。
- `substr()`：获取子字符串。
- `find()`：查找子字符串在主字符串中的位置。
- `replace()`：替换字符串中的某些字符。

```c++
#include <iostream>
#include <string>

int main() {
    // 声明并初始化字符串
    std::string greeting = "Hello, World!";
    std::cout << "Greeting: " << greeting << std::endl;

    // 使用 size() 获取字符串长度
    std::cout << "Length of the greeting: " << greeting.size() << std::endl;

    // 使用 empty() 检查字符串是否为空
    std::cout << "Is the greeting empty? " << (greeting.empty() ? "Yes" : "No") << std::endl;

    // 使用 operator[] 访问特定位置的字符
    std::cout << "Character at position 7: " << greeting[7] << std::endl;

    // 使用 substr() 获取子字符串
    std::string sub = greeting.substr(7, 5);
    std::cout << "Substring from position 7 with length 5: " << sub << std::endl;

    // 使用 find() 查找子字符串
    std::cout << "Position of 'World' in the greeting: " << greeting.find("World") << std::endl;

    // 使用 replace() 替换字符串中的部分内容
    // 替换 'World' 为 'C++'
    std::string modified = greeting;
    std::string::size_type pos = modified.find("World");
    if (pos != std::string::npos) { // std::string::npos 是 一个特殊常量，表示 “未找到”
        modified.replace(pos, 5, "C++"); // 从位置 pos 开始，替换 5 个字符为 "C++"
    }
    std::cout << "Modified greeting: " << modified << std::endl;

    return 0;
}
```

| 函数名                | 描述                                           | 示例代码                                       |
| :-------------------- | :--------------------------------------------- | :--------------------------------------------- |
| `size()`              | 返回字符串的长度（字符数）。                   | `std::cout << str.size();`                     |
| `length()`            | 与 `size()` 相同，返回字符串的长度。           | `std::cout << str.length();`                   |
| `empty()`             | 判断字符串是否为空。                           | `std::cout << (str.empty() ? "Yes" : "No");`   |
| `operator[]`          | 访问字符串中指定位置的字符。                   | `std::cout << str[0];`                         |
| `at()`                | 访问字符串中指定位置的字符（带边界检查）。     | `std::cout << str.at(0);`                      |
| **`substr()`**        | 返回从指定位置开始的子字符串。                 | `std::string sub = str.substr(0, 5);`          |
| `find()`              | 查找子字符串在字符串中的位置。                 | `std::cout << str.find("sub") << std::endl;`   |
| `rfind()`             | 从字符串末尾开始查找子字符串的位置。           | `std::cout << str.rfind("sub") << std::endl;`  |
| `replace()`           | 替换字符串中的部分内容。                       | `str.replace(pos, length, "new_substring");`   |
| `append()`            | 在字符串末尾添加内容。                         | `str.append(" more");`                         |
| `insert()`            | 在指定位置插入内容。                           | `str.insert(pos, "inserted");`                 |
| `erase()`             | 删除指定位置的字符或子字符串。                 | `str.erase(pos, length);`                      |
| `clear()`             | 清空字符串。                                   | `str.clear();`                                 |
| `c_str()`             | 返回 C 风格的字符串（以 null 结尾）。          | `const char* cstr = str.c_str();`              |
| `data()`              | 返回指向字符数据的指针（C++11 及之后的版本）。 | `const char* data = str.data();`               |
| `compare()`           | 比较两个字符串。                               | `int result = str.compare("other");`           |
| `find_first_of()`     | 查找第一个匹配任意字符的位置。                 | `size_t pos = str.find_first_of("aeiou");`     |
| `find_last_of()`      | 查找最后一个匹配任意字符的位置。               | `size_t pos = str.find_last_of("aeiou");`      |
| `find_first_not_of()` | 查找第一个不匹配任意字符的位置。               | `size_t pos = str.find_first_not_of("aeiou");` |
| `find_last_not_of()`  | 查找最后一个不匹配任意字符的位置。             | `size_t pos = str.find_last_not_of("aeiou");`  |

```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, World!";
    
    // size()
    std::cout << "Length: " << str.size() << std::endl;

    // empty()
    std::cout << "Is empty? " << (str.empty() ? "Yes" : "No") << std::endl;

    // operator[]
    std::cout << "First character: " << str[0] << std::endl;

    // at()
    std::cout << "Character at position 7: " << str.at(7) << std::endl;

    // substr()
    std::string sub = str.substr(7, 5);
    std::cout << "Substring from position 7 with length 5: " << sub << std::endl;

    // find()
    size_t pos = str.find("World");
    std::cout << "Position of 'World': " << pos << std::endl;

    // replace()
    str.replace(pos, 5, "C++");
    std::cout << "Modified string: " << str << std::endl;

    // append()
    str.append(" How are you?");
    std::cout << "Appended string: " << str << std::endl;

    // insert()
    str.insert(7, " Beautiful");
    std::cout << "String after insert: " << str << std::endl;

    // erase()
    str.erase(7, 10);
    std::cout << "String after erase: " << str << std::endl;

    // clear()
    str.clear();
    std::cout << "String after clear: " << (str.empty() ? "Empty" : "Not empty") << std::endl;

    // c_str()
    str = "Hello, C++!";
    const char* cstr = str.c_str();
    std::cout << "C-style string: " << cstr << std::endl;

    // compare()
    int cmp = str.compare("Hello, C++!");
    std::cout << "Comparison result: " << cmp << std::endl;

    // find_first_of()
    size_t pos_first_vowel = str.find_first_of("aeiou");
    std::cout << "First vowel at position: " << pos_first_vowel << std::endl;

    // find_last_of()
    size_t pos_last_vowel = str.find_last_of("aeiou");
    std::cout << "Last vowel at position: " << pos_last_vowel << std::endl;

    // find_first_not_of()
    size_t pos_first_non_vowel = str.find_first_not_of("aeiou");
    std::cout << "First non-vowel at position: " << pos_first_non_vowel << std::endl;

    // find_last_not_of()
    size_t pos_last_non_vowel = str.find_last_not_of("aeiou");
    std::cout << "Last non-vowel at position: " << pos_last_non_vowel << std::endl;

    return 0;
}
```

### **📌 C++ 标准库 `<utility>`** 

`<utility>` 头文件定义了多种工具类和函数，它们主要用于简化编程任务，提高代码的可读性和可维护性，这些工具类和函数包括：

- `pair`：一个包含两个元素的容器，通常用于存储和返回两个相关联的值。
- `make_pair`：一个函数模板，用于创建 `pair` 对象。
- `swap`：一个函数模板，用于交换两个对象的值。
- `forward` 和 `move`：用于完美转发和移动语义的函数模板。

#### 使用 pair 和 make_pair

```c++
#include <iostream>
#include <utility>
using namespace std;

int main() {
    pair<int, string> p(1, "hello");
    //tuple<int, string, double> t(1, "hello", 3.14);
    cout << p.first << " " << p.second << endl; // 1 hello
}
```

```c++
auto p = make_pair(1, "hello"); // 类型自动推导成 pair<int, const char*>
cout << p.first << " " << p.second << endl;
```

### 使用 swap 函数

```c++
#include <iostream>
#include <utility>
int main() {
    int a = 5;
    int b = 10;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    // 使用 swap 函数交换 a 和 b 的值
    std::swap(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
    return 0;
}
```

### 使用 move 函数

```c++
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = std::move(v1);
    std::cout << "v1 size: " << v1.size() << std::endl; // v1 现在为空
    std::cout << "v2 size: " << v2.size() << std::endl; // v2 拥有 v1 的元素
    return 0;
}
```

### **📌 low_bound和upper_bound**

```
#include <algorithm>
```

默认按升序查找：

| 函数                         | 找到的位置                     |
| ---------------------------- | ------------------------------ |
| `lower_bound(begin, end, x)` | 第一个 **大于等于 `x`** 的元素 |
| `upper_bound(begin, end, x)` | 第一个 **大于 `x`** 的元素     |

查找范围是 **`[begin, end)`**：包含 `begin`，不包含 `end`。找不到时返回 `end`。

### 1. 普通数组

```C++
int a[] = {1, 2, 2, 2, 4, 6};
int n = 6;

int l = lower_bound(a, a + n, 2) - a;
int r = upper_bound(a, a + n, 2) - a;

cout << l << '\n';  // 1：第一个 >= 2 的元素下标
cout << r << '\n';  // 4：第一个 > 2 的元素下标
```

**函数返回的是位置（指针或迭代器），减去起始位置才能得到下标。**

### 2. vector

```c++
vector<int> a = {1, 2, 2, 2, 4, 6};

auto it = lower_bound(a.begin(), a.end(), 2);

int index = it - a.begin();  // 下标：1

if (it != a.end()) {
    cout << *it;            // 元素值：2
}
```

`upper_bound` 的写法相同：

```c++
auto it = upper_bound(a.begin(), a.end(), 2);
// it 指向 4
```

### 3. 找不到时

```c++
int index = lower_bound(a.begin(), a.end(), 10) - a.begin();
// index == a.size()
```

此时返回的是尾后位置，**不能用 `a[index]` 或 `*it` 读取元素**。

对于普通数组和 `vector`，两者的查找时间复杂度都是 **`O(log n)`**。

总结：**lower 找 `>=`，upper 找 `>`。**