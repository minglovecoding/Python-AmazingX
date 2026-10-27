## APCSA 第二轮复习 04：循环算法与遍历应用

## 📚 1. 本章内容

### 1.1 Iteration 与 Iterator 必须分开

| 名称 | 含义 | 本章地位 |
| --- | --- | --- |
| Iteration | 重复执行/循环，如 for、while | 主线 |
| Iterator | java.util 中的迭代器接口，提供遍历集合的操作 | Java 拓展 |

AP 复习优先熟悉索引循环、增强 for、ArrayList 的 get/size/remove；

### 1.2 过关目标

- 对每个循环说清：已经处理什么、下一步处理什么、何时退出。
- 正确处理数字 0、字符串空串、单元素容器和连续待删元素。
- 区分“按元素读取”与“按索引修改”。
- 判断多段循环次数相加、固定嵌套相乘、变化嵌套求和。
- 完成回文、过滤、统计、二维遍历与安全删除。
- 解释原地修改与返回新结果的区别。

## 2. 核心知识与易错点

### 2.1 数字拆位：%10 取末位，/10 去末位

适用于本章的非负整数：

```java
int remaining = 472;
int total = 0;
while (remaining > 0) {
    total += remaining % 10;
    remaining /= 10;
}
// total 为 13，remaining 为 0
```

需要保留原数时，先复制到工作变量。数字从低位到高位处理，与人平常从左到右读数不同。

| 已处理步数 | remaining（剩余高位） | 取出的末位 | total |
| --- | --- | --- | --- |
| 0 | 472 | — | 0 |
| 1 | 47 | 2 | 2 |
| 2 | 4 | 7 | 9 |
| 3 | 0 | 4 | 13 |

反转数字：

```java
reversed = reversed * 10 + remaining % 10;
remaining /= 10;
```

`120` 的反转整数是 `21`，整数结果不保留前导零。反转可能溢出，所以必须关注输入前提；本章 FRQ 限制到 9 位非负数。

**0 的边界：**`while(n > 0)` 对 n=0 执行 0 次。数字和返回 0 通常正确，但位数应该是 1，不能直接返回循环次数 0。

### 2.2 去空格：空串不是空格

原稿的 `indexOf("")` 查找空字符串，任意字符串（包括空串）都会在位置 0 匹配；它不是查找空格。

```java
"abc".indexOf(""); // 0
"".indexOf("");    // 0
"a b".indexOf(" "); // 1
```

**方法一：逐个读取、保留非空格字符。**

```java
String result = "";
for (int i = 0; i < text.length(); i++) {
    String ch = text.substring(i, i + 1);
    if (!ch.equals(" ")) {
        result += ch;
    }
}
```

**方法二：反复定位并删除一个空格。**

```java
int pos = text.indexOf(" ");
while (pos != -1) {
    text = text.substring(0, pos) + text.substring(pos + 1);
    pos = text.indexOf(" ");
}
```

两种方案都能处理连续、首尾空格。每次删一个字符时，要重新定位；不要使用旧长度或旧索引。

本章“空格”仅指普通字符 `" "`，不包含制表符、换行或所有 Unicode 空白。String 不可变，更新的是局部变量的引用；方法应返回结果。

### 2.3 回文：只比较对称位置

```java
public static boolean isPalindrome(String text) {
    int n = text.length();
    for (int i = 0; i < n / 2; i++) {
        String left = text.substring(i, i + 1);
        String right = text.substring(n - 1 - i, n - i);
        if (!left.equals(right)) {
            return false;
        }
    }
    return true;
}
```

- 左位置 i，右位置 n-1-i。
- 找到一处不同即可返回 false。
- true 应在全部必要比较完成后返回，不能只因为第一对相同就返回 true。
- 偶数长度比较 n/2 对；奇数长度中间字符无需与自己重复比较。
- 本章约定空串与单字符都是回文，比较区分大小写，不自动去标点。

原稿遍历全部 n 个位置的版本在前提下也正确，只是重复比较。本稿用一半范围表达算法意图，不把“冗余”误判为“不正确”。

### 2.4 精确次数：相加、相乘还是求和

假设 n>=0，循环体不修改循环变量，且运算不溢出：

| 结构 | x++ 执行次数 |
| --- | --- |
| 两个连续的 n 次循环 | 2n |
| 外层 a 次、内层固定 b 次 | a*b |
| `i=0..n-1`，内层 `j=i..n-1` | n+(n-1)+...+1 = n(n+1)/2 |
| `i=0..n-1`，内层 `j=0..i-1` | 0+1+...+(n-1) = n(n-1)/2 |

精确次数与增长级别不同：`2n` 是线性，`n(n+1)/2` 是二次增长；不能用大 O 直接回答“执行了多少次”。本章优先算清循环体次数，不延伸完整复杂度理论。

图案输出：外层决定行，内层决定本行内容，换行放在内层循环之后。

```java
for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3 - row; col++) {
        System.out.print("*");
    }
    System.out.println();
}
```

```text
***
**
*
```

### 2.5 数组遍历：读取与修改不是同一件事

```java
int total = 0;
for (int value : numbers) {
    total += value;
}
```

增强 for 适合读取元素；给基本类型循环变量赋值，不会更新原数组。

```java
for (int value : numbers) {
    value++; // 只改变当前局部变量
}
```

若要修改数组元素：

```java
for (int i = 0; i < numbers.length; i++) {
    numbers[i]++;
}
```

最大/最小值：对非空数组，用第一个元素初始化往往最自然。

```java
int best = numbers[0];
for (int value : numbers) {
    if (value > best) {
        best = value;
    }
}
```

如果 best 初始化为 0，全负数数组会出错。使用 numbers[0] 必须保证数组非空。

本章只复习遍历，不展开数组创建、复制和排序。容器基本操作未学过时，先回到对应专题。

### 2.6 ArrayList 删除：元素会向左移动

本节假设使用 `ArrayList<Integer>`，且元素非 null。

| 操作 | 含义 |
| --- | --- |
| `list.size()` | 当前元素数，会随删除而变化 |
| `list.get(i)` | 读取索引 i 的元素 |
| `list.set(i, value)` | 替换现有元素，大小不变 |
| `list.remove(i)` | 删除索引 i 的元素，后面的元素左移 |

**常见错误：删完还立即 i++，会跳过移到当前位置的元素。**

```java
// 初始 [-2, -3, 4]
for (int i = 0; i < list.size(); i++) {
    if (list.get(i) < 0) {
        list.remove(i);
    }
}
// 错误结果为 [-3, 4]
```

**正确方案一：从后向前删除。**

```java
for (int i = list.size() - 1; i >= 0; i--) {
    if (list.get(i) < 0) {
        list.remove(i);
    }
}
```

**正确方案二：正向 while，删除后不前进。**

```java
int i = 0;
while (i < list.size()) {
    if (list.get(i) < 0) {
        list.remove(i);
    } else {
        i++;
    }
}
```

所以“只能倒序删除”不准确；关键是索引变化与元素左移是否匹配。别把删除前的 size 当成删除后的边界。

**原地修改和新建结果要分开：**参数为列表，直接调用 remove 改的是原列表；写 `list = new ArrayList<Integer>();` 只改变局部参数的指向，不会替换调用者的引用。

拓展：`ArrayList<Integer>` 的 `remove(1)` 按索引删除；`remove(Integer.valueOf(1))` 按值删除第一次出现的 1。核心解按索引删除，避免误判重载。

### 2.7 二维数组：行数与列数分开

```java
for (int r = 0; r < grid.length; r++) {
    for (int c = 0; c < grid[r].length; c++) {
        System.out.println(grid[r][c]);
    }
}
```

grid.length 是行数，grid[r].length 是第 r 行长度。矩形且至少有一行时，grid[0].length 可作为公共列数；不能把“矩形”误当成“正方形”。

本章 FRQ 使用非空矩形数组；写成 grid[r].length 也便于理解 Java 的“数组的数组”。不要额外假设每个元素非负。

## 3. Iterator 拓展（与 AP 核心分开）

### 3.1 接口与三个操作

Iterator 是接口，不是普通意义上用于 new 的类。ArrayList 可通过 iterator() 获取它；Map 通常通过 keySet、values 或 entrySet 等视图遍历，不是所有 Map 自身都有同样的 iterator() 方法。

```java
import java.util.ArrayList;
import java.util.Iterator;

Iterator<Integer> it = list.iterator();
while (it.hasNext()) {
    int value = it.next();
    if (value < 0) {
        it.remove();
    }
}
```

上段假设 list 已声明为支持 remove 的 ArrayList，元素非 null。

| 调用 | 作用 |
| --- | --- |
| `hasNext()` | 只检查还有没有元素，不前进 |
| `next()` | 返回下一个元素并推进遍历 |
| `remove()` | 删除上次 next 返回的元素；每次 next 后最多调用一次 |

Iterator.remove 是可选操作；本例的 ArrayList 迭代器支持。不能泛化为所有迭代器都支持。

## 4. MCQ 训练

1—16 为核心训练；17—18 明确是显式 Iterator 的 Java 拓展，不用来估算 AP MCQ 分数。每题只有一个正确选项。各题独立；用到 ArrayList/Iterator 时假设已导入 java.util 中对应类型。

### MCQ 1｜数字 0 的边界

```java
int n = 0;
int digits = 0;
while (n > 0) {
    digits++;
    n /= 10;
}
System.out.println(digits);
```

程序实际输出什么？

A. `0`  
B. `1`  
C. `10`  
D. 无限循环

### MCQ 2｜反转数字

```java
int n = 1204;
int reversed = 0;
while (n > 0) {
    reversed = reversed * 10 + n % 10;
    n /= 10;
}
System.out.println(reversed);
```

A. `421`  
B. `4021`  
C. `1204`  
D. `1024`

### MCQ 3｜空字符串不是空格

```java
String text = "a b";
while (text.indexOf("") != -1) {
    int pos = text.indexOf("");
    text = text.substring(0, pos) + text.substring(pos + 1);
}
System.out.println(text);
```

A. 输出 `ab`  
B. 输出空行后正常结束  
C. 输出 `a b`  
D. 最终发生字符串索引越界异常

### MCQ 4｜回文循环边界

方法对任意非 null String（包括空串）判断回文，空串视为回文：

```java
public static boolean palindrome(String s) {
    int n = s.length();
    for (int i = 0; /* condition */; i++) {
        if (!s.substring(i,i+1).equals(s.substring(n-1-i,n-i))) {
            return false;
        }
    }
    return true;
}
```

哪一项既能正确判断，又恰好只比较需要的左右成对位置？

A. `i < n / 2`  
B. `i <= n / 2`  
C. `i < n - 1`  
D. `i <= n`

### MCQ 5｜过早返回 true

```java
public static boolean check(String s) {
    for (int i = 0; i < s.length() / 2; i++) {
        if (!s.substring(i,i+1).equals(
                s.substring(s.length()-1-i,s.length()-i))) {
            return false;
        } else {
            return true;
        }
    }
    return true;
}
```

`check("abca")` 返回什么？

A. `true`  
B. `false`  
C. 编译错误  
D. 运行时索引越界

### MCQ 6｜连续循环次数

假设 n>=0 且以下运算不溢出，最终 x 为多少？

```java
int x = 0;
for (int i = 0; i < n; i++) { x++; }
for (int j = 0; j < n; j++) { x++; }
```

A. `n`  
B. `n*n`  
C. `2*n`  
D. `n*(n+1)/2`

### MCQ 7｜固定嵌套

```java
int count = 0;
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 15; j++) {
        count++;
    }
}
```

最终 count 是？

A. `25`  
B. `100`  
C. `135`  
D. `150`

### MCQ 8｜变化嵌套

假设 n>=0 且结果在 int 范围内，最终 x 是？

```java
int x = 0;
for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
        x++;
    }
}
```

A. `n*(n-1)/2`  
B. `n*(n+1)/2`  
C. `n*n`  
D. `2*n`

选项表达数学公式，不要求实际用 Java int 表达式计算中间乘积。

### MCQ 9｜行与行内输出

```java
for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3 - row; col++) {
        System.out.print("*");
    }
    System.out.print("|");
}
```

A. `***|**|*|`  
B. `*|**|***|`  
C. `***|***|***|`  
D. `******|`

### MCQ 10｜全负数最大值

```java
int[] values = {-8, -3, -10};
int best = 0;
for (int value : values) {
    if (value > best) {
        best = value;
    }
}
System.out.println(best);
```

实际输出什么？

A. `-3`  
B. `0`  
C. `-10`  
D. 编译错误

### MCQ 11｜增强 for 赋值

```java
int[] values = {2, 4, 6};
for (int value : values) {
    value += 10;
}
System.out.println(values[1]);
```

A. `14`  
B. `12`  
C. `16`  
D. `4`

### MCQ 12｜正向删除漏元素

list 初始为 `[-2,-3,4,-1]`：

```java
for (int i = 0; i < list.size(); i++) {
    if (list.get(i) < 0) {
        list.remove(i);
    }
}
System.out.println(list);
```

A. `[4]`  
B. `[-2, 4]`  
C. `[-3, 4]`  
D. `[-3, 4, -1]`

### MCQ 13｜倒序删除

list 初始仍为 `[-2,-3,4,-1]`：

```java
for (int i = list.size() - 1; i >= 0; i--) {
    if (list.get(i) < 0) {
        list.remove(i);
    }
}
System.out.println(list);
```

A. `[-3, 4]`  
B. `[4]`  
C. `[-2, 4]`  
D. 索引越界

### MCQ 14｜正向 while 删除

list 初始为 `[5,5,7,8]`，以下代码应删除所有小于 7 的元素：

```java
int i = 0;
while (i < list.size()) {
    if (list.get(i) < 7) {
        list.remove(i);
        /* X */
    } else {
        /* Y */
    }
}
```

哪一项正确？

A. X 不加语句；Y 写 `i++;`  
B. X 写 `i++;`；Y 不加语句  
C. X、Y 都写 `i++;`  
D. X、Y 都不加语句

### MCQ 15｜Integer 列表 remove 重载

`ArrayList<Integer> list` 初始为 `[1,2,1,3]`：

```java
list.remove(1);
System.out.println(list);
```

A. `[2, 1, 3]`  
B. `[1, 1, 3]`  
C. `[2, 3]`  
D. `[1, 2, 3]`

### MCQ 16｜把行数当列数

```java
int[][] grid = {{1, 2, 3}, {4, 5, 6}};
int total = 0;
for (int r = 0; r < grid.length; r++) {
    for (int c = 0; c < grid.length; c++) {
        total += grid[r][c];
    }
}
System.out.println(total);
```

A. `21`  
B. `6`  
C. 索引越界  
D. `12`

### MCQ 17｜Iterator 拓展：检查不会前进

list 为包含 `"A","B","C"` 的 ArrayList<String>：

```java
Iterator<String> it = list.iterator();
it.hasNext();
it.hasNext();
System.out.print(it.next());
System.out.print(it.next());
```

A. `AB`  
B. `BC`  
C. `AA`  
D. 抛异常

### MCQ 18｜Iterator 拓展：删除协议

list 为包含 `4,7` 的 ArrayList<Integer>：

```java
Iterator<Integer> it = list.iterator();
it.remove();
```

A. 删除 4，列表变为 `[7]`  
B. 删除 7，列表变为 `[4]`  
C. 抛出 IllegalStateException  
D. 编译错误，因为 Iterator 没有 remove

## 5. FRQ 专项训练

方法均放在对应类中，只需写要求的方法；类壳用于参考解运行。除题面特别说明外，不得使用 Stream、递归、正则表达式或现成过滤/去重方法。参数均非 null。

### FRQ 1｜DigitTools：数字分析

前提：`0 <= n <= 999999999`。本题不得转换成字符串。

**(a)** digitCount 返回十进制位数，0 的位数是 1。

```java
public static int digitCount(int n)
```

**(b)** reverse 返回数字反转后的整数，前导零自然省略。

```java
public static int reverse(int n)
```

**(c)** isNumericPalindrome 返回是否为回文数，必须调用 reverse，不重复写反转循环。

```java
public static boolean isNumericPalindrome(int n)
```

| n | digitCount | reverse | isNumericPalindrome |
| --- | --- | --- | --- |
| 0 | 1 | 0 | true |
| 7 | 1 | 7 | true |
| 120 | 3 | 21 | false |
| 12021 | 5 | 12021 | true |
| 1204 | 4 | 4021 | false |

题目限制保证反转结果在 int 范围内，不需要自行处理负数或溢出后的特殊返回值。

### FRQ 2｜TextCleaner：清理与回文

只处理普通空格 `" "`；比较区分大小写，保留数字、标点等其他字符。

**(a)** removeSpaces 返回删去所有普通空格后的字符串；允许空串、连续和首尾空格。不得调用 replace/replaceAll/split。

```java
public static String removeSpaces(String text)
```

**(b)** isPalindrome 判断字符串本身是否回文；空串与单字符返回 true。只比较必要的左右成对位置。

```java
public static boolean isPalindrome(String text)
```

**(c)** isCleanPalindrome 先去空格再判断回文，必须调用 (a)、(b) 两个方法。

```java
public static boolean isCleanPalindrome(String text)
```

| 调用 | 返回值 |
| --- | --- |
| `removeSpaces(" a  b ")` | `"ab"` |
| `removeSpaces("   ")` | `""` |
| `isPalindrome("abca")` | false |
| `isPalindrome("")` | true |
| `isCleanPalindrome("ab ba")` | true |
| `isCleanPalindrome("Aa")` | false |

### FRQ 3｜GridStats：二维数组统计

前提：grid 是至少 1 行、每行至少 1 列的矩形 int 数组；每个元素在 -100 到 100 之间，行、列数均不超过 100。不得修改 grid。

**(a)** rowTotal 返回指定行元素之和，row 是合法行索引。

```java
public static int rowTotal(int[][] grid, int row)
```

**(b)** countAbove 返回所有严格大于 threshold 的元素个数。

```java
public static int countAbove(int[][] grid, int threshold)
```

**(c)** maxRowTotal 返回最大的行和，必须调用 rowTotal；所有行和都为负时也要正确。

```java
public static int maxRowTotal(int[][] grid)
```

| grid | 调用 | 返回值 |
| --- | --- | --- |
| `{{1,2,3},{4,5,6}}` | `rowTotal(grid,1)` | 15 |
| 同上 | `countAbove(grid,3)` | 3 |
| 同上 | `maxRowTotal(grid)` | 15 |
| `{{-4,-2},{-1,-8}}` | `maxRowTotal(grid)` | -6 |
| `{{0}}` | `countAbove(grid,0)` | 0 |

### FRQ 4｜ListCleaner：原地删除

本题 list 为非 null 的 ArrayList<Integer>，元素非 null。允许空列表。不得创建替代列表，不得使用 Iterator、removeIf 或其他批量过滤方法。方法要修改原列表，保留剩余元素的先后顺序。

**(a)** removeBelow 删除所有严格小于 limit 的值。

```java
public static void removeBelow(ArrayList<Integer> list, int limit)
```

**(b)** collapseRuns 将每段连续相等的元素压成一个，非相邻的相同值不能全部去重。

```java
public static void collapseRuns(ArrayList<Integer> list)
```

| 初始列表 | 调用 | 最终列表 |
| --- | --- | --- |
| `[2,2,5,1,7]` | `removeBelow(list,3)` | `[5,7]` |
| `[3,3]` | `removeBelow(list,3)` | `[3,3]` |
| `[]` | `removeBelow(list,3)` | `[]` |
| `[2,2,2,5,5,2]` | `collapseRuns(list)` | `[2,5,2]` |
| `[4]` | `collapseRuns(list)` | `[4]` |
| `[]` | `collapseRuns(list)` | `[]` |

值比较使用 equals 或拆箱后的数值比较，不依赖 Integer 对象缓存碰巧共享引用。

## 6. 官方样题与往年真题

### 6.1 官方 MCQ 样题：全负数最大值

来源：[CED，Effective Fall 2025](https://apcentral.collegeboard.org/media/pdf/ap-computer-science-a-course-and-exam-description.pdf#page=163)，PDF 第 163 页、印刷页码 156，Sample Exam Questions 第 14 题。

这是官方样题，不是某年的实考 MCQ。完成时先构造全负数反例，再判断哪一项修改能修复初值问题。


第 14 题选 A，将最大值初值设为数组第一个元素。与本章 MCQ 10、GridStats 的负数行和相连接。

### 6.2 重点真题：2023 Q3 WeatherData

- [官方题目](https://apcentral.collegeboard.org/media/pdf/ap23-frq-comp-sci-a.pdf#page=11)：PDF 第 11—13 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap23-sg-computer-science-a.pdf)：定位 Q3。

(a) 对 ArrayList 按范围原地清理并保持顺序；适合在 ListCleaner 后完成。(b) 涉及连续段统计，可连接上一章的 StringScan。

检查：连续多个需删值、边界值是否保留，以及严格大于阈值与等于阈值的区别。按原题前提和官方细则给分；本章原创题不是该真题原文。

### 6.3 综合真题：2024 Q3 WordChecker

- [官方题目](https://apcentral.collegeboard.org/media/pdf/ap24-frq-comp-sci-a.pdf#page=10)：PDF 第 10—12 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap24-sg-computer-science-a.pdf)：定位 Q3。

训练相邻元素关系、字符串定位和构造新结果列表。(a) 要在发现反例时返回 false，而不是第一对满足就返回 true；(b) 要保留原列表，返回新的列表。

与本章 ListCleaner 对照：同样操作列表，但原地修改与新建结果的契约不同。阅读题面后先圈出“保持不变”或“更新”的要求。

### 6.4 真题选用说明

先做原创专项，再限时完成对应真题。官方旧题与修订框架不完全对齐，不能拿旧卷的时间、单元编号和题型分布代替现行规则。更多材料见[官方历年题入口](https://apcentral.collegeboard.org/courses/ap-computer-science-a/exam/past-exam-questions)。

## 7. MCQ 答案与解析

### 7.1 答案速查

| 题号 | 答案 | 核心错因 |
| --- | --- | --- |
| 1 | A | 实际执行次数与位数需求不同 |
| 2 | B | 反转过程中保留中间的 0 |
| 3 | D | 把空字符串当空格 |
| 4 | A | 对称边界、空串与比较次数 |
| 5 | A | 第一对匹配不能证明全部匹配 |
| 6 | C | 连续循环次数相加 |
| 7 | D | 固定嵌套次数相乘 |
| 8 | B | 变化嵌套按行求和 |
| 9 | A | 行输出与分隔符位置 |
| 10 | B | 最大值初值不应默认 0 |
| 11 | D | for-each 局部变量赋值不改数组 |
| 12 | C | 删除后元素左移被跳过 |
| 13 | B | 逆序删除不跳过未检查元素 |
| 14 | A | 删除后应检查当前位置的新元素 |
| 15 | B | remove(int) 是按索引删除 |
| 16 | D | 行数不等于列数 |
| 17（拓展） | A | hasNext 不推进遍历 |
| 18（拓展） | C | remove 之前必须有对应 next |

### 7.2 逐题解析

1. n=0 时条件一开始就 false，digits 保持 0。若任务是求正确位数，需要显式处理 0，但本题问的是实际输出。
2. reversed 依次为 4、40、402、4021；n 依次为 120、12、1、0。中间的 0 不能省掉。
3. 每次 pos 都是 0，程序依次删掉第一个字符，直到 text 为空；空串 indexOf("") 仍为 0，接下来 substring(1) 越界。不会正常返回空串。
4. A 比较恰好 n/2 对。B 在空串上第一次就越界；C 在较长字符串上有重复比较，不满足“只比较必要成对位置”；D 还会越界。
5. 首尾都是 a，第一次就从 else 返回 true；内部 b、c 根本没比较。正确的 true 应在循环后返回。
6. 两段循环先后执行，每段 n 次，所以是 2n，不是 n*n。
7. 外层每轮内层都重新执行 15 次，总共 10*15=150 次。
8. 内层依次执行 n、n-1、...、1 次，总和为 n(n+1)/2。不是下三角不含对角线的 n(n-1)/2。
9. 三行的星号数量为 3、2、1；每行末尾打印 |，没有 println，所以输出在同一行。
10. 三个元素都不大于 0，因此 best 从未更新，输出 0。这是逻辑错误，不是编译错误。
11. value 保存当前基本类型元素值的副本。修改它不写回数组，values[1] 仍为 4。
12. 删除 -2 后列表为 [-3,4,-1]，i 变为 1，跳过 -3；随后删除 -1，最终为 [-3,4]。
13. 依次从后检查 -1、4、-3、-2，所有负数都删除，最终只剩 [4]。
14. 删除时新的元素左移到同一索引，必须再次检查；不删除时才 i++。B、D 会停在保留值；C 会漏掉连续的 5。
15. 实参 1 为 int，选择 remove(int index)，删除索引 1 处的 2；最终 [1,1,3]。
16. 行数为 2，内层只访问列 0、1，累计 1+2+4+5=12，漏掉第三列；这个具体数组上不会越界。
17. 两次 hasNext 都不改变遍历位置；两次 next 分别得到 A、B。
18. 尚未调用 next，没有“上次返回的元素”可删除，因此抛 IllegalStateException；ArrayList 的迭代器本身支持 remove。

---

## ✅ 8. FRQ 参考解与课堂评分

### FRQ 1 参考解：DigitTools

```java
public class DigitTools {
    public static int digitCount(int n) {
        if (n == 0) {
            return 1;
        }
        int count = 0;
        while (n > 0) {
            count++;
            n /= 10;
        }
        return count;
    }

    public static int reverse(int n) {
        int result = 0;
        while (n > 0) {
            result = result * 10 + n % 10;
            n /= 10;
        }
        return result;
    }

    public static boolean isNumericPalindrome(int n) {
        return n == reverse(n);
    }
}
```

每小问 3 分：

| 小问 | 课堂评分点，各 1 分 |
| --- | --- |
| (a) | 正确处理 0；循环计数并去末位；返回正确位数 |
| (b) | 结果初值正确；用 result*10+n%10 追加末位；更新 n 并返回，处理 0 |
| (c) | 调用 reverse(n)；与原始 n 比较；返回 boolean 且不重复实现反转 |

测试 0、个位数、末尾有 0、内部有 0、9 位上界。修改方法内的基本类型参数不会改变调用者变量。

### FRQ 2 参考解：TextCleaner

```java
public class TextCleaner {
    public static String removeSpaces(String text) {
        String result = "";
        for (int i = 0; i < text.length(); i++) {
            String ch = text.substring(i, i + 1);
            if (!ch.equals(" ")) {
                result += ch;
            }
        }
        return result;
    }

    public static boolean isPalindrome(String text) {
        int n = text.length();
        for (int i = 0; i < n / 2; i++) {
            if (!text.substring(i, i + 1).equals(
                    text.substring(n - 1 - i, n - i))) {
                return false;
            }
        }
        return true;
    }

    public static boolean isCleanPalindrome(String text) {
        return isPalindrome(removeSpaces(text));
    }
}
```

removeSpaces 4 分：合法遍历 1 分；准确识别普通空格 1 分；保留其他字符与顺序 1 分；正确初始化并返回，含空串 1 分。

isPalindrome 3 分：只遍历必要的对称位置 1 分；比较内容、遇不等返回 false 1 分；完成后返回 true，含空串/单字符 1 分。

isCleanPalindrome 2 分：复用 removeSpaces 1 分；把清理结果传给 isPalindrome 并返回 1 分。

反复 indexOf(" ") 删除的正确版本也可获得 (a) 分数。字符串反复拼接可能复制已有内容；这不等于“循环 n 次就是总成本必为线性”。本章按题意和边界评判，不要求 StringBuilder 优化。

### FRQ 3 参考解：GridStats

```java
public class GridStats {
    public static int rowTotal(int[][] grid, int row) {
        int total = 0;
        for (int c = 0; c < grid[row].length; c++) {
            total += grid[row][c];
        }
        return total;
    }

    public static int countAbove(int[][] grid, int threshold) {
        int count = 0;
        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[r].length; c++) {
                if (grid[r][c] > threshold) {
                    count++;
                }
            }
        }
        return count;
    }

    public static int maxRowTotal(int[][] grid) {
        int best = rowTotal(grid, 0);
        for (int r = 1; r < grid.length; r++) {
            int current = rowTotal(grid, r);
            if (current > best) {
                best = current;
            }
        }
        return best;
    }
}
```

每小问 3 分：

| 小问 | 课堂评分点，各 1 分 |
| --- | --- |
| (a) | 正确遍历指定行；累加该行全部元素；初始化并返回且不改数组 |
| (b) | 行列边界正确；只统计严格大于阈值的元素；计数与返回正确且不改数组 |
| (c) | 通过 rowTotal 获取行和；正确初始化并比较所有行、支持负数；返回最大行和且不改数组 |

maxRowTotal 返回的是“行和”，不是“行索引”，也不是“单个最大元素”。若并列，返回同一个最大和值即可。

### FRQ 4 参考解：ListCleaner

```java
import java.util.ArrayList;

public class ListCleaner {
    public static void removeBelow(ArrayList<Integer> list, int limit) {
        for (int i = list.size() - 1; i >= 0; i--) {
            if (list.get(i) < limit) {
                list.remove(i);
            }
        }
    }

    public static void collapseRuns(ArrayList<Integer> list) {
        int i = 1;
        while (i < list.size()) {
            if (list.get(i).equals(list.get(i - 1))) {
                list.remove(i);
            } else {
                i++;
            }
        }
    }
}
```

| 课堂评分点 | 分值 |
| --- | --- |
| (a) 使用合法索引检查全部需要检查的元素 | 1 |
| (a) 严格小于 limit 的比较正确 | 1 |
| (a) 正确按索引删除且不漏连续元素 | 1 |
| (a) 原地操作、顺序不变并处理空列表 | 1 |
| (b) 正确从相邻对的第二个位置开始 | 1 |
| (b) 按数值/内容判断相邻相等，非错误的引用比较 | 1 |
| (b) 删除当前重复项后不跳过新的当前位置 | 1 |
| (b) 不相等时推进，保留不同连续段 | 1 |
| (b) 正确终止、处理空/单元素列表，原地保序 | 1 |

两题合计 9 分。正确的正向 while 或倒序方案均可按契约给分。

collapseRuns 是压缩“相邻段”，不是删除所有重复值。例 `[2,2,5,2]` 应保留为 `[2,5,2]`。
