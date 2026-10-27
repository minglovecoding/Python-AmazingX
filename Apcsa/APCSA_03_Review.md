## 📚APCSA 第二轮复习 03：布尔表达式、条件分支与循环

##  1. 复习目标

- 将“同时满足”“至少一个”“不在范围内”等文字要求翻译为布尔表达式。
- 用真值表和反例判断表达式是否等价。
- 解释短路求值为何影响安全性、方法调用次数和状态。
- 区分多个独立 if 与一条 if/else if/else 链。
- 追踪 for、while、嵌套循环，写出执行次数和退出后的值。
- 完成计数、求和、连续段统计、模拟等方法型 FRQ。
- 用最小输入、边界输入和反例发现错误，而不只运行普通样例。

## 2. 核心知识与易错点

### 2.1 boolean、关系运算与范围

```java
boolean passed = true;
int score = 85;
boolean meetsTarget = score >= 80;
```

boolean 只有 true/false，不能把整数直接当条件，也不能把 boolean 强制转换成 int。

```java
// if (score) { }       // 编译错误
// boolean ready = 1;   // 编译错误
// if (0 <= score <= 100) { } // 编译错误：不能写数学式连锁比较
```

| 文字要求 | Java 表达式 |
| --- | --- |
| 等于/不等于 10 | `x == 10` / `x != 10` |
| 在闭区间 [10,20] 内 | `x >= 10 && x <= 20` |
| 在开区间 (10,20) 内 | `x > 10 && x < 20` |
| 在 [10,20] 外 | `x < 10 || x > 20` |
| 至少一个成立 | `a || b` |
| 两个都成立 | `a && b` |
| 恰好一个成立 | `(a && !b) || (!a && b)`，也可 `a != b` |
| 偶数/奇数（含负整数） | `n % 2 == 0` / `n % 2 != 0` |

负奇数的余数可能为 -1，所以不要用 `n % 2 == 1` 判断所有整数中的奇数。

`=` 是赋值，`==` 是比较。特别注意：若左右两边为 boolean，误用赋值有时**能编译**。

```java
boolean ready = false;
if (ready = true) { // 合法 Java，但把 ready 改为 true；通常不是本意
    System.out.println("go");
}
```

### 2.2 逻辑运算、优先级与真值表

0/1 仅是表中的真值记号，Java 代码仍写 false/true。

| x | y | x && y | x \|\| y | !x | !y |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 1 | 1 |
| 0 | 1 | 0 | 1 | 1 | 0 |
| 1 | 0 | 0 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 | 0 | 0 |

常见运算分组顺序：括号 → 一元操作（如 !）→ 乘除取余 → 加减 → 大小比较 → 相等比较 → && → || → 赋值。

```java
boolean a = true;
boolean b = false;
boolean c = false;
System.out.println(a || b && c);   // true，相当于 a || (b && c)
System.out.println((a || b) && c); // false
```

尽量用括号表达意图，别要求学生背原稿里包含大量拓展运算符的整张优先级表。

### 2.3 德摩根定律与反例

```text
!(a && b)  等价于  !a || !b
!(a || b)  等价于  !a && !b
```

口诀：**每项取反，连接符互换，保留正确括号。**

| 原比较 | 取反后 |
| --- | --- |
| `x < a` | `x >= a` |
| `x <= a` | `x > a` |
| `x == a` | `x != a` |
| `x != a` | `x == a` |

```java
!(x >= 10 && x <= 20)
// 等价于 x < 10 || x > 20
```

对本章的整数比较可直接这样转换；不要未经分析推广到可能包含 NaN 的浮点比较。

**证明等价：**列出全部布尔输入；**推翻等价：**找到一组结果不同的输入即可。

例如 `x < 10 || x > 20` 不等于 `x <= 10 || x >= 20`；取 x=10 就能区分。

### 2.4 短路求值：不仅是算真和假

| 运算 | 左边的结果 | 是否求右边 |
| --- | --- | --- |
| `a && b` | false | 不求 |
| `a && b` | true | 求 |
| `a || b` | true | 不求 |
| `a || b` | false | 求 |

```java
int divisor = 0;
boolean ok = divisor != 0 && 12 / divisor > 2; // false，不会除以 0
```

```java
String text = null;
boolean hasText = text != null && text.length() > 0; // false，安全
boolean absent = text == null || text.length() == 0; // true，安全
```

保护条件必须放在危险操作之前。若交换两边，可能先抛异常。

**要区分两种等价：** 对已经求好值的 boolean 变量，`a && b` 与 `b && a` 真值相同；但当 a/b 代表会抛异常或改变状态的方法调用时，调换顺序可能改变程序行为。

拓展：Java 的单字符 `&`、`|` 也能用于 boolean，但不短路。本章核心解统一使用 `&&`、`||`，不把它们与整数位运算混淆。

### 2.5 分支结构：互斥还是独立

**一条链：最多执行一个分支。**

```java
if (score >= 90) {
    grade = "A";
} else if (score >= 80) {
    grade = "B";
} else {
    grade = "C";
}
```

从高分开始判断。若先判断 `score >= 80`，95 分会被提前归为 B。

**多个 if：每个都要重新判断，前面的状态更新可能影响后面的条件。**

```java
int x = 5;
if (x > 3) {
    x += 2;
}
if (x > 6) {
    x *= 2;
}
System.out.println(x); // 14
```

“满足多种标签”的题适合独立 if；“只能归一类”的题通常适合 if/else if。

```java
// 没有大括号时，else 归属最近的、尚未匹配 else 的 if。
if (x > 0)
    if (y > 0)
        System.out.print("A");
    else
        System.out.print("B");
```

不要按缩进猜；课堂写作统一加大括号。

常见隐蔽错误：

```java
if (x > 0); { // 分号让 if 控制一个空语句；后面的块总执行
    System.out.println("positive");
}
```

### 2.6 while：先判断，再执行，再回去判断

```java
int n = 23;
int count = 0;
while (n > 0) {
    n /= 2;
    count++;
}
System.out.println(count); // 5
```

| 次数 | 本轮开始 n | 本轮结束 n | count |
| --- | --- | --- | --- |
| 1 | 23 | 11 | 1 |
| 2 | 11 | 5 | 2 |
| 3 | 5 | 2 | 3 |
| 4 | 2 | 1 | 4 |
| 5 | 1 | 0 | 5 |

初始条件就为 false 时执行 0 次。最后一次执行结束后还会再判断条件，不要把“判断次数”与“循环体次数”混为一谈。

循环终止要检查：变量是否向退出方向变化？是否可能被某个分支跳过更新？更新会不会又被覆盖？

### 2.7 for：初始化、条件、循环体、更新

```java
int sum = 0;
for (int i = 2; i <= 10; i += 2) {
    sum += i;
}
System.out.println(sum); // 30
```

循环体看到 i 的值是 `2,4,6,8,10`，共 5 次。退出前更新到 12，再发现条件不成立。这里 i 的作用域只在 for 内，不能在外面直接打印它。

对正步长、正常终止且无整数溢出的简单计数循环：

- `i=a; i<b; i+=d`：a<b 时为 `(b-a+d-1)/d` 次（整数运算）；否则 0 次。
- `i=a; i<=b; i+=d`：a<=b 时为 `(b-a)/d+1` 次；否则 0 次。

实际做题优先列出前几项和最后一项；若循环体也改变 i，不要直接套公式。

等价改写：

```java
int i = 2;
while (i <= 10) {
    sum += i;
    i += 2;
}
```

比较两段完整程序时，还需保证 sum 的初值相同。若涉及 continue 或循环变量作用域，机械改写可能不等价。

### 2.8 嵌套循环与字符串遍历

```java
int count = 0;
for (int row = 1; row <= 4; row++) {
    for (int col = 1; col <= row; col++) {
        count++;
    }
}
// 1+2+3+4=10，不是 4*4
```

内层次数固定才可以直接相乘；次数依赖外层变量时按行求和。

字符串单字符遍历：

```java
int count = 0;
for (int i = 0; i < text.length(); i++) {
    if (text.substring(i, i + 1).equals("a")) {
        count++;
    }
}
```

长度为 m 的模式，在长度为 n 的字符串中，合法起点必须满足 `i+m <= n`。允许重叠匹配时，每次起点只加 1。

```java
// 假设 target 非空；可统计重叠出现。
for (int i = 0; i <= text.length() - target.length(); i++) {
    // 比较 text.substring(i, i + target.length()) 与 target
}
```

空字符串、target 比 text 长时，循环应自然执行 0 次。

### 2.9 四种算法状态

| 任务 | 状态初值 | 典型更新 | 常见失误 |
| --- | --- | --- | --- |
| 计数 | count=0 | 条件满足才 ++ | 每轮都加或漏掉最后一次 |
| 求和 | total=0 | total+=value | 把 total 放进循环反复清零 |
| 连续段 | current=0,best=0 | 满足则 ++，否则清零；更新 best | 清零前没记录、最后一段漏记 |
| 模拟 | 当前状态+已执行步数 | 调用一步方法并更新次数 | 状态耗尽后又多执行一天 |

连续段不等于总出现次数。`"aaXaaa"` 中 a 总数为 5，最长连续段为 3。

若题目保证 helper 正确，就按契约调用它，不需要重新实现 helper，更不能为了方便把调用省略掉。

## 3. MCQ 训练

每题只有一个正确选项。代码置于合法上下文，各题独立。

### MCQ 1｜范围判断

哪一项恰好表示整数 x 在闭区间 [12,18] 内？

A. `x >= 12 || x <= 18`  
B. `x > 12 && x < 18`  
C. `x >= 12 && x <= 18`  
D. `12 <= x <= 18`

### MCQ 2｜区间取反

哪一项与 `!(x < 5 || x >= 12)` 对所有整数 x 等价？

A. `x >= 5 && x < 12`  
B. `x > 5 && x <= 12`  
C. `x >= 5 || x < 12`  
D. `x < 5 && x >= 12`

### MCQ 3｜德摩根定律

哪一项与 `!(a && !b)` 等价？a、b 为 boolean 变量。

A. `!a && b`  
B. `a || b`  
C. `!a || !b`  
D. `!a || b`

### MCQ 4｜逻辑优先级

```java
boolean a = true;
boolean b = false;
boolean c = false;
System.out.println((a || b && c) + " " + ((a || b) && c));
```

A. `false false`  
B. `true false`  
C. `true true`  
D. `false true`

### MCQ 5｜短路与整数除零

```java
int d = 0;
boolean result = d != 0 && 20 / d > 3;
System.out.println(result);
```

A. 编译错误  
B. 运行时抛 ArithmeticException  
C. 输出 `false`  
D. 输出 `true`

### MCQ 6｜null 保护

要求 text 为 null 或空字符串时返回 true，否则 false。哪些表达式对所有 String 引用都安全且正确？

```java
I.   text == null || text.length() == 0
II.  text.length() == 0 || text == null
III. text != null && text.length() == 0
```

A. 仅 I  
B. 仅 I 和 II  
C. 仅 I 和 III  
D. I、II、III

### MCQ 7｜被短路的方法调用

同一类中定义：

```java
private static int calls = 0;
public static boolean probe() {
    calls++;
    return true;
}
```

calls 初始为 0，在 main 中执行：

```java
boolean a = false && probe();
boolean b = true || probe();
boolean c = true && probe();
System.out.println(calls + " " + c);
```

A. `3 true`  
B. `2 true`  
C. `0 false`  
D. `1 true`

### MCQ 8｜分支顺序

```java
int score = 95;
String grade;
if (score >= 80) {
    grade = "B";
} else if (score >= 90) {
    grade = "A";
} else {
    grade = "C";
}
System.out.println(grade);
```

A. `A`  
B. `B`  
C. `AB`  
D. 编译错误

### MCQ 9｜独立 if

```java
int x = 4;
if (x < 5) {
    x += 3;
}
if (x > 6) {
    x *= 2;
} else {
    x--;
}
System.out.println(x);
```

A. `7`  
B. `6`  
C. `14`  
D. `8`

### MCQ 10｜else 归属

```java
int x = 2;
int y = -1;
if (x > 0)
    if (y > 0)
        System.out.print("A");
    else
        System.out.print("B");
System.out.print("C");
```

A. `BC`  
B. `AC`  
C. `C`  
D. 无输出

### MCQ 11｜端点与互斥条件

希望 x 小于 10 时返回 `"low"`，10 到 20（含端点）返回 `"mid"`，大于 20 返回 `"high"`。

```java
public static String category(int x) {
    if (x < 10) {
        return "low";
    } else if (/* missing condition */) {
        return "mid";
    } else {
        return "high";
    }
}
```

哪一项可填入？

A. `x < 20`  
B. `x >= 10`  
C. `x > 10 && x <= 20`  
D. `x <= 20`

### MCQ 12｜boolean 赋值

```java
boolean flag = false;
if (flag = true) {
    System.out.print("A ");
} else {
    System.out.print("B ");
}
System.out.println(flag);
```

A. 编译错误  
B. `A true`  
C. `B false`  
D. `A false`

### MCQ 13｜for 次数与退出值

```java
int i;
int count = 0;
for (i = 2; i < 11; i += 3) {
    count++;
}
System.out.println(count + " " + i);
```

A. `4 11`  
B. `3 8`  
C. `3 11`  
D. `4 14`

### MCQ 14｜while 更新

```java
int n = 20;
int count = 0;
while (n > 1) {
    n /= 2;
    count++;
}
System.out.println(count + " " + n);
```

A. `4 1`  
B. `5 0`  
C. `4 0`  
D. `3 2`

### MCQ 15｜嵌套循环次数

```java
int count = 0;
for (int i = 1; i <= 4; i++) {
    for (int j = i; j <= 4; j++) {
        count++;
    }
}
System.out.println(count);
```

A. `16`  
B. `6`  
C. `4`  
D. `10`

### MCQ 16｜循环改写

以下原代码输出 2、4、6、8，每个数后有一个空格。

```java
for (int i = 2; i <= 8; i += 2) {
    System.out.print(i + " ");
}
```

以下 while 中，应怎样替换注释，才能输出相同内容？

```java
int i = 2;
while (/* condition */) {
    System.out.print(i + " ");
    /* update */
}
```

A. 条件 `i < 8`；更新 `i += 2;`  
B. 条件 `i <= 8`；更新 `i += 2;`  
C. 条件 `i <= 8`；更新 `i++;`  
D. 条件 `i >= 8`；更新 `i += 2;`

### MCQ 17｜重叠子串

```java
String s = "aaaa";
int count = 0;
for (int i = 0; i <= s.length() - 2; i++) {
    if (s.substring(i, i + 2).equals("aa")) {
        count++;
    }
}
System.out.println(count);
```

A. `2`  
B. `4`  
C. `3`  
D. 运行时抛越界异常

### MCQ 18｜循环错误诊断

以下程序意图统计 0 到 4 中的偶数个数：

```java
int i = 0;
int count = 0;
while (i < 5) {
    if (i % 2 == 0) {
        count++;
        i++;
    }
}
```

只做以下哪一个修改，能保证程序终止并得到正确计数？

A. 将 `i++;` 移到 if 块之后、while 块之内  
B. 将条件改成 `i <= 5`  
C. 将 `count++;` 改成 `count += 2;`  
D. 将初始值 `i = 0` 改成 `i = 1`

## 4. FRQ 专项训练（4 题，原创）

仅写要求的方法；无需 main、输入读取或额外打印。各题前提均可直接使用。禁止使用数组、集合、Stream 或递归；允许 if、for、while 和已学 String 方法。

### FRQ 1｜EntryPolicy：规则翻译与分类

三个静态方法放在 EntryPolicy 类中。

**(a)** `mayEnter`：有票，并且“年龄至少 16 或有监护人陪同”时才可进入。

```java
/** Precondition: age >= 0 */
public static boolean mayEnter(int age, boolean hasTicket,
                                boolean withGuardian)
```

**(b)** `scoreBand`：分数 90—100 返回 `"A"`；80—89 返回 `"B"`；60—79 返回 `"C"`；0—59 返回 `"D"`。

```java
/** Precondition: 0 <= score <= 100 */
public static String scoreBand(int score)
```

**(c)** `isLeapYear`：年份能被 400 整除，或能被 4 整除但不能被 100 整除时，返回 true。

```java
/** Precondition: year > 0 */
public static boolean isLeapYear(int year)
```

| 调用 | 结果 |
| --- | --- |
| `mayEnter(15,true,false)` | false |
| `mayEnter(15,true,true)` | true |
| `mayEnter(18,false,true)` | false |
| `scoreBand(90)` | `"A"` |
| `scoreBand(80)` | `"B"` |
| `scoreBand(59)` | `"D"` |
| `isLeapYear(1900)` | false |
| `isLeapYear(2000)` | true |

其中 (c) 保留原稿闰年判断的知识点，改成方法题；不将它标为 AP 官方真题。

### FRQ 2｜TierBilling：分段计费

某练习系统按当月使用分钟数计算费用，规则是**累进计费**：

- 前 30 分钟：每分钟 2 元。
- 第 31—90 分钟：这一部分每分钟 1 元。
- 超过 90 分钟的部分：每分钟 0.5 元。

**(a)** 完成基础费用方法：

```java
/** Precondition: 0 <= minutes <= 10000 */
public static double baseCharge(int minutes)
```

**(b)** 完成实际费用方法，必须调用 baseCharge：若同时是会员且使用不少于 60 分钟，则基础费用打 8 折；否则保持不变。

```java
/** Precondition: 0 <= minutes <= 10000 */
public static double finalCharge(int minutes, boolean member)
```

| minutes | baseCharge | member | finalCharge |
| --- | --- | --- | --- |
| 0 | 0.0 | true | 0.0 |
| 30 | 60.0 | false | 60.0 |
| 31 | 61.0 | true | 61.0 |
| 60 | 90.0 | true | 72.0 |
| 90 | 120.0 | false | 120.0 |
| 100 | 125.0 | true | 100.0 |

结果返回 double，不要求格式化或四舍五入。不要按总分钟数统一套用最后一档单价。

### FRQ 3｜StringScan：计数与连续段

参数均非 null。

**(a)** 完成 countMatches：统计 target 在 text 中出现的次数，允许重叠。前提：target 长度至少 1。

```java
public static int countMatches(String text, String target)
```

**(b)** 完成 longestRun：返回 token 连续出现的最长长度；没有则返回 0。前提：token 长度恰好为 1。

```java
public static int longestRun(String text, String token)
```

| 调用 | 返回值 |
| --- | --- |
| `countMatches("aaaa","aa")` | 3 |
| `countMatches("ababa","aba")` | 2 |
| `countMatches("ab","abcd")` | 0 |
| `countMatches("","a")` | 0 |
| `longestRun("aaXaaa","a")` | 3 |
| `longestRun("baa","a")` | 2 |
| `longestRun("bbb","a")` | 0 |
| `longestRun("","a")` | 0 |

不要求改变 text；不得调用 replace 或 split。

### FRQ 4｜EnergyMeter：受限步数的状态模拟

EnergyMeter 类已有一个实例字段 `energy` 和已实现的构造器，初始化值满足 `0 <= energy <= 1000000`。

**(a)** 完成 useOneDay：每天有 users 个用户，每人消耗 3 单位能量。如果总需求超过剩余能量，剩余能量变为 0，否则扣除需求。前提：`1 <= users <= 1000000`。

```java
public void useOneDay(int users)
```

**(b)** 完成 countActiveDays：最多执行 maxDays 天，返回**当天开始时还有能量**的天数。每天开始时若 energy 为 0，则不再执行。最后一天把能量用完，也算有效一天。

```java
/** Preconditions: 1 <= users <= 1000000; 0 <= maxDays <= 10000 */
public int countActiveDays(int users, int maxDays)
```

必须使用 useOneDay，并且每个有效日恰好调用一次。无论 (a) 是否写对，(b) 都假设它满足契约。执行后保留更新过的 energy。

以下每行从独立的新对象开始：

| 初始 energy | users | maxDays | 返回天数 | 最终 energy |
| --- | --- | --- | --- | --- |
| 20 | 2 | 5 | 4 | 0 |
| 20 | 2 | 2 | 2 | 8 |
| 0 | 2 | 5 | 0 | 0 |
| 6 | 2 | 5 | 1 | 0 |
| 1 | 2 | 5 | 1 | 0 |
| 20 | 2 | 0 | 0 | 20 |

这是原创模拟专项题，采用“已实现单步方法 + 有上限的重复调用”的常见训练结构，不是 Feeder 真题原文。

## 6. 官方题

### 6.1 官方 MCQ 样题

来源：[CED，Effective Fall 2025](https://apcentral.collegeboard.org/media/pdf/ap-computer-science-a-course-and-exam-description.pdf)。以下是 Sample Exam Questions，不是某年实考试卷。

| 官方样题号 | PDF 页码（从 1 开始） | 对应本章 | 作答要求 |
| --- | --- | --- | --- |
| 5 | 157—158，印刷页 150—151 | 分支顺序、分类区间 | 检查所有区间端点与大于上界的反例 |
| 6 | 159，印刷页 152 | 德摩根定律 | 用真值表或等价变换验证 |
| 7 | 159，印刷页 152 | 嵌套循环填空 | 按输出每行的起点与次数反推 |
| 8 | 159，印刷页 152 | 循环次数 | 外层次数与固定内层次数分别计算 |


第 5 题 A；第 6 题 B；第 7 题 A；第 8 题 B，输出语句执行 15 次。请学生先写推理，再核对选项。

### 6.2 重点真题：2024 Q1 Feeder

- [官方题目 PDF](https://apcentral.collegeboard.org/media/pdf/ap24-frq-comp-sci-a.pdf#page=3)：PDF 第 3—7 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap24-sg-computer-science-a.pdf)：定位 Q1。

前面基础章节若已经做过 (a)，本次重点练 (b)：复用单日模拟、限制天数、食物耗尽时停止，以及统计有效天数。随机数基础仍用于 (a)。

建议 20—25 分钟完成整题，再重点检查“初始为 0”和“某天执行后变为 0”两种情况。以原题和官方细则为准，不把本章 EnergyMeter 的自评点套到真题。

### 6.3 进阶真题：2023 Q1 AppointmentBook

- [官方题目 PDF](https://apcentral.collegeboard.org/media/pdf/ap23-frq-comp-sci-a.pdf#page=3)：PDF 第 3—7 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap23-sg-computer-science-a.pdf)：定位 Q1。

训练连续可用时段、最早位置、辅助方法调用及跨时段搜索。可在 StringScan 的连续段统计熟练后安排；不需要把日程实现成数组。

作答顺序：先明确 helper 契约，再完成 findFreeBlock，最后在 makeAppointment 中复用它。注意查找方法与预订方法的副作用不同。

### 6.4 真题材料说明

[官方历年题页面](https://apcentral.collegeboard.org/courses/ap-computer-science-a/exam/past-exam-questions)提醒旧题与修订后的考试不完全对齐。本章按知识点选题，不用旧卷时间、题型分布或单元编号代表现行考试。

## 7. MCQ 答案与解析

### 7.1 答案速查

| 题号 | 答案 | 主要错因 |
| --- | --- | --- |
| 1 | C | 把区间内写成 ||、误用连锁比较 |
| 2 | A | 比较取反漏等号或端点 |
| 3 | D | 德摩根定律、双重否定 |
| 4 | B | && 优先于 || |
| 5 | C | 忽略短路 |
| 6 | A | 保护条件顺序和 null 情况 |
| 7 | D | 把没执行的调用也计数 |
| 8 | B | else if 链的首个匹配 |
| 9 | C | 独立 if 使用更新后的值 |
| 10 | A | else 匹配最近未配对 if |
| 11 | D | 忽略此前分支已经排除的范围 |
| 12 | B | boolean 赋值不一定编译失败 |
| 13 | C | 次数与退出后的值 |
| 14 | A | 整数除法与终止条件 |
| 15 | D | 内层次数随外层变化 |
| 16 | B | 初始化、边界和更新必须一致 |
| 17 | C | 允许重叠匹配 |
| 18 | A | 某条路径没有更新条件变量 |

### 7.2 逐题解析

1. C 同时限制下界和上界并包含端点。A 对任意整数都成立；B 排除了端点；D 不是合法 Java 比较。
2. `x < 5` 取反为 `x >= 5`；`x >= 12` 取反为 `x < 12`；|| 换成 &&。
3. `!(a && !b)` 等价于 `!a || !!b`，即 `!a || b`。双重否定不能遗漏。
4. 第一个表达式为 `true || (false && false)`，结果 true；第二个为 `(true || false) && false`，结果 false。
5. `d != 0` 为 false，右侧不执行，结果 false。代码合法，不会在运行时除以零。
6. I 先检查 null，安全且符合要求。II 遇 null 时先访问 length 而抛异常；III 遇 null 返回 false，与要求不符，虽然它本身是安全的。
7. a 的调用被 false && 短路；b 的调用被 true || 短路；只有 c 的调用执行一次，返回 true。
8. 95 首先满足 `score >= 80`，执行 B 分支后整条链结束。程序能编译，但分类规则顺序不合理。
9. 第一个 if 将 x 从 4 变为 7；第二个 if 用 7 判断并乘 2，得到 14。else 属于第二个 if，未执行。
10. x>0 成立，内层 y>0 不成立，所以输出 B；最后无条件输出 C。else 归属于内层 if。
11. 进入 else if 时 x 已经至少为 10，只需再限制 `x <= 20`。A 漏 20；B 会接受 21；C 漏 10。
12. `flag = true` 将 flag 赋为 true，表达式本身的值也为 true，因此进入 A，最后打印 true。它是合法但通常误写的 Java。
13. 循环体依次看到 i=2、5、8，共 3 次；下一次更新到 11，条件 false，退出。i 在循环前声明，因此外部可访问。
14. n 依次变为 10、5、2、1，共 4 次。到 1 时已不满足 n>1，不会继续除到 0。
15. i=1、2、3、4 时，内层分别执行 4、3、2、1 次，总计 10。
16. B 完整保留边界与步长。A 漏 8；C 还输出奇数；D 在初值 2 时就不执行。
17. 合法起点是 0、1、2，每处都是 aa，所以统计为 3。允许重叠，不应每次跳过 2 个字符。
18. 原代码第一次把 i 从 0 改为 1，随后奇数路径不再更新 i，永久停在 1。A 让每轮都更新，统计 0、2、4 得 3。其他修改都没有解决这条路径。

## 8. FRQ 参考解与课堂评分

### FRQ 1 参考解：EntryPolicy

```java
public class EntryPolicy {
    public static boolean mayEnter(int age, boolean hasTicket,
                                    boolean withGuardian) {
        return hasTicket && (age >= 16 || withGuardian);
    }

    public static String scoreBand(int score) {
        if (score >= 90) {
            return "A";
        } else if (score >= 80) {
            return "B";
        } else if (score >= 60) {
            return "C";
        } else {
            return "D";
        }
    }

    public static boolean isLeapYear(int year) {
        return year % 400 == 0
               || (year % 4 == 0 && year % 100 != 0);
    }
}
```

每小问 3 分，共 9 分：

| 小问 | 课堂评分点，各 1 分 |
| --- | --- |
| (a) | 有票为必要条件；年龄或监护人条件正确；正确分组并返回 boolean |
| (b) | A/B 边界正确；C/D 边界正确；互斥分类并在所有合法输入返回 |
| (c) | 400 年条件正确；4 与 100 的组合正确；用或连接两条规则并返回 |

边界：年龄 15/16；分数 59/60、79/80、89/90；年份 1900、2000、2024、2025。等价 if 写法可得分。

### FRQ 2 参考解：TierBilling

```java
public class TierBilling {
    public static double baseCharge(int minutes) {
        if (minutes <= 30) {
            return minutes * 2.0;
        } else if (minutes <= 90) {
            return 60.0 + (minutes - 30);
        } else {
            return 120.0 + (minutes - 90) * 0.5;
        }
    }

    public static double finalCharge(int minutes, boolean member) {
        double charge = baseCharge(minutes);
        if (member && minutes >= 60) {
            charge *= 0.8;
        }
        return charge;
    }
}
```

| 课堂评分点 | 分值 |
| --- | --- |
| 第一段公式正确，含 0 和 30 | 1 |
| 第二段保留前 30 分钟费用 60 | 1 |
| 第二段只对超出 30 的分钟收费 | 1 |
| 第三段保留前 90 分钟费用 120 | 1 |
| 第三段只对超出 90 的分钟收 0.5，返回值正确 | 1 |
| finalCharge 正确调用 baseCharge(minutes) | 1 |
| 会员与使用时长用 && 正确组合 | 1 |
| 达标时将基础费用乘 0.8，非达标时不改费用 | 1 |
| 返回计算后的 double，无额外输出或遗漏路径 | 1 |

典型错误：100 分钟全部乘 0.5；把“会员且满 60”写成 ||；把打 8 折写成乘 0.2。自测 29/30/31、59/60/61、89/90/91。

### FRQ 3 参考解：StringScan

```java
public class StringScan {
    public static int countMatches(String text, String target) {
        int count = 0;
        int width = target.length();
        for (int i = 0; i <= text.length() - width; i++) {
            if (text.substring(i, i + width).equals(target)) {
                count++;
            }
        }
        return count;
    }

    public static int longestRun(String text, String token) {
        int current = 0;
        int best = 0;
        for (int i = 0; i < text.length(); i++) {
            if (text.substring(i, i + 1).equals(token)) {
                current++;
                if (current > best) {
                    best = current;
                }
            } else {
                current = 0;
            }
        }
        return best;
    }
}
```

countMatches 共 4 分：合法起点边界 1 分；正确截取并 equals 比较 1 分；匹配计数且每次起点加 1（保留重叠）1 分；初始化及返回正确 1 分。

longestRun 共 5 分：合法单字符遍历 1 分；匹配时累计 current 1 分；不匹配时清零 1 分；正确更新 best、不漏末尾段 1 分；初值与返回正确、空串返回 0 共 1 分。

注意 best 要保留历史最大值，不能在遇到非目标字符时一并清零。解法若在每段结束时更新 best，必须额外处理最后一段。

### FRQ 4 参考解：EnergyMeter

以下完整类用于核对与上机验证；作答时只需写题目要求的两个方法。

```java
public class EnergyMeter {
    private int energy;

    public EnergyMeter(int initialEnergy) {
        energy = initialEnergy;
    }

    public void useOneDay(int users) {
        int needed = users * 3;
        if (needed >= energy) {
            energy = 0;
        } else {
            energy -= needed;
        }
    }

    public int countActiveDays(int users, int maxDays) {
        int days = 0;
        while (days < maxDays && energy > 0) {
            useOneDay(users);
            days++;
        }
        return days;
    }
}
```

| 课堂评分点 | 分值 |
| --- | --- |
| 计算当天需求 users*3 | 1 |
| 正确比较需求与当前 energy | 1 |
| 不足时置 0，足够时正确扣除，始终不为负 | 1 |
| days 初值为 0 | 1 |
| 保证不超过 maxDays | 1 |
| 当天开始 energy>0 才执行，耗尽立即停止 | 1 |
| 每个有效日恰当调用 useOneDay(users) 一次 | 1 |
| 统计有效日，包括执行后刚耗尽的那天 | 1 |
| 正确返回，处理初始 0 和 maxDays=0，保留更新后的字段 | 1 |

days++ 虽写在调用后，循环入口已保证当天开始有能量，因此当天被计入。不能在调用后再以 energy>0 决定是否计数，否则漏掉耗尽日。

