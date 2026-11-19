APCSA入门课

## 📚 JAVA可以用来做什么

- Android开发、Netflix开发等
- 游戏引擎开发（例Minecraft）
- 网站开发（例用Spring Boot/Spring Cloud 写 API）
- 自动化测试工具（例Selenium/WebDriver）

## 🖥️ 必备软件

- vscode（写代码用的）
- github（开源代码）
- chatgpt （查阅代码） 

## 🧑🏽‍💻 刷题网站

- [leetcode](https://leetcode.cn/) 力扣
- [usaco](https://usaco.org/index.php) 美国高中信息学竞赛

## 🗓️ 课时安排与教学目标

| 课时   | 教学主题                 | 教学目标                                              |
| ------ | :----------------------- | ----------------------------------------------------- |
| 第1课  | Primitive Types          | 掌握变量定义、字符串、整数、浮点数、布尔值等基础      |
| 第2课  | Using Objects            | 对象与引用、构造器调用、形参与实参等                  |
| 第3课  | Boolean Expressions & If | 布尔与比较、逻辑运算与短路、优先级与括号、if 语句写法 |
| 第4课  | Iteration                | for、while语句                                        |
| 第5课  | Writing Classes          | class、public、private、static、overload等            |
| 第6课  | Arrays                   | 声明、创建、初始化数组、参数传递、浅/深拷贝           |
| 第7课  | ArrayList                | ArrayList<Integer> list 增删改查                      |
| 第8课  | 2D Arrays                | 声明/创建/初始化二维数组                              |
| 第9课  | Inheritance              | extends、override、overload等                         |
| 第10课 | Recursion                | 递归、迭代、分治等                                    |

---

## 📝 示例代码

### 📌 Java程序结构

```c++
public class Main {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
        //return
    }
}
//String[] args 是 主函数 main 的参数，用来接收命令行参数。运行程序时你在命令后面写的每个“空格分隔的词”，都会按顺序放进这个字符串数组里，所有的 Java 程序都由此开始运行。
```

```java
public class Main {
    public static void main(String[] args) {
        System.out.println("参数个数 = " + args.length);
        for (int i = 0; i < args.length; i++) {
            System.out.println(i + ": " + args[i]);
        }
    }
}
//$ java Main.java Alice 123 "hello world"
```

### 📌 编译 & 执行 java 程序

```java
$ java Main.java
```

### 📌 Java标识符

- 所有的标识符都应该以字母（A-Z 或者 a-z）,美元符（$）、或者下划线（_）开始

- 合法标识符举例：age、$salary、_value、__1_value
- 关键字不能用作标识符

- 区分大小写

### 📌 Java枚举

```java
class FreshJuice {
   enum FreshJuiceSize{ SMALL, MEDIUM , LARGE }
   FreshJuiceSize size;
}
 
public class FreshJuiceTest {
   public static void main(String[] args){
      FreshJuice juice = new FreshJuice();
      juice.size = FreshJuice.FreshJuiceSize.MEDIUM  ;
   }
}
//枚举限制变量只能是预先设定好的值
/* 多
   行
   注
   释
*/
```

### 📌 Java关键字

Java里的关键字是不能作为变量命名的

| abstract | default | if         | private      | this      |
| -------- | ------- | ---------- | ------------ | --------- |
| boolean  | do      | implements | protected    | throw     |
| break    | double  | import     | public       | throws    |
| byte     | else    | instanceof | return       | transient |
| case     | extends | int        | short        | try       |
| catch    | final   | interface  | static       | void      |
| char     | finally | long       | strictfp     | volatile  |
| class    | float   | native     | super        | while     |
| const    | for     | new        | switch       |           |
| continue | goto    | package    | synchronized |           |

### 📌 Java 基本数据类型

1. #### byte：

   - 是有符号的8位整数，最小值是 **-128（-2^7）**，最大值是 **127（2^7-1）**
   - byte a = 100，byte b = -50
   - 默认值是 **0**

2. #### short:

   - 是 有符号的16 位整数，最小值是 **-32768（-2^15）**，最大值是 **32767（2^15 - 1）**
   - short s = 1000，short r = -20000
   - 默认值是 **0**

3. #### int：

   - 是有符号的32位整数，最小值是 **-2,147,483,648（-2^31）**，最大值是 **2,147,483,647（2^31 - 1）**
   - int a = 100000, int b = -200000
   - 默认值是 **0** 

4. **long：**
   - long 数据类型是 64 位、有符号的以二进制补码表示的整数
   - 最小值是 **-9,223,372,036,854,775,808（-2^63）**
   - 最大值是 **9,223,372,036,854,775,807（2^63 -1）**
   - 默认值是 **0L**
   - 例子： **long a = 100000L**，**long b = -200000L**
     "L"理论上不分大小写，但是若写成"l"容易与数字"1"混淆，不容易分辩。所以最好大写

5. **float：**
   - float 数据类型是单精度、32位、符合IEEE 754标准的浮点数
   - float 在储存大型浮点数组的时候可节省内存空间
   - 默认值是 **0.0f**
   - 例子：float f1 = 234.5f

6. **double：**

   - double 数据类型是双精度、64 位、符合 IEEE 754 标准的浮点数

   - 浮点数的默认类型为 double 类型

   - double类型同样不能表示精确的值，如货币

   - 默认值是 **0.0d**

     ```java
     double   d1  = 7D ;
     double   d2  = 7.; 
     double   d3  =  8.0; 
     double   d4  =  8.D; 
     double   d5  =  12.9867; 
     ```

7. ##### boolean:

   - boolean数据类型表示一位的信息
   - 只有两个取值：true 和 false
   - 默认值是 **false**
   - 例子：boolean one = true

8. #####  char:

   - char 类型是一个单一的 16 位 Unicode 字符
   - 最小值是 **\u0000**（十进制等效值为 0）
   - 最大值是 **\uffff**（即为 65535）
   - char 数据类型可以储存任何字符
   - 例子：char letter = 'A'

```java
public class PrimitiveTypeTest {  
    public static void main(String[] args) {  
        // byte  
        System.out.println("基本类型：byte 二进制位数：" + Byte.SIZE);  
        System.out.println("包装类：java.lang.Byte");  
        System.out.println("最小值：Byte.MIN_VALUE=" + Byte.MIN_VALUE);  
        System.out.println("最大值：Byte.MAX_VALUE=" + Byte.MAX_VALUE);  
        System.out.println();  
  
        // short  
        System.out.println("基本类型：short 二进制位数：" + Short.SIZE);  
        System.out.println("包装类：java.lang.Short");  
        System.out.println("最小值：Short.MIN_VALUE=" + Short.MIN_VALUE);  
        System.out.println("最大值：Short.MAX_VALUE=" + Short.MAX_VALUE);  
        System.out.println();  
  
        // int  
        System.out.println("基本类型：int 二进制位数：" + Integer.SIZE);  
        System.out.println("包装类：java.lang.Integer");  
        System.out.println("最小值：Integer.MIN_VALUE=" + Integer.MIN_VALUE);  
        System.out.println("最大值：Integer.MAX_VALUE=" + Integer.MAX_VALUE);  
        System.out.println();  
  
        // long  
        System.out.println("基本类型：long 二进制位数：" + Long.SIZE);  
        System.out.println("包装类：java.lang.Long");  
        System.out.println("最小值：Long.MIN_VALUE=" + Long.MIN_VALUE);  
        System.out.println("最大值：Long.MAX_VALUE=" + Long.MAX_VALUE);  
        System.out.println();  
  
        // float  
        System.out.println("基本类型：float 二进制位数：" + Float.SIZE);  
        System.out.println("包装类：java.lang.Float");  
        System.out.println("最小值：Float.MIN_VALUE=" + Float.MIN_VALUE);  
        System.out.println("最大值：Float.MAX_VALUE=" + Float.MAX_VALUE);  
        System.out.println();  
  
        // double  
        System.out.println("基本类型：double 二进制位数：" + Double.SIZE);  
        System.out.println("包装类：java.lang.Double");  
        System.out.println("最小值：Double.MIN_VALUE=" + Double.MIN_VALUE);  
        System.out.println("最大值：Double.MAX_VALUE=" + Double.MAX_VALUE);  
        System.out.println();  
  
        // char  
        System.out.println("基本类型：char 二进制位数：" + Character.SIZE);  
        System.out.println("包装类：java.lang.Character");  
        // 以数值形式而不是字符形式将Character.MIN_VALUE输出到控制台  
        System.out.println("最小值：Character.MIN_VALUE="  
                + (int) Character.MIN_VALUE);  
        // 以数值形式而不是字符形式将Character.MAX_VALUE输出到控制台  
        System.out.println("最大值：Character.MAX_VALUE="  
                + (int) Character.MAX_VALUE);  
    }  
}
```

### 类型默认值

下表列出了 Java 各个类型的默认值：

| 数据类型                   | 默认值   |
| :------------------------- | :------- |
| int                        | 0        |
| long                       | 0L       |
| short                      | 0        |
| char                       | '\u0000' |
| byte                       | 0        |
| float                      | 0.0f     |
| double                     | 0.0d     |
| boolean                    | false    |
| 引用类型（类、接口、数组） | null     |

```java
public class Test {
    static boolean bool;
    static byte by;
    static char ch;
    static double d;
    static float f;
    static int i;
    static long l;
    static short sh;
    static String str;
 
    public static void main(String[] args) {
        System.out.println("Bool :" + bool);
        System.out.println("Byte :" + by);
        System.out.println("Character:" + ch);
        System.out.println("Double :" + d);
        System.out.println("Float :" + f);
        System.out.println("Integer :" + i);
        System.out.println("Long :" + l);
        System.out.println("Short :" + sh);
        System.out.println("String :" + str);
    }
}
```

### 📌 Java常量

常量在程序运行时是不能被修改的。

在 Java 中使用 final 关键字来修饰常量，声明方式和变量类似：

```java
final double PI = 3.1415927;
```

虽然常量名也可以用小写，但为了便于识别，通常使用大写字母表示常量。

byte、int、long、和short都可以用十进制、16进制以及8进制的方式来表示。前缀 **0** 表示 8 进制，而前缀 **0x** 代表 16 进制, 例如：

```java
int decimal = 100;
int octal = 0144;
int hexa =  0x64;
```

Java的字符串常量是包含在两个引号之间的字符序列,例如：

```java
public class Main {
    public static void main(String[] args) {
        System.out.println("Hello World");
        System.out.println("two\nlines");
        System.out.println("\"This is in quotes\"");
      /* "This is not
      a legal String." */
      /* "This is not a "legal" String either." */
    }
}
```

字符串常量和字符变量都可以包含任何 Unicode 字符。例如：

```java
public class Main {
    public static void main(String[] args) {
        char a = '\u0001';
        String b = "\u0001";
        System.out.println(a);
        System.out.println(b);
    }
}
```

Java语言支持一些特殊的转义字符序列。

| 符号   | 字符含义                 |
| :----- | :----------------------- |
| \n     | 换行 (0x0a)              |
| \r     | 回车 (0x0d)              |
| \f     | 换页符(0x0c)             |
| \b     | 退格 (0x08)              |
| \0     | 空字符 (0x0)             |
| \s     | 空格 (0x20)              |
| \t     | 制表符                   |
| \"     | 双引号                   |
| \'     | 单引号                   |
| \\     | 反斜杠                   |
| \ddd   | 八进制字符 (ddd)         |
| \uxxxx | 16进制Unicode字符 (xxxx) |

### 📌 自动类型转换

数据转换一般是从低级到高级，因为从容量大类型转换为容量小的类型可能会溢出或损失精度。

```java
低  ------------------------------------>  高

byte,short,char—> int —> long—> float —> double 
```

```java
int i =128;   
byte b = (byte)i;
//byte 类型是 8 位，最大值为127，所以当 int 强制转换为 byte 类型时，值 128 时候就会导致溢出。
(int)23.7 == 23;        
(int)-45.89f == -45
//浮点数到整数的转换是通过舍弃小数得到，而不是四舍五入
  
//不能对boolean类型进行类型转换。
```

```java
//转换前的数据类型的位数低于转换后的数据类型可以直接转
public class ZiDongLeiZhuan{
        public static void main(String[] args){
            char c1='a';//定义一个char类型
            int i1 = c1;//char自动类型转换为int
            System.out.println("char自动类型转换为int后的值等于"+i1);
            char c2 = 'A';//定义一个char类型
            int i2 = c2+1;//char 类型和 int 类型计算
            System.out.println("char类型和int计算后的值等于"+i2);
        }
}
//c1 的值为字符 a ,查 ASCII 码表可知对应的 int 类型值为 97， A 对应值为 65，所以 i2=65+1=66。
```

### 📌 隐含强制类型转换

- 1、 整数的默认类型是 int。
- 2、 小数默认是 double 类型浮点型，在定义 float 类型时必须在数字后面跟上 F 或者 f。

***

### 📌 Java 变量类型

在 Java 语言中，所有的变量在使用前必须声明

```java
int a, b, c;         // 声明三个int型整数：a、 b、c
int d = 3, e = 4, f = 5; // 声明三个整数并赋予初值
byte z = 22;         // 声明并初始化 z
String s = "runoob";  // 声明并初始化字符串 s
double pi = 3.14159; // 声明了双精度浮点型变量 pi
char x = 'x';        // 声明变量 x 的值是字符 'x'。
```

```java
public class RunoobTest {
    // 成员变量
    private int instanceVar;
    // 静态变量
    private static int staticVar;
    
    public void method(int paramVar) {
        // 局部变量
        int localVar = 10;
        
        // 使用变量
        instanceVar = localVar;
        staticVar = paramVar;
        
        System.out.println("成员变量: " + instanceVar);
        System.out.println("静态变量: " + staticVar);
        System.out.println("参数变量: " + paramVar);
        System.out.println("局部变量: " + localVar);
    }
    
    public static void main(String[] args) {
        RunoobTest v = new RunoobTest();
        v.method(20);
    }
}
// 局部变量是在方法、构造函数或块内部声明的变量，它们在声明的方法、构造函数或块执行结束后被销毁，局部变量在声明时需要初始化，否则会导致编译错误。
// 静态变量是在类中用 static 关键字声明的变量，它们属于类而不是实例，所有该类的实例共享同一个类变量的值，类变量在类加载时被初始化，而且只初始化一次。
// 参数是方法或构造函数声明中的变量，用于接收调用该方法或构造函数时传递的值，参数变量的作用域只限于方法内部。
```

### 📌 Java 参数变量

```java
public class RunoobTest {
    public static void main(String[] args) {
        int a = 10, b = 20;
        swap(a, b); // 调用swap方法
        System.out.println("a = " + a + ", b = " + b); // 输出a和b的值
    }
    
    public static void swap(int x, int y) {
        int temp = x;
        x = y;
        y = temp;
    }
}
```

```java
public class RunoobTest {
    public static void main(String[] args) {
        int a = 10, b = 20;
        //swap(a, b); 调用swap方法
        int[] r = swap(a, b);
        a = r[0];
        b = r[1];
        System.out.println("a = " + a + ", b = " + b); // 输出a和b的值
    }
    
    static int[] swap(int x, int y){
        return new int[]{y, x};
    }
}
```

### 📌 Java 局部变量

```java
public class LocalVariablesExample {
    public static void main(String[] args) {
        int a = 10; // 局部变量a的声明和初始化
        int b;     // 局部变量b的声明
        b = 20;    // 局部变量b的初始化
        
        System.out.println("a = " + a);
        System.out.println("b = " + b);
        
        // 如果在使用之前不初始化局部变量，编译器会报错
        // int c;
        // System.out.println("c = " + c);
    }
}
//如果在使用局部变量之前不初始化它，编译器会报错。
```

### 📌 Java 成员变量

成员变量的值在创建对象时被分配，即使未对其初始化，它们也会被赋予默认值，例如 int 类型的变量默认值为 0，boolean 类型的变量默认值为 false。

成员变量可以通过对象访问，也可以通过类名访问（如果它们是静态成员变量）。

```java
import java.io.*;
public class Employee{
   // 这个成员变量对子类可见
   public String name;
   // 私有变量，仅在该类可见
   private double salary;
   //在构造器中对name赋值
   public Employee (String empName){
      name = empName;
   }
   //设定salary的值
   public void setSalary(double empSal){
      salary = empSal;
   }  
   // 打印信息
   public void printEmp(){
      System.out.println("名字 : " + name );
      System.out.println("薪水 : " + salary);
   }
 
   public static void main(String[] args){
      Employee empOne = new Employee("RUNOOB");
      empOne.setSalary(1000.0);
      empOne.printEmp();
   }
}
```

### 📌 类变量（静态变量）

Java 中的静态变量是指在类中定义的一个变量，它与类相关而不是与实例相关，即无论创建多少个类实例，静态变量在内存中只有一份拷贝，被所有实例共享。

静态变量的定义方式是在类中使用 **static** 关键字修饰变量，通常也称为类变量。

以下实例中我们定义一个静态变量 **count** ，其初始值为 0：

```java
public class MyClass {
    public static int count = 0;
    // 其他成员变量和方法
}
//由于静态变量是与类相关的，因此可以通过类名来访问静态变量，也可以通过实例名来访问静态变量。
MyClass.count = 10; // 通过类名访问
MyClass obj = new MyClass();
obj.count = 20; // 通过实例名访问
```

#### 静态变量的命名规范

静态变量（也称为类变量）的命名规范通常遵循驼峰命名法，并且通常使用全大写字母，单词之间用下划线分隔，并且要用 static 关键字明确标识。

- **使用驼峰命名法：** 即首字母小写，后续每个单词的首字母大写。例如：**`myStaticVariable`**。
- **全大写字母：** 静态常量通常使用全大写字母，单词之间用下划线分隔。这被称为"大写蛇形命名法"（Upper Snake Case）。例如：`MY_STATIC_VARIABLE`。
- **避免使用缩写：** 尽量避免使用缩写，以提高代码的可读性。如果使用缩写是必要的，确保广泛理解，并在注释中进行解释。
- **避免关键字：** 不要使用 Java 关键字（例如，class、int、boolean等）作为变量名。
- **区分大小写：** Java 是大小写敏感的，因此变量名中的大小写字母被视为不同的符号。例如，`myVariable` 和 `myvariable` 是两个不同的变量。
- **不以数字开头：** 变量名不能以数字开头，但可以包含数字。

```java
public class MyClass {
    // 使用驼峰命名法
    public static int myStaticVariable;

    // 使用大写蛇形命名法
    public static final int MAX_SIZE = 100;

    // 避免使用缩写
    public static final String employeeName;

    // 具有描述性的变量名
    public static double defaultInterestRate;
}
```

### 📌 Java输入输出

```java
import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();          // 读整数
    double x = in.nextDouble();    // 读小数
    String s = in.next();          // 读一个“单词”（空白分隔）
    in.nextLine();                 // 读掉当前行剩余换行
    String line = in.nextLine();   // 读一整行（可含空格）
    System.out.printf("n=%d, x=%.2f, s=%s, line=%s%n", n, x, s, line);
  }
}
//System.out.println() is just the way that you ask Java to print out the value of something followed by a new line (ln). 
//System.out.print() without the ln will print out something without advancing to the next new line. 
```

### 📌 Math函数

#### 1) 取绝对值 `abs`

```java
System.out.println(Math.abs(-5));      // 5
System.out.println(Math.abs(-3.2));    // 3.2
```

#### 2) 幂运算 `pow` 与 开方 `sqrt`

```java
System.out.println(Math.pow(2, 10));   // 1024.0
System.out.println(Math.sqrt(9));      // 3.0
```

小贴士：整数次方且指数小时，优先自己写乘法/循环，避免 `double` 误差。

#### 3) 取最小/最大 `min` / `max`

```java
System.out.println(Math.min(3, 7));           // 3
System.out.println(Math.max(3.5, 2.1));       // 3.5
```

#### 4) 舍入相关：`round` / `floor` / `ceil`

```java
System.out.println(Math.round(2.49));  // 2  （≈ 四舍五入到最接近整数）
System.out.println(Math.round(2.5));   // 3  （实现等价于 floor(x+0.5)）

System.out.println(Math.floor(2.9));   // 2.0（向下取整）
System.out.println(Math.ceil(2.1));    // 3.0（向上取整)

// 负数要特别注意：
System.out.println(Math.floor(-2.3));  // -3.0（向“更小”的数取整）
System.out.println(Math.ceil(-2.3));   // -2.0（向“更大”的数取整）
System.out.println(Math.round(-1.5));  // -1  （因为 floor(-1.5 + 0.5) = floor(-1.0) = -1）
```

**常见坑**：`(int)2.9` 是**直接截断**成 `2`，不是四舍五入；要四舍五入请用 `Math.round` 或 `Math.floor(x+0.5)`。

#### 5) 随机数 `random()`（返回 `[0,1)` 的 `double`）

```java
public class Main {
    public static void main(String[] args) {
        // Math.random(): [0.0, 1.0)
        double r = Math.random();
        System.out.println("r in [0,1): " + r);

        // 0..n-1
        int n = 6;
        int a = (int)(Math.random() * n);
        System.out.println("int in [0," + (n-1) + "]: " + a);

        // [lo, hi]  (闭区间，含两端)
        int lo = 10, hi = 20;
        int b = lo + (int)(Math.random() * (hi - lo + 1));
        System.out.println("int in [" + lo + "," + hi + "]: " + b);

        // [lo, hi)  (左闭右开，不含 hi)
        int c = lo + (int)(Math.random() * (hi - lo));
        System.out.println("int in [" + lo + "," + hi + "): " + c);
    }
}
```

### 📌  赋值与表达式

```java
public class Main {
    public static void main(String[] args) {
        int a = 7;                  // = 赋值：把右侧表达式的值放入左侧变量
        int b = 3;

        // 基本运算
        System.out.println(a + b);  // 10  加
        System.out.println(a - b);  // 4   减
        System.out.println(a * b);  // 21  乘
        System.out.println(a / b);  // 2   整数除法，截断小数
        System.out.println(a % b);  // 1   取模（余数）

        // 让除法产生小数：任一操作数变 double
        System.out.println(a / 3.0);      // 2.333...
        System.out.println((double)a / b);// 2.333...

        // 复合赋值：相当于 x = x (+/-/*///%) expr
        int x = 10;
        x += 5;        // 15
        x -= 3;        // 12
        x *= 2;        // 24
        x /= 4;        // 6
        x %= 5;        // 1
        System.out.println(x);      // 1

        // 自增自减：++ --
        int n = 5;
        System.out.println(n++);    // 5  后缀：先用值，再 +1；n 变 6
        System.out.println(++n);    // 7  前缀：先 +1，再用值；n 变 7
        System.out.println(n--);    // 7  后缀：先用值，再 -1；n 变 6
        System.out.println(--n);    // 5  前缀：先 -1，再用值；n 变 5

        // 组合在表达式里（看清“先用还是先改”）
        int i = 1, y = 10;
        int z = i++ + ++y;          // z = 1 + 11 = 12；i=2, y=11
        System.out.println("i=" + i + ", y=" + y + ", z=" + z);

        // 字符串拼接：有 String 时 + 表示拼接
        System.out.println("sum=" + (a + b)); // "sum=10"
        System.out.println("a=" + a + ", b=" + b); // 自动转字符串

        // 复合赋值的类型提升（容易被忽略）
        byte bb = 1;
        // bb = bb + 1;            // 编译错：右侧是 int
        bb += 1;                    // ✅ 复合赋值会隐式窄化转换
        System.out.println(bb);     // 2
    }
}

```

### 📌 Homework

**Lab1：You must use exactly 5 different print statements.(println and/or print).**

Output:

I am Sam. Sam I am. I do not like them, Sam-I-am. 

I do not like green eggs and ham.

**Lab2 ：Create Variables and Printing:**

For you to do:

- Create a boolean variable called "isTrue" and set it to false
- Create a double variable called "money" and set it to 99999.99
- Print the variable "money" first
- Then print the variable "isTrue" without skipping to the next line.

**Lab 3: Create Variables and Printing 2:**

For you to do:

- Create a String variable called "name" and set it to "Chen"
- Create an integer variable called "age" and set it to 50
- Create an integer variable called "iq" and set it to the value of age (do NOT use '= 50')
- Print the value of name
- Print the value of age without skipping a new line
- Print the value of iq

**Lab 4: Create Variables and Printing them:**

For you to do:

1. Create two String variables called `firstName` and `lastName` respectively.
2. Assign the String `"Bob"` to `firstName` and `"Jones"` to `lastName`.
3. Print `firstName` and `lastName`, one per line. Each should use a different print statement.

**Lab 5: Output Average Value:**

For example, if the list is {78,80,77}.

Average =78.33333333333333
