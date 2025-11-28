## 📚 Writing Classes

Java **定义自己的类、创建对象、编写方法、封装数据**。

### ✅ **Class 1: Student.java**

```java
public class Student {
    // Instance variables
    private String name;
    private int score;

    // Constructor
    public Student(String name, int score) {
        this.name = name;
        this.score = score;
    }

    // Accessors (getters)
    public String getName() {
        return name;
    }

    public int getScore() {
        return score;
    }

    // Mutators (setters)
    public void setScore(int newScore) {
        score = newScore;
    }

    // Method: return letter grade
    public String getLetterGrade() {
        if (score >= 90) return "A";
        else if (score >= 80) return "B";
        else if (score >= 70) return "C";
        else if (score >= 60) return "D";
        else return "F";
    }

    // toString: for printing
    public String toString() {
        return name + " (" + score + ")";
    }
}
```

### ✅ **Class 2: Course.java**

课程类中包含**多个 Student 对象** —— AP 考点非常重要。

```java
import java.util.ArrayList;

public class Course {
    private String courseName;
    private ArrayList<Student> students;

    // Constructor
    public Course(String courseName) {
        this.courseName = courseName;
        this.students = new ArrayList<Student>();
    }

    // Add a student
    public void addStudent(Student s) {
        students.add(s);
    }

    // Get average score
    public double getAverage() {
        if (students.size() == 0) return 0;

        int sum = 0;
        for (Student s : students) {
            sum += s.getScore();
        }
        return (double) sum / students.size();
    }

    // Get the highest scoring student
    public Student getTopStudent() {
        if (students.size() == 0) return null;

        Student best = students.get(0);
        for (Student s : students) {
            if (s.getScore() > best.getScore()) {
                best = s;
            }
        }
        return best;
    }

    // Print all students
    public void printStudents() {
        for (Student s : students) {
            System.out.println(s);
        }
    }
}
```

### 🎯 **Tester: CourseTester.java**

```java
public class CourseTester {
    public static void main(String[] args) {
        // Create Students
        Student a = new Student("Alex", 92);
        Student b = new Student("Mia", 85);
        Student c = new Student("James", 73);

        // Create Course and add students
        Course apcs = new Course("AP Computer Science A");
        apcs.addStudent(a);
        apcs.addStudent(b);
        apcs.addStudent(c);

        // Print all students
        apcs.printStudents();

        // Test methods
        System.out.println("Average: " + apcs.getAverage());
        System.out.println("Top student: " + apcs.getTopStudent());

        // Update score
        c.setScore(95);  
        System.out.println("New top student: " + apcs.getTopStudent());
    }
}
```

### 🧱 1. **类（Class）与对象（Object）的概念**

- 类是蓝图（blueprint）

- 对象是类创建出来的实例（instance）

- 如何实例化对象：

  ```java
  Student s = new Student("Alex", 16);
  ```

### 🧩 2. **实例变量（Instance Variables）**

- 类的“属性”
- 必须写在类里、方法外
- 必须加 `private`（AP 考试高度重视封装）

```java
private String name;
private int score;
```

### 🛠️ 3. **构造方法（Constructors）**

- 用来初始化对象
- 与类同名
- 没有返回值类型（连 void 都没有）

示例：

```java
public Student(String n, int s) {
    name = n;
    score = s;
}
```

### 🔒 4. **封装（Encapsulation）**

- 实例变量 `private`
- 提供 `public` getter / setter

```java
public String getName() { return name; }
public void setScore(int s) { score = s; }
```

### 📞 5. **方法（Methods）**

包括：

### ✔ 实例方法（non-static methods）

用于操作对象的数据

### ✔ 参数与返回值

- void 方法
- 有返回值的方法

```java
public int getScore() {
    return score;
}
```

### 🔁 6. **this 关键字**

- 区分实例变量与局部变量
- 在构造器中常用

```java
this.name = name;
```

### 🔤 7. **String 与其他对象作为实例变量**

- String 是对象
- AP 考试大量使用
- 涉及 length()、substring() 等

### 🧱 8. **编写类之间的交互（Working with Classes）**

会涉及：

- 一个类有另一个类的对象作为成员变量
- 从 main 或 tester 类调用你的类

示例：

```java
Student s = new Student("James", 95);
System.out.println(s.getScore());
```

### 📝 **健身房会员系统（GymMember）**

某健身房需要一个程序来管理会员的信息。需要编写一个名为 **GymMember** 的类，用来保存和管理会员资料。

### **📌 Part A — 类的设计（Class Definition）**

请编写一个名为 `GymMember` 的类，包含下面内容：

### **1. 实例变量（private）**

- `String name` — 会员名字
- `int age` — 会员年龄
- `int totalVisits` — 累计到访次数
- `boolean vip` — 是否为 VIP 会员

### **📌 Part B — 构造方法（Constructors）**

编写两个构造器：

### **(1) 完整构造器：**

```java
public GymMember(String name, int age, boolean vip)
```

要求：

- 初始化 `name`、`age`、`vip`
- `totalVisits` 初始为 0

### **(2) 非 VIP 构造器：**

```java
public GymMember(String name, int age)
```

要求：

- `vip` 默认为 `false`
- `totalVisits` 初始为 0

### **📌 Part C — 方法（Methods）**

请实现以下方法：

### **1. addVisit()**

```java
public void addVisit()
```

每当会员到访一次：

- `totalVisits` 加 1

### **2. promoteToVIP()**

```java
public void promoteToVIP()
```

如果会员累计到访次数 ≥ 50 次，将其升级为 VIP。

### **3. getSummary()**

```java
public String getSummary()
```

返回会员概要信息（格式如下）：

```java
Name: Alice, Age: 27, VIP: true, Visits: 73
```

### **📌 Part D — 比较方法（AP 常考）**

### **compareTo(GymMember other)**

比较两个会员谁访问次数更多：

```java
public int compareTo(GymMember other)
```

返回：

- 正数 → 当前对象访问次数更多
- 0 → 相同
- 负数 → 当前对象访问次数更少

***

### ✔️ **你需要写的内容**

你要写完整的 `GymMember` 类，包含：

- 4 个实例变量
- 2 个构造器
- 3 个普通方法
- compareTo 方法

结构示例如下（你要把内容补全）：

```c++
public class GymMember {
    // instance variables
    private String name;
    private int age;
    private int totalVisits;
    private boolean vip;

    // constructors
    // ...
    
    // methods
    // ...
}
```

### 🧪 **测试代码（你写完可以用来验错）**

```java
public class TestMember {
    public static void main(String[] args) {
        GymMember g1 = new GymMember("Alice", 27, false);
        GymMember g2 = new GymMember("Bob", 30);

        for (int i = 0; i < 60; i++) {
            g1.addVisit();
        }

        g1.promoteToVIP();
        g2.addVisit();

        System.out.println(g1.getSummary());
        System.out.println(g2.getSummary());
        System.out.println(g1.compareTo(g2));
    }
}
```

运行结果应类似：

```java
Name: Alice, Age: 27, VIP: true, Visits: 60
Name: Bob, Age: 30, VIP: false, Visits: 1
59
```

Answer：

```java
public class GymMember {

    // ---------------------
    // Instance Variables
    // ---------------------
    private String name;
    private int age;
    private int totalVisits;
    private boolean vip;

    // ---------------------
    // Constructors
    // ---------------------

    // Full constructor
    public GymMember(String name, int age, boolean vip) {
        this.name = name;
        this.age = age;
        this.vip = vip;
        this.totalVisits = 0;
    }

    // Non-VIP constructor
    public GymMember(String name, int age) {
        this.name = name;
        this.age = age;
        this.vip = false;
        this.totalVisits = 0;
    }

    // ---------------------
    // Methods
    // ---------------------

    // 1. Add one visit
    public void addVisit() {
        totalVisits++;
    }

    // 2. Promote to VIP if visits >= 50
    public void promoteToVIP() {
        if (totalVisits >= 50) {
            vip = true;
        }
    }

    // 3. Return summary string
    public String getSummary() {
        return "Name: " + name + ", Age: " + age +
               ", VIP: " + vip + ", Visits: " + totalVisits;
    }

    // ---------------------
    // compareTo
    // ---------------------
    public int compareTo(GymMember other) {
        return this.totalVisits - other.totalVisits;
    }
}
```

> ### 🧠 题目：Task 与 TaskScheduler（任务与任务调度）
>
> 你要为一个简单的 **待办任务系统** 编写类。
>  系统有两部分：
>
> 1. 一个表示单个任务的类：`Task`
> 2. 一个帮助管理任务数组的类：`TaskScheduler`

***

### 📚 APCSA Arrays

### 1️⃣ 什么是数组（Array）？

- **固定长度（fixed length）**
- **保存同一种类型的数据**
- **通过 index 访问，index 从 0 开始**

```java
int[] nums = {3, 5, 7, 9};
```

### 2️⃣ 数组的声明与创建

### ✔ 声明 + 创建 (典型 AP 考法)

```java
int[] arr = new int[5];  
```

- 默认值：`0`
- 长度固定：`arr.length == 5`

### ✔ 声明 + 初始化

```java
String[] names = {"Alex", "Ben", "Lina"};
```

### ✔ 分步写法

```java
double[] scores;
scores = new double[3];
```

### 3️⃣ 数组长度（length 属性）

数组的长度使用 `.length`，不是方法，没有括号：

```java
int len = arr.length;
```

**AP 必考易错点：**
 不能写：`arr.length()` ❌

### 4️⃣ 遍历数组（AP 高频考点）

### ✔ 普通 for 循环（index）

AP 最常考写法：

```java
for (int i = 0; i < arr.length; i++) {
    System.out.println(arr[i]);
}
```

- 从 0 到 length - 1
- 不能越界：`IndexOutOfBoundsException`

### ✔ 增强 for 循环（for-each）

AP 常考：

```Java
for (int value : arr) {
    System.out.println(value);
}
```

⚠️ 注意：

- 不能通过增强 for 循环改变数组元素（修改不会生效）

错误示例：

```java
for (int x : arr) {
    x = 10;  // 不会真的修改 arr
}
```

### 5️⃣ Arrays 的常见操作（AP 必考）

以下内容 **每年必考**：

### ✔ 最大值/最小值

```java
int max = arr[0];
for (int i = 1; i < arr.length; i++) {
    if (arr[i] > max)
        max = arr[i];
}
```

### ✔ 求和 + 平均值

```java
int sum = 0;
for (int n : arr) sum += n;
double avg = (double) sum / arr.length;
```

### ✔ 查找（Search）

### 遍历查找一个值

```java
boolean found = false;
for (int i = 0; i < arr.length; i++) {
    if (arr[i] == target) found = true;
}
```

### 查找 index（AP 常考）

```java
int index = -1;
for (int i = 0; i < arr.length; i++) {
    if (arr[i] == target) {
        index = i;
        break;
    }
}
```

### 6️⃣ 修改数组元素

普通 for：

```java
for (int i = 0; i < arr.length; i++) {
    arr[i] += 5;
}
```

### 7️⃣ Arrays 与 Methods（AP 重心）

一个方法接收数组作为参数：

```java
public static int sum(int[] arr) {
    int total = 0;
    for (int n : arr) total += n;
    return total;
}
```

调用：

```java
int[] nums = {2, 4, 6};
System.out.println(sum(nums));   // 12
```

### 8️⃣ Arrays of Objects（AP 强考点）

数组不仅可以存数字，也可以存对象：

```java
Student[] list = new Student[3];
list[0] = new Student("Alex", 90);
```

遍历对象数组：

```java
for (Student s : list) {
    System.out.println(s.getName());
}
```

### 9️⃣ String array（AP 常考）

```java
String[] words = {"apple", "cat", "banana"};
```

排序前找最小字母：

```java
String min = words[0];
for (String w : words) {
    if (w.compareTo(min) < 0)
        min = w;
}
```

### 🔟 常见错误（AP 考试陷阱整理）

❌ 越界访问（最容易丢分）

```java
arr[arr.length]   // 错
```

❌ length 写成 length()

```java
arr.length()      // 错
```

❌ for-each 修改元素失败

```java
for (int x : arr) x = 100; // arr 不变
```

❌ 忘记初始化对象数组元素

***

### ⭐ AP CSA 风格 Exam 例题

已知数组 int[] nums，写一个方法返回数组中 连续出现最多次数的数字。

例如：nums = {2, 2, 2, 3, 3}
 返回 → 2

```java
public int mostFrequent(int[] arr) {
    int bestNum = arr[0];
    int bestCount = 1;

    int currentNum = arr[0];
    int currentCount = 1;

    for (int i = 1; i < arr.length; i++) {
        if (arr[i] == currentNum) {
            currentCount++;
        } else {
            if (currentCount > bestCount) {
                bestCount = currentCount;
                bestNum = currentNum;
            }
            currentNum = arr[i];
            currentCount = 1;
        }
    }

    // final check
    if (currentCount > bestCount) {
        bestCount = currentCount;
        bestNum = currentNum;
    }

    return bestNum;
}
```

### 🧪 FRQ 1：Longest Increasing Run（最长递增连续段）

### 题干（中文版）

给定一个 `int[] arr`，元素个数 ≥ 1。
 “递增连续段”指的是在数组中**相邻元素连续**，并且满足：

```java
arr[i] < arr[i+1] < arr[i+2] < ...
```

请写一个方法：

```java
public static int longestIncreasingRunLength(int[] arr)
```

返回数组中 **最长递增连续段的长度**。
 如果所有元素都不递增（比如全是相等或递减），最长递增连续段的长度就是 1。

例子：

- `{1, 2, 3, 2, 5, 7, 8}` → 最长递增连续段是 `2, 5, 7, 8`，长度为 4
- `{5, 4, 3}` → 每个单独算一段，返回 1

### ✅ 参考答案

```java
public static int longestIncreasingRunLength(int[] arr) {
    if (arr.length == 0) {
        return 0;  // 保险写法，虽然题目说长度 ≥ 1
    }

    int bestLen = 1;     // 目前为止找到的最长长度
    int currentLen = 1;  // 当前这段递增连续段的长度

    for (int i = 1; i < arr.length; i++) {
        if (arr[i] > arr[i - 1]) {
            // 递增，当前段继续延长
            currentLen++;
        } else {
            // 递增被打断了，更新 bestLen
            if (currentLen > bestLen) {
                bestLen = currentLen;
            }
            currentLen = 1;  // 重新从当前位置开始新的一段
        }
    }

    // 最后一段也要和 bestLen 比较
    if (currentLen > bestLen) {
        bestLen = currentLen;
    }

    return bestLen;
}
```

### 🧪 FRQ 2：Compress Runs（压缩连续段）

### 题干

给定 `int[] arr`，你需要把数组中**相同数字的连续段**压缩成两两成对的形式，
 例如：

原数组：

```java
[5, 5, 5, 2, 2, 9]
```

压缩结果为新数组：

```java
[5, 3, 2, 2, 9, 1]
```

含义是：

- `5` 连续出现了 3 次
- `2` 连续出现了 2 次
- `9` 连续出现了 1 次

请写一个方法：

```java
public static int[] compressRuns(int[] arr)
```

返回**新的数组**，其中格式为 `[值1, 次数1, 值2, 次数2, ...]`。

你可以假设 `arr.length >= 1`。

### ✅ 参考答案

```java
public static int[] compressRuns(int[] arr) {
    // 第一步：先数一数有多少“连续段”，好提前知道新数组长度
    int runCount = 1;  // 至少有一段
    for (int i = 1; i < arr.length; i++) {
        if (arr[i] != arr[i - 1]) {
            runCount++;
        }
    }

    // 每一段变成两个数字（值 + 次数）
    int[] result = new int[runCount * 2];

    int index = 0;               // result 当前写入位置
    int currentValue = arr[0];   // 当前段的值
    int currentCount = 1;        // 当前段的长度（次数）

    for (int i = 1; i < arr.length; i++) {
        if (arr[i] == currentValue) {
            currentCount++;
        } else {
            // 把之前那一段写入 result
            result[index] = currentValue;
            result[index + 1] = currentCount;
            index += 2;

            // 开始新的一段
            currentValue = arr[i];
            currentCount = 1;
        }
    }

    // 别忘了最后一段
    result[index] = currentValue;
    result[index + 1] = currentCount;

    return result;
}
```

### 🧪 FRQ 3（难）：考试评分 + 连续答对加分

### 题干

你要实现一个考试评分系统：

给你两个 `char[]`：

- `char[] key`：答案（比如 `{'A','C','B','D','B'}`）
- `char[] stu`：学生作答（比如 `{'A','C','D','D','B'}`）

**规则：**

- 每题答对 +2 分
- 答错或空着（假设用 `'?'` 表示空）得 0 分
- **连续答对奖励**：
  - 如果学生**连续答对 3 题或以上**，从第 3 题开始，每题额外 +1 分
  - 比如连续 4 题都对：
    - 第 1 题：2 分
    - 第 2 题：2 分
    - 第 3 题：2+1 = 3 分
    - 第 4 题：2+1 = 3 分

请写一个方法：

```java
public static int scoreExam(char[] key, char[] stu)
```

返回学生总分。你可以假设 `key.length == stu.length` 且长度 ≥ 1。

### ✅ 参考答案

```java
public static int scoreExam(char[] key, char[] stu) {
    int total = 0;
    int consecutiveCorrect = 0;  // 当前连续答对的题数

    for (int i = 0; i < key.length; i++) {
        if (stu[i] == key[i]) {
            // 答对
            consecutiveCorrect++;
            int questionScore = 2;

            if (consecutiveCorrect >= 3) {
                // 从第 3 题连续答对开始，每题额外 +1
                questionScore += 1;
            }

            total += questionScore;
        } else {
            // 答错或空
            consecutiveCorrect = 0;  // 连续中断
        }
    }

    return total;
}
```
