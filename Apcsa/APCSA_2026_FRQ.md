### 2026 APCSA FRQ：四题讲解

| 题目 | 建议讲解重点 | 需要提交的内容 |
| --- | --- | --- |
| Q1 Account | 候选名称、字符串索引与拼接 | 构造函数和一个方法 |
| Q2 Bottle | 对象状态、构造函数、临界值 | 完整类 |
| Q3 Attendance | 两个对象列表的匹配与计数 | 一个方法 |
| Q4 GameBoard | 固定一行遍历、累加与布尔标记 | 一个方法 |

以下 Q1、Q3、Q4 代码应放在题目给定的类中，不能直接作为独立 Java 文件运行。题目已有的辅助方法不需要重新实现。

## Q1：Account

### A. 建立可用用户名

**题意：**先检查原名；若不可用，就依次尝试在原名后拼接 1、2、3……，将第一个可用名称存入 `username`。

### 思路

把“名称生成”和“可用性判断”分开：本题负责生成候选名称，已有的 `isAvailable` 负责判断。

循环开始时，`candidate` 始终是当前待检查的完整名称。只有检查失败，才构造下一个候选；循环结束后再写入实例变量。

```java
public Account(String requestedName)
{
    String candidate = requestedName;
    int suffix = 1;

    while (!isAvailable(candidate))
    {
        candidate = requestedName + suffix;
        suffix++;
    }

    username = candidate;
}
```

### 自编演示

假设 `coder`、`coder1` 已被使用，而 `coder2` 可用。

| 检查的 candidate | 是否可用 | 下一步 |
| --- | --- | --- |
| `coder` | false | 生成 `coder1` |
| `coder1` | false | 生成 `coder2` |
| `coder2` | true | 结束循环并赋值 |

### 易错点

- 每次都从 `requestedName` 生成新候选。若写 `candidate += suffix`，会生成 `coder1`、`coder12`、`coder123`。
- 先检查原名，不能直接从 `coder1` 开始。
- 构造函数没有返回类型，不能写 `public void Account(...)`。
- `suffix++` 不会改变已生成的字符串；它准备的是下一轮使用的整数。

**课堂提问：**原名可用时，循环执行几次？答案：0 次。

### B. 缩短用户名

**题意：**删除每个 `-` 以及它紧前面的字符，返回结果，但保留原 `username`。题目保证没有首尾连字符或连续连字符。

### 思路：扫描原字符串，决定哪些字符保留

一个字符应被跳过，当且仅当：它本身是 `-`，或者它后面的字符是 `-`。

这种写法始终读取原字符串，索引不会因删除而移动。使用 `substring(i, i + 1)` 取得一个字符对应的字符串。

```java
public String getShortenedName()
{
    String shortened = "";

    for (int i = 0; i < username.length(); i++)
    {
        String current = username.substring(i, i + 1);
        boolean beforeHyphen = false;

        if (i + 1 < username.length())
        {
            beforeHyphen =
                username.substring(i + 1, i + 2).equals("-");
        }

        if (!current.equals("-") && !beforeHyphen)
        {
            shortened += current;
        }
    }

    return shortened;
}
```

### 自编演示

输入 `Ab-Cd-Ef`：

| 当前字符 | 跳过的原因 | 当前结果 |
| --- | --- | --- |
| A | 保留 | A |
| b | 后面是连字符 | A |
| - | 本身是连字符 | A |
| C | 保留 | AC |
| d | 后面是连字符 | AC |
| - | 本身是连字符 | AC |
| E | 保留 | ACE |
| f | 保留 | ACEf |

### 易错点

- `substring(a, b)` 包含下标 `a`，不包含下标 `b`。
- 读取下一个字符前必须检查 `i + 1 < username.length()`。
- 字符串内容用 `.equals()` 比较。
- 只修改局部变量 `shortened`；不要把结果赋回 `username`。
- 无连字符时，每个字符都被保留；输入 `a-b` 时，结果为 `b`。

**课堂提问：**为什么不用删除后 `i--`？答案：我们没有修改正在遍历的字符串。

## Q2：Bottle

**题意：**瓶子初始装满。每次扣除指定液量后，若剩余量严格低于容量的 25%，立即补满，返回最终液量。

### 思路：区分固定属性与变化状态

`capacity` 表示最大容量；`remaining` 表示当前液量。一次调用的顺序是“扣除 → 判断 → 必要时补满 → 返回”。

```java
public class Bottle
{
    private double capacity;
    private double remaining;

    public Bottle(double initialCapacity)
    {
        capacity = initialCapacity;
        remaining = initialCapacity;
    }

    public double updateAmount(double removed)
    {
        remaining = remaining - removed;

        if (remaining < capacity / 4.0)
        {
            remaining = capacity;
        }

        return remaining;
    }
}
```

### 自编演示：连续调用

```java
Bottle bottle = new Bottle(80.0);
System.out.println(bottle.updateAmount(40.0)); // 40.0
System.out.println(bottle.updateAmount(20.0)); // 20.0
System.out.println(bottle.updateAmount(1.0));  // 80.0
```

容量为 80，阈值是 20。剩余量等于 20 时不补满；降为 19 后补满。第三次调用读取的是上一次保存的状态。

### 易错点

- 条件是 `<`，不是 `<=`。
- 阈值来自容量，不能来自本次扣除前的剩余液量。
- 先补满再 `return`，否则会返回补满前的数值。
- 字段不能声明为 `static`，否则不同瓶子会共享状态。
- `capacity / 4.0` 避免了 `1 / 4` 的整数除法问题。
- 在题目前置条件成立时，无须额外处理非法扣除量。

**课堂提问：**为什么需要两个字段？答案：液量会减少，但判断阈值仍需要知道最大容量。

## Q3：Attendance

**题意：**按学生 ID 匹配两个课程列表，统计同时选课且历史缺勤次数更多的学生人数。列表内 ID 不重复，列表内容不能改变。

### 思路：先确认同一学生，再比较缺勤次数

外层取一条历史记录，内层寻找同 ID 的数学记录。找到后比较缺勤次数，并结束本次内层搜索。

```java
public int moreHistoryThanMathAbsences()
{
    int count = 0;

    for (int h = 0; h < historyList.size(); h++)
    {
        CourseRecord history = historyList.get(h);

        for (int m = 0; m < mathList.size(); m++)
        {
            CourseRecord math = mathList.get(m);

            if (history.getStudentID().equals(math.getStudentID()))
            {
                if (history.getAbsences() > math.getAbsences())
                {
                    count++;
                }

                break;
            }
        }
    }

    return count;
}
```

### 自编演示

| 学生 ID | 历史缺勤 | 数学缺勤 | 是否计数 |
| --- | ---: | ---: | --- |
| s1 | 5 | 2 | 是 |
| s2 | 1 | 1 | 否 |
| s3 | 4 | 未选课 | 否 |
| s4 | 2 | 6 | 否 |

结果为 1。两个列表可以采用不同排列顺序，不能把相同下标当成同一学生。

### 为什么 break 放在这里？

匹配到同 ID 后，无论缺勤比较结果是什么，都已找到这位学生的数学记录。ID 不重复，所以可以结束搜索。

`break` 只结束内层循环；外层仍会继续处理下一位学生。

### 易错点

- 比较 `getStudentID()` 返回的字符串内容，不比较两个记录对象是否是同一个对象。
- 缺勤相等不计数。
- 不使用 `remove`，也不排序列表。
- `ArrayList` 使用 `.size()` 和 `.get(i)`，不是 `.length` 和 `[i]`。
- 不假设 `indexOf(history)` 能按学生 ID 找到数学记录：题目没有保证对象的 `equals` 实现这种规则。

最坏情况下，两个列表长度为 H、M 时，需要 H×M 次配对检查。对这道题而言，双重循环直接表达了匹配逻辑。

**课堂提问：**历史缺勤为 10 的学生是否一定计数？答案：还必须选了数学，并且数学缺勤少于 10。

## Q4：GameBoard

**题意：**求指定行的分数总和；若该行所有格子颜色相同，返回两倍总和。

### 思路：一次遍历，同时完成两件事

用 `total` 累加分数，用 `uniform` 记录是否整行同色。选第一格颜色作为基准；只要发现不同颜色，标记就永久变为 `false`。

```java
public int getPointsForRow(int targetRow)
{
    int total = 0;
    boolean uniform = true;
    String referenceColor = board[targetRow][0].getColor();

    for (int col = 0; col < board[targetRow].length; col++)
    {
        Space cell = board[targetRow][col];
        total += cell.getPoints();

        if (!referenceColor.equals(cell.getColor()))
        {
            uniform = false;
        }
    }

    if (uniform)
    {
        return total * 2;
    }

    return total;
}
```

### 自编演示

| 行内颜色 | 行内分数 | 总和 | 返回值 |
| --- | --- | ---: | ---: |
| red, red, red | 10, 20, 30 | 60 | 120 |
| red, blue, red | 10, 20, 30 | 60 | 60 |

第二行最后一格又变成红色，也不能把标记恢复成 `true`，因为已经发现过蓝色格子。

### 易错点

- `board[targetRow][col]`：固定行，改变列。
- 列数是 `board[targetRow].length`；`board.length` 是行数。方阵可能掩盖这一错误，长方形数组会暴露它。
- 发现不同颜色后不能 `break`：仍然需要累加后面的格子分数。
- 不要在每次匹配颜色时把 `uniform` 重设为 `true`。
- 第一格也需要加入分数总和。
- 遍历完再决定是否翻倍，不能在循环中反复翻倍。

**课堂提问：**为什么初始标记为 `true`？答案：尚未发现反例；后续发现一个不同颜色，就足以否定整行同色。

## 变量的含义

| 变量 | 在算法中承担的职责 |
| --- | --- |
| `candidate` | 当前等待检查的完整名称 |
| `suffix` | 下一次生成名称时使用的数字 |
| `shortened` | 已扫描部分中应该保留的字符 |
| `remaining` | 跨方法调用保存的对象状态 |
| `count` | 已确认符合条件的学生人数 |
| `total` | 当前已经访问的格子的分数总和 |
| `uniform` | 到目前为止是否尚未发现颜色反例 |

