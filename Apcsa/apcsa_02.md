## 📚 Java class and object

1、**类（Class）**：

- 定义对象的蓝图，包括属性和方法。
- 示例：`public class Car { ... }`

**2、对象（Object）**：

- 类的实例，具有状态和行为。
- 示例：`Car myCar = new Car();`

**3、继承（Inheritance）**：

- 一个类可以继承另一个类的属性和方法。
- 示例：`public class Dog extends Animal { ... }`

**4、封装（Encapsulation）**：

- 将对象的状态（字段）私有化，通过公共方法访问。

- 示例：

  ```java
  private String name; 
  public String getName() { return name; }
  ```
  

**5、多态（Polymorphism）**：

- 对象可以表现为多种形态，主要通过方法重载和方法重写实现。
- 示例：
  - 方法重载：`public int add(int a, int b) { ... }` 和 `public double add(double a, double b) { ... }`
  - 方法重写：`@Override public void makeSound() { System.out.println("Meow"); }`

```java
public class Main {
    public static void main(String[] args) {
        Animal a1 = new Animal();
        Animal a2 = new Dog();          // 多态：父类引用指向子类对象
       
        a1.speak();                     // 调用 Animal.speak()
        a2.speak();                     // 调用 Dog.speak()（重写生效）
    }
}

class Animal {
    //Animal(int x,int y){a=x,b=y}
    //private int a,b;
    public void speak() {
        System.out.println("Animal: ...");
    }
}

class Dog extends Animal {               // extend：Dog 继承 Animal
    @Override                            // override：重写 speak()
    public void speak() {
        System.out.println("Dog: Woof!");
    }
}

```

### 📌 **case**

```java
public class Dog {
    String breed;
    int size;
    String colour;
    int age;
 
    void eat() {
    }
 
    void run() {
    }
 
    void sleep(){
    }
 
    void name(){
    }
}
```

### 构造方法

每个类都有构造方法。如果没有显式地为类定义构造方法，Java 编译器将会为该类提供一个默认构造方法。

在创建一个对象的时候，至少要调用一个构造方法。构造方法的名称必须与类同名，一个类可以有多个构造方法。

```java
public class Puppy{
    String name;
    int age;
    public Puppy(){
      System.out.println("Puppy对象已创建");
    }// 1、无参构造方法（默认构造方法）
 
    public Puppy(String name, int age){
        this.name = name;
        this.age = age;
        // 2、有参构造方法
    }
}
```

### 创建对象

对象是根据类创建的。在Java中，使用关键字 new 来创建一个新的对象。创建对象需要以下三步：

- **声明**：声明一个对象，包括对象名称和对象类型。
- **实例化**：使用关键字 new 来创建一个对象。
- **初始化**：使用 new 创建对象时，会调用构造方法初始化对象。

```java
public class Puppy{
   private String name
   public Puppy(String name){
      //这个构造器仅有一个参数：name
      this.name=name
      System.out.println("小狗的名字是 : " + name ); 
   }
   public static void main(String[] args){
      // 下面的语句将创建一个Puppy对象
      Puppy myPuppy = new Puppy( "tommy" );
   }
}
```

### 访问实例变量和方法

```java
public class Puppy {
    private int age;
    private String name;
 
    // 构造器
    public Puppy(String name) {
        this.name = name;
        //this.age= age
        System.out.println("小狗的名字是 : " + name);
    }
 
    // 设置 age 的值
    public void setAge(int age) {
        this.age = age;
    }
 
    // 获取 age 的值
    public int getAge() {
        return age;
    }
 
    // 获取 name 的值
    public String getName() {
        return name;
    }
 
    // 主方法
    public static void main(String[] args) {
        // 创建对象
        Puppy myPuppy = new Puppy("Tommy",2);
 
        // 通过方法来设定 age
        myPuppy.setAge(2);
 
        // 调用另一个方法获取 age
        int age = myPuppy.getAge();
        System.out.println("小狗的年龄为 : " + age);
 
        // 也可以直接访问成员变量（通过 getter 方法）
        System.out.println("变量值 : " + myPuppy.getAge());
    }
}
```

### 构造方法中的 this 关键字

在构造方法中，this 关键字通常用于两种情况：

**1、引用当前对象的属性或方法：**当构造方法的参数名与类属性名相同时，使用 this 来区分类属性和参数。例如：

```java
public Person(String name, int age) {
    this.name = name; // this.name 表示类的属性
    this.age = age;
}
```

**2、调用另一个构造方法：**可以使用 this() 调用当前类的其他构造方法，常用于避免重复代码，但必须放在构造方法的第一行。

```java
public Person(String name) {
    this(name, 0); // 调用另一个双参数的构造方法
}

public Person(String name, int age) {
    this.name = name;
    this.age = age;
}
```

### import 语句

在 Java 中，如果给出一个完整的限定名，包括包名、类名，那么 Java 编译器就可以很容易地定位到源代码或者类。import 语句就是用来提供一个合理的路径，使得编译器可以找到某个类。

例如，下面的命令行将会命令编译器载入 java_installation/java/io 路径下的所有类

```java
import java.io.*;
```

- 常见：`InputStream/OutputStream` 族、`Reader/Writer` 族、`File`、`BufferedReader/BufferedWriter`、`PrintWriter`、`ObjectInputStream/ObjectOutputStream` 等。
- 用途：**字节/字符流 I/O、文件读写、序列化**。

```java
import java.util.*
```

- 常见：集合框架 `List/ArrayList`, `Map/HashMap`, `Set/HashSet`, `Collections`, `Arrays`，`Scanner`，`Random`，`Date/Calendar` 等。
- 用途：**容器、工具类、随机数、时间（旧 API）**等。

```java
import java.io.*;
 
public class Employee {
    private String name;
    private int age;
    private String designation;
    private double salary;
 
    // Employee 类的构造器
    public Employee(String name) {
        this.name = name;
    }
 
    // 设置 age 的值
    public void setAge(int age) {
        this.age = age;
    }
 
    // 获取 age 的值
    public int getAge() {
        return age;
    }
 
    // 设置 designation 的值
    public void setDesignation(String designation) {
        this.designation = designation;
    }
 
    // 获取 designation 的值
    public String getDesignation() {
        return designation;
    }
 
    // 设置 salary 的值
    public void setSalary(double salary) {
        this.salary = salary;
    }
 
    // 获取 salary 的值
    public double getSalary() {
        return salary;
    }
 
    // 打印信息
    public void printEmployee() {
        System.out.println(this);
    }
 
    // 重写 toString 方法
    @Override
    public String toString() {
        return "名字: " + name + "\n" +
               "年龄: " + age + "\n" +
               "职位: " + designation + "\n" +
               "薪水: " + salary;
    }
}
```

### 📌  读取控制台输入

Java 的控制台输入由 System.in 完成。为了获得一个绑定到控制台的字符流，可以把 System.in 包装在一个 BufferedReader 对象中来创建一个字符流。然后使用 read() 方法从控制台读取一个字符，或者用 readLine() 方法读取一个字符串。

```java
//使用 BufferedReader 在控制台读取字符
import java.io.*;
 
public class Main {
    public static void main(String[] args) throws IOException {
        char c;
        // 使用 System.in 创建 BufferedReader
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("输入字符, 按下 'q' 键退出。");
        // 读取字符
        do {
            c = (char) br.read();
            System.out.println(c);
        } while (c != 'q');
    }
}
```

从标准输入读取一个字符串需要使用 BufferedReader 的 readLine() 方法。

```java
//使用 BufferedReader 在控制台读取字符
import java.io.*;
 
public class BRReadLines {
    public static void main(String[] args) throws IOException {
        // 使用 System.in 创建 BufferedReader
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str;
        System.out.println("Enter lines of text.");
        System.out.println("Enter 'end' to quit.");
        do {
            str = br.readLine();
            System.out.println(str);
        } while (!str.equals("end"));
    }
}
```

### 📌 Scanner（方便但慢一些）

```java
import java.util.*;

public class EasyIn {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        double x = in.nextDouble();
        String s = in.next();   // 遇空白就停
        in.nextLine();          // 若后面要整行，先吃掉残余换行
        String line = in.nextLine();
        System.out.printf("n=%d, x=%.2f, s=%s, line=%s%n", n, x, s, line);
        in.close();
    }
}

//System.out.println() is just the way that you ask Java to print out the value of something followed by a new line (ln). 
//System.out.print() without the ln will print out something without advancing to the next new line. 
```

### 📌  Void Methods & **Overloaded Methods**

```java
//Void methods do not have return values and are therefore not called as part of an expression. 
public class MyClass{
	public static void main(String[] args){
		int a = 3 + printX(5); //error! Does not return!
		int b = 5 * twiceX(3); // correct, b = 30
		printX(5); // correct  
			    // Output: The input x is 5
	}
	public static void printX(int x){
		System.out.println(“The input x is” + x);
	}
	public static int twiceX(int x){
		return 2 * x;
	}
}
```

```java
//Methods are said to be overloaded when there are multiple methods with the same name but a different signature. 
public class MyClass{
	public static void main(String[] args){
		double a = add(1, 2) + add(1.8, 5.2) + add(1, 2, 3);
		System.out.println(a); // 16.0
	}
	public static int add(int x, int y){
		return x + y;
	}
	public static double add(double x, double y){
		return x + y;
	}
	public static int add(int x, int y, int z){
		return x + y + z;
	}
}
```

### 📌 **形式参数**

```java
public class MyClass{
	public static void main(String[] args){
			int x = 23;
    		strange(x);
    		System.out.println("2. x = " + x);
	}
	public static void strange(int x){
	  		x = x + 1;
   		System.out.println("1. x = " + x);
}
}
//The value of x in main did not change. 
```

**Case**（寻找错误）

```java
public class MyClass{
	public static void main(String[] args){
		printX();  
		add(); 
		add(3, 5); 
			   
		System.out.println(printX(5)); 
						  
		System.out.println(“3 + 5 = “ + add(3, 5));
		int y = 3 + add(4, 6.0); 
	}
	public static void printX(int x){
		System.out.println(“The input x is” + x);
	}
	public static int add(int x, int y){
		return x + y;
	}
}
```

```java
public class MyClass{
	public static void main(String[] args){
		printX(); // missing actual parameter. 
		add(); // missing actual parameters.
		add(3, 5); // returned value not stored
			    // but not a syntax error. 
		System.out.println(printX(5)); // error!
						   //no returned value!
		System.out.println(“3 + 5 = “ + add(3, 5));//correct!
		int y = 3 + add(4, 6.0); // incompatible types!
	}
	public static void printX(int x){
		System.out.println(“The input x is” + x);
	}
	public static int add(int x, int y){
		return x + y;
	}
}

```

***

### 📌 **String**

- String is not a primitive type. String is an object type.

```java
String a = new String(”John Smith”);
String b = “John Smith”;
String c = ”John” + “Smith”;
```

- String是由n个字符构成的，可以通过0-based索引找到指定字符。
- 使用+号打印字符串与其他数字的连接。

```java
System.out.println("Grade: " + (95.1 + 71.9) / 2);
```

- 常用函数

```java
public class Main{
	public static void main(String[] args){
    String s1 = "programming in java";
    System.out.println(s1.length());         
	  // 19
	  System.out.println(s1.indexOf(“i")); // 8
	  System.out.println(s1.indexOf(“gram")); // 3
	  System.out.println(s1.indexOf(“hi")); // -1
	
	  System.out.println(s1.substring(7, 10)); // "min"
	  System.out.println(s1.substring(12)); // "in java"
	  System.out.println(s1.substring(2,3));// "o"
	  System.out.println(s1.substring(2,2));
    // "", empty string
	
	  String s2 = s1.substring(10, 17); // "g in ja"
                                  
    String a = “hello”, b = “Hello”;
    System.out.println(a.equals(b)); // false
    //System.out.println(a == b);
    System.out.println(a.equals(“hello”)); // true
	}
```

***

### Homework1: 距离函数

#### 题目描述

给出平面坐标上不在一条直线上三个点坐标 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$，坐标值是实数，且绝对值不超过 100.00，求围成的三角形周长。保留两位小数。

对于平面上的两个点 $(x_1,y_1),(x_2,y_2)$，则这两个点之间的距离 $dis=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}$。

#### 输入格式

输入三行，第 $i$ 行表示坐标 $(x_i,y_i)$，以一个空格隔开。

#### 输出格式

输出一个两位小数，表示由这三个坐标围成的三角形的周长。

### 输入 #1

```
0 0
0 3
4 0
```

### 输出 #1

```
12.00
```

## 说明/提示

数据保证，坐标均为实数且绝对值不超过 $100$，小数点后最多仅有 $3$ 位。

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        double x1 = in.nextDouble(), y1 = in.nextDouble();
        double x2 = in.nextDouble(), y2 = in.nextDouble();
        double x3 = in.nextDouble(), y3 = in.nextDouble();

        double a = Math.hypot(x1 - x2, y1 - y2);
        double b = Math.hypot(x2 - x3, y2 - y3);
        double c = Math.hypot(x3 - x1, y3 - y1);

        System.out.printf("%.2f%n", a + b + c);
    }
}
```

### Homework2: 计算阶乘

#### 题目描述

求 *n*!，也就是 1×2×3⋯×*n*。

挑战：尝试不使用循环语句（for、while）完成这个任务。

#### 输入格式

第一行输入一个正整数 $n$。

#### 输出格式

输出一个正整数，表示 $n!$。

#### 输入输出样例 #1

### 输入 #1

```
3
```

### 输出 #1

```
6
```

## 说明/提示

数据保证，1≤*n*≤12。

```java
import java.util.*;

public class Main {
    static long fact(int n) {
        if (n <= 1) return 1;
        return n * fact(n - 1); // 递归
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();           // 1 ≤ n ≤ 12
        System.out.println(fact(n));    // 12! = 479001600，long 足够
    }
}

```

### Homework3：杨辉三角

#### 题目描述

给出  *n*(1≤*n*≤20)，输出杨辉三角的前 `n` 行。

如果你不知道什么是杨辉三角，可以观察样例找找规律。

#### 输入格式

无

#### 输出格式

无

### 输入输出样例 #1

### 输入 #1

```
6
```

### 输出 #1

```
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
```

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();                 // 1 ≤ n ≤ 20

        int[][] a = new int[n][n];

        // 生成杨辉三角
        for (int i = 0; i < n; i++) {
            a[i][0] = a[i][i] = 1;            // 两侧为 1
            for (int j = 1; j < i; j++) {
                a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
            }
        }

        // 输出
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j > 0) sb.append(' ');
                sb.append(a[i][j]);
            }
            sb.append('\n');
        }
        System.out.print(sb.toString());
    }
}

```

### Homework4：[USACO1.1] 你的飞碟在这儿 Your Ride Is Here

#### 题目描述

众所周知，在每一个彗星后都有一只 UFO。这些 UFO 时常来收集地球上的忠诚支持者。不幸的是，他们的飞碟每次出行都只能带上一组支持者。因此，他们要用一种聪明的方案让这些小组提前知道谁会被彗星带走。他们为每个彗星起了一个名字，通过这些名字来决定这个小组是不是被带走的那个特定的小组（你认为是谁给这些彗星取的名字呢？）。关于如何搭配的细节会在下面告诉你；你的任务是写一个程序，通过小组名和彗星名来决定这个小组是否能被那颗彗星后面的 UFO 带走。

小组名和彗星名都以下列方式转换成一个数字：最终的数字就是名字中所有字母的积，其中 A 是 1，Z 是 26。例如，例如，USACO 小组就是 21×19×1×3×15=17955。如果小组的数字mod47等于彗星的数字 mod47，你就得告诉这个小组需要准备好被带走！（记住“*a*mod*b*”是 *a* 除以 *b* 的余数，例如 34mod10 等于 4）


写出一个程序，读入彗星名和小组名并算出用上面的方案能否将两个名字搭配起来，如果能搭配，就输出 `GO`，否则输出 `STAY`。小组名和彗星名均是没有空格或标点的一串大写字母（不超过 `6` 个字母）。

#### 输入格式

第 1 行：一个长度为 `1` 到 `6` 的大写字母串，表示彗星的名字。

第 2 行：一个长度为 `1` 到 `6` 的大写字母串，表示队伍的名字。

#### 输出格式

无

#### 输入输出样例 #1

#### 输入 #1

```
COMETQ
HVNGAT
```

#### 输出 #1

```
GO
```

#### 输入输出样例 #2

#### 输入 #2

```
ABSTAR
USACO
```

#### 输出 #2

```
STAY
```

```java
import java.util.*;

public class Main {
    static long val(String s) {
        long prod = 1;
        for (int i = 0; i < s.length(); i++) {
            prod *= (s.charAt(i) - 'A' + 1);
        }
        return prod % 47;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String comet = in.next();
        String group = in.next();
        System.out.println(val(comet) == val(group) ? "GO" : "STAY");
    }
}

```
