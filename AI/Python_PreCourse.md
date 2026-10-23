## Python 基础：

> 使用版本：Python 3。例子采用 Python 3.10+ 可用的常规写法。

## 📚 课程目标与使用方法

本节重点：读取数据、整理样本、编写函数、表达规则、计算简单预测结果、检查程序输出。

### 🗓️ 建议课时安排

| 课次 | 对应章节 | 主题 | 学生应完成的任务 |
|---|---|---|---|
| 1 | 1–2 | 环境、程序结构、变量与输入输出 | 编写交互式信息卡 |
| 2 | 3–4 | 运算符与条件判断 | 编写二分类规则 |
| 3 | 5 | for、while、嵌套与循环控制 | 生成真值表并完成猜数字 |
| 4 | 6 | 字符串与列表 | 清理文本、统计一组数据 |
| 5 | 7 | 元组、字典、集合 | 保存样本并统计标签频率 |
| 6 | 8 | 函数与参数 | 编写预测函数和准确率函数 |
| 7 | 9 | 推导式、排序与常用工具 | 筛选样本并按属性排序 |
| 8 | 10 | 模块、文件、异常 | 读取 CSV 并处理无效输入 |
| 9 | 11 | 类与对象 | 封装规则分类器 |
| 10 | 12 | NumPy 与 Pandas 衔接 | 读取数据表、检查数组形状 |
| 11 | 13 | 综合项目 | 完成可评估的规则分类程序 |
| 12 | 14–16 | 练习订正与能力验收 | 独立实现、测试并解释代码 |

基础语法必修：第 1–10 章。AI 衔接建议学习：第 11–13 章。

---

## 1. Python 导论与程序结构

### 1.1 Python 可以做什么

- 自动化脚本、文本和文件处理。
- 数据分析、可视化、人工智能与机器学习。
- 网站后端、小游戏及算法练习。

Python 语言与 NumPy、Pandas 等第三方库是不同层次：先学习语言，再学习工具。

### 1.2 环境与运行

需要安装 Python 3；VS Code 用于编辑代码，配合 Python 扩展选择解释器。GitHub 用于保存与分享代码，不是执行 Python 的必备软件。

新建 `hello.py`：

```python
print("Hello, Python!")
```

在文件所在目录的终端运行：

```bash
python3 hello.py
```

部分 Windows 环境使用 `py hello.py`。确认终端解释器与 VS Code 选择的解释器一致。

### 1.3 缩进、冒号与语句

```python
score = 85
if score >= 60:
    print("通过")
    print("继续学习")
print("程序结束")
```

- `if`、`for`、`while`、`def`、`class` 等语句头末尾通常需要冒号。
- 缩进表示代码块；统一使用 4 个空格，不混用 Tab。
- 普通语句一般不写分号。
- 文件顶层语句按顺序执行；定义函数时不会自动执行函数体。

### 1.4 注释与多行书写

```python
# 单行注释：解释目的或规则
total = (
    10 + 20
    + 30
)
message = """第一行
第二行"""
print(total)      # 60
print(message)
```

括号内可以自然换行；原讲义中的反斜杠续行也可用，但通常优先使用括号。三引号创建字符串，**不是专门的多行注释语法**。函数或类开头的说明字符串称为文档字符串。

### 1.5 命名与常量

```python
student_name = "Ming"
sample_count = 100
LEARNING_RATE = 0.01
```

变量名不能以数字开头，不能使用 `if`、`class` 等关键字；区分大小写。采用 `snake_case`。全大写表示“约定不修改”的常量，语言本身并不禁止重新赋值。

**不要用 `list`、`str`、`dict`、`tuple`、`set`、`sum` 作变量名**，否则会遮蔽内置类型或函数。

### 📌 课堂练习

编写程序输出姓名、课程名和学习目标。增加一个布尔变量 `ready`，仅当它为 `True` 时输出“开始学习”。

---

## 2. 变量、数据类型与输入输出

### 2.1 变量与赋值

```python
count = 10
count = count + 1
x, y = 3, 5
x, y = y, x
print(count, x, y)  # 11 5 3
```

右侧先求值，再把结果绑定到左侧名字。Python 不要求预先声明变量类型，同一个名字可以重新绑定到不同类型的对象；课堂代码应尽量保持含义与类型稳定。

```python
a = b = 1
print(a, b)
```

这不表示创建了三个独立内存空间。名字绑定对象；可变对象共享问题见第 6、8 章。

### 2.2 常用类型

| 类型 | 用途 | 示例 | 能否原地修改对象 |
|---|---|---|---|
| `int` | 整数、下标、数量 | `12` | 否 |
| `float` | 小数、平均值 | `0.75` | 否 |
| `bool` | 条件、标记 | `True`、`False` | 否 |
| `str` | 文本 | `"AI"` | 否 |
| `list` | 可变序列 | `[1, 2, 3]` | 是 |
| `tuple` | 不可变序列 | `(1, 2)` | 否 |
| `dict` | 键到值的映射 | `{"label": 1}` | 是 |
| `set` | 去重、成员判断 | `{1, 2}` | 是 |
| `NoneType` | 暂无结果 | `None` | 否 |
| `complex`（选学） | 复数 | `1 + 2j` | 否 |

```python
age = 16
height = 1.72
is_student = True
name = "Ming"
result = None
print(type(age))                 # <class 'int'>
print(isinstance(name, str))      # True
print(10 ** 30)                  # Python 整数可以超过 64 位范围
```

Python 3 没有单独的 `long` 类型，也不使用 `123L`。整数大小受可用内存等限制。`bool` 是 `int` 的子类，参与数值运算时 `True` 对应 1、`False` 对应 0；表达判断时仍使用布尔值。

### 2.3 类型转换

```python
print(int("12"))       # 12
print(float("3.5"))    # 3.5
print(str(42))         # 文本 "42"
print(int(3.9))        # 3：向 0 截断
print(int(-3.9))       # -3
print(bool(0))         # False
print(bool("False"))   # True：非空字符串
```

`int("3.5")` 会产生 `ValueError`。`bool("False")` 不能解析文字真假，输入布尔值需要自己定义转换规则。

| 原讲义涉及的工具 | Python 3 写法与用途 |
|---|---|
| `int`、`float`、`str` | 转换整数、小数、文本 |
| `complex` | `complex(1, 2)` 得到 `1 + 2j` |
| `list`、`tuple`、`set` | `list("abc")`、`tuple([1, 2])`、`set([1, 1, 2])` |
| `dict` | `dict([("x", 1), ("y", 2)])` 创建键值映射 |
| `frozenset`（选学） | `frozenset([1, 2])` 创建不可变集合 |
| `repr` | `repr("a\nb")` 得到包含引号及转义表示的字符串，便于调试 |
| `ord`、`chr` | `ord("A")` 得到 65；`chr(65)` 得到 `"A"` |
| `hex`、`oct`、`bin` | `hex(10)` 为 `"0xa"`；`oct(10)` 为 `"0o12"`；`bin(10)` 为 `"0b1010"` |
| `int(text, base)` | `int("1010", 2)` 得到 10 |
| `long`、`unichr` | Python 3 中分别使用 `int`、`chr` |
| `eval`（了解） | 执行字符串表达式；不用于处理用户输入或外部数据 |

`eval` 不只是类型转换。读取数字用 `int` / `float`，读取 JSON 用第 10 章的 `json`。确需解析 Python 字面量时，可查阅 `ast.literal_eval`，并处理解析错误。

### 2.4 输入：input

```python
name = input("姓名：")
age = int(input("年龄："))
print(name, age + 1)
```

`input()` 读取一行，返回字符串，去掉末尾换行。不会自动变成数字，也不会执行表达式。

一行读取两个整数：

```python
# 输入：3 5
a, b = map(int, input().split())
print(a + b)  # 8
```

`split()` 按空白拆分；`map(int, ...)` 逐项转换；解包要求恰好两个值。在线判题通常不添加输入提示。

### 2.5 输出：print 与格式化

```python
print("AI", "Python", sep=" / ")  # AI / Python
print("Hello", end=" ")
print("World")                    # 接在上一行后面
score = 0.87654
print(f"准确率：{score:.2%}")      # 准确率：87.65%
print(f"数值：{score:.3f}")        # 数值：0.877
```

`sep` 控制多个对象之间的分隔符，默认空格；`end` 控制输出结尾，默认换行。格式化仅改变显示，不改变变量的数值。

原讲义中的 `%s`、`%d` 仍可用，也可使用 `format`；新代码优先 f-string：

```python
name, age = "Ming", 16
print("%s: %d" % (name, age))
print("{}: {}".format(name, age))
print(f"{name}: {age}")
```

### 📌 课堂练习

输入两个整数，输出和、差、积；再输入姓名和分数，用 f-string 输出信息。思考 `input()` 输入 `3 + 5` 时会得到什么。

---

## 3. 运算符与表达式

### 3.1 算术运算

| 运算符 | 含义 | 示例结果 |
|---|---|---|
| `+`、`-`、`*` | 加、减、乘 | `3 + 5` → 8 |
| `/` | 普通除法 | `7 / 2` → 3.5 |
| `//` | 向下取整的除法 | `7 // 2` → 3；`-7 // 2` → -4 |
| `%` | 余数 | `7 % 2` → 1；`-7 % 2` → 1 |
| `**` | 幂 | `2 ** 3` → 8 |

整数输入的 `/` 也得到浮点结果；`//` 若操作数包含浮点数，结果也可能是浮点类型。除数不能为 0。

```python
a, b = 17, 5
print(a // b, a % b)  # 3 2
print(a == (a // b) * b + a % b)  # True
```

与 C++ / Java 不同，Python 的负数整除向下取整，不是向 0 截断。整数与非零整数取余时，非零余数与除数同号。

```python
x = 1234
print(x % 10)   # 4：假设 x 非负
print(x // 10)  # 123
```

### 3.2 赋值与复合赋值

```python
count = 0
count += 1
count *= 3
count -= 1
print(count)  # 2
```

还有 `/=`、`//=`、`%=`、`**=`。Python 没有 C++ 风格的自增、自减运算符；使用 `count += 1`。可变容器的 `+=` 可能原地修改，与普通重新绑定存在区别。

### 3.3 比较运算

`==`、`!=`、`<`、`<=`、`>`、`>=` 用于普通值比较。`=` 是赋值；不等于使用 `!=`，不是 `<>`。

```python
score = 85
print(0 <= score <= 100)  # True：支持连续比较
print("AI" == "ai")      # False：区分大小写
```

### 3.4 逻辑运算与短路

```python
age, has_ticket = 16, True
can_enter = age >= 12 and has_ticket
print(can_enter)             # True
print(age < 12 or has_ticket) # True
print(not has_ticket)        # False
```

使用 `and`、`or`、`not`，不是 `&&`、`||`、`!`。

| x | y | x and y | x or y | not x |
|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 0 | 1 | 1 |
| 1 | 0 | 0 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 |

表中用 0 / 1 表示假 / 真。实际布尔值显示为 `False` / `True`。

```python
n = 0
if n != 0 and 10 / n > 2:
    print("满足条件")
```

`and` 左侧为假时，不再计算右侧；`or` 左侧为真时，不再计算右侧。

`0`、`0.0`、空字符串、空容器、`None` 通常为假。`and` / `or` 返回某个操作数，不保证返回 `bool`：

```python
print(10 and 20)  # 20
print(10 or 20)   # 10
print(not 10)     # False
```

### 3.5 成员与身份判断

```python
labels = [0, 1, 1]
print(1 in labels)       # True
print(2 not in labels)   # True
print("AI" in "Learn AI") # True：检查子串

a = [1, 2]
b = [1, 2]
c = a
print(a == b)  # True：值相同
print(a is b)  # False：不同对象
print(a is c)  # True：同一个对象
result = None
print(result is None)  # True
```

`is` / `is not` 判断对象身份；数字、字符串的值比较使用 `==`。不要通过小整数对象缓存推导身份规则。

### 3.6 位运算

```python
a, b = 60, 13
print(a & b)   # 12：按位与
print(a | b)   # 61：按位或
print(a ^ b)   # 49：按位异或
print(~a)      # -61
print(a << 2)  # 240
print(a >> 2)  # 15
```

二进制整数写成 `0b00111100`，不能直接写带空格的 `0011 1100`。Python 整数不是固定 8 位；`~x == -x - 1`。若只想取反最低 8 位，可以使用 `(~x) & 0xff`。左移不会按固定整数位宽自动丢弃高位。

位运算 `&` / `|` 与布尔逻辑 `and` / `or` 是不同操作；NumPy 数组使用元素级条件时还需特别注意括号，见第 12 章。

### 3.7 常用优先级

从高到低的常用子集：

| 顺序 | 运算 |
|---|---|
| 1 | 括号中的表达式 |
| 2 | `**` |
| 3 | 一元 `+`、`-`、`~` |
| 4 | `*`、`/`、`//`、`%` |
| 5 | `+`、`-` |
| 6 | `<<`、`>>` |
| 7–9 | `&`，然后 `^`，然后 `\|` |
| 10 | 比较、`in` / `not in`、`is` / `is not` |
| 11–13 | `not`，然后 `and`，然后 `or` |

这是常用子集，不是完整语法表。普通赋值语句 `=` 不属于这里的表达式优先级。幂与一元符号有特殊结合规则：

```python
print(-2 ** 2)    # -4
print((-2) ** 2)  # 4
print(2 ** -2)    # 0.25
print(2 ** 3 ** 2) # 512：按 2 ** (3 ** 2) 计算
```

混合运算优先加括号，使意图清楚。

### 3.8 浮点数与常用数学工具

```python
import math

print(abs(-5))              # 5
print(min(3, 7), max(3, 7))  # 3 7
print(math.sqrt(9))         # 3.0
print(math.floor(-2.3))     # -3
print(math.ceil(2.3))       # 3
print(math.isclose(0.1 + 0.2, 0.3))  # True
```

浮点数采用有限精度，`0.1 + 0.2 == 0.3` 为 `False`。按任务设置容差；比较接近 0 的值时还需考虑 `abs_tol`。`round` 不是始终“四舍五入”，恰好中点时采用向偶数舍入，且浮点表示会影响结果。

### 📌 课堂练习

1. 解释 `-9 // 2`、`-9 % 2` 和 `int(-9 / 2)` 的结果。
2. 写出判断 `x` 属于 `[0, 5]` 或 `[10, 15]` 的条件。
3. 判断两个列表是否内容相同，并说明为何不使用 `is`。

---

## 4. 条件判断

### 4.1 if、elif、else

```python
num = int(input())
if num > 0:
    print("正数")
elif num < 0:
    print("负数")
else:
    print("零")
```

一组 `if / elif / else` 最多执行一个分支；多个独立 `if` 可能执行多个分支。

### 4.2 条件顺序与嵌套

```python
score = 85
if not 0 <= score <= 100:
    print("分数无效")
elif score >= 90:
    print("A")
elif score >= 80:
    print("B")
elif score >= 60:
    print("C")
else:
    print("未通过")
```

从高分向低分检查。若先写 `score >= 60`，85 会提前进入该分支。

### 4.3 条件表达式与 pass

```python
score = 85
label = 1 if score >= 60 else 0
print(label)  # 1
```

复杂规则使用普通分支。

`pass` 是占位语句，什么也不做；代码块暂时为空时可以使用。

### 4.4 AI 衔接：手工规则分类

```python
hours, attendance = 4.0, 0.9
if hours >= 3 and attendance >= 0.8:
    prediction = 1
else:
    prediction = 0
print(prediction)  # 1
```

这里的规则由人指定，可用于练习分类程序。决策树模型通常从训练数据学习划分规则，两者不要混淆。

### 📌 课堂练习

根据学习时长和出勤率预测标签。测试时长 2.9、3.0、3.1 以及出勤率 0.79、0.80、0.81，说明边界是否包含。

---

## 5. 循环与循环控制

### 5.1 for 与 range

```python
for i in range(3):
    print(i)  # 依次输出 0、1、2

for i in range(2, 7, 2):
    print(i)  # 2、4、6

for i in range(5, 0, -1):
    print(i)  # 5、4、3、2、1
```

`range(start, stop, step)` 包含起点、不包含终点；默认起点 0、步长 1；步长不能为 0。方向与步长不一致时可得到空范围。

Python 的 `for` 遍历可迭代对象，不限于数字范围：

```python
fruits = ["banana", "apple", "mango"]
for fruit in fruits:
    print(fruit)
```

### 5.2 累加、计数与最大值

```python
nums = [2, 5, -1, 8]
total = 0
positive_count = 0
largest = nums[0]  # 假设列表非空
for x in nums:
    total += x
    if x > 0:
        positive_count += 1
    if x > largest:
        largest = x
print(total, positive_count, largest)  # 14 3 8
```

先掌握循环实现，再学习 `sum`、`max` 等工具。列表可能全为负数时，不要把最大值初始化为 0。

### 5.3 while

```python
count = 0
while count < 3:
    print(count)
    count += 1
```

循环前检查条件；条件最初为假时执行 0 次。更新变量时应能逐渐接近结束条件。

### 5.4 break 、pass与 continue

```python
for x in [2, -1, 0, 5, 8]:
    if x < 0:
        continue  # 跳过当前这一轮
        #pass 不执行任何操作
    if x == 5:
        break     # 结束当前循环
    print(x)      # 输出 2、0
```

`break` 只跳出最内层循环。`while` 中若更新语句放在 `continue` 后面，可能被反复跳过而导致死循环。手动停止终端程序通常使用 Ctrl+C。

### 5.5 循环的 else

```python
n = 17
if n < 2:
    print("不是质数")
else:
    for divisor in range(2, n):
        if n % divisor == 0:
            print("不是质数")
            break
    else:
        print("是质数")
```

循环正常结束、没有因 `break` 退出时，执行对应的 `else`；不是“循环条件为假就属于 else 分支”的普通 if 结构。`while` 也支持该写法。

### 5.6 嵌套循环与真值表

```python
print("x y and or not_x")
for x in [False, True]:
    for y in [False, True]:
        print(int(x), int(y), int(x and y), int(x or y), int(not x))
```

外层每运行一轮，内层完整遍历一次。该结构可用于枚举命题的所有真假组合。

### 5.7 原讲义项目：猜数字

```python
import random

answer = random.randint(1, 100)  # 两端都包含
attempts = 0
while True:
    guess = int(input("猜一个 1–100 的整数："))
    attempts += 1
    if guess < answer:
        print("猜小了")
    elif guess > answer:
        print("猜大了")
    else:
        print(f"猜对了！共尝试 {attempts} 次")
        break
```

本版本假设输入为整数；第 10 章学完异常后，再增加无效输入处理。讨论如何每次将可能范围缩小约一半。

### 📌 课堂练习

1. 计算 1 到 100 的整数和。
2. 输出 1 到 20 中能被 3 整除的数。
3. 枚举三种布尔变量的 8 组组合，计算 `(x and y) or not z`。
4. 在猜数字程序中增加最多 7 次有效猜测的限制。

---

## 6. 字符串与列表

### 6.1 字符串创建与转义

```python
word = 'Python'
sentence = "Learn AI"
paragraph = """第一行
第二行"""
print("A\nB")          # 换行
print("A\tB")          # 制表符
print("She said \"Hi\"")
print(r"A\nB")         # 输出 A\nB，反斜杠保留
```

单引号与双引号都创建字符串。`\n` 是换行、`\t` 是制表符、`\\` 表示一个反斜杠。原始字符串 `r"..."` 常用于路径或正则表达式，但不能以奇数个反斜杠结束。

### 6.2 索引与切片

```python
text = "123456789"
print(text[0])      # 1
print(text[-1])     # 9
print(text[2:5])    # 345
print(text[2:])     # 3456789
print(text[:3])     # 123
print(text[1:5:2])  # 24
print(text[:-1])    # 12345678
print(text[::-1])   # 987654321
```

索引从 0 开始；负下标从末尾计算。切片 `sequence[start:stop:step]` 不包含终点，步长不能为 0。单个下标越界会报错，切片超出范围通常会自动截到有效范围。

Python 没有独立 `char` 类型，`text[0]` 仍是长度为 1 的字符串。

### 6.3 拼接、重复与不可变性

```python
text = "AI"
print(text + " course")  # AI course
print(text * 3)          # AIAIAI
print("Hello " "world")  # 相邻字符串字面量自动拼接
text = "a" + text[1:]
print(text)              # aI
```

字符串不可原地修改，不能写 `text[0] = "a"`。重新给名字赋值与修改原对象是不同操作。

### 6.4 常用字符串方法

```python
text = "  AI,Python,AI  "
clean = text.strip()
parts = clean.split(",")
print(parts)                    # ['AI', 'Python', 'AI']
print(" / ".join(parts))         # AI / Python / AI
print(clean.lower())             # ai,python,ai
print(clean.upper())             # AI,PYTHON,AI
print(clean.replace("AI", "ML")) # ML,Python,ML
print(clean.find("Python"))      # 3；找不到返回 -1
print(clean.count("AI"))         # 2
print(clean.startswith("AI"))    # True
print(clean.endswith("AI"))      # True
```

| 工具 | 说明 |
|---|---|
| `len(s)` | 字符串长度 |
| `strip()` | 去除两端空白；不会去除中间空白 |
| `split()` | 不传参数时按连续空白拆分 |
| `split(",")` | 按指定分隔符拆分，可能包含空字符串 |
| `join(items)` | 用指定分隔符连接字符串序列 |
| `find(t)` / `index(t)` | 查找位置；前者失败返回 -1，后者失败抛异常 |
| `isdigit()` | 检查数字字符，不是通用数字解析器；不能识别 `-3`、`3.5` |

字符串方法一般返回新值，不修改原字符串；需要保存结果时写 `text = text.strip()`。

### 6.5 列表的创建、读取与修改

```python
scores = [80, 90, 75]
scores[0] = 85
scores.append(95)
print(scores)      # [85, 90, 75, 95]
print(scores[1:3]) # [90, 75]
print(len(scores)) # 4
```

列表可以混合类型，但一组数值样本通常使用相同类型。列表是 Python 内置序列，不等同于 NumPy 数组。

| 操作 | 功能 | 注意事项 |
|---|---|---|
| `append(x)` | 末尾添加一个对象 | `append([1, 2])` 添加嵌套列表 |
| `extend(items)` | 逐项追加 | `extend([1, 2])` 添加两个元素 |
| `insert(i, x)` | 指定位置插入 | 后续元素需要移动 |
| `pop()` / `pop(i)` | 删除并返回元素 | 空列表或无效下标会报错 |
| `remove(x)` | 删除第一个等于 x 的元素 | 不存在时抛异常 |
| `del a[i]` / `del a[l:r]` | 删除下标或切片 | 不返回被删除对象 |
| `clear()` | 清空 | 修改原列表 |
| `count(x)` / `index(x)` | 统计个数 / 查位置 | `index` 找不到会抛异常 |
| `reverse()` | 原地反转 | 返回 `None` |
| `sort()` | 原地排序 | 返回 `None`；排序见第 9 章 |
| `copy()` / `a[:]` | 浅复制 | 嵌套可变对象仍共享 |

### 6.6 常用统计与遍历

```python
nums = [2, 4, 6]
print(sum(nums))                 # 12
print(min(nums), max(nums))      # 2 6
print(sum(nums) / len(nums))     # 4.0，假设非空
for i, value in enumerate(nums):
    print(i, value)

for i in range(len(nums)):
    nums[i] *= 2
print(nums)                     # [4, 8, 12]
```

`sum([])` 为 0；`min([])`、`max([])` 会报错。`for value in nums: value *= 2` 不会把整数结果写回列表。遍历时不要直接删除同一个列表的元素，容易跳过元素；使用筛选生成新列表。

### 6.7 深复制与浅复制

```python
a = [1, 2]
b = a
c = a.copy()
b.append(3)
print(a)  # [1, 2, 3]
print(c)  # [1, 2]
```

`b = a` 没有复制列表。对于二维列表，`a.copy()` 只复制外层；需要各层独立时可以按结构逐层复制，或使用 `copy.deepcopy`。

### 6.8 二维列表

```python
rows, cols = 2, 3
grid = [[0 for _ in range(cols)] for _ in range(rows)]
grid[0][0] = 1
print(grid)  # [[1, 0, 0], [0, 0, 0]]
for row in grid:
    for value in row:
        print(value, end=" ")
    print()
```

这里使用列表推导式，第 9 章进一步说明。简写 `[[0] * cols for _ in range(rows)]` 也正确；**不要使用 `[[0] * cols] * rows`**，它会让多行引用同一个内层列表。

### 📌 课堂练习

1. 清理 `"  Python, AI, Data  "`，得到 `['python', 'ai', 'data']`。
2. 求非空分数列表的平均值、最高分及及格人数。
3. 创建 3 行 2 列的独立二维列表，只修改第 2 行第 1 列。

---

## 7. 元组、字典与集合

### 7.1 元组：tuple

```python
point = (3, 5)
x, y = point
single = (3,)  # 一个元素需要逗号
print(x, y, single)
print(point[0], point[:1])  # 3 (3,)
```

元组支持索引、切片、遍历、拼接和重复。不能替换元素，不代表名字永远不能重新赋值；元组内部若包含列表，该列表仍可以修改。

### 7.2 字典：dict

```python
sample = {"hours": 4.0, "attendance": 0.9, "label": 1}
print(sample["hours"])            # 4.0
sample["hours"] = 4.5
sample["id"] = 101
print(sample.get("score", 0))      # 0：缺失时返回默认值
print("label" in sample)           # True：检查键
```

Python 3.7+ 字典保持插入顺序，不会像 C++ `map` 一样自动按键排序。

键必须可哈希；字符串、整数、只包含可哈希元素的元组常可作键。列表、字典、集合不能直接作键。键唯一，重复赋值会覆盖值。

```python
for key, value in sample.items():
    print(key, value)
print(list(sample.keys()))
print(list(sample.values()))
removed_id = sample.pop("id")
print(removed_id)  # 101
```

不存在的键用 `sample[key]` 读取会产生 `KeyError`；`get` 不会把默认值自动插入字典。也可使用 `del sample[key]` 删除键值对。

### 7.3 频率统计

```python
labels = [1, 0, 1, 1, 0]
counts = {}
for label in labels:
    counts[label] = counts.get(label, 0) + 1
print(counts)  # {1: 3, 0: 2}
```

AI 衔接：检查类别是否不平衡。统计词频也可使用相同结构。

### 7.4 集合：set

```python
a = {1, 2, 3}
b = {3, 4}
a.add(5)
a.discard(2)
print(sorted(a & b))  # [3]：交集
print(sorted(a | b))  # [1, 3, 4, 5]：并集
print(sorted(a - b))  # [1, 5]：差集
print(sorted(a ^ b))  # [1, 4, 5]：对称差
print(len(set([1, 1, 2])))  # 2
```

集合不保留用于序列访问的顺序，不能用下标读取；需要稳定显示时使用 `sorted`。空集合是 `set()`，`{}` 是空字典。

`remove(x)` 在元素不存在时抛异常，`discard(x)` 不会。集合元素必须可哈希；不可变集合 `frozenset` 可用于需要可哈希集合的场景。

### 7.5 如何选择容器

| 需求 | 首选 | AI 相关示例 |
|---|---|---|
| 有顺序、需要修改 | `list` | 样本列表、预测标签 |
| 固定字段的位置组合 | `tuple` | 坐标、多个返回值 |
| 按名字读取属性 | `dict` | 样本记录、参数表、词频 |
| 去重、检查是否存在 | `set` | 不重复标签、词汇表 |

### 📌 课堂练习

统计 `['cat', 'dog', 'cat', 'bird']` 的频率，输出不同类别的数量。解释检查字典成员时检查的是键还是值。

---

## 8. 函数与参数

### 8.1 定义、调用与返回

```python
def add(a, b):
    """返回两个数的和。"""
    return a + b

result = add(3, 5)
print(result)  # 8
```

`a`、`b` 是形参，3、5 是实参。`return` 把值交给调用者并立即结束函数。函数必须在执行调用之前已被定义。

### 8.2 print 与 return 的区别

```python
def show_sum(a, b):
    print(a + b)

result = show_sum(3, 5)  # 屏幕输出 8
print(result)           # None
```

没有显式返回值的函数返回 `None`。输出值不等于返回值；用于进一步计算的函数通常使用 `return`。

### 8.3 默认参数与关键字参数

```python
def predict(hours, threshold=3.0):
    return int(hours >= threshold)

print(predict(4))                      # 1
print(predict(4, threshold=5))         # 0
print(predict(threshold=2, hours=1))   # 0
```

普通调用中位置实参放在关键字实参之前；默认参数后面不能直接接没有默认值的普通位置参数。

### 8.4 多个返回值与类型提示

```python
def summarize(values):
    if not values:
        raise ValueError("列表不能为空")
    return sum(values) / len(values), max(values)

average, largest = summarize([2.0, 4.0, 6.0])
print(average, largest)
#给一个列表[1,2,3..,10] 调用一个函数返回相加值以及最大值
```

多个返回值实际打包为元组。类型提示帮助读者和编辑器理解代码，**不会自动转换或强制校验参数**。`raise` 的作用见第 10 章。

### 8.5 作用域

```python
threshold = 3.0

def predict(hours):
    return int(hours >= threshold)  # 可以读取外部变量

print(predict(4))
```

函数内赋值通常创建局部变量，不能因此自动修改同名全局变量。确需重新绑定全局名字可使用 `global`；本课程优先把需要的值作为参数传入。闭包中重新绑定外层函数名字可使用 `nonlocal`，作为选学。

Python 的普通 `if` / `for` 不建立 C++ 风格的独立块作用域，但函数和类有各自的作用域规则。

### 8.6 参数绑定与可变对象

```python
def change_number(x):
    x = 99

def add_item(items):
    items.append(99)

n = 1
nums = [1]
change_number(n)
add_item(nums)
print(n)     # 1
print(nums)  # [1, 99]
```

实参对象绑定到形参名字。重新绑定形参不会重新绑定调用者的名字；修改共享的可变对象则能被调用者观察到。不要直接套用 C++ 的引用参数规则。

### 8.7 默认可变参数陷阱

正确写法：

```python
def collect(value, items=None):
    if items is None:
        items = []
    items.append(value)
    return items

print(collect(1))  # [1]
print(collect(2))  # [2]
```

不要把默认列表写成 `items=[]`，因为默认对象在定义函数时创建一次，之后调用可能共享它。

### 8.8 可变参数与解包（选学）

```python
def total(*values):
    return sum(values)

def describe(**fields):
    return fields

nums = [1, 2, 3]
print(total(*nums))                  # 6
print(describe(name="AI", size=10))  # {'name': 'AI', 'size': 10}
```

形参中 `*args` 收集额外位置实参为元组，`**kwargs` 收集额外关键字实参为字典；调用中 `*`、`**` 用于展开序列和映射。

### 8.9 递归（选学）

```python
def factorial(n):
    if n < 0:
        raise ValueError("n 必须非负")
    if n <= 1:
        return 1
    return n * factorial(n - 1)

print(factorial(5))  # 120
```

必须有结束条件，并向结束条件推进。Python 有递归深度限制；本例仅用于小规模教学，普通累乘也可用循环。

### 📌 课堂练习

实现 `accuracy(y_true, y_pred)`，返回正确预测数除以总数。约定两列表等长且非空，否则抛出 `ValueError`。不要在计算函数里直接输出。

---

## 9. 推导式、排序与常用工具

### 9.1 列表、字典与集合推导式

```python
nums = [1, 2, 3, 4]
squares = [x ** 2 for x in nums]
evens = [x for x in nums if x % 2 == 0]
labels = [1 if x >= 3 else 0 for x in nums]
square_map = {x: x ** 2 for x in nums}
remainders = {x % 2 for x in nums}
print(squares, evens, labels)
```

`[表达式 for 变量 in 数据 if 筛选条件]` 将符合条件的元素处理后放入新列表。表达式中的 `if ... else ...` 决定值，后面的 `if` 决定是否保留元素。刚开始学习时先写普通循环，再改成推导式。

### 9.2 enumerate 与 zip

```python
names = ["A", "B", "C"]
scores = [80, 90, 85]
for index, name in enumerate(names, start=1):
    print(index, name)
for name, score in zip(names, scores):
    print(name, score)
```

`enumerate` 同时提供序号和元素；`zip` 同步遍历多组数据。默认 `zip` 在最短一组结束时停止。必须长度一致的标签评估，应先检查长度，或使用 Python 3.10+ 的 `zip(..., strict=True)`。

### 9.3 sorted 与 sort

```python
nums = [3, 1, 2]
ordered = sorted(nums)
print(nums, ordered)  # [3, 1, 2] [1, 2, 3]
nums.sort(reverse=True)
print(nums)           # [3, 2, 1]
```

`sorted` 返回新列表，`list.sort` 修改原列表并返回 `None`。不要写 `nums = nums.sort()`。

### 9.4 lambda 与自定义排序

```python
students = [
    {"id": 1, "score": 80},
    {"id": 3, "score": 90},
    {"id": 2, "score": 90},
]
ordered = sorted(students, key=lambda student: (-student["score"], student["id"]))
print([student["id"] for student in ordered])  # [2, 3, 1]
```

`lambda 参数: 表达式` 创建简短函数。`key` 返回排序依据，不是 C++ 中比较两个对象的 `cmp`。上例先按分数降序，再按编号升序；排序是稳定的。

### 9.5 any、all 与生成器表达式

```python
nums = [1, 2, -3]
print(any(x < 0 for x in nums))   # True
print(all(x >= 0 for x in nums)) # False
print(sum(x ** 2 for x in nums)) # 14
```

圆括号形式可创建生成器表达式，按需产生结果，不预先建立完整列表。`all([])` 为 `True`，`any([])` 为 `False`；验证数据时还要单独检查是否为空。

### 9.6 map、filter 与迭代器（了解）

```python
nums = list(map(int, ["1", "2", "3"]))  #把string转化成int
positive = list(filter(lambda x: x > 0, [-1, 0, 2]))
iterator = iter(nums)
print(next(iterator))  # 1
print(positive)        # [2]
```

`map`、`filter`、`zip` 返回的迭代器通常不能靠下标访问，遍历后会被消耗。需要重复访问时可以用 `list(...)` 保存。编写简单筛选时通常优先推导式。

### 9.7 常用标准库补充（按需查阅）

```python
from collections import Counter, deque
from bisect import bisect_left, bisect_right#第一个大于或等于目标值的位置与第一个严格大于目标值的位置
import heapq

print(Counter([1, 0, 1]))  # Counter({1: 2, 0: 1})
queue = deque([1, 2])
queue.append(3)
print(queue.popleft())    # 1
ordered = [1, 2, 2, 4]
print(bisect_left(ordered, 2), bisect_right(ordered, 2))  # 1 3
heap = [3, 1, 2]
heapq.heapify(heap)
print(heapq.heappop(heap)) # 1：最小堆
```

`bisect_left` 对应查找第一个不小于目标值的位置，`bisect_right` 对应第一个大于目标值的位置；这里要求序列升序。返回插入位置，不保证目标存在。

### 📌 课堂练习

对样本字典列表筛选 `hours >= 3` 的样本，再按出勤率降序排列。保留原列表不变。

---

## 10. 模块、文件与异常

### 10.1 导入模块

```python
import math
from random import randint
import random as rnd

print(math.sqrt(16))
print(randint(1, 3))
print(rnd.choice(["A", "B", "C"]))
```

`import 模块`、`from 模块 import 名字`、`as 别名` 是常见形式。不要把文件命名为 `random.py`、`math.py`、`numpy.py` 等，否则可能遮蔽同名库。

### 10.2 自己的模块与程序入口

可以将预测函数写入 `tools.py`，在同目录的其他文件使用 `from tools import predict`。

```python
def predict(hours):
    return int(hours >= 3)

def main():
    print(predict(4))

if __name__ == "__main__":
    main()
```

直接运行文件时执行 `main`；被导入时不执行这段入口代码。Python 不强制要求 `main`，但此结构有助于组织项目。

### 10.3 第三方库与虚拟环境

在终端运行，不要放进 Python 源文件：

```bash
python3 -m venv .venv
```

macOS / Linux 激活：

```bash
source .venv/bin/activate
```

Windows PowerShell 激活方式通常为 `.venv\Scripts\Activate.ps1`。若环境禁止运行激活脚本，可以直接调用虚拟环境中的 Python。

激活后安装本讲义衔接部分所需库：

```bash
python -m pip install numpy pandas
```

VS Code 也应选择该虚拟环境。标准库如 `math`、`csv`、`json` 无需单独安装。

### 10.4 文本文件与 with

```python
with open("notes.txt", "w", encoding="utf-8") as file:
    file.write("Python\nAI\n")

with open("notes.txt", "r", encoding="utf-8") as file:
    for line in file:
        print(line.rstrip("\n"))
```

`r` 读取，`w` 写入并覆盖已有内容，`a` 追加；`b` 表示二进制模式。`with` 离开代码块时关闭文件。相对路径相对于程序的当前工作目录，不一定是源文件目录。

### 10.5 CSV：数据表

CSV 文件内容示例：

```csv
hours,attendance,label
4,0.9,1
1,0.5,0
```

完整写入并读取示例：

```python
import csv

#newline="" 要求python不自动转换写入的换行符，csv.writer 默认用 \r\n 结束一条记录，\r\n -> \r\r\n
with open("samples.csv", "w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file)
    writer.writerow(["hours", "attendance", "label"])
    writer.writerows([[4, 0.9, 1], [1, 0.5, 0]])

samples = []
with open("samples.csv", newline="", encoding="utf-8") as file:
    for row in csv.DictReader(file):
        samples.append({
            "hours": float(row["hours"]),
            "attendance": float(row["attendance"]),
            "label": int(row["label"]),
        })
print(samples)
```

CSV 读取的单元格先是字符串，必须按数据含义转换。不要只用 `split(",")` 解析任意 CSV，因为带引号的字段本身可能含逗号或换行。

### 10.6 JSON：结构化数据

```python
import json

config = {"threshold": 3.0, "name": "规则模型"}
with open("config.json", "w", encoding="utf-8") as file:
    json.dump(config, file, ensure_ascii=False, indent=2)

with open("config.json", encoding="utf-8") as file:
    loaded = json.load(file)
print(loaded["threshold"])  # 3.0
```

`dump` / `load` 面向文件；`dumps` / `loads` 面向字符串。JSON 中的 `true`、`false`、`null` 对应 Python 的 `True`、`False`、`None`。

### 10.7 try、except、else、finally、raise

```python
try:
    value = int(input("请输入整数："))
except ValueError:
    print("输入不是有效整数")
else:
    print(value * 2)
finally:
    print("本次处理结束")
```

`except` 处理匹配的异常，`else` 在 try 正常完成时执行，`finally` 用于清理等工作。应捕获能处理的具体异常，不要用空的 `except: pass` 隐藏问题。

```python
def average(values):
    if not values:
        raise ValueError("不能计算空列表平均值")
    return sum(values) / len(values)
```

### 10.8 常见错误与调试

| 错误 | 常见原因 | 检查方式 |
|---|---|---|
| `SyntaxError` | 引号、括号、冒号错误 | 先看报错位置附近 |
| `IndentationError` | 缩进不一致 | 统一 4 个空格 |
| `NameError` | 名字未定义 | 检查拼写、作用域、执行顺序 |
| `TypeError` | 类型不匹配 | 如字符串与整数直接相加 |
| `ValueError` | 值无法转换或不满足要求 | 如 `int("abc")` |
| `IndexError` | 下标越界 | 检查长度和下标 |
| `KeyError` | 字典键缺失 | 检查字段名或使用 `get` |
| `ZeroDivisionError` | 除数为 0 | 检查样本数量等 |
| `FileNotFoundError` | 文件路径错误 | 检查当前工作目录 |
| `ModuleNotFoundError` | 环境中没有模块 | 检查所选解释器及安装环境 |

从 traceback 最后一行确认错误类型，再向上定位自己的代码。使用 `print(type(x), repr(x))`、断点与小样例检查中间值。

```python
assert 2 + 3 == 5
```

`assert` 可用于调试和测试；不要用它代替必须执行的输入校验，因为优化模式可能禁用断言。

### 📌 课堂练习

让猜数字程序在输入 `abc` 时提示后继续，且不计入有效猜测次数。读取 CSV，检查 `hours >= 0`、`0 <= attendance <= 1`、`label` 为 0 或 1。

---

## 11. 类与对象：为 AI 工具调用作准备

### 11.1 属性、方法与初始化

```python
class RuleClassifier:
    def __init__(self, threshold=3.0):
        self.threshold = threshold

    def predict_one(self, hours):
        return int(hours >= self.threshold)

    def predict(self, values):
        return [self.predict_one(x) for x in values]

model = RuleClassifier(threshold=3.0)
print(model.threshold)            # 3.0
print(model.predict([1, 3, 5]))   # [0, 1, 1]
```

类定义对象的结构与行为；对象是类的实例。`__init__` 初始化实例属性；实例方法的第一个形参通常写 `self`，调用时由 Python 自动传入实例。

`predict_one` 是方法；独立定义的 `predict_one(...)` 可以是函数。`model.predict(...)` 表示通过对象调用方法。

### 11.2 实例属性与类属性

```python
class Sample:
    category = "training"  # 类属性

    def __init__(self, label):
        self.label = label
        self.features = []  # 每个实例自己的列表

a = Sample(0)
b = Sample(1)
a.features.append(3)
print(a.features, b.features)  # [3] []
```

各实例需要独立的数据应在 `__init__` 中创建，避免把共享列表误放为类属性。

### 11.3 继承与特殊方法（选学）

```python
class StrictClassifier(RuleClassifier):
    def __init__(self):
        super().__init__(threshold=5.0)

    def __repr__(self):
        return f"StrictClassifier(threshold={self.threshold})"

model = StrictClassifier()
print(model)
print(model.predict([3, 5]))  # [0, 1]
```

需要先执行本章 11.1 的类定义。继承可复用父类行为，`super()` 用于调用父类方法。`__repr__` 定义便于调试的对象表示；不需要先背完整特殊方法列表。

后续机器学习库常见 `model.fit(X, y)`、`model.predict(X)`：前者训练，后者预测。本章类只是人工规则，没有实现数据训练。

### 📌 课堂练习

给 `RuleClassifier` 增加 `score(values, labels)` 方法，调用自己的 `predict` 和第 8 章准确率函数。

---

## 12. AI 数据工具衔接：NumPy 与 Pandas

> NumPy 主要用于数值和数组计算，Pandas 主要用于处理表格数据

### 12.1 list 与 NumPy 数组

```python
import numpy as np

values = [1, 2, 3]
array = np.array(values, dtype=float) #将 values 转换成 NumPy 数组，并指定数组元素为浮点数（float）
print(values * 2)  # [1, 2, 3, 1, 2, 3]：重复
print(array * 2)   # [2. 4. 6.]：元素级乘法
print(array + 1)   # [2. 3. 4.]
```

NumPy 数组常用于同类数值数据，支持向量化运算。NumPy 整数类型通常有固定宽度，与 Python 内置 `int` 不同。

### 12.2 形状、维度与数据类型

```python
import numpy as np

X = np.array([[1.0, 0.5], [4.0, 0.9], [2.0, 0.7]])
y = np.array([0, 1, 0])
print(X.shape)  # (3, 2)：3 个样本、每个 2 个特征
print(X.ndim)   # 2
print(X.size)   # 6：元素总数
print(y.shape)  # (3,)
print(X.dtype)
```

通常约定 `X` 的形状为 `(样本数, 特征数)`，`y` 为 `(样本数,)`。`(3,)` 与 `(3, 1)` 不同，错误形状可能导致意外广播。

### 12.3 索引、切片与掩码

```python
import numpy as np

X = np.array([[1.0, 0.5], [4.0, 0.9], [2.0, 0.7]])
print(X[0, 1])          # 0.5
print(X[:, 0])         # [1. 4. 2.]：第一列
print(X[0:2, :])       # 前两个样本
mask = (X[:, 0] >= 3) & (X[:, 1] >= 0.8)
print(X[mask])         # [[4.  0.9]]
```

数组的元素级逻辑使用 `&`、`|`、`~`，每个比较要用括号；不能用普通 `and` 判断多元素数组。

NumPy 基本切片通常得到视图，会共享原数据；布尔或整数高级索引通常得到副本。需要明确独立的数据时使用 `.copy()`。

### 12.4 求和、均值与 axis

```python
import numpy as np

X = np.array([[1.0, 2.0], [3.0, 4.0]])
print(X.sum())         # 10.0
print(X.mean(axis=0))  # [2. 3.]：沿样本方向，对每列求均值
print(X.mean(axis=1))  # [1.5 3.5]：对每行求均值
print(np.zeros((2, 3)))
print(np.ones(3))
print(np.arange(0, 6, 2))  # [0 2 4]
print(np.arange(6).reshape(2, 3)) #先生成 0～5 这 6 个整数，再排列成 2 行、3 列的数组
```

`reshape` 必须保持元素总数一致。`axis` 指被聚合的轴；不要只机械记忆“行/列”，要结合数组形状理解。

### 12.5 广播、点积与矩阵乘法

```python
import numpy as np

X = np.array([[1.0, 2.0], [3.0, 4.0]])
w = np.array([0.5, -0.2])
b = 0.1
z = X @ w + b #[0.1 0.7] + b 广播
print(z)  # [0.2 0.8]
print(X * X)  # 元素级乘法，不是矩阵乘法
```

`@` 是矩阵乘法；二维 `X` 与一维 `w` 相乘时，每行与权重向量做点积。标量 `b` 广播到每个结果。一般广播从末尾维度对齐，维度相同或其中之一为 1 才兼容。

**AI 衔接：** `z = X @ w + b` 是线性打分的常见表达式。此例权重由人给定，没有训练模型。

### 12.6 特征缩放与零分母

```python
import numpy as np

X = np.array([[1.0, 5.0], [3.0, 5.0], [5.0, 5.0]]) 
minimum = X.min(axis=0) # [1. 5.]
span = X.max(axis=0) - minimum # 得到 [4. 0.]
safe_span = np.where(span == 0, 1.0, span) #np.where(条件, 条件成立时的值, 不成立时的值)
scaled = (X - minimum) / safe_span
print(scaled)  # 第一列为 0、0.5、1；常数列为 0
"""
[[0.  0. ]
 [0.5 0. ]
 [1.  0. ]]
"""
```

正式实验中先划分训练集与测试集，仅在训练集上计算缩放参数，再用于测试集，避免数据泄漏。

### 12.7 Pandas 数据表

```python
import pandas as pd

df = pd.DataFrame({
    "hours": [4.0, 1.0, 3.0],
    "attendance": [0.9, 0.5, 0.8],
    "label": [1, 0, 1],
})
print(df.head())  #head() 默认显示前 5 行
print(df.shape)   # (3, 3)
print(df.dtypes)  # 数据类型
print(df["label"].value_counts()) #统计各标签的数量
selected = df.loc[df["hours"] >= 3, ["hours", "label"]]  #df.loc[选哪些行, 选哪些列]
print(selected)
print(df.iloc[0])                     # 按位置取第一行
X = df[["hours", "attendance"]].to_numpy(dtype=float)  #选取两列特征，再转换为浮点 NumPy 数组
y = df["label"].to_numpy(dtype=int)  #取出标签列，转换成整数 NumPy 数组
print(X.shape, y.shape)               # (3, 2) (3,)
```

`df["hours"]` 为一列 `Series`；`df[["hours"]]` 为一列表格。`loc` 按标签或布尔条件选择，`iloc` 按整数位置选择。

读取第 10 章创建的 CSV：

```python
import pandas as pd

df = pd.read_csv("samples.csv")
print(df.isna().sum())  # 每列缺失值数量
clean = df.dropna(subset=["hours", "attendance", "label"])  #删除指定列中存在缺失值的行
print(clean)
```

不能只依赖自动推断：检查字段、数据类型、取值范围和缺失值。删除行仅是课堂处理示例；正式项目应根据缺失原因选择策略，并记录对样本数量和类别分布的影响。

### 12.8 随机数与可复现性

```python
import numpy as np
#打乱样本顺序、划分训练集和测试集
rng = np.random.default_rng(42) #种子值
indices = rng.permutation(5)
print(indices)
```

固定种子便于同一环境下复现实验；不要对具体随机输出背答案。Python `random` 和 NumPy 随机生成器各自维护状态，给一个设置种子不会自动设置另一个。

### 📌 课堂练习

创建 4 个样本、每个 2 个特征的数组，输出形状、每列均值和满足某条件的行。解释 `X * w` 与 `X @ w` 的结果形状和含义。

---

## 13. 综合项目：规则分类与评估

### 13.1 项目任务

使用虚构学习数据，预测一个二分类标签。通过项目练习列表、字典、函数、条件、推导式、解包、循环和测试。

本例是教学用人工规则，不应用来判断真实学生能力；没有训练过程，也不能用这里的分数证明模型具有泛化能力。

### 13.2 完整可运行代码

```python
def predict_one(sample, hour_threshold=3.0, attendance_threshold=0.8):
    return int(
        sample["hours"] >= hour_threshold
        and sample["attendance"] >= attendance_threshold
    )


def predict(samples, hour_threshold=3.0, attendance_threshold=0.8):
    return [
        predict_one(sample, hour_threshold, attendance_threshold)
        for sample in samples
    ]


def accuracy(y_true, y_pred):
    if len(y_true) != len(y_pred):
        raise ValueError("真实标签与预测标签数量不同")
    if not y_true:
        raise ValueError("标签不能为空")
    correct = sum(a == b for a, b in zip(y_true, y_pred))
    return correct / len(y_true)


def confusion_counts(y_true, y_pred):
    if len(y_true) != len(y_pred) or not y_true:
        raise ValueError("标签必须等长且非空")
    counts = {"TP": 0, "TN": 0, "FP": 0, "FN": 0}
    for actual, predicted in zip(y_true, y_pred):
        if actual not in (0, 1) or predicted not in (0, 1):
            raise ValueError("本项目仅支持 0/1 标签")
        if actual == 1 and predicted == 1:
            counts["TP"] += 1
        elif actual == 0 and predicted == 0:
            counts["TN"] += 1
        elif actual == 0 and predicted == 1:
            counts["FP"] += 1
        else:
            counts["FN"] += 1
    return counts


def main():
    samples = [
        {"hours": 4.0, "attendance": 0.9, "label": 1},
        {"hours": 1.0, "attendance": 0.5, "label": 0},
        {"hours": 3.0, "attendance": 0.8, "label": 1},
        {"hours": 2.0, "attendance": 0.9, "label": 1},
        {"hours": 5.0, "attendance": 0.6, "label": 0},
    ]
    y_true = [sample["label"] for sample in samples]
    y_pred = predict(samples)
    print("真实标签：", y_true)
    print("预测标签：", y_pred)
    print(f"准确率：{accuracy(y_true, y_pred):.1%}")
    print("混淆统计：", confusion_counts(y_true, y_pred))


if __name__ == "__main__":
    main()
```

预期输出：

```text
真实标签： [1, 0, 1, 1, 0]
预测标签： [1, 0, 1, 0, 0]
准确率：80.0%
混淆统计： {'TP': 2, 'TN': 2, 'FP': 0, 'FN': 1}
```

| 名字 | 含义 |
|---|---|
| TP | 实际为 1，预测为 1 |
| TN | 实际为 0，预测为 0 |
| FP | 实际为 0，预测为 1 |
| FN | 实际为 1，预测为 0 |

### 13.3 课堂讨论与扩展

1. 逐行跟踪第 4 个样本，解释它为什么被预测为 0。
2. 把时长阈值改为 2，重新计算结果。这是在修改规则，不是已经训练出模型。
3. 改为从 CSV 读取样本，加入字段和范围检查。
4. 将规则封装为类，使预测与评估函数可以复用。
5. 若根据数据选择最佳阈值，应分开用于选择规则的数据与最终测试数据。

**AI 课程衔接：** 接下来可以学习如何让决策树从数据选择规则、神经网络如何调整权重，以及准确率在类别不平衡时有哪些限制。

---

## 14. 分层练习与验收

### A. 读代码：预测输出并说明理由

**A1：切片与列表共享**

```python
a = [1, 2, 3, 4]
b = a
c = a[1:3]
b[0] = 9
print(a, c)
```

**A2：返回值**

```python
def f(x):
    print(x + 1)

result = f(3)
print(result)
```

**A3：短路逻辑**

```python
x = 0
print(x != 0 and 10 / x > 1)
```

**A4：默认参数与临界值**

```python
def classify(x, threshold=0.5):
    return int(x >= threshold)

print(classify(0.5), classify(0.5, 0.6))
```

**A5：循环 else**

```python
for x in [1, 3, 5]:
    if x % 2 == 0:
        print(x)
        break
else:
    print("没有偶数")
```

### B. 写代码

| 题号 | 要求 | 测试样例 |
|---|---|---|
| B1 | 输入三个分数，输出平均分，保留两位小数 | `80 90 100` → `90.00` |
| B2 | 编写函数统计列表中的正数个数 | `[-2, 0, 3, 5]` → 2；空列表 → 0 |
| B3 | 统计句子的小写词频，用空白分词，不处理标点 | `AI is fun AI` → ai:2、is:1、fun:1 |
| B4 | 实现准确率函数，处理空列表和长度不等 | `[1,0,1]` 与 `[1,1,1]` → 2/3 |
| B5 | 按指定最小最大值缩放，要求 max > min | x=15、min=10、max=20 → 0.5 |
| B6 | 打印三变量真值表，表达式为 `(x and y) or not z` | 共 8 行 |
| B7 | NumPy 建立 3×2 数组并计算每列均值 | `[[1,2],[3,4],[5,6]]` → `[3,4]` |

### C. 综合验收

独立完成第 13 章项目的 CSV 版本，并满足：

- 能说明特征、标签、预测分别是什么。
- 能把数据读取、预测和评估拆成函数。
- 能测试阈值边界、无效字段、空数据、长度不匹配。
- 能解释列表共享、`return`、`zip` 和 `X.shape`。
- 能指出人工规则与训练模型的区别，并说明为什么测试集不应用来调参。

---

## 15. 参考答案

### 15.1 各章练习参考要点

| 章节 | 参考要点 |
|---|---|
| 1 | 使用 `print`，再用 `if ready:` 控制输出 |
| 2 | 将输入转为整数；输入 `3 + 5` 得到字符串，不会自动计算 |
| 3 | `-9 // 2` 为 -5；`-9 % 2` 为 1；`int(-9 / 2)` 为 -4；区间条件为 `(0 <= x <= 5) or (10 <= x <= 15)` |
| 4 | 默认规则含边界；hours=3.0 且 attendance=0.80 时预测为 1 |
| 5 | 整数和为 5050；被 3 整除的数为 3、6、9、12、15、18 |
| 6 | 使用 `strip`、`split`、逐项 `strip().lower()`；二维列表使用独立内层列表 |
| 7 | cat:2、dog:1、bird:1；不同类别为 3；字典成员判断检查键 |
| 8 | 长度检查后用 `sum(a == b for a,b in zip(...)) / len(...)` |
| 9 | 先筛选，再 `sorted(..., key=lambda s: s['attendance'], reverse=True)` |
| 10 | 仅在整数转换成功并满足范围时计数；CSV 转换后检查范围 |
| 11 | `return accuracy(labels, self.predict(values))`，先定义准确率函数 |
| 12 | `X.mean(axis=0)` 为每列均值；3×2 的 X 与长度 2 的 w，元素乘法结果为 3×2，矩阵乘法结果为长度 3 |

### 15.2 A 组答案

| 题号 | 输出 | 理由 |
|---|---|---|
| A1 | `[9, 2, 3, 4] [2, 3]` | b 与 a 共享列表，c 为切片生成的新列表 |
| A2 | 先输出 4，再输出 None | 函数没有显式 return |
| A3 | False | 短路，不计算除以 0 |
| A4 | `1 0` | `>=` 包含临界值，第二次使用显式阈值 |
| A5 | 没有偶数 | 正常完成遍历，未执行 break |

### 15.3 B 组参考实现

**B1**

```python
a, b, c = map(float, input().split())
print(f"{(a + b + c) / 3:.2f}")
```

**B2**

```python
def count_positive(values):
    return sum(x > 0 for x in values)

print(count_positive([-2, 0, 3, 5]))  # 2
```

**B3**

```python
def word_counts(sentence):
    counts = {}
    for word in sentence.lower().split():
        counts[word] = counts.get(word, 0) + 1
    return counts

print(word_counts("AI is fun AI"))
```

**B4**：参考第 13 章的 `accuracy`；该版本以 Python 列表为输入，不能把 `if not y_true` 直接用于多元素 NumPy 数组，处理数组时改用 `len(y_true) == 0` 等明确检查。

**B5**

```python
def min_max_scale(x, minimum, maximum):
    if maximum <= minimum:
        raise ValueError("maximum 必须大于 minimum")
    return (x - minimum) / (maximum - minimum)

print(min_max_scale(15, 10, 20))  # 0.5
```

该函数按指定范围做线性映射，不自动裁剪；输入超出范围时结果可能不在 `[0, 1]`。

**B6**

```python
for x in [False, True]:
    for y in [False, True]:
        for z in [False, True]:
            print(int(x), int(y), int(z), int((x and y) or not z))
```

**B7**

```python
import numpy as np

X = np.array([[1, 2], [3, 4], [5, 6]])
print(X.mean(axis=0))  # [3. 4.]
```

### 15.4 猜数字的有效输入版本

```python
import random

answer = random.randint(1, 100)
attempts = 0
while attempts < 7:
    try:
        guess = int(input("猜一个 1–100 的整数："))
    except ValueError:
        print("请输入整数")
        continue
    if not 1 <= guess <= 100:
        print("超出范围")
        continue
    attempts += 1
    if guess == answer:
        print(f"猜对了，共 {attempts} 次")
        break
    print("猜小了" if guess < answer else "猜大了")
else:
    print(f"次数用完，答案是 {answer}")
```

### 15.5 CSV 综合项目的读取函数

将此函数与第 13 章的预测和评估函数放在同一个文件，替换硬编码样本。约定首行为 `hours,attendance,label`，时长非负、出勤率为 0–1、标签为 0/1。

```python
import csv
import math


def load_samples(path):
    samples = []
    with open(path, newline="", encoding="utf-8-sig") as file:
        reader = csv.DictReader(file)
        required = {"hours", "attendance", "label"}
        if reader.fieldnames is None or not required.issubset(reader.fieldnames):
            raise ValueError("缺少必需列")
        for record_number, row in enumerate(reader, start=1):
            try:
                hours = float(row["hours"])
                attendance = float(row["attendance"])
                label = int(row["label"])
            except (ValueError, TypeError) as error:
                raise ValueError(f"第 {record_number} 条数据不能转换") from error
            if not math.isfinite(hours) or not math.isfinite(attendance):
                raise ValueError(f"第 {record_number} 条数据含非有限数值")
            if hours < 0 or not 0 <= attendance <= 1 or label not in (0, 1):
                raise ValueError(f"第 {record_number} 条数据超出约定范围")
            samples.append({"hours": hours, "attendance": attendance, "label": label})
    if not samples:
        raise ValueError("没有可用样本")
    return samples
```

记录号按数据记录计数，不等同于文件物理行号，因为 CSV 字段可以跨行。遇到无效记录时本函数停止并说明原因；若改为跳过无效记录，应明确报告跳过数量。

---

## 16. Python 速查

### 16.1 常用语法速查

| 内容 | 常用写法 |
|---|---|
| 输入一行 | `text = input()` |
| 一行多个整数 | `a, b = map(int, input().split())` |
| 格式化输出 | `print(f'{value:.2f}')` |
| 类型转换 | `int(text)`、`float(text)`、`str(value)` |
| 条件 | `if ...:` / `elif ...:` / `else:` |
| 区间判断 | `0 <= x <= 10` |
| 循环 | `for x in items:` / `while condition:` |
| 范围 | `range(start, stop, step)` |
| 循环控制 | `break`、`continue` |
| 切片 | `items[start:stop:step]` |
| 列表追加 | `items.append(x)` |
| 字典安全读取 | `record.get(key, default)` |
| 成员检查 | `x in items`、`key in record` |
| 定义函数 | `def function(parameters):` |
| 返回 | `return result` |
| 定义类 | `class Model:` |
| 推导式 | `[f(x) for x in items if condition]` |
| 排序 | `sorted(items, key=..., reverse=True)` |
| 导入 | `import module` / `from module import name` |
| 文件 | `with open(path, encoding='utf-8') as file:` |
| 异常 | `try:` / `except ValueError:` |
| 数组形状 | `X.shape` |
| 矩阵乘法 | `X @ w` |
