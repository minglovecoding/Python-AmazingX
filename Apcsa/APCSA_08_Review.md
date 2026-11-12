## APCSA 第二轮复习 08：二维数组与网格遍历

## 📚 1. 本轮目标与授课安排

本章从“能遍历二维数组”提升到“能解释访问顺序、写出边界正确的网格算法，并区分修改原数组与构造新数组”。

| 本轮能力 | 学生应能回答 |
| --- | --- |
| 维度与边界 | 行数、列数、合法下标分别是什么？ |
| 遍历顺序 | 外层控制行还是列？访问坐标按什么顺序变化？ |
| 状态与计数 | 求每行最大值时，变量应在哪里重置？ |
| 相邻关系 | 右邻居存在的条件是什么？允许跨行配对吗？ |
| 引用语义 | row 指向原数组的哪一行？交换行与复制行有何区别？ |
| 对象网格 | new Student[2][3] 创建了几名学生？何时需要判空？ |

## 2. 核心知识与易错点

### 2.1 数组的数组：类型、默认值与维度

```java
int[][] grid = new int[2][3];
String[][] names = new String[2][3];
int[][] values = {{1, 2, 3}, {4, 5, 6}};
```

| 表达式 | 类型/含义 | 上例 values 的结果 |
| --- | --- | --- |
| `values` | int[][]，二维数组引用 | 整个网格 |
| `values.length` | 行数 | 2 |
| `values[0]` | int[]，第 0 行引用 | 含 1、2、3 的行 |
| `values[0].length` | 第 0 行列数 | 3 |
| `values[1][2]` | int，行 1 列 2 的元素 | 6 |

int 元素默认 0，double 默认 0.0，boolean 默认 false，String/Student 等引用元素默认 null。

对 R×C 矩形数组，合法行索引为 `0..R-1`，合法列索引为 `0..C-1`。`grid.length` 与 `grid[0].length` 是两个独立维度，不能因为方阵样例通过就混用。

**先看契约**：只有存在第 0 行，才能访问 `grid[0]`。`new int[0][3]` 在 Java 中合法，但执行 `grid[0].length` 会越界；`new int[2][0]` 有两行，每行长度为 0。不要从没有第 0 行的数组读取列数。本章各 FRQ 会明确是否允许零行、零列。

### 2.2 行优先与列优先：访问同一个坐标表达式

以下 grid 是非空矩形数组：

```java
// 行优先：先横向走完一行，再换行
for (int r = 0; r < grid.length; r++) {
    for (int c = 0; c < grid[r].length; c++) {
        System.out.print(grid[r][c] + " ");
    }
    System.out.println();
}

// 列优先：先纵向走完一列，再换列
for (int c = 0; c < grid[0].length; c++) {
    for (int r = 0; r < grid.length; r++) {
        System.out.print(grid[r][c] + " ");
    }
    System.out.println();
}
```

对 `{{1, 2, 3}, {4, 5, 6}}`：

| 顺序 | 访问坐标 | 连续输出的值 |
| --- | --- | --- |
| 行优先 | (0,0)、(0,1)、(0,2)、(1,0)、(1,1)、(1,2) | 1、2、3、4、5、6 |
| 列优先 | (0,0)、(1,0)、(0,1)、(1,1)、(0,2)、(1,2) | 1、4、2、5、3、6 |

列优先不要求把访问式改成 grid[c][r]；应先确定两个变量的含义，再决定循环边界。原稿在 3×3 方阵中交换下标容易掩盖错误，二轮复习优先用 2×3 反测。

### 2.3 增强 for：修改元素与重绑定变量不同

```java
for (int[] row : grid) {
    for (int value : row) {
        value = 0; // 只改局部变量，不改变原网格
    }
}
```

外层 row 是一个行数组引用，内层 value 是一个 int 值。下面两段也不同：

```java
for (int[] row : grid) {
    row[0] = 0; // 修改每行第一个元素；要求每行至少一列
}

for (int[] row : grid) {
    row = new int[3]; // row 改指新行；不替换 grid 中的行引用
}
```

| 语句 | 是否改变原网格 |
| --- | --- |
| `value = value + 1` | 否 |
| `row[0] = row[0] + 1` | 是，修改被引用行中的元素 |
| `row = new int[3]` | 否，只重绑定局部变量 |
| `grid[r] = new int[3]` | 是，替换网格中第 r 行引用 |

### 2.4 统计模板：总量、每行、每列的变量位置

```java
public static int sumAll(int[][] grid) {
    int total = 0;
    for (int[] row : grid) {
        for (int value : row) {
            total += value;
        }
    }
    return total;
}

public static int countEvens(int[][] grid) {
    int count = 0;
    for (int[] row : grid) {
        for (int value : row) {
            if (value % 2 == 0) count++;
        }
    }
    return count;
}
```

以上方法假设累计结果不会超出 int 范围。总和、总个数只初始化一次；每行最大值则必须在每行开始时重新初始化。

```java
// 前置条件：矩形数组，每行至少一个元素
int[] result = new int[grid.length];
for (int r = 0; r < grid.length; r++) {
    int max = grid[r][0];
    for (int c = 1; c < grid[r].length; c++) {
        if (grid[r][c] > max) max = grid[r][c];
    }
    result[r] = max;
}
```

不要用 max = 0 处理可能全负的行。求每列总和时，外层固定 c、内层改变 r，且每一列的 sum 要重新置 0。

### 2.5 查找：true 可以提前返回，false 通常要等遍历结束

```java
public static boolean containsName(String[][] seats, String name) {
    for (String[] row : seats) {
        for (String studentName : row) {
            if (studentName != null && studentName.equals(name)) {
                return true;
            }
        }
    }
    return false;
}
```

前置条件：seats 和各行非 null，name 非 null；单元格允许 null。String 内容用 equals；先判空再调用方法。不能在发现第一个“不匹配”时就返回 false。

若问题要求返回第一个匹配对象或坐标，遍历顺序也是契约的一部分。行优先与列优先可能返回不同的匹配项。

### 2.6 相邻元素：边界从访问式推出来

检查同一行左右相邻的一对 `(r,c)`、`(r,c+1)`：需要 `c+1 < grid[r].length`，等价于 `c < grid[r].length-1`。

```java
public static int countHorizontalPairs(int[][] grid) {
    int count = 0;
    for (int r = 0; r < grid.length; r++) {
        for (int c = 0; c < grid[r].length - 1; c++) {
            if (grid[r][c] == grid[r][c + 1]) count++;
        }
    }
    return count;
}
```

`[2, 2, 2]` 有 **2 对**，因为 (0,1)、(1,2) 都符合，允许重叠；不是 3 个相等元素，也不是选任意两个元素的组合数。

相邻空座位同理，必须同一行中两个位置都为 0。某一行末尾与下一行开头不构成左右相邻。

| 关系 | 访问位置 | 需要检查的边界 |
| --- | --- | --- |
| 右邻居 | `[r][c+1]` | c+1 < 列数 |
| 下邻居 | `[r+1][c]` | r+1 < 行数 |
| 2×2 窗口 | `[r][c]`、`[r+1][c]`、`[r][c+1]`、`[r+1][c+1]` | r < R-1 且 c < C-1 |

### 2.7 对角线、转置与相邻平均

**两条完整对角线的标准公式用于 n×n 方阵**：

```java
int main = 0;
int anti = 0;
for (int i = 0; i < m.length; i++) {
    main += m[i][i];
    anti += m[i][m.length - 1 - i];
}
```

主对角线满足 r = c，副对角线满足 r+c = n-1。若要把两条对角线涉及的位置每个只加一次，奇数 n 的中心被重复算了，要减去一次 `m[n/2][n/2]`；偶数 n 不减。

**转置**：原 R×C 数组变成 C×R，新旧坐标满足 `result[c][r] = grid[r][c]`。转置与“按列输出”不同：转置需要构造结果数组，改变结果的形状。

**2×2 相邻平均**：以每个合法窗口左上角为输出位置，结果大小为 `(R-1)×(C-1)`。原稿使用 int[][] 和整数除法，表达的是截断后的平均；本章 FRQ 改成 double[][]，保留小数。

```java
int sum = grid[r][c] + grid[r + 1][c]
        + grid[r][c + 1] + grid[r + 1][c + 1];
double average = sum / 4.0;
```

`(double)(sum / 4)` 先整数除法，再转 double，无法恢复被截断部分。int 除法向 0 截断，例如 -3 / 4 = 0，不是数学向下取整的 -1。本章数值范围保证四项和不溢出。

### 2.8 交换行、共享行与新数组

```java
public static void swapRows(int[][] grid, int r1, int r2) {
    int[] temp = grid[r1];
    grid[r1] = grid[r2];
    grid[r2] = temp;
}
```

这段交换两条行引用，时间 O(1)。它不逐个交换元素，也不复制行内内容。调用前保存的某行引用，调用后仍指向同一个行数组。

```java
int[][] a = {{1, 2}, {3, 4}};
int[] saved = a[0];
swapRows(a, 0, 1);
// a[0] 是原第二行；saved 是原第一行，现在等于 a[1]
```

`a[1] = a[0]` 则让两个位置引用同一行，不是交换，也不是复制。修改其中一个行引用访问到的元素，另一个位置也能看到变化。这是引用语义辨析，不要求实现复杂的深复制工具。

### 2.9 对象二维数组：数组存在不等于对象存在

```java
Student[][] students = new Student[2][3];
// 此时 6 个单元格均为 null，没有自动创建 Student 对象
students[0][0] = new Student("Amy", 90);
```

假设 Student 提供 getName()，遍历姓名可以写成：

```java
for (Student[] row : students) {
    for (Student student : row) {
        if (student != null) {
            System.out.println(student.getName());
        }
    }
}
```

原稿的 `p.getname()` 需要与类中声明的大小写完全一致，也需要完整闭合代码块。本章统一使用 getName()；Student 的可编译定义见 FRQ 4。

把同一 Student 对象引用放在多个位置，不会创建多名学生。题目若要求统计“符合条件的座位数”，每个符合的单元格都算；如果要求统计“不同对象数”，则是另一个问题。

### 2.10 用输入形状和契约检查算法

| 算法 | 核心前置条件 | 时间 | 结果空间 |
| --- | --- | --- | --- |
| 完整遍历/对象筛选 | 行可访问 | O(RC) | 若只计数则 O(1) |
| 每行最大值 | 每行至少一列 | O(RC) | O(R) |
| 每列求和 | 至少一行，矩形 | O(RC) | O(C) |
| 水平相邻对 | 只访问存在的右邻居 | O(RC) 上界 | O(1) |
| 转置 | 非空矩形 | O(RC) | O(RC) |
| 2×2 平均 | R、C 均至少 2 | O(RC) | O((R-1)(C-1)) |
| 交换两行引用 | 两个行索引合法 | O(1) | O(1) |

R 和 C 是两个独立输入维度；非方阵不要直接写成 O(n²)。结果空间与不含结果的辅助变量空间分开说明。本章 FRQ 的输出数组以外都只需 O(1) 临时变量。

## 🎯 3. MCQ 训练（原创）

每题只有一个正确选项。代码均在合法上下文，使用标准 Java；除题目明确的别名、null 外，数组都是矩形且各行存在。swapRows 指 2.8 的方法，sumAll/containsName 指本章方法。

### MCQ 1：维度与默认值

```java
int[][] a = new int[2][3];
System.out.println(a.length + " " + a[0].length + " " + a[1][2]);
```

A. `3 2 0`  
B. `2 3 0`  
C. `2 3 null`  
D. 编译错误

### MCQ 2：列优先输出

忽略空格差异，以下代码输出什么？

```java
int[][] a = {{1, 2, 3}, {4, 5, 6}};
for (int c = 0; c < a[0].length; c++) {
    for (int r = 0; r < a.length; r++) {
        System.out.print(a[r][c]);
    }
}
```

A. `142536`  
B. `123456`  
C. `135246`  
D. `654321`

### MCQ 3：非方阵的循环边界

a 是至少一行一列的矩形数组。要按列优先访问全部元素，下列哪组填空正确？

```java
for (int c = 0; c < /* I */; c++) {
    for (int r = 0; r < /* II */; r++) {
        System.out.print(a[r][c] + " ");
    }
}
```

A. I = a.length，II = a[0].length  
B. I = a.length，II = a.length  
C. I = a[0].length，II = a[0].length  
D. I = a[0].length，II = a.length

### MCQ 4：增强 for 的局部变量

```java
int[][] a = {{1, 2}, {3, 4}};
for (int[] row : a) {
    for (int x : row) x = 0;
}
System.out.println(sumAll(a));
```

A. 0  
B. 4  
C. 10  
D. 编译错误

### MCQ 5：通过行引用修改

```java
int[][] a = {{1, 2}, {3, 4}};
for (int[] row : a) row[0] += 10;
System.out.println(a[0][0] + " " + a[1][0]);
```

A. `11 13`  
B. `1 3`  
C. `11 3`  
D. `11 12`

### MCQ 6：共享同一行

```java
int[][] a = {{1, 2}, {3, 4}};
a[1] = a[0];
a[1][0] = 9;
System.out.println(a[0][0] + " " + a[1][0]);
```

A. `1 9`  
B. `9 9`  
C. `9 3`  
D. `1 3`

### MCQ 7：交换行与已有引用

```java
int[][] a = {{1, 2}, {4, 5}};
int[] saved = a[0];
swapRows(a, 0, 1);
System.out.println(a[0][0] + " " + a[1][0] + " " + saved[0]);
```

A. `1 4 1`  
B. `4 1 4`  
C. `4 1 1`  
D. `1 1 1`

### MCQ 8：全负数的每行最大值

对 `{{-8, -2, -5}, {-1, -7, -3}}` 求每行最大值，结果应是什么？

A. `[0, 0]`  
B. `[-8, -1]`  
C. `[-2, -2]`  
D. `[-2, -1]`

### MCQ 9：每列总和

对 `{{1, 2, 3}, {4, 5, 6}}` 求每列总和，结果是什么？

A. `[5, 7, 9]`  
B. `[6, 15]`  
C. `[5, 9]`  
D. `[1, 4, 2, 5, 3, 6]`

### MCQ 10：对角线的重复中心

m 为 `{{1,2,3},{4,5,6},{7,8,9}}`。将主对角线和与副对角线和相加，再减去一次中心元素，结果是什么？

A. 15  
B. 25  
C. 30  
D. 20

### MCQ 11：允许重叠的相邻对

对 `{{2, 2, 2}, {3, 4, 4}}` 调用 countHorizontalPairs，返回什么？

A. 2  
B. 4  
C. 3  
D. 6

### MCQ 12：相邻不能跨行

0 表示空座位、1 表示已占用。seats 为 `{{1, 0}, {0, 1}}`，是否存在同一行中两个左右相邻的空座位？

A. true，因为两个 0 在输出序列中连续  
B. true，因为两行各有一个 0  
C. true，因为两个 0 斜向相邻  
D. false

### MCQ 13：相邻平均与整数除法

sum 为 int，值为 11。哪一个表达式结果为 2.75？

A. `(double)(sum / 4)`  
B. `sum / 4.0`  
C. `sum / 4`  
D. `(double)(sum / 4) + 0.0`

### MCQ 14：转置的形状与坐标

a 为 `{{1,2,3},{4,5,6}}`，t 是它的转置。哪项正确？

A. t 有 3 行 2 列，t[2][1] 为 6  
B. t 有 2 行 3 列，t[1][2] 为 6  
C. t 有 3 行 2 列，t[1][2] 为 6  
D. t 有 3 行 2 列，t[2][1] 为 3

### MCQ 15：错误的提前返回

```java
public static boolean badContains(String[][] a, String target) {
    for (String[] row : a) {
        for (String s : row) {
            if (s.equals(target)) return true;
            else return false;
        }
    }
    return false;
}
```

对 `{{"Amy", "Bo"}, {"Cy", "Di"}}` 调用 badContains(a, "Bo")，返回什么？

A. true，因为 Bo 在第一行  
B. true，因为循环会遍历全部元素  
C. 发生空指针异常  
D. false，因为第一次检查 Amy 时就返回

### MCQ 16：对象数组的默认元素

假设 Student 是合法类，并提供 getName()。

```java
Student[][] a = new Student[2][3];
System.out.println(a[0][0].getName());
```

A. 输出空字符串  
B. 输出 null  
C. 发生 NullPointerException  
D. 发生 ArrayIndexOutOfBoundsException

### MCQ 17：统计位置还是不同对象

Student 提供 getScore()，以下方法统计分数 >= 60 的非空单元格数。代码输出什么？

```java
Student s = new Student("Amy", 90);
Student[][] a = {{s, null}, {s, null}};
int count = 0;
for (Student[] row : a) {
    for (Student p : row) {
        if (p != null && p.getScore() >= 60) count++;
    }
}
System.out.println(count);
```

A. 1  
B. 2  
C. 4  
D. 发生 NullPointerException

### MCQ 18：二维遍历的成本

R×C 的矩形数组中，每个元素只访问一次，每次做常数时间操作。总时间的紧确阶是什么？

A. Θ(RC)  
B. Θ(R+C)  
C. Θ(R²)，与 C 无关  
D. Θ(1)

## 4. FRQ 训练

统一约定：数组本身与各行不为 null；数组为矩形。方法为 public static，不需要输入输出，也不需要编写 main。每题另给允许的形状、数值和修改要求；不得用 Stream API 或现成矩阵工具替代循环。

### FRQ 1：GridStatistics（行最大值与列总和）

前置条件：grid 至少 1 行 1 列，行列数均不超过 100，每个值在 -1000 到 1000 之间。两个方法均不得修改原网格。

**(a)** `public static int[] rowMaxes(int[][] grid)`

返回一个新数组，第 r 项为第 r 行的最大值。必须支持全负数行。

**(b)** `public static int[] columnSums(int[][] grid)`

返回一个新数组，第 c 项为第 c 列的总和。

示例：grid 为 `{{-5, -2, -8}, {4, 1, 6}}`：rowMaxes 返回 `[-2, 6]`，columnSums 返回 `[-1, -1, -2]`。

自测：1×1、1×多列、多行×1、全负数、最大值在最后一列、非方阵。

### FRQ 2：SeatPlanner（水平相邻与首个空座对）

前置条件：seats 中只有 0、1，0 为空、1 为占用。允许零行或零列；各行仍是非 null 的等长数组。

**(a)** `public static int countHorizontalPairs(int[][] seats)`

统计每行中左右相邻且值相等的元素对数。相等的 0 或 1 都算，允许重叠；不能跨行。没有元素或没有相邻对时返回 0。

示例：`{{0,0,0},{1,0,0}}` 返回 3：第一行 2 对，第二行 1 对。

**(b)** `public static int[] firstAdjacentSeats(int[][] seats)`

按行优先顺序，返回首个左右相邻空座对的**左侧座位**坐标 `{r,c}`；不存在则返回 null。只返回坐标，不占用座位，不修改输入。

示例：`{{1,0,1,0},{1,0,0,0}}` 返回 `{1,1}`。`{{1,0},{0,1}}` 返回 null。

迁移：原稿作业 hasAdjacentSeats 可以依据相同遍历逻辑返回 boolean。这里增加“首个坐标”，训练访问顺序与返回契约。

### FRQ 3：GridTransforms（转置与 2×2 平均）

前置条件：grid 为矩形，行列数均不超过 100，元素在 -1000 到 1000 之间。两个方法都返回新数组，原网格不变。

**(a)** `public static int[][] transpose(int[][] grid)`

本小题至少 1 行 1 列。返回转置，结果为 C×R，满足 `result[c][r] = grid[r][c]`。不能仅返回原数组，也不能共享原来的行数组。

示例：`{{1,2,3},{4,5,6}}` → `{{1,4},{2,5},{3,6}}`。

**(b)** `public static double[][] neighborAverages(int[][] grid)`

本小题至少 2 行 2 列。返回 `(R-1)×(C-1)` 的新数组，其中 `[r][c]` 为输入中以 `(r,c)` 为左上角的 2×2 窗口的精确平均值，保留小数。

示例：`{{1,2,4},{3,5,8}}` → `{{2.75,4.75}}`。

自测：2×2 只产生一个结果；2×3、3×2 检查形状；四项和不是 4 的倍数；负数平均。修改返回数组的值不应影响输入。

### FRQ 4：StudentGrid（对象、判空与并列规则）

已知下列 Student 类，score 为 0 到 100 的整数，name 不为 null：

```java
public class Student {
    private String name;
    private int score;

    public Student(String name, int score) {
        this.name = name;
        this.score = score;
    }

    public String getName() { return name; }
    public int getScore() { return score; }
}
```

前置条件：students 至少 1 行 1 列，单元格可以为 null；两个方法均不得修改网格或学生对象。

**(a)** `public static int countPassing(Student[][] students, int passMark)`

返回分数 >= passMark 的非空单元格数，passMark 为 0..100。即使多个位置引用同一 Student，也按符合条件的位置分别计数。

**(b)** `public static Student topStudent(Student[][] students)`

返回最高分学生的原对象引用；并列时返回**按行优先顺序最先遇到**的那个。全表为 null 时返回 null。不能新建同名同分对象代替返回原对象。

示例（名字旁数字为分数，— 为 null）：

| | 列 0 | 列 1 |
| --- | --- | --- |
| 行 0 | Amy 90 | — |
| 行 1 | Bo 90 | Cy 59 |

passMark = 60 时 countPassing 返回 2，topStudent 返回 Amy 对象引用。

自测：全部 null、只有最后一个位置非空、分数全为 0、恰等于及格线、不同对象并列最高分、同一对象占多个位置。

## 5. 官方真题迁移

以下是公开官方 FRQ 的中文任务摘要与训练建议，**不重印完整题面**。请按原题的前置条件与评分作答；本稿原创题的边界规则不能直接移植到真题。

| 年份与题目 | 与本章的联系 | 练习安排 |
| --- | --- | --- |
| [2023 Q4 BoxOfCandy](https://apcentral.collegeboard.org/media/pdf/ap23-frq-comp-sci-a.pdf#page=14)，PDF 第 14—18 页 | 对象二维数组、null、沿列移动、指定顺序查找 | FRQ 4 后做；重点辨析“移动对象引用”与“复制” |
| [2024 Q4 GridPath](https://apcentral.collegeboard.org/media/pdf/ap24-frq-comp-sci-a.pdf#page=13)，PDF 第 13—18 页 | 右/下邻居边界、坐标对象、路径累计 | FRQ 2、3 后选做；需会使用 Location 类和辅助方法 |

**BoxOfCandy 检查点**：空位置为 null；移动后要清空原位置。(b) 的遍历从最后一行开始，每行从左到右；不是普通的从上到下行优先。按口味删除时，只清空找到的位置并返回原对象；不把整个二维数组“缩短”。

**GridPath 检查点**：只考虑右、下邻居；先处理仅有一个邻居的边界。原题保证值互异，不必自创平局规则。sumPath 依次调用 getNextLoc，累计路径包含起点与终点；到终点后停止，不再调用下一步。它要求遵循题定路径，不是求所有路径的最小总和。

评分对照：[2023 官方评分](https://apcentral.collegeboard.org/media/pdf/ap23-sg-computer-science-a.pdf)；[2024 官方评分](https://apcentral.collegeboard.org/media/pdf/ap24-sg-computer-science-a.pdf)。历年题号仅用于定位原题，不据此推断当前考试结构。

## 6. MCQ 答案与解析

| 题号 | 答案 | 关键理由 |
| --- | --- | --- |
| 1 | B | 2 行 3 列，int 元素默认 0 |
| 2 | A | 每次固定 c，先访问上行再访问下行 |
| 3 | D | c 用列数，r 用行数，访问仍为 a[r][c] |
| 4 | C | 给局部 int 变量赋值不修改原元素 |
| 5 | A | row 指向原来的行数组，row[0] 修改会保留 |
| 6 | B | 两个行位置已经指向同一行 |
| 7 | C | saved 始终指向原第一行，交换后它在 a[1] |
| 8 | D | 每行从实际元素初始化，最大值分别 -2、-1 |
| 9 | A | 每列沿行相加：1+4、2+5、3+6 |
| 10 | B | 两条对角线各为 15，中心 5 去重：30-5 |
| 11 | C | 第一行两对、第二行一对，允许共享中间元素 |
| 12 | D | 空座分属不同行，不能跨行配对 |
| 13 | B | 浮点除法保留小数，其余先算 int 除法 |
| 14 | A | 转置交换维度，t[2][1] = a[1][2] |
| 15 | D | 第一项不等于目标便返回，后续没有机会检查 |
| 16 | C | 单元格为 null，对 null 调用 getName() |
| 17 | B | 统计符合条件的位置数，不是不同对象数 |
| 18 | A | R 行每行 C 项，共 RC 次常数操作 |

订正建议：

- 2、3：先写坐标序列，再解释输出；不能只背“交换两层循环”。
- 4—7：标出哪些变量是值，哪些是行引用；区分元素赋值与引用重绑定。
- 11、12：把计数对象写成坐标对，防止重叠规则和跨行关系混淆。
- 15、16：区分逻辑错误与运行时异常；修复时分别考虑返回时机与判空。

## FRQ 参考代码

各 public 类分别保存为同名 .java 文件。FRQ 4 需要 Student.java 与 StudentGrid.java 一起编译。这里实现方法，不含 main；运行时需另写驱动程序调用，不应直接把“没有输出”理解成方法错误。

### FRQ 1 参考实现

```java
public class GridStatistics {
    public static int[] rowMaxes(int[][] grid) {
        int[] result = new int[grid.length];
        for (int r = 0; r < grid.length; r++) {
            int max = grid[r][0];
            for (int c = 1; c < grid[r].length; c++) {
                if (grid[r][c] > max) {
                    max = grid[r][c];
                }
            }
            result[r] = max;
        }
        return result;
    }

    public static int[] columnSums(int[][] grid) {
        int[] result = new int[grid[0].length];
        for (int c = 0; c < grid[0].length; c++) {
            int sum = 0;
            for (int r = 0; r < grid.length; r++) {
                sum += grid[r][c];
            }
            result[c] = sum;
        }
        return result;
    }
}
```

| 部分 | 评分点 | 分值 |
| --- | --- | --- |
| (a) | 新建长度为行数的结果数组 | 1 |
| (a) | 每行重新初始化最大值，支持全负数 | 1 |
| (a) | 正确遍历并比较该行元素 | 1 |
| (a) | 将最大值存到对应行索引并返回 | 1 |
| (b) | 新建长度为列数的结果数组 | 1 |
| (b) | 正确遍历所有列 | 1 |
| (b) | 每列重置 sum 并沿各行求和 | 1 |
| (b) | 正确赋值并返回 | 1 |
| 整体 | 输入不变，单行/单列和非方阵均正确 | 1 |

总计 9 分。行优先遍历并累计 result[c] 的列求和实现也正确。两部分时间 O(RC)，结果空间分别 O(R)、O(C)。

### FRQ 2 参考实现

```java
public class SeatPlanner {
    public static int countHorizontalPairs(int[][] seats) {
        int count = 0;
        for (int r = 0; r < seats.length; r++) {
            for (int c = 0; c < seats[r].length - 1; c++) {
                if (seats[r][c] == seats[r][c + 1]) {
                    count++;
                }
            }
        }
        return count;
    }

    public static int[] firstAdjacentSeats(int[][] seats) {
        for (int r = 0; r < seats.length; r++) {
            for (int c = 0; c < seats[r].length - 1; c++) {
                if (seats[r][c] == 0 && seats[r][c + 1] == 0) {
                    return new int[] {r, c};
                }
            }
        }
        return null;
    }
}
```

两个方法时间 O(RC) 上界，临时空间 O(1)；(b) 找到后只创建长度 2 的坐标数组。零行或零列不需要读取 seats[0]。

### FRQ 3 参考实现

```java
public class GridTransforms {
    public static int[][] transpose(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        int[][] result = new int[cols][rows];
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                result[c][r] = grid[r][c];
            }
        }
        return result;
    }

    public static double[][] neighborAverages(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        double[][] result = new double[rows - 1][cols - 1];
        for (int r = 0; r < rows - 1; r++) {
            for (int c = 0; c < cols - 1; c++) {
                int sum = grid[r][c] + grid[r + 1][c]
                        + grid[r][c + 1] + grid[r + 1][c + 1];
                result[r][c] = sum / 4.0;
            }
        }
        return result;
    }
}
```

都为 O(RC) 时间，结果空间见 2.10；临时空间 O(1)。给定数值范围确保 int 四项和安全。

### FRQ 4 参考实现

Student 类使用题目给定代码，无须重复编写。StudentGrid.java：

```java
public class StudentGrid {
    public static int countPassing(Student[][] students, int passMark) {
        int count = 0;
        for (Student[] row : students) {
            for (Student student : row) {
                if (student != null && student.getScore() >= passMark) {
                    count++;
                }
            }
        }
        return count;
    }

    public static Student topStudent(Student[][] students) {
        Student best = null;
        for (Student[] row : students) {
            for (Student student : row) {
                if (student != null) {
                    if (best == null || student.getScore() > best.getScore()) {
                        best = student;
                    }
                }
            }
        }
        return best;
    }
}
```

best 初始为 null，表示还未找到学生。严格 `>` 保留并列时较早的对象；若改成 `>=` 会被后遇到的并列对象替换。

两方法时间 O(RC)，空间 O(1)。topStudent 返回引用不创建学生；返回对象的身份也是评分条件之一。
