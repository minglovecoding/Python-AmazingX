## 📚 APCSA 第二轮复习 06：数组、引用传递与反转 

## 1. 本章目标与授课安排

### 1.1 本轮必须能解释的内容

- 数组声明、创建、默认值、长度和合法索引。
- 增强 for 读取元素与索引循环更新元素的区别。
- 方法修改原数组、重新给形参赋值、返回新数组三者的不同。
- 新建反转与原地反转的契约和边界。
- “至少一个满足”与“全部满足”的正确返回时机。
- 用数组作小范围频数表；区分严格小于和小于等于。
- 用平行数组枚举无序对，避免重复计数。

## 2. 核心知识

### 2.1 声明、创建、长度与边界

```java
double[] scores = new double[3];
int[] values = {3, 5, 7};
int[] other;
other = new int[] {2, 4, 6};
```

数组变量保存引用。`int[] other;` 只声明局部变量；使用前还需要赋值。

```java
// values = {1, 2}; // 编译错误：不能独立使用这种初始化器赋值
values = new int[] {1, 2}; // 合法
```

| 项目 | 规则 |
| --- | --- |
| 数组长度 | `arr.length`，不是 `arr.length()` |
| 有效索引 | `0` 到 `arr.length-1` |
| 空数组 | `new int[0]` 合法，但不能访问任何元素 |
| 数组大小 | 数组对象创建后长度固定；变量仍可改指另一数组 |
| 越界 | 执行访问时通常抛 ArrayIndexOutOfBoundsException |

新数组元素默认值：int 为 0，double 为 0.0，boolean 为 false，String 等引用类型为 null。

这不代表未赋值的局部数组变量可以直接使用。`int[] arr; System.out.println(arr.length);` 不能编译。

### 2.2 读取与修改：选对循环

```java
double total = 0.0;
for (double value : scores) {
    total += value;
}
```

增强 for 适合逐个读取；基本类型循环变量是当前值的副本。

```java
for (int value : values) {
    value += 5; // 不写回数组
}
```

```java
for (int i = 0; i < values.length; i++) {
    values[i] += 5; // 更新原数组槽位
}
```

对象数组的循环变量保存引用副本；通过它调用 setter 可以修改对象，重新赋给该循环变量则不替换数组槽位。这一规则已在第 05 章展开。

### 2.3 数组参数：Java 仍然按值传递

```java
public static void change(int[] arr) {
    arr[0] = 9;
    arr = new int[] {1, 2};
}
```

若调用前 `numbers` 指向 `[3,4]`，调用后仍指向原数组，其内容变成 `[9,4]`。

| 操作 | 改变内容/指向 | 调用者能否观察到 |
| --- | --- | --- |
| `arr[0] = 9` | 修改共享数组的元素 | 能 |
| `arr = new int[]{1,2}` | 修改局部参数的引用值 | 不会让调用者变量改指向 |
| `return result` | 返回结果数组的引用 | 调用者需要接收返回值 |

`int[] copy = original;` 也只复制引用，不复制数组内容。若要独立副本，可以创建新数组后逐个复制。

### 2.4 两种反转：契约先于代码

**返回新数组：**

```java
public static int[] reversedCopy(int[] arr) {
    int[] result = new int[arr.length];
    for (int i = 0; i < arr.length; i++) {
        result[i] = arr[arr.length - 1 - i];
    }
    return result;
}
```

**原地反转：**

```java
public static void reverseInPlace(int[] arr) {
    for (int i = 0; i < arr.length / 2; i++) {
        int opposite = arr.length - 1 - i;
        int temp = arr[i];
        arr[i] = arr[opposite];
        arr[opposite] = temp;
    }
}
```

| 比较项 | reversedCopy | reverseInPlace |
| --- | --- | --- |
| 返回类型 | int[] | void |
| 原数组 | 保持不变 | 内容改变 |
| 额外结果数组 | 创建一个 | 不创建 |
| 处理范围 | 遍历全部位置并写到新数组 | 交换前一半位置与对应后半位置 |
| 空/单元素数组 | 都可自然处理 | 都不需要交换 |

若原地反转遍历全部位置，会将每一对交换两次，最后恢复原样。奇数长度中间元素无需移动。

`reversedCopy(arr);` 若没有接收返回值，原 arr 不会因此被反转。别用方法名猜副作用，要看题目契约和实现。

### 2.5 最大值与平均值

double 数组最大值，应使用 double 变量和非空前提：

```java
// Precondition: arr.length >= 1; all entries are finite double values.
double largest = arr[0];
for (double value : arr) {
    if (value > largest) {
        largest = value;
    }
}
```

不能写 `int largest = arr[0]` 接收 double；全负数时也不能把最大值初始为 0。

平均值先确认空输入规则，再保证浮点除法：

```java
// Precondition: arr.length >= 1; sum fits in int.
int sum = 0;
for (int value : arr) { sum += value; }
double average = (double) sum / arr.length;
```

`(double)(sum / arr.length)` 先丢失小数，再转换，不能修复。对本章小范围数值不讨论 NaN、无穷大或累计溢出的特殊处理。

### 2.6 “存在”与“全部”是两个不同任务

原稿“判断所有的数是否有偶数”含义不清，本稿拆成两种契约。

```java
public static boolean hasEven(int[] arr) {
    for (int value : arr) {
        if (value % 2 == 0) {
            return true;
        }
    }
    return false;
}
```

```java
public static boolean allEven(int[] arr) {
    for (int value : arr) {
        if (value % 2 != 0) {
            return false;
        }
    }
    return true;
}
```

| 任务 | 循环中可以提前确定的情况 | 循环后结论 | 本章空数组结果 |
| --- | --- | --- | --- |
| 存在偶数 | 找到一个就 true | 没找到则 false | false |
| 全部偶数 | 找到反例就 false | 没反例则 true | true |

不能在 hasEven 遇到第一个奇数时就返回 false；后面可能有偶数。负数奇偶判断同样使用 `%2 == 0` 或 `%2 != 0`。

### 2.7 统计左侧严格更小的元素

给定 `[2,2,3,1,3]`，输出 `[0,0,2,0,3]`：只看当前位置之前，且必须严格小于当前值。

**直观方法：**对每个 i 枚举 j=0..i-1，统计 arr[j]<arr[i]。

**小值域优化：**若题面保证值在 0..10，可用长度 11 的 freq。

```java
int[] freq = new int[11];
for (int i = 0; i < values.length; i++) {
    int smaller = 0;
    for (int v = 0; v < values[i]; v++) {
        smaller += freq[v];
    }
    result[i] = smaller;
    freq[values[i]]++;
}
```

处理位置 i 前，freq[v] 表示此前值为 v 的个数。按“先查询、后加入当前值”的顺序能清楚保持这一含义。

严格小于使用 `v < values[i]`；写 `<=` 会把此前等值元素也计入。本题恰好不统计当前值所在桶，因此即使先加当前桶也不会改变严格小于的答案，但会改变查询前的状态含义；不要把“先更新必错”当作普遍结论。

如果数值不在 0..10，长度 11 的数组不能直接使用。原稿 [P1428](https://www.luogu.com.cn/problem/P1428) 确实给出该值域，优化依赖这个前提。

### 2.8 平行数组与无序对

```java
int[] chinese = new int[n];
int[] math = new int[n];
int[] english = new int[n];
```

同一索引代表同一个人。不能分别排序后仍认为同一索引保持对应。

枚举不同学生的无序对：

```java
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        // 每一对恰好访问一次
    }
}
```

比较次数为 n(n-1)/2。若用所有 i!=j，会把 (i,j)、(j,i) 各算一次。

原稿 [P5728](https://www.luogu.com.cn/problem/P5728) 要求每科分差都不超过 5，且总分差不超过 10，四个限制必须同时满足。每科均差 5 时，总分可能差 15，所以总分条件不能省略。

### 2.9 二维数组入门：只区分两级长度

```java
int[][] grid = new int[2][3];
// grid.length == 2
// grid[0].length == 3
```

所有元素默认 0。一般按行读取：

```java
for (int r = 0; r < grid.length; r++) {
    for (int c = 0; c < grid[r].length; c++) {
        System.out.println(grid[r][c]);
    }
}
```

二维数组专题再讲行列统计、路径与复杂操作；本章不要求实现完整 GridPath。

## 3. MCQ 训练

每题只有一个正确答案，各题独立。数组参数均非 null；代码放在合法上下文中。明确故意错误的代码除外。

### MCQ 1｜长度与默认值

```java
double[] values = new double[3];
System.out.println(values.length + " " + values[1]);
```

A. `3 null`  
B. `3 0.0`  
C. `2 0.0`  
D. 编译错误


### MCQ 2｜数组长度的写法

已声明 `int[] arr = {2,4,6};`。哪一句能编译并把数组长度存入 n？

A. `int n = arr.length();`  
B. `int n = arr.size();`  
C. `int n = arr.length;`  
D. `int n = arr[3];`

### MCQ 3｜边界错误

```java
int[] arr = {2,4,6};
int sum = 0;
for (int i = 0; i <= arr.length; i++) {
    sum += arr[i];
}
System.out.println(sum);
```

A. 输出 `12`  
B. 输出 `0`  
C. 编译错误  
D. 访问索引 3 时抛 ArrayIndexOutOfBoundsException

### MCQ 4｜数组别名

```java
int[] a = {2,4};
int[] b = a;
b[0] = 7;
System.out.println(a[0]);
```

A. `7`  
B. `2`  
C. `0`  
D. 编译错误

### MCQ 5｜参数重新赋值

```java
public static void update(int[] a) {
    a[1] = 9;
    a = new int[] {5,6};
}
```

在同一类中执行：

```java
int[] values = {1,2};
update(values);
System.out.println(values[0] + " " + values[1]);
```

A. `5 6`  
B. `1 2`  
C. `1 9`  
D. `5 9`

### MCQ 6｜返回新数组

采用 2.4 的 reversedCopy：

```java
int[] a = {1,2,3};
int[] b = reversedCopy(a);
System.out.println(a[0] + " " + b[0] + " " + (a == b));
```

A. `3 3 true`  
B. `1 3 false`  
C. `3 1 false`  
D. `1 1 true`

### MCQ 7｜反转两次

采用 2.4 的 reverseInPlace：

```java
int[] arr = {1,2,3,4};
reverseInPlace(arr);
reverseInPlace(arr);
System.out.println(arr[0] + " " + arr[3]);
```

A. `1 4`  
B. `4 1`  
C. `1 1`  
D. `4 4`

### MCQ 8｜原地交换范围过大

```java
int[] arr = {1,2,3,4};
for (int i = 0; i < arr.length; i++) {
    int j = arr.length - 1 - i;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
System.out.println(arr[0] + " " + arr[3]);
```

A. `4 1`  
B. `4 4`  
C. `1 4`  
D. 运行时越界

### MCQ 9｜奇数长度中点

采用 2.4 的 reverseInPlace，反转 `{5,8,2,7,9}` 后，索引 2 的值是？

A. `5`  
B. `9`  
C. `8`  
D. `2`

### MCQ 10｜double 最大值

arr 为非空 double[]，所有值有限。要正确寻找最大值，包括全负数情况，largest 应怎样声明并初始化？

A. `double largest = arr[0];`  
B. `double largest = 0;`  
C. `int largest = arr[0];`  
D. `double largest = Double.MAX_VALUE;`

### MCQ 11｜过早返回 false

```java
public static boolean check(int[] arr) {
    for (int value : arr) {
        if (value % 2 == 0) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}
```

`check(new int[]{3,4})` 返回什么？

A. `true`  
B. `false`  
C. 编译错误  
D. 数组越界

### MCQ 12｜全部满足与空数组

```java
public static boolean allEven(int[] arr) {
    for (int value : arr) {
        if (value % 2 != 0) { return false; }
    }
    return true;
}
```

`allEven(new int[0])` 返回什么？

A. `false`  
B. 运行时异常  
C. `true`  
D. 编译错误

### MCQ 13｜平均值转换

已知 `int sum=13; int count=3;`。哪些表达式得到浮点平均值，而不是先做整数除法？

```java
I.   (double)(sum / count)
II.  (double)sum / count
III. sum / (double)count
```

A. 仅 I  
B. 仅 II  
C. 仅 I 和 II  
D. 仅 II 和 III

### MCQ 14｜左侧严格更小

对 `{2,2,3,1,3}` 的每个位置，统计它左侧严格小于它的元素个数。结果是？

A. `[0,0,2,0,3]`  
B. `[0,1,2,0,4]`  
C. `[1,1,3,0,4]`  
D. `[0,0,2,1,3]`

### MCQ 15｜频数查询边界

```java
int[] values = {2,2,1};
int[] freq = new int[11];
int[] result = new int[values.length];
for (int i = 0; i < values.length; i++) {
    for (int v = 0; v <= values[i]; v++) {
        result[i] += freq[v];
    }
    freq[values[i]]++;
}
System.out.println(result[0] + " " + result[1] + " " + result[2]);
```

A. `0 0 0`  
B. `0 1 0`  
C. `1 2 1`  
D. `0 1 2`

### MCQ 16｜有序对与无序对

```java
int count = 0;
for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        if (i != j) { count++; }
    }
}
System.out.println(count);
```

A. `4`  
B. `6`  
C. `12`  
D. `16`

### MCQ 17｜单科相近不代表总分相近

配对规则：每一科分差<=5，且总分差<=10。甲三科均为 80，乙三科均为 85。哪一项正确？

A. 可以配对，因为每科都差 5  
B. 可以配对，因为只要一科满足就可以  
C. 不可配对，因为单科不能恰好差 5  
D. 不可配对，因为总分差 15

### MCQ 18｜二维数组默认值

```java
int[][] grid = new int[2][3];
System.out.println(grid.length + " " + grid[0].length + " " + grid[1][2]);
```

A. `2 3 0`  
B. `3 2 0`  
C. `2 3 null`  
D. 编译错误

---

## 💻 5. FRQ 训练（4 题）

每题课堂自评 9 分。只需完成要求的方法；参考解的类壳用于上机验证。所有数组参数非 null，输入长度不超过 10000；另有更小上界时按该题说明。不使用 Stream、排序或现成反转 API。

### FRQ 1｜NumericArrays：查询与返回时机

**(a)** maximum：返回 double 数组的最大值。前提：至少一个元素，元素有限且绝对值不超过 1000000。

```java
public static double maximum(double[] values)
```

**(b)** average：返回 double 数组的平均值，前提与 (a) 相同。不要求格式化或舍入。

```java
public static double average(double[] values)
```

**(c)** hasEven：int 数组存在至少一个偶数则返回 true，空数组返回 false。

```java
public static boolean hasEven(int[] values)
```

**(d)** allEven：int 数组没有奇数则返回 true，空数组返回 true。

```java
public static boolean allEven(int[] values)
```

四个方法都不能修改输入数组。

| 调用 | 返回值 |
| --- | --- |
| `maximum(new double[]{-8.5,-3.2,-10.0})` | -3.2 |
| `average(new double[]{1,2,4})` | 7.0/3 |
| `hasEven(new int[]{3,4})` | true |
| `hasEven(new int[0])` | false |
| `allEven(new int[]{-2,0,4})` | true |
| `allEven(new int[]{2,3,4})` | false |
| `allEven(new int[0])` | true |

### FRQ 2｜ArrayReverse：返回新数组与原地修改

**(a)** reversedCopy：返回反序排列的新 int 数组，原数组保持不变。即使输入为空，也返回一个新的长度为 0 的数组。

```java
public static int[] reversedCopy(int[] values)
```

**(b)** reverseInPlace：在原数组上完成反转，不创建额外数组，不返回结果。

```java
public static void reverseInPlace(int[] values)
```

允许空数组与单元素数组。

```java
int[] a = {1,2,3};
int[] b = reversedCopy(a);
// a 内容仍为 [1,2,3]；b 为 [3,2,1]，且 a != b

reverseInPlace(a);
// a 内容变为 [3,2,1]；b 不受影响
```

不要把“返回新数组”实现成仅返回原引用，也不要用创建新数组的方式假装满足原地修改。

### FRQ 3｜EarlierSmaller：两个思路解决同一任务

本题根据原稿 P1428 重编为方法型练习，题意是每个位置统计左侧严格更小元素的个数。长度 0—1000，元素在 0—10，不能改动输入。两问均返回长度与输入相同的新数组。

**(a)** byScanning：用两个位置索引枚举此前元素，不能用频数表。

```java
public static int[] byScanning(int[] values)
```

**(b)** byFrequency：使用长度为 11 的频数数组；不要再次逐个枚举此前所有位置。

```java
public static int[] byFrequency(int[] values)
```

| 输入 | 两个方法均应返回 |
| --- | --- |
| `[2,2,3,1,3]` | `[0,0,2,0,3]` |
| `[1,2,3]` | `[0,1,2]` |
| `[3,2,1]` | `[0,0,0]` |
| `[0,0,10]` | `[0,0,2]` |
| `[]` | `[]` |

口述问题：如果输入可能出现 100，(b) 能直接照用吗？为什么？

### FRQ 4｜ScorePairs：平行数组与无序配对

根据原稿 P5728 重编。三个 int 数组 chinese、math、english 长度相同，0—1000 个学生；各科分数在 0—150。同一索引表示同一学生。

**(a)** areSimilar：返回索引 i、j 的学生是否满足每科分差不超过 5 且总分差不超过 10。i、j 是合法索引；只比较，不修改数据。

```java
public static boolean areSimilar(int[] chinese, int[] math,
                                  int[] english, int i, int j)
```

**(b)** countPairs：统计不同学生组成的无序对数量，每对只能计数一次。必须适当调用 areSimilar。

```java
public static int countPairs(int[] chinese, int[] math, int[] english)
```

空数组或只有一个学生时返回 0；不得修改或分别排序输入数组。

| chinese、math、english 三个数组 | countPairs |
| --- | --- |
| 三个都是 `[80,85,82]` | 2：第 0/2 与第 1/2 可配，0/1 不可配 |
| `[80,85]`、`[80,85]`、`[80,80]` | 1：总分恰差 10 |
| `[80,85]`、`[80,85]`、`[80,81]` | 0：总分差 11 |
| 三个都是 `[100]` | 0 |
| 三个都是 `[]` | 0 |

## 🏁 6. 官方题迁移

### 6.1 官方 MCQ 样题：数组最大值

来源：[CED，Effective Fall 2025](https://apcentral.collegeboard.org/media/pdf/ap-computer-science-a-course-and-exam-description.pdf#page=163)，PDF 第 163 页、印刷页码 156，Sample Exam Questions 第 14 题。

这是官方样题，不是实考年份题。针对“最大值从 0 开始”构造全负数反例，判断修复方案。

<details>
<summary>教师核对</summary>

答案 A，使用数组第一个元素初始化最大值。与本章 MCQ 10、FRQ 1(a) 对照：官方样题用 int，本章还要求注意 double 类型一致。

</details>

### 6.2 进阶真题：2025 Q3 Round 的构造器部分

- [官方题目](https://apcentral.collegeboard.org/media/pdf/ap25-frq-computer-science-a.pdf#page=11)：完整 Q3 在 PDF 第 11—15 页，构造器要求在第 13 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap25-sg-computer-science-a.pdf)：定位 Q3(a)。

输入为 String[]，需要遍历并按顺序创建对象存入列表。适合数组与对象、ArrayList 基础都已学过的学生。前章若已做过，本章可只复盘数组索引与业务名次的差别，不重复完整配对问。

本章主线方法无需 ArrayList；此题是跨章节选做，按原题契约与官方细则完成。

### 6.3 二维选做真题：2025 Q4 SumOrSameGame 的初始化部分

- [官方题目](https://apcentral.collegeboard.org/media/pdf/ap25-frq-computer-science-a.pdf#page=16)：类框架在 PDF 第 16 页，构造器要求在第 17 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap25-sg-computer-science-a.pdf)：定位 Q4(a)。

创建给定行列数的二维数组，并填入指定范围随机整数，连接本章二维入门与此前 Math.random。需复习随机数后选做；本章不要求完整实现清除配对的 (b)。

检查行数、列数、每个元素是否赋值，以及随机区间两端是否正确。

### 6.4 使用说明

按技能选择旧题，不把旧卷的时长、题型分布当成现行规则。公开题与评分入口见[官方历年题页面](https://apcentral.collegeboard.org/courses/ap-computer-science-a/exam/past-exam-questions)。原创数组方法题用于先练基本能力，跨章节真题按学生进度选做。

## 7. MCQ 答案与解析

### 7.1 答案速查

| 题号 | 答案 | 主要错因 |
| --- | --- | --- |
| 1 | B | double 数组默认值 |
| 2 | C | length 是属性 |
| 3 | D | 最后有效索引是 length-1 |
| 4 | A | 数组别名 |
| 5 | C | 共享内容修改与形参改指向不同 |
| 6 | B | 新数组与原数组独立 |
| 7 | A | 反转两次恢复内容 |
| 8 | C | 每一对交换两次 |
| 9 | D | 奇数数组中点不动 |
| 10 | A | 类型匹配与全负数初值 |
| 11 | B | 不能由第一个奇数判断“没有偶数” |
| 12 | C | 全称判断的空输入约定 |
| 13 | D | 浮点除法前转换 |
| 14 | A | 严格小于、只统计左侧 |
| 15 | B | <= 会计入此前等值 |
| 16 | C | 无序对被重复枚举 |
| 17 | D | 四个限制同时满足 |
| 18 | A | 行数、列数与 int 默认值 |

### 7.2 逐题解释

1. 长度为 3；每个 double 元素初值为 0.0。引用类型默认 null 的规则不能套给 double。
2. `.length` 是数组属性。A、B 不是数组可用的长度方法；D 虽能编译，但执行时访问索引 3 越界，也没有获取长度。
3. i=0、1、2 的访问合法；i=3 时越界，还没执行最后的 println。不是因为 for 语法而编译失败。
4. a、b 指向同一个数组，b[0] 的修改也能通过 a[0] 读取。
5. a[1]=9 修改原数组；接着形参 a 改指向新数组，但调用者 values 仍指向原数组 [1,9]。
6. reversedCopy 创建独立结果 [3,2,1]，原数组仍是 [1,2,3]，引用比较为 false。
7. 第一次原地反转成 [4,3,2,1]，第二次恢复 [1,2,3,4]。
8. 前半轮反转，后半轮把每对再次换回；最后内容与初始一致，不会因该索引公式越界。
9. 长度 5 的中点为索引 2，其镜像仍是 2。只交换前两对，中点值 2 保持不变。
10. A 使用已有元素且类型为 double。B 对全负数错误；C 不能直接窄化；D 从最大有限值开始，普通输入不可能将它更新为正确结果。
11. 第一项 3 为奇数，立即返回 false，根本没检查 4。应把最终 false 放在循环后。
12. 空数组没有发现奇数，循环后返回 true。本题问实际实现，亦符合本章明确的空输入契约。
13. I 先算 13/3=4，再转 4.0；II、III 在除法前引入 double，得到浮点平均值。
14. 位置 2 的 3 左侧有两个 2；最后的 3 左侧严格更小的是 2、2、1，共 3 个，不能计入此前的 3。
15. 使用 <= 查询“左侧小于或等于”。第一个 2 前无元素，得 0；第二个 2 计入前一个 2，得 1；1 左侧没有 <=1 的值，得 0。
16. 每个 i 都有 3 个不相等的 j，总共 4*3=12。每个无序对出现两次；若要无序对，固定 j>i。
17. 单科条件都满足，但总分分别为 240 与 255，差 15，不符合总分要求。恰好差 5 本身允许。
18. 外层长度为 2，每行长度为 3，所有 int 元素默认 0。

## 8. FRQ 参考解与课堂评分

### FRQ 1 参考解：NumericArrays

```java
public class NumericArrays {
    public static double maximum(double[] values) {
        double best = values[0];
        for (double value : values) {
            if (value > best) {
                best = value;
            }
        }
        return best;
    }

    public static double average(double[] values) {
        double total = 0.0;
        for (double value : values) {
            total += value;
        }
        return total / values.length;
    }

    public static boolean hasEven(int[] values) {
        for (int value : values) {
            if (value % 2 == 0) {
                return true;
            }
        }
        return false;
    }

    public static boolean allEven(int[] values) {
        for (int value : values) {
            if (value % 2 != 0) {
                return false;
            }
        }
        return true;
    }
}
```

| 小问 | 课堂评分点 | 分值 |
| --- | --- | --- |
| (a) | 类型正确且从合法初值开始；遍历并正确比较；返回最大值、支持全负数且不修改输入 | 3 |
| (b) | 浮点累计全部元素；除以长度并返回且不修改输入 | 2 |
| (c) | 找到一个偶数即 true；否则完整检查后 false，含空数组 | 2 |
| (d) | 找到奇数反例即 false；无反例返回 true，含空数组 | 2 |

最大值和平均值按题目前提不调用空数组，不必擅自增加“空数组最大值为 0”等规则。

### FRQ 2 参考解：ArrayReverse

```java
public class ArrayReverse {
    public static int[] reversedCopy(int[] values) {
        int[] result = new int[values.length];
        for (int i = 0; i < values.length; i++) {
            result[i] = values[values.length - 1 - i];
        }
        return result;
    }

    public static void reverseInPlace(int[] values) {
        for (int i = 0; i < values.length / 2; i++) {
            int j = values.length - 1 - i;
            int temp = values[i];
            values[i] = values[j];
            values[j] = temp;
        }
    }
}
```

(a) 4 分：创建正确长度的新数组 1 分；所有输出位置均被填入 1 分；反向索引正确 1 分；返回结果且原数组不变，包含空数组 1 分。

(b) 5 分：只交换必要的对称位置 1 分；镜像索引正确 1 分；借临时变量正确交换 1 分；原数组实际改变且不建额外数组 1 分；void 方法、空/单元素和奇数中点处理正确 1 分。

自检：新建反转后修改结果数组，输入不应随之改变；原地反转两次应恢复原内容。这些测试与只检查一次普通输出相比，更能发现引用与副作用错误。

### FRQ 3 参考解：EarlierSmaller

```java
public class EarlierSmaller {
    public static int[] byScanning(int[] values) {
        int[] result = new int[values.length];
        for (int i = 0; i < values.length; i++) {
            for (int j = 0; j < i; j++) {
                if (values[j] < values[i]) {
                    result[i]++;
                }
            }
        }
        return result;
    }

    public static int[] byFrequency(int[] values) {
        int[] result = new int[values.length];
        int[] freq = new int[11];
        for (int i = 0; i < values.length; i++) {
            int smaller = 0;
            for (int v = 0; v < values[i]; v++) {
                smaller += freq[v];
            }
            result[i] = smaller;
            freq[values[i]]++;
        }
        return result;
    }
}
```

(a) 4 分：新数组长度正确、初值为 0 共 1 分；只枚举此前位置 1 分；严格小于才累计到正确位置 1 分；返回新数组、处理空数组且输入不变 1 分。

(b) 5 分：11 个计数桶且初值正确 1 分；查询严格更小的桶 1 分；将此前出现次数相加并写答案 1 分；正确纳入当前值并维护频数 1 分；结果长度、返回和空输入正确且输入不变 1 分。

正确实现不强求语句排列与参考解逐字一致，要核对频数所代表的时刻和查询区间。两种方法可以互相校验；(a) O(n²)，(b) O(11n)，后者依赖小值域，不能移植到任意整数时照搬数组长度。

### FRQ 4 参考解：ScorePairs

```java
public class ScorePairs {
    public static boolean areSimilar(int[] chinese, int[] math,
                                     int[] english, int i, int j) {
        int firstTotal = chinese[i] + math[i] + english[i];
        int secondTotal = chinese[j] + math[j] + english[j];
        return Math.abs(chinese[i] - chinese[j]) <= 5
               && Math.abs(math[i] - math[j]) <= 5
               && Math.abs(english[i] - english[j]) <= 5
               && Math.abs(firstTotal - secondTotal) <= 10;
    }

    public static int countPairs(int[] chinese, int[] math, int[] english) {
        int count = 0;
        for (int i = 0; i < chinese.length; i++) {
            for (int j = i + 1; j < chinese.length; j++) {
                if (areSimilar(chinese, math, english, i, j)) {
                    count++;
                }
            }
        }
        return count;
    }
}
```

| 课堂评分点 | 分值 |
| --- | --- |
| (a) 三科分差分别正确取绝对值并比较 <=5 | 2 |
| (a) 总分计算及总分差 <=10 正确 | 1 |
| (a) 用 && 合并四个限制并返回 boolean | 1 |
| (b) 按合法索引枚举学生 | 1 |
| (b) 只枚举 i<j，不包含自身、不重复计数 | 1 |
| (b) 正确调用 areSimilar | 1 |
| (b) 满足时累计、返回正确，含 0/1 个学生 | 1 |
| 两问签名正确，输入对应关系与数组内容不变 | 1 |

分数上界保证总分、分差及结果均在 int 范围内。若扩展到任意 int 数值，不能忽略减法与 Math.abs 的溢出问题。

