## C++数据结构

### 📌 数组（Array）

```c++
int arr[5] = {1, 2, 3, 4, 5};
cout << arr[0]; // 输出第一个元素
```

📌 **动态数组（Vector）**

`vector` 是 C++ 标准库提供的动态数组实现，可以动态扩展容量，支持随机访问。

**特点**：

- 动态调整大小。
- 支持随机访问，时间复杂度为 O(1)。

```C++
vector<int> v1;  []            // 空vector
vector<int> v2(5);           // 含5个元素，默认值0
vector<int> v3(5, 10);       // 含5个元素，每个都是10
vector<int> v4 = {1, 2, 3};  // 初始化列表

v1.push_back(10);       // 尾部添加
v1.pop_back();          // 删除最后一个
v.insert(v.begin()+2, 5); // 在第3个位置插入 5
v.erase(v.begin()+1);  // 删除第2个元素
v.clear(); 
cout << v4[0]; // 输出 1
```

### 📌 **结构体（Struct**)

```c++
struct Person {
    string name;
    int age;
};
Person p = {"Alice", 25};
cout << p.name << endl; // 输出 Alice
```

### 📌 **类（Class）**

```c++
class Person {
public:
    Person(string n, int a) {
      name=n;
      age=a;
    }
    void printInfo() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
private:
    string name;
    int age;
};

Person p("Bob", 30);
p.printInfo(); // 输出: Name: Bob, Age: 30
```

### 📌 **链表（Linked List）**

```c++
struct Node {
    int data;
    Node* next;
};
Node* head = nullptr;
Node* newNode = new Node{10, nullptr};
Node* newNode2 = new Node{10, nullptr};
head = newNode; // 插入新节点
head.next = newNode2;

list<int> l1;                // 空list
list<int> l2(5);             // 5个元素，默认值0
list<int> l3(5, 10);         // 5个元素，每个是10
list<int> l4 = {1, 2, 3, 4}; // 初始化列表

l.push_back(10);        // 尾部添加
l.push_front(20);       // 头部添加
l.pop_back();           // 删除最后一个
l.pop_front();          // 删除第一个

auto it = l.begin();    // 迭代器
++it;
l.insert(it, 15);       // 在第2个位置插入15
l.erase(it);            // 删除第2个位置的元素

l.clear();              // 清空

```

### 📌 **栈（Stack）**

栈是一种后进先出（LIFO, Last In First Out）的数据结构，常用于递归、深度优先搜索等场景。

**特点**：

- 只允许在栈顶进行插入和删除操作。
- 时间复杂度为 O(1)。

```c++
#include<iostream>
using namespace std;
int main(){
   stack<double> s1;
   s1.push(1.0);
   s1.push(2.0);
   s1.push(3.0);
   s1.push(4.0);
   cout<<s1.top()<<endl;
   s1.pop();
   cout<<s1.top()<<endl;
   return 0;
}
```

### 📌 **队列（Queue）**

队列是一种先进先出（FIFO, First In First Out）的数据结构，常用于广度优先搜索、任务调度等场景。

**特点**：

- 插入操作在队尾进行，删除操作在队头进行。
- 时间复杂度为 O(1)。

```c++
#include<iostream>
#include<queue>
#include<string>
using namespace std;
int main(){
   queue<string> str;
   str.push("apple");
   str.push("orange");
   str.push("pineapple");
   cout<<str.front()<<endl;
   str.pop();
   cout<<str.size()<<endl;
   return 0;
}
```

### 📌 双端队列（Deque）

双端队列允许在两端进行插入和删除操作，是栈和队列的结合体。

**特点**：

- 允许在两端进行插入和删除。
- 时间复杂度为 O(1)。

```c++
#include<iostream>
#include<string>
#include<queue>
using namespace std;
int main(){
   deque<string> str;
   str.push_back("apple");
   str.push_front("orange");
   cout<<str.front()<<endl;
   str.pop_front();
   cout<<str.front()<<endl;
   return 0;
}
```

### 📌 **哈希表（Hash Table）**

哈希表是一种通过键值对存储数据的数据结构，支持快速查找、插入和删除操作。C++ 中的 `unordered_map` 是哈希表的实现。

**特点**：

- 使用哈希函数快速定位元素，时间复杂度为 O(1)。
- 不保证元素的顺序。

```c++
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
int main(){
   unordered_map<string,int>goods;
   goods["apple"]=10;
   goods["orange"]=5;
   cout<<goods["apple"]<<endl;
   cout<<goods.size();
   return 0;
}
```

### 📌 **映射（Map）**

`map` 是一种有序的键值对容器，底层实现是红黑树。与 `unordered_map` 不同，它保证键的顺序，查找、插入和删除的时间复杂度为 O(log n)。

**特点**：

- 保证元素按键的顺序排列。
- 使用二叉搜索树实现。

```c++
map<string, int> myMap;
myMap["a"] = 10;
myMap["b"] = 20;
cout << myMap ; // 输出 10
```

### 📌 **集合（Set**）

`set` 是一种用于存储唯一元素的有序集合，底层同样使用红黑树实现。它保证元素不重复且有序。

**特点**：

- 保证元素的唯一性。
- 元素自动按升序排列。
- 时间复杂度为 O(log n)。

```C++
#include<iostream>
#include<string>
#include<map>
#include<set>
using namespace std;
int main(){
   set<double>s1;
   s1.insert(1.0);
   s1.insert(3.0);
   s1.insert(2.0);
   for(auto iter=s1.begin();iter!=s1.end();iter++){
      cout<<*iter<<endl;
   }
   //cout<<*s1.begin()<<endl;
   //cout<<*s1.begin()+1<<endl;
   //cout<<*s1.begin()+2<<endl;
}
```

---

## C++ 类&对象

```c++
#include <iostream>
 
using namespace std;
 
class Box
{
   public:
      double length;   // 长度
      double breadth;  // 宽度
      double height;   // 高度
      // 成员函数声明
      double get(void);
      void set( double len, double bre, double hei );
};
// 成员函数定义
double Box::get(void)
{
    return length * breadth * height;
}
 
void Box::set( double len, double bre, double hei)
{
    length = len;
    breadth = bre;
    height = hei;
}
int main( )
{
   Box Box1;        // 声明 Box1，类型为 Box
   Box Box2;        // 声明 Box2，类型为 Box
   Box Box3;        // 声明 Box3，类型为 Box
   double volume = 0.0;     // 用于存储体积
 
   // box 1 详述
   Box1.height = 5.0; 
   Box1.length = 6.0; 
   Box1.breadth = 7.0;
 
   // box 2 详述
   Box2.height = 10.0;
   Box2.length = 12.0;
   Box2.breadth = 13.0;
 
   // box 1 的体积
   volume = Box1.height * Box1.length * Box1.breadth;
   cout << "Box1 的体积：" << volume <<endl;
 
   // box 2 的体积
   volume = Box2.height * Box2.length * Box2.breadth;
   cout << "Box2 的体积：" << volume <<endl;
 
 
   // box 3 详述
   Box3.set(16.0, 8.0, 12.0); 
   volume = Box3.get(); 
   cout << "Box3 的体积：" << volume <<endl;
   return 0;
}
```

1. #### C++类成员函数

类的成员函数是指那些把定义和原型写在类定义内部的函数

```c++
#include <iostream>
using namespace std;
class Box
{
   public:
      // 成员函数声明
      double getVolume(void);
      void setLength( double len );
      void setBreadth( double bre );
      void setHeight( double hei );
  private:
      double length;         // 长度
      double breadth;        // 宽度
      double height;         // 高度
};
 
// 成员函数定义
double Box::getVolume(void)
{
    return length * breadth * height;
}
 
void Box::setLength( double len )
{
    length = len;
}
 
void Box::setBreadth( double bre )
{
    breadth = bre;
}
 
void Box::setHeight( double hei )
{
    height = hei;
}
 
// 程序的主函数
int main( )
{
   Box Box1;                // 声明 Box1，类型为 Box
   Box Box2;                // 声明 Box2，类型为 Box
   double volume = 0.0;     // 用于存储体积
 
   // box 1 详述
   Box1.setLength(6.0); 
   Box1.setBreadth(7.0); 
   Box1.setHeight(5.0);
 
   // box 2 详述
   Box2.setLength(12.0); 
   Box2.setBreadth(13.0); 
   Box2.setHeight(10.0);
 
   // box 1 的体积
   volume = Box1.getVolume();
   cout << "Box1 的体积：" << volume <<endl;
 
   // box 2 的体积
   volume = Box2.getVolume();
   cout << "Box2 的体积：" << volume <<endl;
   return 0;
}
```

2. #### C++类访问修饰符

关键字 **public、private、protected** 称为访问修饰符。一个类可以有多个 public、protected 或 private 标记区域，访问限制目的主要是防止函数直接访问类类型的内部成员。

##### 2.1 公有（public）成员

**公有**成员在程序中类的外部是可直接访问的。

```c++
#include <iostream>
 
using namespace std;
 
class Line
{
   public:
      //double length;
      void setLength( double len );
      double getLength( void );
   private:
      double length;
};
 
// 成员函数定义
double Line::getLength(void)
{
    return length ;
}
 
void Line::setLength( double len )
{
    length = len;
}
 
// 程序的主函数
int main( )
{
   Line line;
 
   // 设置长度
   line.setLength(6.0); 
   cout << "Length of line : " << line.getLength() <<endl;
 
   // 不使用成员函数设置长度
   line.length = 10.0; // OK: 因为 length 是公有的
   cout << "Length of line : " << line.length <<endl;
   return 0;
}
```

##### 2.2 私有（private）成员

**私有**成员变量或函数在类的外部是不可访问的，甚至是不可查看的。一般会在**private**域定义数据，在**public**域定义相关的函数，以便在类的外部也可以调用这些函数。

```c++
#include <iostream>
 
using namespace std;
 
class Box
{
   public:
      double length;
      void setWidth( double wid );
      double getWidth( void );
 
   private:
      double width;
};
 
// 成员函数定义
double Box::getWidth(void)
{
    return width ;
}
 
void Box::setWidth( double wid )
{
    width = wid;
}
 
// 程序的主函数
int main( )
{
   Box box;
 
   // 不使用成员函数设置长度
   box.length = 10.0; // OK: 因为 length 是公有的
   cout << "Length of box : " << box.length <<endl;
 
   // 不使用成员函数设置宽度
   // box.width = 10.0; // Error: 因为 width 是私有的
   box.setWidth(10.0);  // 使用成员函数设置宽度
   cout << "Width of box : " << box.getWidth() <<endl;
 
   return 0;
}
```

##### 2.3 protected (受保护) 成员

**protected（受保护）**成员变量或函数与私有成员十分相似，但有一点不同，protected（受保护）成员在派生类（即子类）中是可访问的。例下例的父类 **Box** 派生了一个子类 **smallBox**。

```C++
#include <iostream>
using namespace std;
 
class Box
{
   protected:
      double width;
};
 
class SmallBox:Box // SmallBox 是派生类
{
   public:
      void setSmallWidth( double wid );
      double getSmallWidth( void );
};
 
// 子类的成员函数
double SmallBox::getSmallWidth(void)
{
    return width ;
}
 
void SmallBox::setSmallWidth( double wid )
{
    width = wid;
}
 
// 程序的主函数
int main( )
{
   SmallBox box;
 
   // 使用成员函数设置宽度
   box.setSmallWidth(5.0);
   cout << "Width of box : "<< box.getSmallWidth() << endl;
 
   return 0;
}
```

3. #### C++类构造函数&析构函数

##### 3.1 类的构造函数

类的**构造函数**是类的一种特殊的成员函数，它会在每次创建类的新对象时执行。

```c++
#include <iostream>
 
using namespace std;
 
class Line
{
   public:
      void setLength( double len );
      double getLength( void );
      Line(void);  // 这是不带参数的构造函数
      Line(double len);  // 这是带参数的构造函数
 
   private:
      double length;
};
 
// 成员函数定义，包括构造函数
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
 
Line::Line( double len)
{
    cout << "Object is being created, length = " << len << endl;
    length = len;
}
/*Line::Line( double len): length(len)
{
    cout << "Object is being created, length = " << len << endl;
}
*/

void Line::setLength( double len )
{
    length = len;
}
 
double Line::getLength( void )
{
    return length;
}
// 程序的主函数
int main( )
{
   //Line line;
   Line line(10.0);
   // 设置长度
   line.setLength(6.0); 
   cout << "Length of line : " << line.getLength() <<endl;
 
   return 0;
}
```

也可使用初始化列表来初始化字段：

```c++
Line::Line( double len): length(len)
{
    cout << "Object is being created, length = " << len << endl;
}
// 多个初始参数
C::C( double a, double b, double c): X(a), Y(b), Z(c)
{
  ....
}
```

##### 3.2 类的析构函数

类的**析构函数**是类的一种特殊的成员函数，它会在每次删除所创建的对象时执行，有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。

```C++
#include <iostream>
using namespace std;

class Line
{
   public:
      void setLength( double len );
      double getLength( void );
      Line();   // 这是构造函数声明
      ~Line();  // 这是析构函数声明
 
   private:
      double length;
};
 
// 成员函数定义，包括构造函数
Line::Line(void)
{
    cout << "Object is being created" << endl;
}
Line::~Line(void)
{
    cout << "Object is being deleted" << endl;
}
 
void Line::setLength( double len )
{
    length = len;
}
 
double Line::getLength( void )
{
    return length;
}
// 程序的主函数
int main( )
{
   Line line;
 
   // 设置长度
   line.setLength(6.0); 
   cout << "Length of line : " << line.getLength() <<endl;
 
   return 0;
}
```

4. #### C++拷贝构造函数

**拷贝构造函数**是使用同一类中之前创建的对象来初始化新创建的对象。

```c++
#include <iostream>
using namespace std;
class Line
{
   public:
      int getLength( void );
      void display(Line obj);
      Line( int len );             // 简单的构造函数
      Line( const Line &obj);      // 拷贝构造函数
      ~Line();                     // 析构函数
 
   private:
      int *ptr;
};
 
// 成员函数定义，包括构造函数
Line::Line(int len)
{
    cout << "调用构造函数" << endl;
    // 为指针分配内存
    ptr = new int;
    *ptr = len;
}
 
Line::Line(const Line &obj)
{
    cout << "调用拷贝构造函数并为指针 ptr 分配内存" << endl;
    ptr = new int;
    *ptr = *obj.ptr; // 拷贝值
}
 
Line::~Line(void)
{
    cout << "释放内存" << endl;
    delete ptr;
}
int Line::getLength( void )
{
    return *ptr;
}
 
void display(Line obj)
{
   cout << "line 大小 : " << obj.getLength() <<endl;
}
 
// 程序的主函数
int main( )
{
   Line line1(10);
 
   Line line2 = line1; // 这里也调用了拷贝构造函数
 
   display(line1);
   display(line2);
 
   return 0;
}
```

5. #### C++友元函数

友元函数有权访问类的所有私有（private）成员和保护（protected）成员。尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数。如果要声明函数为一个类的友元，需要在类定义中该函数原型前使用关键字 **friend**。

```c++
#include <iostream>
 
using namespace std;
 
class Box
{
private:
   double width;
public:
   friend void printWidth( Box box );
   void setWidth( double wid );
};
 
// 成员函数定义
void Box::setWidth( double wid )
{
    width = wid;
}
 
// 请注意：printWidth() 不是任何类的成员函数
void printWidth( Box box )
{
   /* 因为 printWidth() 是 Box 的友元，它可以直接访问该类的任何成员 */
   cout << "Width of box : " << box.width <<endl;
}
 
// 程序的主函数
int main( )
{
   Box box;
 
   // 使用成员函数设置宽度
   box.setWidth(10.0);
   
   // 使用友元函数输出宽度
   printWidth( box );
 
   return 0;
}
```

6. ##### C++内联函数

在 C++ 里，如果想把一个函数定义为内联函数，则需要在函数名前面放置关键字 **inline**，在类定义中的定义的函数都是内联函数。

```c++
inline int add(int a, int b) {
    return a + b;
}
```

编译器在调用 `add(x, y)` 时，**不会真的跳到函数地址去执行**，而是会在调用点 **直接把函数体的代码拷贝展开**。

所以：

```c++
int c = add(2, 3);
```

可能会在编译时直接变成：

```c++
int c = 2 + 3;
```

7. #### C++ this指针

在 C++ 中，**this** 指针是一个特殊的指针，它指向当前对象的实例。每一个对象都能通过 **this** 指针来访问自己的地址。它可以在类的成员函数中使用，它可以用来指向调用对象。

```c++
#include <iostream>
class MyClass {
private:
    int value;
 
public:
    void setValue(int val) {
        this->value = val;
    }
 
    void printValue() {
        std::cout << "Value: " << this->value << std::endl;
    }
};
 
int main() {
    MyClass obj;
    obj.setValue(42);
    obj.printValue();
 
    return 0;
}
```

```c++
#include <iostream>
 
using namespace std;
 
class Box
{
   public:
      // 构造函数定义
      Box(double l=2.0, double b=2.0, double h=2.0)
      {
         cout <<"调用构造函数。" << endl;
         length = l;
         breadth = b;
         height = h;
      }
      double Volume()
      {
         return length * breadth * height;
      }
      int compare(Box box)
      {
         return this->Volume() > box.Volume();
      }
   private:
      double length;     // 宽度
      double breadth;    // 长度
      double height;     // 高度
};
 
int main(void)
{
   Box Box1(3.3, 1.2, 1.5);    // 声明 box1
   Box Box2(8.5, 6.0, 2.0);    // 声明 box2
 
   if(Box1.compare(Box2))
   {
      cout << "Box1 的体积比 Box2 大" <<endl;
   }
   else
   {
      cout << "Box2 的体积大于或等于 Box1" <<endl;
   }
   return 0;
}
```

8. #### C++ 指向类的指针

8.1 声明和初始化指向类的指针

```c++
#include <iostream>

class MyClass {
public:
    int data;

    void display() {
        std::cout << "Data: " << data << std::endl;
    }
};

int main() {
    // 创建类对象
    MyClass obj;
    obj.data = 42;

    // 声明和初始化指向类的指针
    MyClass *ptr = &obj;

    // 通过指针访问成员变量
    std::cout << "Data via pointer: " << ptr->data << std::endl;

    // 通过指针调用成员函数
    ptr->display();

    return 0;
}
```

8.2 **动态分配内存**

```c++
//指向类的指针还可以用于动态分配内存，创建类的对象：
#include <iostream>

class MyClass {
public:
    int data;

    void display() {
        std::cout << "Data: " << data << std::endl;
    }
};

int main() {
    // 动态分配内存创建类对象
    MyClass *ptr = new MyClass;
    ptr->data = 42;

    // 通过指针调用成员函数
    ptr->display();

    // 释放动态分配的内存
    delete ptr;

    return 0;
}
```

8.3 **指向类的指针作为函数参数**

```c++
#include <iostream>

class MyClass {
public:
    int data;

    void display() {
        std::cout << "Data: " << data << std::endl;
    }
};

// 函数接受指向类的指针作为参数
void processObject(MyClass *ptr) {
    ptr->display();
}

int main() {
    MyClass obj;
    obj.data = 42;

    // 将指向类的指针传递给函数
    processObject(&obj);

    return 0;
}
```

9. C++类的静态成员

9.1 **静态成员**在类的所有对象中是共享的，默认所有的静态数据都会被初始化为零。

```c++
#include <iostream>
 
using namespace std;
 
class Box
{
   public:
      static int objectCount;
      // 构造函数定义
      Box(double l=2.0, double b=2.0, double h=2.0)
      {
         cout <<"Constructor called." << endl;
         length = l;
         breadth = b;
         height = h;
         // 每次创建对象时增加 1
         objectCount++;
      }
      double Volume()
      {
         return length * breadth * height;
      }
   private:
      double length;     // 长度
      double breadth;    // 宽度
      double height;     // 高度
};
 
// 初始化类 Box 的静态成员
int Box::objectCount = 0;
 
int main(void)
{
   Box Box1(3.3, 1.2, 1.5);    // 声明 box1
   Box Box2(8.5, 6.0, 2.0);    // 声明 box2
 
   // 输出对象的总数
   cout << "Total objects: " << Box::objectCount << endl;
 
   return 0;
}
```

9.2 **静态函数**只要使用类名加范围解析运算符 **::** 就可以访问。

**静态成员函数与普通成员函数的区别：**

- 静态成员函数没有 this 指针，只能访问静态成员（包括静态成员变量和静态成员函数）。
- 普通成员函数有 this 指针，可以访问类中的任意成员；而静态成员函数没有 this 指针。

```c++
#include <iostream>
 
using namespace std;
 
class Box
{
   public:
      static int objectCount;
      // 构造函数定义
      Box(double l=2.0, double b=2.0, double h=2.0)
      {
         cout <<"Constructor called." << endl;
         length = l;
         breadth = b;
         height = h;
         // 每次创建对象时增加 1
         objectCount++;
      }
      double Volume()
      {
         return length * breadth * height;
      }
      static int getCount()
      {
         return objectCount;
      }
   private:
      double length;     // 长度
      double breadth;    // 宽度
      double height;     // 高度
};
 
// 初始化类 Box 的静态成员
int Box::objectCount = 0;
 
int main(void)
{
  
   // 在创建对象之前输出对象的总数
   cout << "Inital Stage Count: " << Box::getCount() << endl;
 
   Box Box1(3.3, 1.2, 1.5);    // 声明 box1
   Box Box2(8.5, 6.0, 2.0);    // 声明 box2
 
   // 在创建对象之后输出对象的总数
   cout << "Final Stage Count: " << Box::getCount() << endl;
 
   return 0;
}
```

