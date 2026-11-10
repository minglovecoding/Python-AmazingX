## 📚APCSA 第二轮复习 05：类设计、对象协作与数组算法

## 1. 复习目标

### 1.1 本章过关目标

- 根据调用表确定字段、构造器、方法签名与状态变化。
- 分清实例字段、静态字段、参数和局部变量。
- 解释把对象放进列表、返回对象引用后，哪些地方能看到后续修改。
- 安全处理对象数组中的 null，不把“数组创建”误当成“所有对象都创建”。
- 明确空输入、并列结果、连续与不连续、原地修改与新建结果。
- 完成完整类设计、对象列表统计和数组连续段 FRQ。

##  2. 核心知识

### 2.1 一个贯穿本章的 Student 类

以下类用于后面的示例与 MCQ。姓名非 null；构造器及 setScore 的分数前提为 0—100。

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

    public void setScore(int newScore) {
        score = newScore;
    }

    public String getLetterGrade() {
        if (score >= 90) return "A";
        else if (score >= 80) return "B";
        else if (score >= 70) return "C";
        else if (score >= 60) return "D";
        else return "F";
    }

    public String getSummary() {
        return name + " (" + score + ")";
    }
}
```

| 部分 | 能解释的内容 |
| --- | --- |
| private 字段 | 通过方法维护对象状态；不是语法上所有字段都必须 private |
| 构造器 | 与类同名，没有返回类型；负责建立初始状态 |
| this.name | 当前对象字段；右侧 name 是参数 |
| getter | 返回信息；不应擅自修改状态 |
| setter | 更新字段；若题目给了合法输入前提，可直接使用 |
| getSummary | 返回字符串，不等于自动打印 |

没有任何构造器声明时才会获得编译器提供的默认构造器。有了 `Student(String,int)`，不能自动调用 `new Student()`。

`name = name;` 只给参数自赋值；`public void Student(...)` 是普通方法而不是构造器。

### 2.2 从调用表反推类的契约

| 需求 | 合适的签名例子 |
| --- | --- |
| 修改当前学生分数 | `public void setScore(int newScore)` |
| 读取当前学生分数 | `public int getScore()` |
| 计算两个给定分数的平均值 | `public static double average(int a,int b)` |
| 比较当前对象与另一个对象 | `public boolean higherThan(Student other)` |

静态方法没有当前对象 this；要用某个学生的实例方法，需要明确的 Student 引用。

private 是类的访问控制，不是“只有这个对象能访问”。Student 类的方法中可以访问另一个 Student 的 private 字段；另一个顶层类 Course 则应调用 public getter。

### 2.3 Course 保存的是 Student 引用

原稿 Course 使用 `ArrayList<Student>`，核心语义如下：

```java
Student alex = new Student("Alex", 92);
Course course = new Course("APCSA");
course.addStudent(alex);
alex.setScore(98);
```

列表里的引用与 alex 指向同一个对象，因此 course 后续读取到的分数也是 98。addStudent 没有自动复制 Student。

Course 的完整实现放在 FRQ 2 参考解。这里先读清其契约：

| 方法 | 本章约定 |
| --- | --- |
| addStudent | 添加给定引用，不复制对象 |
| getAverage | 空课程返回 0.0；否则返回浮点平均值 |
| getTopStudent | 空课程返回 null；并列返回最先加入的最高分对象 |
| countPassing | 返回分数至少 60 的学生数 |

```java
Student best = course.getTopStudent();
// best 非 null 时，best.setScore(...) 也会改变课程中该学生的状态。
```

返回对象引用不等于返回深拷贝。若调用者不应修改内部对象，需要另行设计接口或复制策略；本章按题面明确的共享引用契约实现。

**并列规则通过比较符体现：**从第一项开始，只有更高分时更新，则保留首个；用 >= 更新会改为保留最后一个。

### 2.4 数组：长度、默认值和引用

| 类型/容器 | 获取长度/大小 | 新创建元素的默认值 |
| --- | --- | --- |
| int[] | `.length` | 0 |
| double[] | `.length` | 0.0 |
| boolean[] | `.length` | false |
| String[]、Student[] | `.length` | null |
| String | `.length()` | 不适用数组默认值规则 |
| ArrayList | `.size()` | 新建空列表没有元素 |

```java
Student[] students = new Student[3];
students[0] = new Student("Alex", 90);
// students[1]、students[2] 仍为 null
```

若直接对以上数组的所有元素调用 getName，会遇到 NullPointerException。要么题目保证每个位置已初始化，要么检查 null。

```java
for (Student s : students) {
    if (s != null) {
        System.out.println(s.getName());
    }
}
```

```java
int[] a = {2,4,6};
int[] b = a;
b[0] = 9;
// a[0] 也是 9：两个引用指向同一个数组。
```

数组长度固定，但数组变量可以重新指向另一数组。`b = new int[3]` 不会让 a 自动改指向。

### 2.5 增强 for：重新赋值与修改对象不同

```java
for (int x : numbers) {
    x += 5; // 不写回原数组
}
```

```java
for (Student s : students) {
    if (s != null) {
        s.setScore(100); // 修改 s 指向的对象，能影响原数组里的学生
    }
}
```

```java
for (Student s : students) {
    s = new Student("New", 100); // 仅替换局部变量 s，不替换数组槽位
}
```

需要替换数组槽位时，用 `students[i] = ...`。

Java 始终按值传递。数组/对象实参传的是引用值副本；通过副本可修改同一对象，但给参数重新赋引用不会替换调用者变量。

### 2.6 数组统计与查找的前提

- 需要访问 arr[0] 的最大值/最小值算法，必须保证非空。
- 求平均值前明确空数组怎么办；整数除法要在运算之前引入 double。
- 查找第一个位置，可以找到就 return；找不到返回 -1。
- String 内容比较使用 equals，字典序比较使用 compareTo 的正负或零。
- 只读方法不能偷偷修改数组、学生分数或列表顺序。

```java
public static int firstIndex(int[] arr, int target) {
    for (int i = 0; i < arr.length; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}
```

### 2.7 连续段不是全局频数，也不是子序列

| 任务 | 比较规则 | 示例 |
| --- | --- | --- |
| 最长相同连续段 | 与前一项相同则延长 | `[2,2,1,2,3,3,3]` 的最长相同段是 3 的那段 |
| 全局出现最多 | 不要求相邻 | 原稿 mostFrequent 实际不是这个任务 |
| 最长严格递增连续段 | `arr[i] > arr[i-1]` 则延长 | `[1,2,2,3,4]` 返回 3 |
| 最长递增子序列 | 可跳过元素 | 不属于本章这道连续段题的要求 |

严格递增时，等于也会中断；长度按元素个数算，不按比较成功次数算。

每步维护 current 与 best：非空数组初始均为 1，延长则 current++，中断则 current=1；每轮更新 best 就能自然包含最后一段。

原稿返回“最长相同段的值”的方法宜改名为 `valueOfLongestEqualRun`，并明确并列保留最早段。若在段结束时才更新，一定要在循环后检查最后一段。

### 2.8 压缩连续段与评分状态

**压缩输出：**每段两个整数“值、次数”，不是仅保留值。

```text
[5,5,5,2,2,9] → [5,3,2,2,9,1]
```

先数段数确定结果数组长度，再扫描填充，写入索引每次增加 2。最后一段也要写入。返回新数组，原数组保持不变。

**评分系统：**total 与 streak 必须分开；错题/空题只把 streak 清零，不能把 total 清零。

```text
连续正确 1、2 题：每题 2 分
连续正确的第 3 题及以后：每题 3 分
错题或空题：0 分，并中断连续状态
```

每个长度为 k 的正确连续段贡献 `2*k + max(0,k-2)`。这个公式可用于手工核对，不要求替代循环代码。

## 4. MCQ 训练（18 题）

每题只有一个正确选项，各题独立。用到 Student 时采用 2.1 的完整实现；用到 Course 时采用 FRQ 2 的题面契约与参考实现。除明确出现 null 外，对象实参非 null。

### MCQ 1｜构造器匹配

```java
public class Book {
    public Book(String title, int pages) { }
    public Book(String title) { }
}
```

另一个类中，哪句能编译？

A. `Book b = new Book();`  
B. `Book b = new Book(100, "AP");`  
C. `Book b = new Book("AP", 100);`  
D. `Book b = new Book("AP", 100.0);`

### MCQ 2｜参数遮蔽

```java
public class Wallet {
    private int money;
    public Wallet(int money) { money = money; }
    public int getMoney() { return money; }
}
```

`new Wallet(50).getMoney()` 的值是？

A. `0`  
B. `50`  
C. `null`  
D. 编译错误

### MCQ 3｜同类对象的 private 字段

在 Student 类内增加 `public boolean higherThan(Student other)`，哪一个方法体既合法又实现“当前学生分数更高时返回 true”？

A. `return score > Student.score;`  
B. `return score > other.score;`  
C. `return this > other;`  
D. `return score > other.getName();`

### MCQ 4｜共享引用

```java
Student a = new Student("Ada", 80);
Student b = a;
b.setScore(95);
System.out.println(a.getScore() + " " + b.getScore());
```

A. `80 95`  
B. `95 80`  
C. `80 80`  
D. `95 95`

### MCQ 5｜增强 for 与对象修改

```java
Student[] group = {
    new Student("A", 5), new Student("B", 7)
};
for (Student s : group) {
    s.setScore(s.getScore() + 10);
    s = new Student("New", 0);
}
System.out.println(group[0].getScore() + " " + group[1].getScore());
```

A. `0 0`  
B. `15 17`  
C. `5 7`  
D. `15 7`

### MCQ 6｜对象数组初始化

```java
Student[] group = new Student[2];
group[0] = new Student("A", 90);
System.out.println(group[1].getScore());
```

A. 输出 `0`  
B. 输出 `90`  
C. 执行时抛 NullPointerException  
D. 编译错误

### MCQ 7｜平均值的转换位置

```java
int[] values = {3, 4, 6};
int sum = 0;
for (int x : values) { sum += x; }
double average = sum / values.length;
System.out.println(average);
```

A. `4.0`  
B. `4.333333333333333`  
C. `13.0`  
D. 编译错误

### MCQ 8｜数组参数重新赋值

```java
public static void change(int[] arr) {
    arr[0] = 8;  //真的能修改
    arr = new int[] {1, 2};  //修改局部变量
}
```

在同一类 main 中执行：

```java
int[] values = {3, 4};
change(values);
System.out.println(values[0] + " " + values[1]);
```

A. `1 2`  
B. `3 4`  
C. `8 4`  
D. `8 2`

### MCQ 9｜数组赋值不是复制内容

```java
int[] values = {1, 2};
int[] other = values;
other[1] = 9;
System.out.println(values[1]);
```

A. `1`  
B. `2`  
C. `0`  
D. `9`

### MCQ 10｜并列最高分

```java
Course c = new Course("CSA");
c.addStudent(new Student("Alex", 92));
c.addStudent(new Student("Mia", 92));
System.out.println(c.getTopStudent().getName());
```

按本章“并列保留最先加入者”的契约，输出是？

A. `Mia`  
B. `Alex`  
C. `null`  
D. 编译错误

### MCQ 11｜static 方法访问实例

在 Student 类内增加一个静态方法，哪一项能编译并返回所给学生的分数？

A. `public static int read(Student s) { return s.getScore(); }`  
B. `public static int read(Student s) { return Student.getScore(); }`  
C. `public static int read(Student s) { return this.getScore(); }`  
D. `public static int read(Student s) { return score; }`

### MCQ 12｜遗漏最后一段

```java
int[] arr = {1, 0, 1, 2, 3};
int current = 1;
int best = 1;
for (int i = 1; i < arr.length; i++) {
    if (arr[i] > arr[i - 1]) {
        current++;
    } else {
        if (current > best) { best = current; }
        current = 1;
    }
}
System.out.println(best);
```

实际输出什么？

A. `4`  
B. `1`  
C. `3`  
D. `5`

### MCQ 13｜连续段与全局频数

数组为 `{2,2,1,2,1,2,3,3,3}`。方法返回“最长相同连续段对应的值”，而不是全局出现最多的值。它应该返回？

A. `3`  
B. `2`  
C. `1`  
D. `9`

### MCQ 14｜压缩结果长度

数组 `{4,4,2,2,4}` 按“每段保存值、次数”压缩，新数组长度应为？

A. `3`  
B. `4`  
C. `6`  
D. `10`

### MCQ 15｜严格递增连续段

数组 `{1,2,2,3,4}` 的最长严格递增连续段长度为？

A. `5`  
B. `4`  
C. `2`  
D. `3`

### MCQ 16｜连续正确奖励

采用 FRQ 4 的规则：答对每题 2 分，同一连续正确段从第 3 题起每题再加 1 分，`"?"` 为未答。

```java
String[] key = {"A","A","A","A","A","A","A"};
String[] answer = {"A","A","A","?","A","A","A"};
```

应得总分是？

A. `12`  
B. `15`  
C. `14`  
D. `16`

### MCQ 17｜实例状态与共享计数

```java
public class Badge {
    private static int count = 0;
    private int id;
    public Badge() {
        id = count;
        count++;
    }
    public int getId() { return id; }
    public static int getCount() { return count; }
}
```

假设此前未创建 Badge 对象，在另一个类中执行：

```java
Badge a = new Badge();
Badge b = new Badge();
System.out.println(a.getId() + " " + b.getId() + " " + Badge.getCount());
```

A. `1 2 2`  
B. `0 0 2`  
C. `0 1 1`  
D. `0 1 2`

### MCQ 18｜数组元素默认值

```java
int[] counts = new int[1];
boolean[] flags = new boolean[1];
String[] names = new String[1];
System.out.println(counts[0] + " " + flags[0] + " " + (names[0] == null));
```

A. `0 false false`  
B. `0 false true`  
C. `0 true true`  
D. 编译错误，因为数组元素未初始化

## 5. FRQ 训练（4 题）

### FRQ 1｜GymMember：完整类设计

写完整 GymMember 类，包含四个私有实例字段：String name、int age、int totalVisits、boolean vip。

构造器：

```java
public GymMember(String name, int age, boolean vip)
public GymMember(String name, int age)
```

完整构造器保存姓名、年龄、VIP 状态，到访数为 0；两参构造器建立非 VIP 会员，到访数同为 0。姓名非 null、年龄非负，测试中累计访问不超过 1000000。

方法：

- `void addVisit()`：只将 totalVisits 加 1，不自动升级。
- `void promoteToVIP()`：访问至少 50 次时把 vip 设为 true；否则保持原状态，不把已有 VIP 降级。
- `String getSummary()`：精确返回下例格式，逗号后一个空格。
- `int compareTo(GymMember other)`：当前对象访问次数更多返回正数，相同返回 0，较少返回负数。other 非 null。

```text
Name: Alice, Age: 27, VIP: true, Visits: 60
```

| 调用情形 | 结果要求 |
| --- | --- |
| 新建非 VIP，49 次访问后调用 promoteToVIP | 仍为 false |
| 非 VIP 达 50 次，但尚未调用 promoteToVIP | 仍为 false |
| 达 50 次后调用 promoteToVIP | 变为 true |
| 新建 VIP，0 次访问后调用 promoteToVIP | 仍为 true |
| 两个对象分别 60 次与 1 次访问 | compareTo 的结果为正；不要求一定是 59 |

这里 compareTo 是题面指定的普通方法，不要求实现 Comparable，也不自动提供排序功能。

### FRQ 2｜Course：对象列表协作

使用 2.1 已实现的 Student 类，写完整 Course 类：

- 私有字段 String courseName 和 ArrayList<Student> students。
- `Course(String courseName)`：保存名字，创建一个新的空列表。
- `void addStudent(Student s)`：加入所给引用，不复制学生对象；s 非 null。每次加入视为一个条目，不要求按姓名去重；条目数不超过 10000。
- `double getAverage()`：空列表返回 0.0，否则返回所有条目的分数平均值。
- `Student getTopStudent()`：空列表返回 null；否则返回最早加入的最高分对象引用。
- `int countPassing()`：统计分数至少 60 的条目数。

除 addStudent 外，这些方法不能修改列表、排序或改变任何学生分数。学生分数始终在 0—100。

```java
Student alex = new Student("Alex", 92);
Student mia = new Student("Mia", 85);
Student james = new Student("James", 73);
Course c = new Course("AP CSA");
c.addStudent(alex);
c.addStudent(mia);
c.addStudent(james);
```

此时平均分为 `250.0/3`，最高分对象是 alex。执行 `james.setScore(95)` 后，最高分对象应变为 james。若通过 `c.getTopStudent().setScore(...)` 修改学生，也会反映到对应对象上。

### FRQ 3｜RunTools：连续段与新数组

只能使用数组、循环与基本运算；不得用 ArrayList、Stream 或排序。输入数组保持不变，两问的输入长度均不超过 10000。

**(a)** longestIncreasingRunLength：返回最长严格递增连续段的长度。前提：arr.length>=1；单元素、全相等、全递减都返回 1。

```java
public static int longestIncreasingRunLength(int[] arr)
```

**(b)** compressRuns：将每段连续相等元素编码为“值、次数”，返回长度恰好为段数两倍的新数组。本稿允许空数组，此时返回长度为 0 的新数组。

```java
public static int[] compressRuns(int[] arr)
```

| 输入 | longestIncreasingRunLength | compressRuns |
| --- | --- | --- |
| `[1,2,3,2,5,7,8]` | 4 | `[1,1,2,1,3,1,2,1,5,1,7,1,8,1]` |
| `[5,5,5,2,2,9]` | 2 | `[5,3,2,2,9,1]` |
| `[7]` | 1 | `[7,1]` |
| `[5,4,3]` | 1 | `[5,1,4,1,3,1]` |
| `[]` | 不在 (a) 前提内，不调用 | `[]` |

这两问保留并整理原稿的两道数组专项，不是往年真题。

### FRQ 4｜ExamScorer：连续正确奖励

原稿使用 char[]；本稿核心题改用 String[]，训练对象数组中的内容比较。key 与 answer 长度相同，范围 1—10000，所有元素非 null。key 的每项为 `"A"`、`"B"`、`"C"`、`"D"` 之一；answer 还可以为 `"?"`，表示未答。

规则：

- 正确答案得 2 分；错题、未答得 0 分。
- 每段连续正确答案，从第 3 题开始，每题额外加 1 分。
- 错题或未答都会中断连续状态。

```java
public static int scoreExam(String[] key, String[] answer)
```

返回总分，不修改任一数组或元素。必须按 String 内容判断正确与否。

| 正确/错误状态（T=对，F=错或未答） | 总分 |
| --- | --- |
| T | 2 |
| TTT | 7 |
| TTTT | 10 |
| TTTFTTT | 14 |
| FFFF | 0 |

若自行保留原稿 char[] 版本，单个 char 可用 == 比较；不要把这个规则套到 String[]。

## 6. 官方样题与历年真题迁移

### 6.1 官方 MCQ 样题

来源：[CED，Effective Fall 2025](https://apcentral.collegeboard.org/media/pdf/ap-computer-science-a-course-and-exam-description.pdf)。这些是官方样题，不是某年实考试卷，按 PDF 原题完成。

| 样题号 | PDF 页码（从 1 开始） | 本章训练点 |
| --- | --- | --- |
| 9 | 160，印刷页 153 | 字段与访问器的类设计 |
| 11 | 161，印刷页 154 | 持有其他对象并调用其 public 方法 |
| 12 | 162，印刷页 155 | 比较两个对象的属性 |
| 14 | 163，印刷页 156 | 非空数组最大值的初始状态 |


第 11 题 C；第 12 题 C；第 14 题 A。第 9 题包含设计图，需在原 PDF 中查看图形选项；这里不凭纯文本抽取猜图形答案。

### 6.2 类设计真题：2024 Q2 Scoreboard

- [官方题目](https://apcentral.collegeboard.org/media/pdf/ap24-frq-comp-sci-a.pdf#page=8)：PDF 第 8—9 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap24-sg-computer-science-a.pdf)：定位 Q2。

适合完成 GymMember 后独立训练：从调用表识别需要持久保存的状态，区分修改方法与只读返回方法。重点检查连续调用、状态切换及两个对象互不影响。

建议 20—25 分钟完成并按官方评分，不能套用本稿原创题的评分表。

### 6.3 对象协作真题：2025 Q3 Round

- [官方题目](https://apcentral.collegeboard.org/media/pdf/ap25-frq-computer-science-a.pdf#page=11)：PDF 第 11—15 页。
- [官方评分细则](https://apcentral.collegeboard.org/media/pdf/ap25-sg-computer-science-a.pdf)：定位 Q3。

将 String[] 中的信息转为对象集合，再建立新对象的配对结果，与 Student/Course 的对象引用协作直接相连。需要已学 ArrayList 基础，可先做构造器部分，再做配对方法。

检查对象创建参数、名次起点、奇偶数量和原列表保持不变的要求。按原题阅读，不把本章 Course 或后面的 TaskScheduler 称为这道题原文。

## 7. MCQ 答案与解析

### 7.1 答案速查

| 题号 | 答案 | 主要错因 |
| --- | --- | --- |
| 1 | C | 构造器参数类型与顺序 |
| 2 | A | 参数遮蔽字段 |
| 3 | B | private 以类为访问边界 |
| 4 | D | 共享引用修改同一个对象 |
| 5 | B | 对象字段修改与循环变量重赋值不同 |
| 6 | C | 创建引用数组未创建所有 Student |
| 7 | A | 先整数除法再存 double |
| 8 | C | 修改数组内容与参数重赋值不同 |
| 9 | D | 数组赋引用不复制元素 |
| 10 | B | 最高分并列保留首次 |
| 11 | A | 静态方法需要明确对象引用 |
| 12 | B | 最后一段未更新 best |
| 13 | A | 连续段长度不是总频数 |
| 14 | C | 每段输出两个整数 |
| 15 | D | 相等会中断严格递增 |
| 16 | C | 未答题会清零连续状态 |
| 17 | D | 实例 id 与共享 count 不同 |
| 18 | B | 数组元素有对应类型默认值 |

### 7.2 逐题解析

1. C 匹配 (String,int)。A 无匹配无参构造器；B 顺序相反；D 的 double 不能自动窄化为 int。
2. 构造器中的 money 是参数，给自己赋值不改变字段；字段保留默认值 0。
3. 在 Student 类内部可以读取另一个 Student 的 private 字段。A 把实例字段当静态字段；C 不能对对象引用用 >；D 将 int 与 String 比较。
4. a、b 指向同一个 Student，setScore 后两者都读取到 95。
5. setter 改变原学生对象，得分变为 15、17；给 s 重新赋引用不会替换 group 的数组槽位。
6. group[1] 默认 null；调用 getScore 时抛 NullPointerException。数组创建本身合法。
7. sum=13，13/3 先算出 int 值 4，再存为 4.0。要得到小数应在除法前转 double。
8. arr[0]=8 修改原数组；后续 arr 重新赋值只影响局部参数。调用者的数组仍为 [8,4]。
9. other 与 values 指向同一个数组，因此 values[1] 变为 9。
10. 本章契约保留最先加入的并列对象。比较用 > 而不是 >= 时返回 Alex。
11. A 使用给定对象调用实例方法，合法。静态方法中没有 this，也不能直接访问当前实例字段或以类名调用实例方法。
12. 下降处只更新了一次 best，仍为 1；后面的 [0,1,2,3] 延长到 4，但循环后未检查，因此实际输出 1。
13. 2 全局出现 4 次，但最长连续段只有 2；3 连续出现 3 次，所以返回 3。
14. 段为 [4,4]、[2,2]、[4]，三段各存值与次数，长度 6。
15. 第二个 2 会中断 [1,2]；随后 [2,3,4] 长度为 3。
16. 两段 TTT 各得 2+2+3=7 分，未答使连续状态中断，总计 14。
17. 第一个对象先取 id=0，再将 count 增为 1；第二个取 id=1，再增为 2。两个 id 不是同一份字段。
18. 数组对象分配后，元素依类型初始化：int 为 0、boolean 为 false、String 引用为 null。局部数组变量本身也已经赋值。

## 8. FRQ 参考解与课堂评分

### FRQ 1 参考解：GymMember

```java
public class GymMember {
    private String name;
    private int age;
    private int totalVisits;
    private boolean vip;

    public GymMember(String name, int age, boolean vip) {
        this.name = name;
        this.age = age;
        this.vip = vip;
        totalVisits = 0;
    }

    public GymMember(String name, int age) {
        this.name = name;
        this.age = age;
        vip = false;
        totalVisits = 0;
    }

    public void addVisit() {
        totalVisits++;
    }

    public void promoteToVIP() {
        if (totalVisits >= 50) {
            vip = true;
        }
    }

    public String getSummary() {
        return "Name: " + name + ", Age: " + age
               + ", VIP: " + vip + ", Visits: " + totalVisits;
    }

    public int compareTo(GymMember other) {
        return totalVisits - other.totalVisits;
    }
}
```

### FRQ 2 参考解：Course

Student 使用 2.1 的完整类；分别保存为 Student.java、Course.java。

```java
import java.util.ArrayList;

public class Course {
    private String courseName;
    private ArrayList<Student> students;

    public Course(String courseName) {
        this.courseName = courseName;
        students = new ArrayList<Student>();
    }

    public void addStudent(Student s) {
        students.add(s);
    }

    public double getAverage() {
        if (students.size() == 0) {
            return 0.0;
        }
        int sum = 0;
        for (Student s : students) {
            sum += s.getScore();
        }
        return (double) sum / students.size();
    }

    public Student getTopStudent() {
        if (students.size() == 0) {
            return null;
        }
        Student best = students.get(0);
        for (Student s : students) {
            if (s.getScore() > best.getScore()) {
                best = s;
            }
        }
        return best;
    }

    public int countPassing() {
        int count = 0;
        for (Student s : students) {
            if (s.getScore() >= 60) {
                count++;
            }
        }
        return count;
    }
}
```

### FRQ 3 参考解：RunTools

```java
public class RunTools {
    public static int longestIncreasingRunLength(int[] arr) {
        int current = 1;
        int best = 1;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > arr[i - 1]) {
                current++;
            } else {
                current = 1;
            }
            if (current > best) {
                best = current;
            }
        }
        return best;
    }

    public static int[] compressRuns(int[] arr) {
        if (arr.length == 0) {
            return new int[0];
        }
        int runs = 1;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] != arr[i - 1]) {
                runs++;
            }
        }
        int[] result = new int[runs * 2];
        int write = 0;
        int value = arr[0];
        int count = 1;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] == value) {
                count++;
            } else {
                result[write] = value;
                result[write + 1] = count;
                write += 2;
                value = arr[i];
                count = 1;
            }
        }
        result[write] = value;
        result[write + 1] = count;
        return result;
    }

    // 补全原稿“最长相同段的值”方法，不计入本题两问分数。
    // Precondition: arr.length >= 1; ties keep the earliest run.
    public static int valueOfLongestEqualRun(int[] arr) {
        int bestValue = arr[0];
        int bestCount = 1;
        int currentCount = 1;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] == arr[i - 1]) {
                currentCount++;
            } else {
                currentCount = 1;
            }
            if (currentCount > bestCount) {
                bestCount = currentCount;
                bestValue = arr[i];
            }
        }
        return bestValue;
    }
}
```

### FRQ 4 参考解：ExamScorer

```java
public class ExamScorer {
    public static int scoreExam(String[] key, String[] answer) {
        int total = 0;
        int streak = 0;
        for (int i = 0; i < key.length; i++) {
            if (answer[i].equals(key[i])) {
                streak++;
                total += 2;
                if (streak >= 3) {
                    total++;
                }
            } else {
                streak = 0;
            }
        }
        return total;
    }
}
```

***

## 附录 A：Task/TaskScheduler 选做案例

Task 表示任务：标题、优先级、是否完成。优先级越大越优先。TaskScheduler 选择未完成任务中的最高优先级对象；允许数组中有 null，若无候选返回 null，并列保留最早位置。不修改数组或任务。

```java
public class Task {
    private String title;
    private int priority;
    private boolean completed;

    public Task(String title, int priority) {
        this.title = title;
        this.priority = priority;
        completed = false;
    }

    public String getTitle() { return title; }
    public int getPriority() { return priority; }
    public boolean isCompleted() { return completed; }
    public void markCompleted() { completed = true; }
}
```

```java
public class TaskScheduler {
    public static Task selectNext(Task[] tasks) {
        Task best = null;
        for (Task task : tasks) {
            if (task != null && !task.isCompleted()) {
                if (best == null || task.getPriority() > best.getPriority()) {
                    best = task;
                }
            }
        }
        return best;
    }
}
```

示例：任务 A、B 的优先级为 3、5，则先选择 B；B 调用 markCompleted 后再选择，得到 A。这里返回的是原任务引用，并未自动将其标记完成。

