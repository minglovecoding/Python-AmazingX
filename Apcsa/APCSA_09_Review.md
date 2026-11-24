## APCSA 第二轮复习 09：类设计复盘与继承、多态拓展

## 📚 1. 本章定位

| 路线 | 内容 | 对应训练 |
| --- | --- | --- |
| **AP 主线** | 构造器、封装、this、对象引用、方法重载、类设计与对象集合 | MCQ 1—6；FRQ 1—2；官方类设计题 |
| **Java 拓展** | 自定义继承、构造链、重写、多态、转型、字段隐藏、自定义接口 | MCQ 7—18；FRQ 3—4 |

## 2. 核心知识与易错点

参考原稿./Apcsa/1/apcsa_09.md

## 3. MCQ 训练

### A 组：现行 AP 主线（1—6）

### MCQ 1：构造器中的同名变量

```java
class Wallet {
    private int money;
    public Wallet(int money) { money = money; }
    public int getMoney() { return money; }
}
```

执行 `System.out.println(new Wallet(50).getMoney());`，输出什么？

A. 50  
B. null  
C. 0  
D. 编译错误

### MCQ 2：共享对象状态

```java
class Wallet {
    private int money;
    public Wallet(int money) { this.money = money; }
    public void deposit(int amount) { money += amount; }
    public int getMoney() { return money; }
}
```

调用代码：

```java
Wallet a = new Wallet(50);
Wallet b = a;
b.deposit(20);
System.out.println(a.getMoney());
```

A. 50  
B. 70  
C. 20  
D. 编译错误

### MCQ 3：普通方法重载

```java
class Formatter {
    public String show(int x) { return "I"; }
    public String show(double x) { return "D"; }
}
```

执行 `Formatter f = new Formatter();` 后，`System.out.print(f.show(3) + f.show(3.0));` 输出什么？

A. ID  
B. II  
C. DD  
D. DI

### MCQ 4：封装与外部访问

Wallet 声明了 `private int money;` 和 `public int getMoney()`。在另一个普通顶层类的 main 中，a 为 Wallet 对象。哪条语句不能编译？

A. `int x = a.getMoney();`  
B. `System.out.println(a.getMoney());`  
C. `Wallet b = a;`  
D. `System.out.println(a.money);`

### MCQ 5：实例字段是否共享

```java
class Counter {
    private int count = 0;
    public void add() { count++; }
    public int getCount() { return count; }
}
```

调用代码：

```java
Counter a = new Counter();
Counter b = new Counter();
a.add(); a.add(); b.add();
System.out.print(a.getCount() + " " + b.getCount());
```

A. `3 3`  
B. `1 2`  
C. `2 1`  
D. `2 2`

### MCQ 6：String 内容与引用

```java
String a = new String("AP");
String b = new String("AP");
System.out.print(a.equals(b) + " " + (a == b));
```

A. `true true`  
B. `true false`  
C. `false true`  
D. `false false`

### MCQ 7：重写实例方法

```java
class A {
    public String f() { return "A"; }
}
class B extends A {
    @Override
    public String f() { return "B"; }
}
```

执行 `A x = new B(); System.out.print(x.f());`，结果是什么？

A. B  
B. A  
C. AB  
D. 编译错误

### MCQ 8：引用类型限制调用

```java
class A {
    public void m() { System.out.print("A"); }
}
class B extends A {
    public void n() { System.out.print("N"); }
}
```

执行 `A x = new B(); x.n();`，结果是什么？

A. N  
B. A  
C. 运行时 ClassCastException  
D. 编译错误：A 类型没有 n 方法

### MCQ 9：隐式 super()

```java
class A {
    public A(int n) { }
}
class B extends A {
    public B() { System.out.print("B"); }
}
```

哪项正确？

A. new B() 输出 B  
B. B 的构造器不能编译，因为隐式 super() 没有对应的 A()  
C. 运行时发生 NullPointerException  
D. A(int) 会自动接收默认值 0

### MCQ 10：显式构造器调用

```java
class A {
    public A() { System.out.print("A0 "); }
    public A(int n) { System.out.print("A" + n + " "); }
}
class B extends A {
    public B() {
        super(3);
        System.out.print("B ");
    }
}
```

new B() 的输出是什么？忽略末尾空格。

A. `A0 B`  
B. `B A3`  
C. `A3 B`  
D. `A0 A3 B`

### MCQ 11：运行时类型不能挽救非法重载调用

```java
class A {
    public void f(int x) { System.out.print("A1"); }
}
class B extends A {
    public void f(double x) { System.out.print("B2"); }
}
```

执行 `A x = new B(); x.f(5.0);`，结果是什么？

A. B2  
B. A1  
C. 运行时 ClassCastException  
D. 编译错误

### MCQ 12：继承的重载仍参与选择

使用 MCQ 11 的类，执行：

```java
A x = new B();
B y = new B();
x.f(5);
y.f(5);
```

输出什么？

A. A1A1  
B. A1B2  
C. B2B2  
D. 编译错误

### MCQ 13：super 调用父类实现

```java
class A {
    public String f() { return "A"; }
}
class B extends A {
    @Override
    public String f() { return super.f() + "B"; }
}
```

执行 `A x = new B(); System.out.print(x.f());`，结果是什么？

A. B  
B. AB  
C. BA  
D. 无限递归直至栈溢出

### MCQ 14：不安全的向下转型

```java
class A { }
class B extends A { }
```

执行下面的代码会发生什么？

```java
A x = new A();
B y = (B) x;
System.out.print("ok");
```

A. 输出 ok  
B. 编译错误：任何父类引用都不能向下转型  
C. 运行时 ClassCastException，未输出 ok  
D. y 为 null，输出 ok

### MCQ 15：instanceof 与 null

使用 MCQ 14 的类：

```java
A x = new A();
A y = null;
System.out.print((x instanceof B) + " " + (y instanceof B));
```

A. `true false`  
B. `false true`  
C. `true true`  
D. `false false`

### MCQ 16：toString 拓展

```java
class A {
    public String toString() { return "A"; }
}
class B extends A {
    @Override
    public String toString() { return "B"; }
}
```

执行 `A x = new B(); System.out.print(x);`，输出什么？

A. A  
B. B  
C. 固定格式的内存地址  
D. 编译错误

### MCQ 17：字段隐藏与实例方法重写

```java
class A {
    public int x = 1;
    public int getX() { return x; }
}
class B extends A {
    public int x = 2;
    @Override
    public int getX() { return x; }
}
```

执行 `A obj = new B(); System.out.print(obj.x + " " + obj.getX());`，输出什么？

A. `2 2`  
B. `1 1`  
C. `1 2`  
D. `2 1`

### MCQ 18：接口实现的访问权限

```java
interface Shape {
    double getArea();
}
class Square implements Shape {
    private double side;
    public Square(double side) { this.side = side; }
    double getArea() { return side * side; }
}
```

哪项正确？

A. 正常编译，接口方法默认包访问  
B. 正常编译，Square.getArea 自动成为 public  
C. 编译错误，因为类不能保存 double 字段  
D. 编译错误，实现方法的权限不能低于 public

## 4. FRQ 训练

### FRQ 1：ScoreRecord【AP 主线：完整类设计】

编写完整的 public 类 ScoreRecord，保存姓名与分数。name 不为 null，初始分数为 0..100；bonus 为 0..100。除特别说明外，方法不改变对象状态。

| 调用 | 要求 |
| --- | --- |
| `new ScoreRecord(name, score)` | 初始化私有实例字段 |
| `getName()` | 返回 String 姓名 |
| `getScore()` | 返回 int 分数 |
| `addBonus(int bonus)` | void；增加分数，但最高为 100 |
| `getSummary()` | 返回 `name + ":" + score`，不打印 |

示例：

| 语句 | 结果 |
| --- | --- |
| `ScoreRecord r = new ScoreRecord("Amy", 85);` | 创建独立记录 |
| `r.addBonus(10);` | 分数变为 95 |
| `r.getSummary();` | 返回 `"Amy:95"` |
| `r.addBonus(20);` | 分数变为 100 |
| `r.getSummary();` | 返回 `"Amy:100"` |

要求：不使用 public 字段，不使用 static 保存每个人的姓名或成绩，不重写 toString；输出字符串使用普通 getSummary 方法。

### FRQ 2：StudyGroup【AP 主线：组合与对象集合】

使用 FRQ 1 的 ScoreRecord 类，编写完整 public 类 StudyGroup。每个学习小组持有自己的 ArrayList<ScoreRecord>，这是 has-a 关系，不继承 ScoreRecord。最多保存 1000 条记录。

| 调用 | 要求 |
| --- | --- |
| `new StudyGroup()` | 创建本组独立的空集合 |
| `addRecord(ScoreRecord record)` | void；将非 null 参数的原引用追加到集合；不复制记录 |
| `averageScore()` | double；返回当前所有位置对应分数的平均，空组返回 0.0 |
| `topRecord()` | 返回最高分记录的原引用；并列返回最先加入的；空组返回 null |

记录允许重复引用；统计按位置进行。加入后，如果外部对某条记录调用 addBonus，下一次 averageScore/topRecord 必须使用更新后的分数。因此不能把“加入时的总分”缓存后永不更新。

示例：先加入 Amy 80、Bo 90，平均为 85.0，最高记录为 Bo；再对 Amy 加 20 分，下次平均为 95.0，最高记录为 Amy。查询不得修改集合或记录。

### FRQ 3：DiscountTicket【Java 拓展：继承与 super】

本题是拓展编程练习，不标为当前 AP FRQ 必考形式。给定：

```java
public class EventTicket {
    private String label;
    private double price;

    public EventTicket(String label, double price) {
        this.label = label;
        this.price = price;
    }

    public double getPrice() { return price; }
    public String getLabel() { return label; }
    public String describe() { return getLabel() + ":" + getPrice(); }
}
```

编写完整的 DiscountTicket extends EventTicket：

- 构造器 `DiscountTicket(String label, double price, int discountPercent)`，调用父类构造器，保存折扣百分比。price 为 0..10000 的有限值，discountPercent 为 0..100。
- 重写 getPrice()：使用父类原价计算折后价。百分比 25 表示减价 25%，不是只支付 25%。必须复用 super.getPrice()。
- 重写 describe()：调用 super.describe()，在后面追加 `" [student]"`。不得修改父类字段或重复声明父类同名字段。

示例：

```java
EventTicket t = new DiscountTicket("Concert", 80.0, 25);
// t.getPrice() -> 60.0
// t.describe() -> "Concert:60.0 [student]"
```

另用文字解释：为什么 super.describe() 内部的 getPrice() 仍使用 DiscountTicket 的实现？

### FRQ 4：Shape 与 ShapeTools【Java 拓展：接口契约】

给定自定义接口：

```java
public interface Shape {
    double getArea();
    int compareTo(Shape other);
}
```

**(a)** 编写完整 public 类 Rectangle implements Shape。

- 保存私有 double width、height，构造器接收并初始化它们。
- 两边均为 0..1000 的有限值，面积也为有限值。
- public getArea() 返回面积。
- public compareTo(Shape other) 按面积返回 -1、0 或 1；other 不为 null，getArea() 返回有限非负值。
- 不得把面积差强转成 int 作为比较结果，小于 1 的差也必须正确区分。本题用 double 的实际比较结果判等，不另设容差。

**(b)** 编写 public 类 ShapeTools 的静态方法：

```java
public static Shape largest(Shape[] shapes)
```

数组不为 null，元素不为 null，允许空数组。必须使用接口 compareTo 比较，返回面积最大的原对象引用；并列返回数组中最早的；空数组返回 null。不得重排数组。

示例：Rectangle(2,3)、Rectangle(1,6)、Rectangle(2,4) → 返回第三个原对象；若只有前两个，则返回第一个。

## 5. 官方真题迁移：类设计，而非自定义继承

以下两题是公开真题，适合本章 AP 主线路线。**它们都不要求自定义继承层次**，与 FRQ 1—2 的联系是“根据调用表设计对象状态、构造器和方法”，不要把它们标为继承真题。

| 真题 | 训练重点 | 必查细节 |
| --- | --- | --- |
| [2023 Q2 Sign](https://apcentral.collegeboard.org/media/pdf/ap23-frq-comp-sci-a.pdf#page=8)，PDF 第 8—10 页 | 保存字符串与宽度；完整类、String 分段 | 空消息返回规则、宽度整除、末尾不能多分号、重复查询不能破坏状态 |
| [2024 Q2 Scoreboard](https://apcentral.collegeboard.org/media/pdf/ap24-frq-comp-sci-a.pdf#page=8)，PDF 第 8—9 页 | 两队分数与当前活动队伍；状态更新和字符串输出 | 得分后仍由本队活动，0 分才换队；每个对象状态独立 |

推荐：FRQ 1 后做 Sign，FRQ 2 后做 Scoreboard。先读原题与调用表，再设计最少需要哪些实例字段。这里只给中文学习摘要，不重印完整题面；前置条件和官方评分以原题为准。

评分链接：[2023 官方评分](https://apcentral.collegeboard.org/media/pdf/ap23-sg-computer-science-a.pdf)；[2024 官方评分](https://apcentral.collegeboard.org/media/pdf/ap24-sg-computer-science-a.pdf)。历史题号用于定位，不据此推断当前考试结构。

## 6. MCQ 答案与解析

### A 组：AP 主线

| 题号 | 答案 | 核心理由 |
| --- | --- | --- |
| 1 | C | money = money 只操作形参；字段仍为默认 0 |
| 2 | B | b 与 a 引用同一 Wallet，deposit 修改共享对象 |
| 3 | A | int 实参选 int 重载，double 实参选 double 重载 |
| 4 | D | 普通外部类不能直接访问 private 字段 |
| 5 | C | 两次 new 产生独立实例状态，分别累加 2、1 |
| 6 | B | 两个新 String 内容相同，但对象引用不同 |

### B 组：Java 拓展

| 题号 | 答案 | 核心理由 |
| --- | --- | --- |
| 7 | A | A 中有 f()，运行时分派到 B.f() |
| 8 | D | 编译期 A 类型没有 n，不能先跳到运行期 |
| 9 | B | 父类只有 A(int)，没有隐式调用所需的 A() |
| 10 | C | 显式调用 A(3)，再执行 B 构造器剩余代码 |
| 11 | D | A 可见的 f(int) 不能接收 double 5.0 |
| 12 | A | 两次均选 f(int)，B 没有重写它，只继承 A 的实现 |
| 13 | B | 动态进入 B.f()；super.f() 返回 A，再拼接 B |
| 14 | C | 转型不改变对象，实际 A 不是 B，未执行到打印 |
| 15 | D | 普通 A 不是 B；null 对任何该类检查都返回 false |
| 16 | B | 使用实际 B 对象的 toString 实现 |
| 17 | C | 字段访问选 A.x；重写实例方法执行 B.getX() |
| 18 | D | 接口中的该方法隐含 public，实现不能缩小权限 |

订正时要求先判阶段：

1. 有没有重复类名、缺少构造器、不可访问成员等编译错误？
2. 编译通过后，转型是否与实际对象兼容？
3. 调用选中的签名是什么，有没有对应重写？
4. 最后再追踪输出与状态；不能为不能编译的代码猜运行输出。

## FRQ 参考实现

每个 public 类或接口分别保存为同名 .java 文件。完整类代码不含 main；用驱动类调用测试。FRQ 1—2 为 AP 主线，FRQ 3—4 为 Java 拓展。

### FRQ 1：ScoreRecord

```java
public class ScoreRecord {
    private String name;
    private int score;

    public ScoreRecord(String name, int score) {
        this.name = name;
        this.score = score;
    }

    public String getName() { return name; }
    public int getScore() { return score; }

    public void addBonus(int bonus) {
        score = Math.min(100, score + bonus);
    }

    public String getSummary() {
        return name + ":" + score;
    }
}
```

总计 9 分。也可用 if 实现上限；本题前置条件已给出，不要求异常处理。

### FRQ 2：StudyGroup

```java
import java.util.ArrayList;

public class StudyGroup {
    private ArrayList<ScoreRecord> records;

    public StudyGroup() {
        records = new ArrayList<ScoreRecord>();
    }

    public void addRecord(ScoreRecord record) {
        records.add(record);
    }

    public double averageScore() {
        if (records.size() == 0) return 0.0;
        int sum = 0;
        for (ScoreRecord record : records) {
            sum += record.getScore();
        }
        return (double) sum / records.size();
    }

    public ScoreRecord topRecord() {
        ScoreRecord best = null;
        for (ScoreRecord record : records) {
            if (best == null || record.getScore() > best.getScore()) {
                best = record;
            }
        }
        return best;
    }
}
```

总计 9 分。averageScore 和 topRecord 时间 O(n)、额外空间 O(1)。给定记录数与分数范围保证 int 累加安全。

### FRQ 3：DiscountTicket（拓展）

EventTicket.java 使用题目给定代码；DiscountTicket.java：

```java
public class DiscountTicket extends EventTicket {
    private int discountPercent;

    public DiscountTicket(String label, double price, int discountPercent) {
        super(label, price);
        this.discountPercent = discountPercent;
    }

    @Override
    public double getPrice() {
        return super.getPrice() * (100 - discountPercent) / 100.0;
    }

    @Override
    public String describe() {
        return super.describe() + " [student]";
    }
}
```

调用追踪：

| 步骤 | 执行位置 | 结果/下一步 |
| --- | --- | --- |
| 1 | t.describe() | 实际对象为 DiscountTicket，进入其 describe |
| 2 | super.describe() | 执行 EventTicket.describe 的代码 |
| 3 | 父类代码中的 getPrice() | 接收对象仍是同一 DiscountTicket，进入其 getPrice |
| 4 | 子类 getPrice 中 super.getPrice() | 获取父类保存的原价 80.0，计算为 60.0 |
| 5 | 返回并拼接 | 得到 `Concert:60.0 [student]` |

super 选择了某次调用的父类实现，并没有把当前对象临时变成 EventTicket。

总计 9 分，仅用于拓展课堂反馈。

### FRQ 4：Rectangle 与 ShapeTools（拓展）

Shape.java 使用题目给定接口。

```java
public class Rectangle implements Shape {
    private double width;
    private double height;

    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }

    @Override
    public double getArea() {
        return width * height;
    }

    @Override
    public int compareTo(Shape other) {
        if (getArea() < other.getArea()) return -1;
        if (getArea() > other.getArea()) return 1;
        return 0;
    }
}
```

```java
public class ShapeTools {
    public static Shape largest(Shape[] shapes) {
        Shape best = null;
        for (Shape shape : shapes) {
            if (best == null || shape.compareTo(best) > 0) {
                best = shape;
            }
        }
        return best;
    }
}
```

总计 9 分，仅用于拓展课堂反馈。largest 时间 O(n)、额外空间 O(1)。

### 原稿 Circle 的保留实现（拓展，可与 FRQ 4 联用）

```java
public class Circle implements Shape {
    private double radius;

    public Circle(double radius) {
        this.radius = radius;
    }

    @Override
    public double getArea() {
        return Math.PI * radius * radius;
    }

    @Override
    public int compareTo(Shape other) {
        if (getArea() < other.getArea()) return -1;
        if (getArea() > other.getArea()) return 1;
        return 0;
    }
}
```

radius 为 0..1000 的有限值。可用 `Shape[] shapes = {new Circle(1), new Rectangle(2, 2)};` 检查同一接口下的不同实现。相同的方法名不意味着 Rectangle 与 Circle 必须互相继承。
