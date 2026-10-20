## 📚APCSA 第二轮复习 01：变量、表达式、类型转换与方法基础

## 1. 第二轮目标

- 写出表达式的**类型、中间结果、最终值**。
- 解释为什么 `double result = a / b;` 仍可能丢失小数。
- 区分编译错误、运行时错误和结果错误。
- 判断随机数的最小值、最大值，以及能否覆盖所有要求值。
- 追踪局部变量、参数、实例字段和静态字段的变化。
- 在给定方法签名下完成短 FRQ，并用边界样例检查。

## 2. 核心知识与易错点

### 2.1 程序结构与输出

```java
public class Main {
    public static void main(String[] args) {
        int score = 85;
        System.out.print("Score: ");
        System.out.println(score);
    }
}
```

输出为 `Score: 85`，随后换行。

| 写法 | 行为 |
| --- | --- |
| `System.out.print(x);` | 输出后不主动换行 |
| `System.out.println(x);` | 输出后换行 |
| `System.out.println();` | 只换行 |
| `\n` | 字符串中的换行 |
| `\"` | 字符串中的双引号 |
| `\\` | 字符串中的一个反斜杠 |

```java
System.out.println("Path: C:\\AP");
System.out.println("She said \"Hi\".");
```

```text
Path: C:\AP
She said "Hi".
```

读输出题时，给每个 `print` 标记“当前行”，遇到 `println` 再换行，不要自行补空格。

### 2.2 类型、声明与初始化

本章主线使用 `int`、`double`、`boolean` 和 `String`。

| 类型 | 示例 | 要点 |
| --- | --- | --- |
| `int` | `int count = 12;` | 整数，32 位有符号 |
| `double` | `double rate = 0.25;` | 浮点数，可能存在表示误差 |
| `boolean` | `boolean ready = false;` | 只有 `true`、`false` |
| `String` | `String name = "Ada";` | 引用类型，不是基本类型 |

```java
int a = 7;
int b = a;
a = 9;
System.out.println(a + " " + b); // 9 7
```

`b = a` 复制当时的整数值，不建立持续联动。

**局部变量：必须在使用前确定已赋值，不要求声明时就赋值。**

```java
int total;
total = 12;
System.out.println(total);  // 合法

// int count;
// System.out.println(count); // 编译错误：使用前没有赋值
```

**字段有默认值，局部变量不能套用这条规则。**

| 字段类型 | 未显式赋值时的默认值 |
| --- | --- |
| `int` | `0` |
| `double` | `0.0` |
| `boolean` | `false` |
| 引用类型 | `null` |

`null` 不等于空字符串 `""`。

标识符区分大小写，不能是关键字，不能以数字开头。课堂命名使用 `studentCount` 这样的 lowerCamelCase；不要背完整关键字表。

### 2.3 整数除法与取余

**先看操作数类型，再看接收结果的变量类型。**

```java
int a = 17;
int b = 5;
double x = a / b;           // 3.0
double y = (double) a / b;  // 3.4
double z = (double) (a / b);// 3.0
```

| 表达式 | 运算过程 | 结果 |
| --- | --- | --- |
| `17 / 5` | 整数除法 | `3` |
| `17 / 5.0` | 浮点除法 | `3.4` |
| `(double) 17 / 5` | 转换后再除 | `3.4` |
| `(double) (17 / 5)` | 整数除法后再转换 | `3.0` |
| `17 % 5` | 求余数 | `2` |

整数除法向 0 截断：`-17 / 5 == -3`。非零整数余数与被除数同号：`-17 % 5 == -2`。

自检关系：`a == (a / b) * b + a % b`，其中 `b != 0`，且不考虑整数溢出的特殊情况。

**应用：拆位与单位换算**，前提均为非负整数：

```java
int n = 472;
int hundreds = n / 100;     // 4
int tens = n / 10 % 10;     // 7
int ones = n % 10;          // 2

int seconds = 3671;
int hours = seconds / 3600;        // 1
int minutes = seconds % 3600 / 60; // 1
int remaining = seconds % 60;      // 11
```

### 2.4 自动转换、强制转换与溢出

```java
double a = 8;       // 合法：8 转为 8.0
// int b = 8.6;     // 编译错误：需要显式转换
int c = (int) 8.6;  // 8
int d = (int) -8.6; // -8，向 0 截断
```

“转换为 `double`”不等于“之前的运算自动变成浮点运算”。

对于非负、转换结果在 `int` 范围内的数，`(int) (x + 0.5)` 可用于课堂中的最近整数舍入。不要把它直接推广为负数舍入公式。

`int` 范围：`-2147483648` 到 `2147483647`。整数溢出不会自动变成 `double`，也不会自动报错。

```java
int value = Integer.MAX_VALUE;
value++;
System.out.println(value); // -2147483648
```

浮点误差要知道原因，但本章不展开金融精度处理。

```java
System.out.println(0.1 + 0.2 == 0.3); // false
```

### 2.5 表达式顺序、赋值与字符串拼接

本章常见优先级：括号 → 转换/一元运算 → `* / %` → `+ -` → 赋值。

同级的 `* / %` 和二元 `+ -` 按从左到右分组计算。

```java
System.out.println(18 / 4 * 2); // 8，不是 2
System.out.println(18 / (4 * 2)); // 2
System.out.println(17 % 5 * 2); // 4
```

`+` 遇到字符串操作数时执行拼接；仍需逐步计算。

```java
System.out.println(2 + 3 + "AP");   // 5AP
System.out.println("AP" + 2 + 3);   // AP23
System.out.println("AP" + (2 + 3)); // AP5
```

```java
int x = 8;
x += 3; // 11
x /= 2; // 5
x %= 3; // 2
```

常量用 `final` 声明；惯例是 `MAX_SIZE`，不是所有 `static` 字段都用全大写。

```java
final int MAX_SIZE = 20;
int count = MAX_SIZE - 1;
// MAX_SIZE = 30; // 编译错误
```

主线只使用独立语句 `x++;`、`x--;`。原稿中把多个前后缀自增嵌入一个表达式的写法移至拓展，避免用语法谜题代替算法训练。

### 2.6 Math 方法与随机数

| 方法 | 示例 | 返回结果/范围 |
| --- | --- | --- |
| `Math.abs(int)` | `Math.abs(-7)` | `7`，类型为 `int` |
| `Math.abs(double)` | `Math.abs(-7.5)` | `7.5`，类型为 `double` |
| `Math.pow(double, double)` | `Math.pow(2, 3)` | `8.0`，类型为 `double` |
| `Math.sqrt(double)` | `Math.sqrt(25)` | `5.0`，类型为 `double` |
| `Math.random()` | 每次调用生成新值 | `double`，`0.0 <= r < 1.0` |

注意：`^` 不是 Java 的幂运算符。`Math.pow(2, 3)` 虽然数学结果为整数，返回类型仍是 `double`。

对适当大小的整数边界 `lo <= hi`，生成闭区间 `[lo, hi]` 的随机整数：

```java
int value = (int) (Math.random() * (hi - lo + 1)) + lo;
```

例如 `[4, 9]` 有 6 个整数：

```java
int value = (int) (Math.random() * 6) + 4;
```

| 步骤 | 范围 |
| --- | --- |
| `Math.random()` | `[0.0, 1.0)` |
| `Math.random() * 6` | `[0.0, 6.0)` |
| `(int) (Math.random() * 6)` | `0, 1, 2, 3, 4, 5` |
| 再加 `4` | `4, 5, 6, 7, 8, 9` |

错误例子：

```java
int a = (int) Math.random() * 6 + 4; // 恒为 4
int b = (int) (Math.random() * 5) + 4; // 只有 4..8
```

**随机题三步检查：最小值、最大值、是否覆盖所有目标值。**

`Math.min/max/floor/ceil/round` 保留为“题目给出功能时可用”的工具箱，不要求全部背诵。特别注意 `Math.round(double)` 返回 `long`；本章核心题不依赖它。`Math.abs(Integer.MIN_VALUE)` 是超出本章常规数值范围的边界特例，不用于本套训练。

### 2.7 方法：参数、返回值与调用

```java
public static double average(int first, int second) {
    return ((double) first + second) / 2;
}
```

| 部分 | 本例含义 |
| --- | --- |
| 返回类型 | `double` |
| 方法名 | `average` |
| 形参 | `first`、`second` |
| 实参 | 调用 `average(7, 10)` 中的 `7`、`10` |
| 返回结果 | `8.5` |

`return` 把值交给调用者；`println` 把内容输出。二者不能互相替代。

```java
double value = average(7, 10); // 得到返回值，不输出
System.out.println(value);   // 此处才输出
```

Java 参数传递是**值传递**。对本章的基本类型参数，修改形参不改变调用者变量。

```java
public static void change(int x) {
    x += 5;
}

// 在同一类的 main 中：
int number = 10;
change(number);
System.out.println(number); // 10
```

需要更新调用者变量时，可以返回新值后接收：

```java
public static int increased(int x) {
    return x + 5;
}

// 在同一类的 main 中：
number = increased(number);
```

对象引用也按值传递，但修改对象内容与重新给形参赋引用是两回事；留到对象/数组专题详细复习。

### 2.8 局部变量、字段与 static

| 类别 | 位置 | 使用前的值 | 谁拥有 |
| --- | --- | --- | --- |
| 局部变量 | 方法或代码块内 | 必须先确定赋值 | 当前方法调用/代码块 |
| 参数 | 方法头 | 调用时由实参提供 | 当前方法调用 |
| 实例字段 | 类内、方法外，无 `static` | 有默认值 | 每个对象各一份 |
| 静态字段 | 类内、方法外，有 `static` | 有默认值 | 同一个类共享一份 |

```java
public class Counter {
    private int value;
    private static int created;

    public Counter(int start) {
        value = start;
        created++;
    }

    public void add(int amount) {
        value += amount;
    }

    public int getValue() {
        return value;
    }

    public static int getCreated() {
        return created;
    }
}
```

```java
// 放在另一个类的 main 方法中，假设此前尚未创建 Counter 对象：
Counter first = new Counter(3);
Counter second = new Counter(8);
first.add(2);
System.out.println(first.getValue());  // 5
System.out.println(second.getValue()); // 8
System.out.println(Counter.getCreated()); // 2
```

静态方法没有当前对象，不能直接使用实例字段；可通过明确的对象访问其可访问成员。

**同名参数遮蔽字段**：

```java
private int score;

public void setScore(int score) {
    this.score = score;
}
```

`this.score` 是字段，右边的 `score` 是参数。若写 `score = score;`，字段不会改变。

### 2.9 三类错误要分开

| 类别 | 例子 | 判断依据 |
| --- | --- | --- |
| 编译错误 | `int x = 2.5;` | 类型不匹配，不能正常开始运行 |
| 运行时错误 | `int zero = 0; int x = 5 / zero;` | 执行整数除以 0 时抛异常 |
| 逻辑错误 | `double avg = (7 + 8) / 2;` | 能运行，却得到 `7.0` 而非 `7.5` |

不要把“没有输出”一概叫作编译错误，也不要把 `double` 除以零的行为直接套用到整数除法。

## ✍️ 3. 做题方法

### MCQ：值和类型一起追踪

| 行号 | 右侧表达式类型 | 中间值 | 赋值后的变量值 |
| --- | --- | --- | --- |
| `double x = 9 / 4;` | `int` | `2` | `2.0` |
| `double y = 9 / 4.0;` | `double` | `2.25` | `2.25` |

随机题先写范围，状态题画变量表。对 I/II/III 组合题逐个判断，不根据选项猜答案。

### FRQ：写之前检查四件事

1. 方法头：返回什么？参数顺序是什么？
2. 前提：哪些输入已保证合法？不用擅自改规则。
3. 状态：题目要改字段、返回数值，还是两者都要？
4. 边界：最小合法值、整除情况、不能整除情况分别怎样？

完成方法题通常只写要求的方法，不必补 `main`、键盘输入或额外输出。

## 4. MCQ 训练（原创，18 题）

建议先独立作答，再查看第 7 节答案。每题只有一个正确选项。所有代码片段均放在合法上下文中；另有说明的除外。

### MCQ 1｜整数除法

```java
int a = 23;
int b = 4;
double x = a / b;
double y = a % b;
System.out.println(x + " " + y);
```

A. `5.75 3.0`  
B. `5.0 3.0`  
C. `5 3`  
D. 编译错误

### MCQ 2｜转换放在哪里

已知 `int a = 9; int b = 4;`，哪些表达式结果为 `2.25`？

```java
I.   (double) (a / b)
II.  (double) a / b
III. a / (double) b
```

A. 仅 I  
B. 仅 II  
C. 仅 I 和 II  
D. 仅 II 和 III

### MCQ 3｜负数的商与余数

```java
System.out.println(-19 / 6 + " " + -19 % 6);
```

A. `-4 5`  
B. `-3 1`  
C. `-3 -1`  
D. `-4 -1`

### MCQ 4｜拼接顺序

```java
System.out.println(3 + 4 + "X" + 2 + 1);
```

A. `7X21`  
B. `7X3`  
C. `34X21`  
D. `10X`

### MCQ 5｜赋值语句是否合法

以下三个声明分别独立判断，哪些能够编译？

```java
I.   int a = 6.0;
II.  double b = 6;
III. int c = (int) 6.9;
```

A. 仅 I 和 II  
B. 仅 II 和 III  
C. 仅 I 和 III  
D. I、II、III

### MCQ 6｜默认值

```java
public class Sample {
    private static int count;

    public static void main(String[] args) {
        int local;
        System.out.println(count + " " + local);
    }
}
```

A. 输出 `0 0`  
B. 输出 `0 null`  
C. 编译错误，因为 `count` 没有显式初始化  
D. 编译错误，因为 `local` 使用前没有赋值

### MCQ 7｜final

```java
final int LIMIT = 12;
int count = LIMIT / 5;
count += 2;
LIMIT = count;
```

哪一项描述正确？

A. 最终 `LIMIT` 为 `4`  
B. 最终 `LIMIT` 为 `4.4`  
C. `LIMIT = count;` 导致编译错误  
D. `count += 2;` 导致编译错误

### MCQ 8｜复合赋值

```java
int n = 17;
n /= 4;
n *= 3;
n %= 5;
System.out.println(n);
```

A. `2`  
B. `2.75`  
C. `3`  
D. `12`

### MCQ 9｜参数与返回值

```java
public static int adjust(int value) {
    value += 4;
    return value;
}
```

在同一类的 `main` 中执行：

```java
int value = 6;
adjust(value);
System.out.print(value + " ");
value = adjust(value);
System.out.println(value);
```

A. `10 14`  
B. `6 6`  
C. `10 10`  
D. `6 10`

### MCQ 10｜实例与静态字段

```java
public class Meter {
    private int value;
    private static int total = 0;

    public Meter(int start) {
        value = start;
        total += start;
    }

    public void add(int amount) {
        value += amount;
        total += amount;
    }

    public int getValue() { return value; }
    public static int getTotal() { return total; }
}
```

假设程序首次使用 `Meter`，在另一个类的 `main` 中执行：

```java
Meter a = new Meter(2);
Meter b = new Meter(5);
a.add(3);
System.out.println(a.getValue() + " " + b.getValue()
                   + " " + Meter.getTotal());
```

A. `5 8 10`  
B. `5 5 10`  
C. `5 5 7`  
D. `2 5 10`

### MCQ 11｜Math 返回类型

以下语句分别独立判断，哪一项不能编译？

A. `double x = Math.sqrt(36);`  
B. `int x = Math.abs(-6);`  
C. `int x = Math.pow(2, 3);`  
D. `double x = Math.pow(2, 3);`

### MCQ 12｜随机整数

哪些表达式能按通常的随机整数生成模型产生 `[3, 8]` 中的每个整数，且不产生区间外的数？

```java
I.   (int) (Math.random() * 6) + 3
II.  (int) Math.random() * 6 + 3
III. (int) (Math.random() * 5) + 3
```

A. 仅 I  
B. 仅 I 和 II  
C. 仅 I 和 III  
D. I、II、III

### MCQ 13｜两组随机数的范围

```java
int x = (int) (Math.random() * 7) + 2;
int y = (int) (Math.random() * 4) + 6;
System.out.println(x + " " + y);
```

哪一项可能输出？

A. `9 7`  
B. `4 10`  
C. `1 8`  
D. `8 9`

### MCQ 14｜运算顺序

```java
System.out.println(20 / 6 * 3 + 20 % 6);
```

A. `3`  
B. `11`  
C. `12`  
D. `12.0`

### MCQ 15｜转义与换行

```java
System.out.print("A\nB");
System.out.println("\\C");
```

忽略输出结尾的换行，哪一项正确？

**A.**

```text
A\nB\C
```

**B.**

```text
A
B\\C
```

**C.**

```text
A
B\C
```

**D.**

```text
AB
\C
```

### MCQ 16｜逐行追踪

```java
int a = 5;
int b = a;
a++;
b += a;
a--;
System.out.println(a + " " + b);
```

A. `5 11`  
B. `6 11`  
C. `5 10`  
D. `6 12`

### MCQ 17｜int 溢出

```java
int n = Integer.MAX_VALUE;
n++;
System.out.println(n);
```

A. `2147483648`  
B. `2147483647`  
C. 运行时抛异常  
D. `-2147483648`

### MCQ 18｜同名参数

```java
public class Player {
    private int score = 7;

    public void setScore(int score) {
        score = score + 3;
    }

    public int getScore() {
        return score;
    }
}
```

在另一个类的 `main` 中执行：

```java
Player p = new Player();
p.setScore(10);
System.out.println(p.getScore());
```

A. `10`  
B. `7`  
C. `13`  
D. 编译错误

## 5. FRQ 训练

### FRQ 1｜TripMath：单位换算与平均速度

三个方法放在同一个 `TripMath` 类中。

**(a)** 完成 `wholeMinutes`，返回总秒数中包含的完整分钟数。前提：`totalSeconds >= 0`。

```java
public static int wholeMinutes(int totalSeconds)
```

**(b)** 完成 `extraSeconds`，返回扣除完整分钟后的剩余秒数。前提同上。

```java
public static int extraSeconds(int totalSeconds)
```

**(c)** 完成 `speedKmh`，根据距离（米）和耗时（秒）返回平均时速（千米/小时）。前提：`meters >= 0`，`seconds > 0`。

```java
public static double speedKmh(int meters, int seconds)
```

| 调用 | 返回值 |
| --- | --- |
| `wholeMinutes(125)` | `2` |
| `extraSeconds(125)` | `5` |
| `wholeMinutes(59)` | `0` |
| `extraSeconds(60)` | `0` |
| `speedKmh(1000, 240)` | `15.0` |
| `speedKmh(125, 60)` | `7.5` |

不得通过打印代替返回。先用纸笔写单位换算，再写代码。

### FRQ 2｜NumberCode：整数拆位与字符串

前提：`100 <= number <= 999`。不得使用数组、循环或字符串截取。

**(a)** 完成 `digitSum`，返回三位数的各位数字之和。

```java
public static int digitSum(int number)
```

**(b)** 完成 `reverseValue`，返回反转数字顺序后的整数。前导零在整数结果中自然省略。

```java
public static int reverseValue(int number)
```

**(c)** 完成 `toLabel`，返回“百位-十位-个位”格式的字符串，保留所有数字，不加空格。

```java
public static String toLabel(int number)
```

| 输入 | `digitSum` | `reverseValue` | `toLabel` |
| --- | --- | --- | --- |
| `472` | `13` | `274` | `"4-7-2"` |
| `508` | `13` | `805` | `"5-0-8"` |
| `120` | `3` | `21` | `"1-2-0"` |

### FRQ 3｜RandomPractice：从范围到表达式

三个方法均使用 `Math.random()`，不能调用其他随机数 API。

**(a)** 完成 `randomScore`，生成闭区间 `[35, 85]` 内的随机整数，所有目标整数按通常模型等概率。

```java
public static int randomScore()
```

**(b)** 完成 `randomMultiple`，生成 `{12, 16, 20, 24, 28}` 中的随机整数，五个结果按通常模型等概率。不能用条件语句。

```java
public static int randomMultiple()
```

**(c)** 完成 `randomTenths`，生成 `{0.0, 0.1, ..., 0.9}` 中的随机 `double`，十个结果按通常模型等概率。用“随机整数再除以 10”的方式实现；不要求浮点数具有精确十进制表示。

```java
public static double randomTenths()
```

额外口述，不计入代码分：解释为什么 `(int) Math.random() * 51 + 35` 不满足 (a)。

### FRQ 4｜ReadingLog：参数、字段与返回值

编写完整的 `ReadingLog` 类。每个对象独立记录某位学生的阅读情况，不使用 `static` 字段。规则如下：

- 构造器 `ReadingLog(String studentName)` 保存姓名，将总页数、阅读次数都初始化为 `0`。
- `void record(int pages)` 增加总页数，并将次数加 `1`。前提：`pages > 0`。
- `double averagePages()` 返回每次阅读的平均页数。前提：已经至少调用过一次 `record`。
- `String getSummary()` 返回 `姓名:总页数:次数`，没有额外空格。

```java
ReadingLog first = new ReadingLog("Ada");
ReadingLog second = new ReadingLog("Ben");

first.record(12);
first.record(15);
second.record(8);

System.out.println(first.averagePages());
System.out.println(first.getSummary());
System.out.println(second.getSummary());
```

```text
13.5
Ada:27:2
Ben:8:1
```

提示：确认总页数和次数是在字段上累加，不是在 `record` 中重新创建同名局部变量。

## 6. 官方样题与往年真题迁移

### 6.1 官方 MCQ 样题：转换与随机数

来源：[AP Computer Science A Course and Exam Description，Effective Fall 2025](https://apcentral.collegeboard.org/media/pdf/ap-computer-science-a-course-and-exam-description.pdf#page=156)。定位：PDF 第 156 页，印刷页码 149，Sample Exam Questions 第 1、2 题。

**这是官方样题，不是某一年的实考试卷。** 按原 PDF 完成题目，不需要抄题。

| 题号 | 对应本章 | 学生作答要求 |
| --- | --- | --- |
| Sample MCQ 1 | 2.3、2.4 | 分别写出“转换之前”和“赋值之后”的值 |
| Sample MCQ 2 | 2.6 | 先写两个变量各自的整数范围，再排除选项 |

<details>
<summary>教师核对：官方样题答案与本章连接</summary>

第 1 题选 B：转换后的两个结果为 `7.0` 与 `7.5`。第 2 题选 B：两个变量范围分别为 `5..14`、`10..14`。要求学生解释边界，避免只记选项字母。

### 6.2 往年 FRQ：2024 Q1(a) Feeder

- [官方题目 PDF](https://apcentral.collegeboard.org/media/pdf/ap24-frq-comp-sci-a.pdf#page=3)：PDF 第 3—5 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap24-sg-computer-science-a.pdf#page=3)：Q1(a) 为 4 分。

这是本章“随机整数 + 字段更新”的真题迁移，同时需要已学过的 `if/else`。只安排 **(a)**；(b) 涉及循环，可留到循环专题。

先看原题，然后做三个拆解：区分 5% 与 95% 两种情况；生成 `[10, 50]` 的随机整数；更新食物量并保证不为负。同一天所有鸟采用同一个随机食量。

**本章训练任务：** 限时 12 分钟完成原题 (a)，再用“原有食物不足”和“异常情况”检查代码。

教师按官方细则检查随机调用、概率划分、整数区间、数量缩放与状态更新；具体给分以原细则为准。

### 6.3 往年 FRQ：2024 Q2 Scoreboard

- [官方题目 PDF](https://apcentral.collegeboard.org/media/pdf/ap24-frq-comp-sci-a.pdf#page=8)：PDF 第 8—9 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap24-sg-computer-science-a.pdf)：定位 Q2。

与本章字段、构造器和字符串输出有关，也需要条件分支。建议完成 ReadingLog 后作为进阶作业；按原题给出的调用表追踪状态，再写类。

**来源与适用性提醒：** College Board 提醒旧题与 2025—26 修订后的考试并非完全对齐。本章按知识点选取旧题，不用旧卷的单元编号、时间或题型分布代表现行考试。公开真题及解析入口见[官方历年题页面](https://apcentral.collegeboard.org/courses/ap-computer-science-a/exam/past-exam-questions)。

## 7. MCQ 答案与解析

### 7.1 答案速查

| 题号 | 答案 | 考点 | 错因标签 |
| --- | --- | --- | --- |
| 1 | B | 整数除法后赋给 double | TYPE |
| 2 | D | 转换发生的位置 | CAST |
| 3 | C | 负数商与余数 | DIV |
| 4 | A | 数值加法与拼接 | CONCAT |
| 5 | B | 赋值兼容性 | TYPE |
| 6 | D | 局部变量初始化 | INIT |
| 7 | C | final 不能重新赋值 | FINAL |
| 8 | A | 复合赋值顺序 | TRACE |
| 9 | D | 参数值传递与接收返回值 | PARAM |
| 10 | B | 实例字段与共享字段 | STATE |
| 11 | C | Math.pow 返回 double | TYPE |
| 12 | A | 随机区间与转换位置 | RANGE |
| 13 | D | 随机边界 | RANGE |
| 14 | B | 同级运算顺序 | ORDER |
| 15 | C | 换行与反斜杠 | OUTPUT |
| 16 | A | 变量独立、逐行赋值 | TRACE |
| 17 | D | int 溢出 | OVERFLOW |
| 18 | B | 参数遮蔽字段 | SCOPE |

### 7.2 逐题解析

1. `23 / 4` 先得到 `int` 值 `5`，再存为 `5.0`；余数 `3` 存为 `3.0`。A 把接收类型误当成运算类型；C 忽略了输出变量的类型；D 误认为 int 不能转 double。
2. I 先整数除法得到 `2`，转换后为 `2.0`；II、III 在除法前已有一个 double 操作数，结果均为 `2.25`。
3. `-19 / 6` 向 0 截断为 `-3`；余数为 `-1`。核对 `(-3) * 6 + (-1) == -19`。不是向负无穷取整，也不能把余数强行写成正数。
4. 先计算 `3 + 4 == 7`，随后 `7 + "X"` 变为字符串，后续依次拼接 `2`、`1`，得到 `7X21`。
5. I 是 double 到 int 的隐式窄化，不能编译；II 自动扩大转换；III 显式截断成 `6`。分别判断，不把声明当作连续代码。
6. 静态字段 `count` 默认是 `0`，但局部变量 `local` 没有可直接使用的默认值，整段不能编译。
7. `count` 可以变化，但已初始化的 `final` 变量 `LIMIT` 不能再次赋值。程序不能编译，不能继续讨论最终输出。
8. 依次为 `17 / 4 == 4`、`4 * 3 == 12`、`12 % 5 == 2`。全程是 int 运算。
9. 首次返回的 `10` 被丢弃，调用者变量仍是 `6`；第二次用赋值接收返回值，变量才成为 `10`。输出 `6 10`。
10. a 的实例值从 `2` 变成 `5`；b 仍为 `5`。静态 total 依次为 `2`、`7`、`10`，输出 `5 5 10`。
11. `Math.pow` 返回 double，不能直接赋给 int；需要显式转换，或使用 double 接收。其余三个声明合法。
12. I 生成 `0..5` 再加 `3`；II 在乘法前截断，恒为 `3`；III 只有 `3..7`，缺少 `8`。
13. x 为 `2..8`，y 为 `6..9`。只有 `8 9` 的两个值同时在范围内。A 的 x、B 的 y、C 的 x 越界。
14. `20 / 6 == 3`，接着乘 `3` 得到 `9`；余数为 `2`，相加得到 int 值 `11`。不能先把分母和乘数结合起来。
15. 第一条输出 A，换行后输出 B，但不在 B 后换行。第二条紧接 B 输出一个反斜杠和 C，然后换行。
16. a、b 初始分别为 `5`、`5`；a++ 后是 `6`、`5`；b += a 后是 `6`、`11`；a-- 后是 `5`、`11`。
17. 超过 int 上界后按 Java 整数规则回绕到最小值。不会自动扩大存储类型，也不会因普通整数加法溢出而抛异常。
18. `setScore` 内的 score 指参数，仅将参数从 `10` 改为 `13`。对象字段仍是 `7`。若要设置字段，应按题意写 `this.score = score;`；若要存入参数加 3，则写 `this.score = score + 3;`。

## 8. FRQ 参考解与课堂评分

### FRQ 1 参考解

```java
public static int wholeMinutes(int totalSeconds) {
    return totalSeconds / 60;
}

public static int extraSeconds(int totalSeconds) {
    return totalSeconds % 60;
}

public static double speedKmh(int meters, int seconds) {
    return (double) meters / seconds * 3.6;
}
```

每小问 3 分，共 9 分：

| 小问 | 课堂评分点（各 1 分） |
| --- | --- |
| (a) | 使用正确参数；用 60 做整数除法；正确返回 int |
| (b) | 使用正确参数；用 `% 60`；正确返回 int |
| (c) | 除法前引入 double；正确按 3.6 换算；返回正确表达式 |

常见失分：`meters / seconds * 3.6` 在第一步已经丢失精度；`meters / 1000` 先得到整千米数也会丢失信息。

等价解：`meters / 1000.0 / (seconds / 3600.0)`。

### FRQ 2 参考解

```java
public static int digitSum(int number) {
    int hundreds = number / 100;
    int tens = number / 10 % 10;
    int ones = number % 10;
    return hundreds + tens + ones;
}

public static int reverseValue(int number) {
    int hundreds = number / 100;
    int tens = number / 10 % 10;
    int ones = number % 10;
    return ones * 100 + tens * 10 + hundreds;
}

public static String toLabel(int number) {
    int hundreds = number / 100;
    int tens = number / 10 % 10;
    int ones = number % 10;
    return hundreds + "-" + tens + "-" + ones;
}
```

每小问 3 分：正确提取所需数字 1 分；正确组合（相加/位权/分隔符）1 分；正确返回及遵守限制 1 分。等价拆位方式可得分。

检查 `100`、`101`、`120`、`999`。`reverseValue(120)` 是 `21`，不是字符串 `"021"`；`toLabel(120)` 则必须保留个位 `0`。

### FRQ 3 参考解

```java
public static int randomScore() {
    return (int) (Math.random() * 51) + 35;
}

public static int randomMultiple() {
    return ((int) (Math.random() * 5) + 3) * 4;
}

public static double randomTenths() {
    int digit = (int) (Math.random() * 10);
    return digit / 10.0;
}
```

每小问 3 分：

| 小问 | 课堂评分点（各 1 分） |
| --- | --- |
| (a) | 正确调用并在乘法后转换；51 个候选值；平移至 35..85 |
| (b) | 生成 5 个等概率候选；正确缩放/平移为指定集合；返回且不用条件语句 |
| (c) | 生成整数 0..9；使用浮点除法；返回目标集合内的 double |

随机测试只能帮助发现越界，不能证明均匀性；均匀性应由“等宽区间映射到整数”的构造说明。不要要求一次运行必须同时出现最小值和最大值。

### FRQ 4 参考解

```java
public class ReadingLog {
    private String studentName;
    private int totalPages;
    private int sessions;

    public ReadingLog(String studentName) {
        this.studentName = studentName;
        totalPages = 0;
        sessions = 0;
    }

    public void record(int pages) {
        totalPages += pages;
        sessions++;
    }

    public double averagePages() {
        return (double) totalPages / sessions;
    }

    public String getSummary() {
        return studentName + ":" + totalPages + ":" + sessions;
    }
}
```

***
