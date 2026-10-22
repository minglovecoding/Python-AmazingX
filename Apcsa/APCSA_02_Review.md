## APCSA 第二轮复习 02：类、对象、方法与字符串

## 📚 1. 学习目标

- 分清类、对象和引用变量；能画出“变量指向哪个对象”。
- 根据参数个数、类型和顺序选择构造器及方法。
- 解释构造器、普通方法、`void` 方法和有返回值方法的区别。
- 区分修改对象内容、给引用变量重新赋值，以及修改不可变字符串。
- 熟练使用 `length`、`substring`、`indexOf`、`equals`、`compareTo`。
- 从调用示例反推字段、构造器和方法，在 FRQ 中写完整实现。

## 2. 核心知识与易错点

### 2.1 类、对象、引用变量

```java
public class Puppy {
    private String name;
    private int age;

    public Puppy(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() { return name; }
    public int getAge() { return age; }
    public void setAge(int age) { this.age = age; }
}
```

```java
// 放在另一个类的 main 中：
Puppy pet = new Puppy("Tommy", 2);
```

| 部分 | 含义 |
| --- | --- |
| `Puppy` | 类/引用类型 |
| `pet` | 引用变量，保存对对象的引用 |
| `new Puppy("Tommy", 2)` | 创建对象并调用匹配的构造器 |
| `name`、`age` | 每个对象自己的实例字段 |
| `pet.getAge()` | 调用 pet 指向的对象的方法 |

`Puppy pet;` 只声明局部引用变量，并没有创建对象，也没有为它赋值。`Puppy pet = null;` 则已经赋值，但没有指向对象。

### 2.2 构造器：没有返回类型

构造器与类同名，不写 `void`，也不写其他返回类型。

```java
public class Ticket {
    private String zone;
    private int price;

    public Ticket(String zone, int price) {
        this.zone = zone;
        this.price = price;
    }

    public Ticket(String zone) {
        this.zone = zone;
        price = 50;
    }
}
```

| 调用 | 判断 |
| --- | --- |
| `new Ticket("A", 80)` | 合法，匹配 `(String, int)` |
| `new Ticket("B")` | 合法，匹配 `(String)` |
| `new Ticket(80, "A")` | 参数顺序错误 |
| `new Ticket("A", 80.0)` | double 不能自动窄化为 int |
| `new Ticket()` | 不存在无参构造器 |

**只有未声明任何构造器时，编译器才会提供默认构造器。** 显式写出的无参构造器是“无参构造器”，不应笼统称为“编译器提供的默认构造器”。

```java
public void Ticket() { }
```

这行是一个名为 Ticket 的普通方法，不是构造器。

`this.zone = zone;` 左边是字段，右边是参数；写成 `zone = zone;` 不会初始化字段。

拓展阅读：`this(...)` 可以调用同一类的另一构造器。本章核心解不依赖构造器链。若使用本课 Java 17 环境，显式构造器调用必须位于构造器体首条语句；不要把特定 Java 版本的规则无限推广。

### 2.3 封装、访问器与修改器

- 字段通常设为 `private`，供类内部实现使用。
- `public` 方法提供对外操作。
- 访问器（accessor）通常读取状态；修改器（mutator）通常更新状态。
- 是否有返回值与是否改变状态是两个不同的问题，不能只看名字猜行为。

在 Puppy 类之外：

```java
Puppy pet = new Puppy("Tommy", 2);
pet.setAge(3);
System.out.println(pet.getAge()); // 3
// System.out.println(pet.age);   // 编译错误：age 是 private
```

同一个类的方法可以访问该类其他实例的 private 字段。不能把 private 理解成“只有当前对象能访问”。

### 2.4 方法签名、重载与返回值

方法签名的判断重点：**方法名与有序参数类型列表**。参数名、返回类型不用于区分重载。

```java
public static int add(int a, int b) {
    return a + b;
}

public static double add(double a, double b) {
    return a + b;
}

public static int add(int a, int b, int c) {
    return a + b + c;
}
```

| 调用 | 选择的方法 |
| --- | --- |
| `add(2, 3)` | `(int, int)` |
| `add(2.0, 3.0)` | `(double, double)` |
| `add(2, 3.0)` | `(double, double)`；2 可转为 double |
| `add(2, 3, 4)` | `(int, int, int)` |

不能只将 `int add(int a, int b)` 的返回类型改成 double，便当作新重载。

```java
public static void show(int x) {
    System.out.println(x);
}

public static int twice(int x) {
    return 2 * x;
}
```

| 调用方式 | 是否合法 |
| --- | --- |
| `show(5);` | 合法，输出 5 |
| `int a = twice(5);` | 合法，a 为 10 |
| `twice(5);` | 合法，返回值被丢弃 |
| `int b = show(5);` | 编译错误，void 没有可赋值的结果 |
| `System.out.println(show(5));` | 编译错误，不能打印 void 结果 |

类方法（static）通常用 `ClassName.method(...)`；实例方法通过对象引用调用。静态方法中没有当前对象 `this`。

### 2.5 引用别名与参数传递

**赋引用不会复制对象。**

```java
Puppy first = new Puppy("Tommy", 2);
Puppy second = first;
second.setAge(5);
System.out.println(first.getAge()); // 5
```

| 执行后 | first 指向 | second 指向 |
| --- | --- | --- |
| `second = first` | 对象 A，age=2 | 同一个对象 A |
| `second.setAge(5)` | 对象 A，age=5 | 同一个对象 A |
| `second = new Puppy("Max", 1)` | 仍是对象 A，age=5 | 新对象 B，age=1 |

**Java 始终按值传递。对象实参传递的是“引用值的副本”，不是把调用者变量本身传进去。**

```java
public static void update(Puppy p) {
    p.setAge(8);               // 改变原对象
    p = new Puppy("New", 1);  // 仅改变局部参数 p 的指向
    p.setAge(3);               // 改变新对象
}
```

若调用前 `pet` 指向 age=2 的对象，调用 `update(pet)` 后，`pet` 仍指向原对象，其 age 为 8。不是“对象按引用传递”。

```java
Puppy missing = null;
// missing.getAge(); // 执行时抛出 NullPointerException
```

`null` 检查与条件短路在条件专题展开，本章重点是识别“引用为空却调用实例方法”。

### 2.6 String 不可变

String 是引用类型，String 对象的字符序列不可修改；String 变量可以重新指向其他字符串。

```java
String first = "cat";
String second = first;
first += "s";
System.out.println(first + " " + second); // cats cat
```

`first += "s"` 更新 first 的引用，没有把原字符串对象改成 cats。

```java
String text = "planet";
text.substring(2);
System.out.println(text); // planet，返回值被丢弃

text = text.substring(2);
System.out.println(text); // anet
```

方法收到 String 参数后给它重新赋值，也不会替换调用者变量中的引用：

```java
public static void extend(String s) {
    s += "!";
}
```

### 2.7 String 方法：范围和返回值一起记

| 方法 | 返回类型 | 核心规则 |
| --- | --- | --- |
| `s.length()` | int | 字符串长度；最后有效字符索引为 length-1 |
| `s.substring(a, b)` | String | 取 `[a, b)`；合法条件 `0 <= a <= b <= length` |
| `s.substring(a)` | String | 取 `[a, length)`；允许 a 等于 length |
| `s.indexOf(t)` | int | 第一次出现的位置；找不到返回 -1 |
| `s.equals(t)` | boolean | 比较内容，区分大小写 |
| `s.compareTo(t)` | int | 字典序比较，看结果的负、零、正 |

本章所有索引例题使用普通英文字母、数字和 ASCII 标点，避免 Unicode 代码单元差异。

```java
String s = "COMPUTER";
```

| 索引 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 字符 | C | O | M | P | U | T | E | R |

```java
s.length();         // 8
s.substring(2, 5);  // "MPU"，长度为 5-2=3
s.substring(5);     // "TER"
s.substring(3, 3);  // ""
s.substring(8);     // ""，合法
s.indexOf("PUT");  // 3
s.indexOf("X");    // -1
```

`s.substring(7, 9)` 与 `s.substring(-1)` 执行时越界。它们不是因为参数类型不匹配而编译失败。

**查找后截取：先确定位置是否存在。** 原稿没有这一保护容易导致错误迁移。

```java
int pos = s.indexOf("X");
// s.substring(pos); // pos 为 -1，执行会抛异常
```

### 2.8 equals 与 ==；compareTo

```java
String a = new String("java");
String b = new String("java");
String c = a;

System.out.println(a.equals(b)); // true：内容相同
System.out.println(a == b);      // false：不是同一个对象
System.out.println(a == c);      // true：同一个引用目标
```

字面量可能因字符串池共享对象，但比较内容应使用 equals，不靠字符串池猜结果。

```java
"apple".compareTo("banana"); // < 0
"cat".compareTo("cat");      // == 0
"cart".compareTo("car");     // > 0，前缀相同则较短者在前
```

不要求把 compareTo 结果背成 -1 或 1；判断正负或零即可。比较区分大小写，涉及混合字符时按 Java 的字符顺序，不按自然语言习惯猜。

### 2.9 常用字符串拼接模板

均假定参数非 null，且前提满足。

| 任务 | 前提 | 表达式 |
| --- | --- | --- |
| 首字符 | 长度至少 1 | `s.substring(0, 1)` |
| 末字符 | 长度至少 1 | `s.substring(s.length()-1)` |
| 去首尾 | 长度至少 2 | `s.substring(1, s.length()-1)` |
| 删除索引 p 的一个字符 | `0 <= p < length` | `s.substring(0,p) + s.substring(p+1)` |
| 替换 `[a,b)` | `0 <= a <= b <= length` | `s.substring(0,a) + replacement + s.substring(b)` |
| 左移 k 个字符到末尾 | `0 <= k <= length` | `s.substring(k) + s.substring(0,k)` |

检验三件事：**长度是否正确、各段是否重复/遗漏、最短合法输入是否成立。**

### 2.10 import 与本章范围

`import` 让源代码能用简单类名引用相关类型，不是执行时把整个包载入内存。`import java.util.*;` 不会导入子包，也不代表导入 java.io。

`String`、`Math` 位于 java.lang，无需显式 import。文件读取与 Scanner 后续专题复习，本章方法题直接接收参数。

原稿的继承/重写、多态示例作为概念拓展：当前 CED 保留继承关系的认识，但明确排除设计和实现继承关系，以及重写 toString。本章不安排 Dog/Animal 动态绑定或自写 toString 的核心训练；也不将重载和运行时动态绑定混为一谈。

## 3. 做题方法

### 3.1 对象题：变量与对象分开画

每次 `new` 标一个新对象 A、B；引用赋值只改箭头；调用 mutator 才更新对象状态。代码没写 new，不要自行画新对象。

### 3.2 字符串题：写索引、区间和返回值

```java
String s = "abcdef";
String t = s.substring(1, 4) + s.substring(5);
```

左段是索引 1、2、3，即 bcd；右段是索引 5，即 f；结果 bcdf。不要把结束索引 4 包进左段。

### 3.3 FRQ：先读调用表，再写实现

1. 从构造器实参推字段及类型。
2. 区分 getter、状态更新、返回新字符串。
3. 核对方法头：参数个数、顺序、返回类型。
4. 按前提设计最短输入；测试首位、中间、末位。
5. 保持题目要求不变的对象/字符串状态不变。

## 4. MCQ 训练

每题只有一个正确选项。代码位于合法上下文；每题独立。除非明确使用 null，字符串实参均非 null。

### MCQ 1｜构造器匹配

```java
public class Book {
    public Book(String title, int pages) { }
    public Book(String title) { }
}
```

在另一个类中，哪句能编译？

A. `Book b = new Book();`  
B. `Book b = new Book(120, "Java");`  
C. `Book b = new Book("Java", 120);`  
D. `Book b = new Book("Java", 120.0);`

### MCQ 2｜this 与字段

```java
public class Item {
    private int price;
    public Item(int price) { price = price; }
    public int getPrice() { return price; }
}
```

`System.out.println(new Item(30).getPrice());` 输出什么？

A. `0`  
B. `30`  
C. `null`  
D. 编译错误

### MCQ 3｜无参构造器

```java
public class Box {
    private int size;
    public Box(int size) { this.size = size; }
}
```

在另一个类中执行 `Box b = new Box();`，正确描述是？

A. 创建 size 为 0 的对象  
B. 自动调用 `Box(0)`  
C. 运行时才发生异常  
D. 编译错误，因为没有匹配的构造器

### MCQ 4｜private

```java
public class Account {
    private int balance = 20;
    public int getBalance() { return balance; }
}
```

另一个无嵌套关系的顶层类的方法中，已声明 `Account a = new Account();`。哪句可以编译？

A. `System.out.println(a.balance);`  
B. `System.out.println(a.getBalance());`  
C. `a.balance = 50;`  
D. `System.out.println(Account.balance);`

### MCQ 5｜引用别名

```java
public class Counter {
    private int value;
    public Counter(int value) { this.value = value; }
    public void add(int n) { value += n; }
    public int getValue() { return value; }
}
```

```java
Counter a = new Counter(4);
Counter b = a;
b.add(3);
b = new Counter(1);
System.out.println(a.getValue() + " " + b.getValue());
```

A. `4 1`  
B. `7 7`  
C. `7 1`  
D. `4 7`

### MCQ 6｜传对象参数

使用第 5 题的 Counter 类，以及：

```java
public static void change(Counter c) {
    c.add(2);
    c = new Counter(10);
    c.add(5);
}
```

```java
Counter a = new Counter(3);
change(a);
System.out.println(a.getValue());
```

A. `3`  
B. `5`  
C. `10`  
D. `15`

### MCQ 7｜void 与返回值

```java
public static void show(int x) { System.out.println(x); }
public static int twice(int x) { return 2 * x; }
```

以下语句分别独立判断，哪些可以编译？

```java
I.   twice(3);
II.  int a = show(3);
III. show(twice(3));
```

A. 仅 I  
B. 仅 II 和 III  
C. I、II、III  
D. 仅 I 和 III

### MCQ 8｜重载调用

```java
public static String pick(int a, int b) { return "I"; }
public static String pick(double a, double b) { return "D"; }
```

```java
System.out.println(pick(2, 3) + pick(2, 3.0));
```

A. `ID`  
B. `II`  
C. `DD`  
D. 编译错误

### MCQ 9｜能否重载

某类已有 `public int calculate(int x)`。以下哪个方法头可以作为合法重载加入该类？假设每个方法都配有合法方法体。

A. `public double calculate(int y)`  
B. `public int calculate(int value)`  
C. `public int calculate(double x)`  
D. `private int calculate(int x)`

### MCQ 10｜substring

```java
String s = "COMPUTER";
String result = s.substring(1, 4) + s.substring(6);
System.out.println(result);
```

A. `OMPUER`  
B. `OMPER`  
C. `OMPUTER`  
D. `CMPER`

### MCQ 11｜空串边界

```java
String s = "JAVA";
```

哪些表达式合法且返回空字符串？

```java
I.   s.substring(4)
II.  s.substring(2, 2)
III. s.substring(3, 5)
```

A. 仅 I  
B. 仅 II  
C. I、II、III  
D. 仅 I 和 II

### MCQ 12｜indexOf

```java
String s = "bananana";
System.out.println(s.indexOf("ana") + " " + s.indexOf("x"));
```

A. `1 -1`  
B. `3 -1`  
C. `1 0`  
D. `2 -1`

### MCQ 13｜找到之后再截取

```java
String s = "alpha:beta:gamma";
int p = s.indexOf(":");
String t = s.substring(p + 1);
System.out.println(t.substring(0, t.indexOf(":")));
```

A. `alpha`  
B. `gamma`  
C. `beta`  
D. `beta:gamma`

### MCQ 14｜不可变字符串

```java
String a = "code";
String b = a;
a.substring(1);
b = b + "s";
System.out.println(a + " " + b);
```

A. `ode odes`  
B. `code codes`  
C. `codes codes`  
D. `ode codes`

### MCQ 15｜equals 与 ==

```java
String a = new String("AP");
String b = new String("AP");
String c = a;
System.out.println(a.equals(b) + " " + (a == b) + " " + (a == c));
```

A. `true true true`  
B. `false false true`  
C. `true false false`  
D. `true false true`

### MCQ 16｜compareTo

哪些表达式为 true？

```java
I.   "car".compareTo("cart") < 0
II.  "dog".compareTo("cat") > 0
III. "Java".equals("java")
```

A. 仅 I 和 II  
B. 仅 I 和 III  
C. 仅 II 和 III  
D. I、II、III

### MCQ 17｜交换首尾

已知 `s.length() >= 2`，`int n = s.length();`，哪一项总能返回首尾字符交换后的字符串，保持中间部分不变？

A. `s.substring(n-1) + s.substring(1) + s.substring(0,1)`  
B. `s.substring(0,1) + s.substring(1,n-1) + s.substring(n-1)`  
C. `s.substring(n-1) + s.substring(1,n-1) + s.substring(0,1)`  
D. `s.substring(n) + s.substring(1,n-1) + s.substring(0,1)`

### MCQ 18｜null 与错误类型

```java
String text = null;
System.out.println(text.length());
```

A. 输出 `0`  
B. 编译错误，String 不能赋值 null  
C. 输出 `null`  
D. 执行到方法调用时抛出 NullPointerException

## 5. FRQ 专项训练（4 题，原创）

所有参数均非 null；可以直接依赖前提。FRQ 1、3 只写要求的方法，FRQ 2 写完整类；FRQ 4 允许使用已学的简单 if，是字符串处理到真题的桥梁。每题课堂自评 9 分。

### FRQ 1｜TextTools：分段拼接

方法均位于 TextTools 类中，不得使用循环、数组或 replace 方法。

**(a)** `rotateLeft`：将前 k 个字符移到末尾，保持各段内部顺序。

```java
/** Precondition: 0 <= k <= text.length() */
public static String rotateLeft(String text, int k)
```

**(b)** `removeAt`：删除索引 p 的一个字符。

```java
/** Precondition: 0 <= p < text.length() */
public static String removeAt(String text, int p)
```

**(c)** `replaceRange`：将 `[start,end)` 替换为 replacement，其他字符保留。

```java
/** Precondition: 0 <= start <= end <= text.length() */
public static String replaceRange(String text, int start,
                                  int end, String replacement)
```

| 调用 | 返回值 |
| --- | --- |
| `rotateLeft("planet", 2)` | `"anetpl"` |
| `rotateLeft("", 0)` | `""` |
| `rotateLeft("ab", 2)` | `"ab"` |
| `removeAt("abc", 0)` | `"bc"` |
| `removeAt("a", 0)` | `""` |
| `replaceRange("abcdef", 2, 4, "XY")` | `"abXYef"` |
| `replaceRange("ab", 1, 1, "!")` | `"a!b"` |

这些方法返回新结果，不修改调用者的 String 变量。

### FRQ 2｜NameBadge：设计类

编写完整 NameBadge 类：

- 使用两个私有实例字段保存 firstName、lastName。
- 构造器 `NameBadge(String firstName, String lastName)` 保存两个姓名。
- 重载构造器 `NameBadge(String lastName)` 将 firstName 设为 `"Guest"`。
- `String getDisplay()` 返回 `lastName + ", " + firstName`，逗号后一个空格。
- `String getCode()` 返回 firstName 的首字母与 lastName 的前两字母拼接。
- `void rename(String firstName)` 只更新名，保留姓。

前提：每次提供的 firstName 长度至少 1，lastName 长度至少 2；不要求改大小写。

```java
NameBadge a = new NameBadge("Ada", "Lovelace");
NameBadge b = a;
NameBadge c = new NameBadge("Li");
b.rename("Grace");
System.out.println(a.getDisplay());
System.out.println(a.getCode());
System.out.println(c.getDisplay());
System.out.println(c.getCode());
```

```text
Lovelace, Grace
GLo
Li, Guest
GLi
```

两参构造器和一参构造器都必须能使用，不要求使用 this(...)。

### FRQ 3｜Point2D：方法复用

给定类框架，完成两个方法。字段、构造器已实现，不需要重写整个类。

```java
public class Point2D {
    private double x;
    private double y;

    public Point2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double distanceTo(Point2D other) {
        /* (a) */
    }

    public double trianglePerimeter(Point2D b, Point2D c) {
        /* (b) */
    }
}
```

**(a)** 返回当前点与 other 的欧几里得距离；使用 Math.sqrt，可将差分别相乘。不修改任何点。

**(b)** 返回当前点、b、c 围成的三角形周长；必须恰当地复用 distanceTo，不重复展开距离公式。三点保证不共线，坐标绝对值不超过 100。

```java
Point2D a = new Point2D(0, 0);
Point2D b = new Point2D(0, 3);
Point2D c = new Point2D(4, 0);
```

`a.distanceTo(b)` 返回 `3.0`，`a.trianglePerimeter(b,c)` 返回 `12.0`。方法返回 double，不要求输出两位小数。

这道题把原稿的三角形周长上机题改为 APCSA 风格的对象方法题。

### FRQ 4｜TokenTools：查找与替换一次

完成方法，将 text 中**第一次出现**的 target 替换为 replacement；如果没有出现，原样返回 text。不能使用循环、replace、replaceAll；可以使用 indexOf、substring 和 if。

```java
/** Precondition: target.length() >= 1 */
public static String replaceFirstToken(String text, String target,
                                       String replacement)
```

| 调用 | 返回值 |
| --- | --- |
| `replaceFirstToken("red-red", "red", "blue")` | `"blue-red"` |
| `replaceFirstToken("abc", "x", "!")` | `"abc"` |
| `replaceFirstToken("abc", "abc", "")` | `""` |
| `replaceFirstToken("xabc", "abc", "Q")` | `"xQ"` |
| `replaceFirstToken("aaaa", "aa", "b")` | `"baa"` |

返回后调用者原有的 String 变量不应被替换；这里是构造并返回结果，而不是改写原字符串对象。

---

## 6. 官方样题与历年 FRQ

### 6.1 官方 MCQ 样题：对象创建与字符串截取

来源：[CED，Effective Fall 2025](https://apcentral.collegeboard.org/media/pdf/ap-computer-science-a-course-and-exam-description.pdf#page=157)，PDF 第 157 页、印刷页码 150，Sample Exam Questions 第 3、4 题。

这两题是**官方样题，不是某年实考真题**。直接按原 PDF 作答。

| 题号 | 对应训练 | 要求 |
| --- | --- | --- |
| 第 3 题 | MCQ 1、3 | 先写唯一已声明构造器的参数类型列表 |
| 第 4 题 | MCQ 10、14 | 给每次 substring 单独写返回值 |

<details>
<summary>教师核对</summary>

第 3 题选 B：调用的参数类型与构造器一致。第 4 题选 A：两次截取拼接为 `"OPN"`。

### 6.2 重点真题：2025 Q2 SignedText

- [官方题目](https://apcentral.collegeboard.org/media/pdf/ap25-frq-computer-science-a.pdf#page=8)：PDF 第 8—10 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap25-sg-computer-science-a.pdf)：定位 Q2。

训练构造器、姓名格式化、签名定位与字符串拼接。需要简单条件分支，不需要数组或循环，适合本章结束后的完整类设计任务。

**建议顺序：**读调用表 → 实现构造器 → 实现 getSignature → 将 addSignature 的情况列成表 → 写代码 → 用原题样例检查。

教师重点追问：签名不存在、在开头、在末尾时分别怎样处理？参数恰好等于签名时怎样满足规则？getSignature 能否直接复用？不应在 getter 中改变姓名字段。

题目按原 PDF 完成；不将本章 NameBadge 或 TokenTools 标为这道真题的原题。

### 6.3 进阶真题：2023 Q2 Sign

- [官方题目](https://apcentral.collegeboard.org/media/pdf/ap23-frq-comp-sci-a.pdf#page=8)：PDF 第 8—10 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap23-sg-computer-science-a.pdf)：定位 Q2。

综合类设计、字符串分段、行数计算，完整 getLines 还需要循环。若本轮还没复习循环，可先写构造器和 numberOfLines，把 getLines 留到循环专题。

检查空消息、恰好整除宽度、最后一行不满；特别留意原题对 null 与空字符串的不同要求，以及末尾不能多分隔符。

### 6.4 真题使用说明

[College Board 历年题页面](https://apcentral.collegeboard.org/courses/ap-computer-science-a/exam/past-exam-questions)提醒旧题与现行修订框架并非完全对齐。本章按技能选题；旧卷的时间、单元编号和分布不作为现行考试规则。

## 7. MCQ 答案与解析

### 7.1 答案速查

| 题号 | 答案 | 核心错因 |
| --- | --- | --- |
| 1 | C | 构造器参数匹配 |
| 2 | A | 参数遮蔽字段 |
| 3 | D | 误认为总有无参构造器 |
| 4 | B | private 访问权限 |
| 5 | C | 引用赋值不复制对象 |
| 6 | B | 修改对象与重定向参数混淆 |
| 7 | D | void 不能作为值使用 |
| 8 | A | 根据参数类型选择重载 |
| 9 | C | 返回类型、参数名不区分重载 |
| 10 | B | substring 结束位置不包含 |
| 11 | D | 空串合法边界 |
| 12 | A | indexOf 是第一次出现的位置 |
| 13 | C | 截取后的新索引 |
| 14 | B | 忽略返回值、String 不可变 |
| 15 | D | 内容相同与对象相同不同 |
| 16 | A | 前缀比较与大小写 |
| 17 | C | 拼接区间遗漏/重复 |
| 18 | D | 编译错误与运行时异常不同 |

### 7.2 逐题解释

1. 仅 C 对应 `(String,int)`。A 缺无参构造器；B 顺序不符；D 的 double 不能自动转 int。
2. 参数 price 给自己赋值；字段没有显式赋值，因此保留默认值 0。应写 `this.price = price;`。
3. 类已经声明有参构造器，编译器不再额外提供默认构造器。不会自动“补参数 0”。
4. public getter 可在另一个顶层类调用。字段 private，因此 A、C 不合法；D 也不能以类名访问该 private 实例字段。
5. a、b 起初指向同一对象，add 后该对象为 7；b 的后续赋值只令 b 指向新对象，其值为 1。
6. 原对象由 3 改为 5。新对象的值变为 15，但调用者 a 仍保存原对象的引用。
7. I 允许丢弃返回值；III 先获得 6 再传给 show，合法。II 试图把 void 当 int 接收，非法。
8. 第一个调用精确匹配 int 重载，第二个调用只能匹配 double 重载，拼接为 ID。
9. C 参数类型不同。A 仅返回类型不同；B 仅参数名不同；D 仅访问修饰符不同，均不能区分为新重载。
10. `substring(1,4)` 为 OMP，`substring(6)` 为 ER，拼接 OMPER。A 错把结束位置包含进来。
11. `substring(length)` 和同起止索引都能返回空串；III 的结束索引 5 超出长度 4，执行时越界。
12. 第一个 ana 从索引 1 开始；没有 x，返回 -1。不是找最后一次，也不是从 1 计数。
13. 第一次截取后 t 为 beta:gamma；此时冒号在 t 的索引 4，取 `[0,4)` 为 beta。新字符串的索引从 0 重新开始。
14. `a.substring(1)` 的结果未接收，a 仍为 code；b 拼接后重新赋为 codes，不改变 a。
15. a、b 内容相等，但各自 new 的对象不同；c 复制 a 的引用，因此 `a == c` 为 true。
16. car 是 cart 的较短前缀，排序在前；dog 在 cat 后；equals 区分大小写，III 为 false。
17. C = 末字符 + 不含首尾的中间段 + 首字符，长度不变。A 重复末字符；B 原样；D 没有保留原末字符。长度为 2 时中间段为空串，C 仍正确。
18. null 可以赋给 String 引用变量，所以能编译；但执行实例方法调用时没有对象，抛 NullPointerException。

## 8. FRQ 参考解与课堂评分

### FRQ 1 参考解：TextTools

```java
public class TextTools {
    public static String rotateLeft(String text, int k) {
        return text.substring(k) + text.substring(0, k);
    }

    public static String removeAt(String text, int p) {
        return text.substring(0, p) + text.substring(p + 1);
    }

    public static String replaceRange(String text, int start,
                                       int end, String replacement) {
        return text.substring(0, start) + replacement + text.substring(end);
    }
}
```

额外自测：k=0、k=length；p=0、p=length-1；start=end；替换全部字符；replacement 为空串。

### FRQ 2 参考解：NameBadge

```java
public class NameBadge {
    private String firstName;
    private String lastName;

    public NameBadge(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public NameBadge(String lastName) {
        firstName = "Guest";
        this.lastName = lastName;
    }

    public String getDisplay() {
        return lastName + ", " + firstName;
    }

    public String getCode() {
        return firstName.substring(0, 1) + lastName.substring(0, 2);
    }

    public void rename(String firstName) {
        this.firstName = firstName;
    }
}
```

两个引用指向同一 NameBadge 时，rename 更新共享对象的字段。这不与 String 不可变矛盾：修改的是 NameBadge 内保存的引用，而不是 String 对象的字符。

### FRQ 3 参考解：Point2D

```java
public class Point2D {
    private double x;
    private double y;

    public Point2D(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double distanceTo(Point2D other) {
        double dx = x - other.x;
        double dy = y - other.y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    public double trianglePerimeter(Point2D b, Point2D c) {
        return distanceTo(b) + b.distanceTo(c) + c.distanceTo(this);
    }
}
```

distanceTo 共 5 分：正确 x 差、y 差各 1 分；平方后相加 1 分；正确开方并返回 1 分；不修改点的字段 1 分。

trianglePerimeter 共 4 分：三条边正确调用各 1 分；求和返回且不修改对象 1 分。方向等价的距离调用可得分；直接重复写公式不满足方法复用要求。

同一个类内部可访问其他 Point2D 对象的私有字段，因此 `other.x` 合法。`this` 是当前点的引用。

### FRQ 4 参考解：TokenTools

```java
public class TokenTools {
    public static String replaceFirstToken(String text, String target,
                                            String replacement) {
        int pos = text.indexOf(target);
        if (pos == -1) {
            return text;
        }
        return text.substring(0, pos) + replacement
               + text.substring(pos + target.length());
    }
}
```

