## APCSP Trial Lesson 

> **适用范围：Quest 0–7 复习 / Unit Test 准备**  
> **核心内容：Variables、if / else if / else、Functions、Parameters、Return Values、Scope、Function Calls**

---

## 1. 本节课目标

完成本节课后，你应该能够：

- 读懂基础 C# 函数
- 区分 **parameter（形参）** 和 **argument（实参）**
- 判断函数的 **return value**
- 理解 `void` 函数与有返回值函数的区别
- 理解变量的 **scope（作用域）**
- 阅读 `if / else if / else`
- 追踪一个函数调用另一个函数的执行过程
- 把多个相似函数合并成一个带参数的函数
- 用 AP Written Response 的方式解释一个 procedure

---

## 2. C# Function 基础

### 2.1 函数的基本结构

```csharp
int Add(int a, int b)
{
    return a + b;
}
```

拆开来看：

```text
int     Add      (int a, int b)
↑        ↑             ↑
返回类型  函数名        parameters
```

调用：

```csharp
Add(3, 5);
```

这里：

```text
a = 3
b = 5
```

所以：

```text
return 3 + 5
→ 8
```

### 2.2 Parameter vs Argument

### Parameter

写在函数定义中的变量：

```csharp
void PrintReadyLine(string name)
```

`name` 是 **parameter**。

### Argument

调用函数时传进去的实际值：

```csharp
PrintReadyLine("Rook");
```

`"Rook"` 是 **argument**。

### 2.3 参数顺序很重要

```csharp
int Subtract(int a, int b)
{
    return a - b;
}
```

```csharp
Subtract(10, 3);
```

结果：

```text
10 - 3 = 7
```

但是：

```csharp
Subtract(3, 10);
```

结果：

```text
3 - 10 = -7
```

> **考试重点：argument 的顺序改变，结果可能完全不同。**

### 3. `void` Function

`void` 表示：

> 这个函数 **不返回一个值**。

例如 Quest 1：

```csharp
void PrintDivider()
{
    Console.WriteLine("~~~~~~~~~~~~~~~~~~~~");
}
```

调用：

```csharp
PrintDivider();
```

它会打印内容，但不会产生可以保存的 return value。

### 3.1 Function Calling Function

Quest 1 中：

```csharp
void PrintQuestBanner()
{
    PrintDivider();
    Console.WriteLine("QUEST OF THE PARTY");
    PrintDivider();
}
```

执行：

```csharp
PrintQuestBanner();
```

执行顺序：

```text
PrintDivider()
↓
打印 QUEST OF THE PARTY
↓
PrintDivider()
```

### 输出

```text
~~~~~~~~~~~~~~~~~~~~
QUEST OF THE PARTY
~~~~~~~~~~~~~~~~~~~~
```

### 4. Functions with Parameters

Quest 2 中：

```csharp
void PrintReadyLine(string name)
{
    Console.WriteLine(name + " is ready.");
}
```

调用：

```csharp
PrintReadyLine("Rook");
```

输出：

```text
Rook is ready.
```

调用：

```csharp
PrintReadyLine("Mote");
```

输出：

```text
Mote is ready.
```

### 为什么 parameter 很重要？

如果没有 parameter，可能需要：

```csharp
void PrintRookReady()
{
    Console.WriteLine("Rook is ready.");
}

void PrintMoteReady()
{
    Console.WriteLine("Mote is ready.");
}
```

使用 parameter 后：

```csharp
void PrintReadyLine(string name)
{
    Console.WriteLine(name + " is ready.");
}
```

一个函数就可以处理不同角色。

> **Parameter makes a function reusable.**

### 5. `if / else if / else`

Quest 0 中使用了完整的条件判断。

```csharp
if (totalHealth <= 0)
{
    mood = "fallen";
}
else if (totalHealth <= 8 && potions == 0)
{
    mood = "desperate";
}
else if (totalHealth <= 8 && potions >= 1)
{
    mood = "in trouble";
}
else if (totalHealth <= 16)
{
    mood = "hurting";
}
else
{
    mood = "strong";
}
```

### 5.1 判断顺序

`if / else if / else`：

> **从上向下判断，找到第一个为 true 的条件后停止。**

例如：

```text
totalHealth = 6
potions = 0
```

判断：

```text
totalHealth <= 0
false

totalHealth <= 8 && potions == 0
true
```

所以：

```text
mood = "desperate"
```

后面的条件不会继续执行。

### 5.2 `&&`

```csharp
A && B
```

表示：

> A 和 B 必须 **同时为 true**。

例如：

```csharp
totalHealth <= 8 && potions == 0
```

只有：

```text
Health ≤ 8
并且
Potions = 0
```

时才成立。


### 5A. Quest 3 — Multiple Parameters & Code Tracing

Quest 3 进一步练习了 **多个参数、条件判断、字符串拼接，以及参数顺序**。

### `PrintLeaderLine`

```csharp
void PrintLeaderLine(string name, int hp, int attack)
{
    if (hp <= 0)
    {
        Console.WriteLine("Leader " + name + " (down)");
    }

    Console.WriteLine(
        "Leader " + name + ": health " + hp + ", " + attack + " attack."
    );
}
```

##### Parameters

```text
name
hp
attack
```

例如：

```csharp
PrintLeaderLine("Rook", 8, 4);
```

输出：

```text
Leader Rook: health 8, 4 attack.
```

如果：

```csharp
PrintLeaderLine("Rook", 0, 4);
```

需要特别注意：这里使用的是单独的 `if`，并没有 `else`。

因此程序会先打印：

```text
Leader Rook (down)
```

然后继续执行函数后面的代码，再打印：

```text
Leader Rook: health 0, 4 attack.
```

> **考试重点：`if` 执行结束不代表整个函数结束。**
>
> 除非遇到 `return`，否则程序会继续执行后面的语句。

### `PrintTrade`

Quest 3 还使用了一个带多个不同类型参数的函数：

```csharp
void PrintTrade(string giver, string taker, string item, int count)
{
    // prints a trade message
}
```

这里的参数类型分别是：

```text
giver  → string
taker  → string
item   → string
count  → int
```

调用时必须按照函数定义中的参数顺序传入：

```csharp
PrintTrade("Rook", "Mote", "potion", 2);
```

可以理解为：

```text
giver = "Rook"
taker = "Mote"
item  = "potion"
count = 2
```

如果 argument 顺序写错，即使类型仍然合法，程序的输出含义也可能完全错误。

例如：

```csharp
PrintTrade("Mote", "Rook", "potion", 2);
```

此时 giver 和 taker 的角色就交换了。

> **这正对应考试 Part A 中：**
>
> “Given a call with its arguments in the wrong order, what comes out?”


### 6. Return Values

Quest 0：

```csharp
string PartyMood(int totalHealth, int potions)
{
    string mood = "?";

    // conditions...

    return mood;
}
```

这里：

```text
string
```

表示函数最后必须返回一个字符串。

例如：

```csharp
PartyMood(5, 0)
```

可能返回：

```text
"desperate"
```

### `Console.WriteLine()` vs `return`

这两个概念不要混淆。

### Print

```csharp
Console.WriteLine("Hello");
```

作用：

> 把内容显示到屏幕。

### Return

```csharp
return "Hello";
```

作用：

> 把一个值交回给调用这个函数的位置。

### 7. Scope（作用域）

Quest 5 中：

```csharp
string ManaWarning(int mana, int cost)
{
    if (mana < cost)
    {
        string message = "Not enough mana.";
        return message;
    }
    else
    {
        string message = "Ready to cast.";
        return message;
    }
}
```

这里的：

```csharp
string message
```

是在 `{ }` 内创建的局部变量。

它只能在所在的 block 中使用。

### 7.1 Local Variable

```csharp
int ShortBy(int mana, int cost)
{
    int missing = cost - mana;

    if (missing < 0)
    {
        missing = 0;
    }

    return missing;
}
```

`missing`：

```text
只存在于 ShortBy() 内部
```

函数结束后不能在外部直接访问它。

### 8. Function Calling Another Function

Quest 5：

```csharp
int ShortBy(int mana, int cost)
{
    int missing = cost - mana;

    if (missing < 0)
    {
        missing = 0;
    }

    return missing;
}
```

另一个函数：

```csharp
string ShortByLine(int mana, int cost)
{
    string message =
        "You are short by " + ShortBy(mana, cost) + ".";

    return message;
}
```

调用：

```csharp
ShortByLine(4, 10);
```

先执行：

```csharp
ShortBy(4, 10)
```

得到：

```text
10 - 4 = 6
```

然后：

```text
"You are short by " + 6 + "."
```

最终：

```text
You are short by 6.
```

### 9. 综合例子：Quest 6 风格

```csharp
int HealTo(int hp, int amount, int maxHp)
{
    int newHp = hp + amount;

    if (newHp > maxHp)
    {
        newHp = maxHp;
    }

    return newHp;
}
```

调用：

```csharp
HealTo(6, 3, 10);
```

结果：

```text
6 + 3 = 9
→ return 9
```

调用：

```csharp
HealTo(8, 5, 10);
```

结果：

```text
8 + 5 = 13
13 > 10
→ newHp = 10
→ return 10
```

### 10. 合并相似函数

Quest 7 给出了三个相似函数：

```csharp
void PrintRedGate()
{
    Console.WriteLine("The red gate needs 1 key.");
}

void PrintBlueGate()
{
    Console.WriteLine("The blue gate needs 2 keys.");
}

void PrintGoldGate()
{
    Console.WriteLine("The gold gate needs 3 keys.");
}
```

它们只有两个地方不同：

```text
color
keys
```

因此可以写成：

```csharp
void PrintGate(string color, int keys)
{
    Console.WriteLine(
        "The " + color + " gate needs " + keys + " keys."
    );
}
```

然后调用：

```csharp
PrintGate("red", 1);
PrintGate("blue", 2);
PrintGate("gold", 3);
```

---

## 核心思想

原来：

```text
3 functions
```

修改后：

```text
1 reusable function
+
different arguments
```

这就是 **procedural abstraction** 的基础思想之一。

### 11. Part A — Reading Code Practice

### Question 1

```csharp
int Power(int baseValue, int bonus)
{
    return baseValue + bonus;
}
```

调用：

```csharp
Power(7, 3);
```

返回什么？

A. `3`  
B. `7`  
C. `10`  
D. `21`

### Question 2

```csharp
int Difference(int first, int second)
{
    return first - second;
}
```

调用：

```csharp
Difference(4, 10);
```

返回什么？

A. `6`  
B. `-6`  
C. `14`  
D. `40`

### Question 3

```csharp
string Status(int hp)
{
    if (hp <= 0)
    {
        return "down";
    }
    else if (hp <= 5)
    {
        return "weak";
    }
    else
    {
        return "ready";
    }
}
```

调用：

```csharp
Status(4);
```

返回什么？

A. `"down"`  
B. `"weak"`  
C. `"ready"`  
D. `4`

### Question 4

```csharp
int Double(int x)
{
    return x * 2;
}

int AddDouble(int a, int b)
{
    return a + Double(b);
}
```

调用：

```csharp
AddDouble(3, 4);
```

返回什么？

A. `7`  
B. `8`  
C. `11`  
D. `14`

### 12. Part B — Writing Code Practice

### Question 1 — Merge Functions

原代码：

```csharp
void PrintSmallPotion()
{
    Console.WriteLine("Potion heals 5 HP.");
}

void PrintLargePotion()
{
    Console.WriteLine("Potion heals 10 HP.");
}
```

将两个函数合并成：

```csharp
void PrintPotion(int amount)
{
    // your code
}
```

然后分别调用它产生：

```text
Potion heals 5 HP.
Potion heals 10 HP.
```

### Question 2 — Write a Function

完成：

```csharp
int HitThroughShields(int attackPower, int shields)
{
    // return the damage after shields
    // damage cannot be below 0
}
```

例如：

```text
HitThroughShields(10, 3)
→ 7
```

```text
HitThroughShields(5, 8)
→ 0
```

### 13. Part C — Written Response Practice

阅读：

```csharp
int HealTo(int hp, int amount, int maxHp)
{
    int newHp = hp + amount;

    if (newHp > maxHp)
    {
        newHp = maxHp;
    }

    return newHp;
}
```

### Question 1

Identify the parameters of the procedure.

### Question 2

Explain how the parameters are used in the program.

### 推荐回答结构

### Q1

```text
The parameters are hp, amount, and maxHp.
```

### Q2

```text
hp represents the current health,
amount represents how much health is added,
and maxHp represents the maximum allowed health.

Using parameters allows the same procedure
to work with different values each time it is called.
```

### 14. 高频易错点

### ① Parameter ≠ Argument

```csharp
int Add(int a, int b)
```

`a`、`b`：

```text
parameters
```

```csharp
Add(3, 5);
```

`3`、`5`：

```text
arguments
```

### ② `void` 不返回值

```csharp
void PrintHello()
```

通常用于：

```text
print / perform an action
```

### ③ 有返回类型必须 `return`

```csharp
int Add(...)
```

需要返回：

```csharp
return someInteger;
```

### ④ 参数顺序不能随意交换

```csharp
Damage(attack, shield)
```

和：

```csharp
Damage(shield, attack)
```

可能产生完全不同的结果。

### ⑤ `if / else if` 找到第一个 true 就停止

不是把所有 true 的分支都执行。

### ⑥ Local Variable 有 Scope

在函数或 `{ }` 内声明的变量：

```csharp
int missing = ...
```

只能在对应的作用域内使用。

### 15. Quick Check

不运行程序，直接回答：

```csharp
int ShortBy(int mana, int cost)
{
    int missing = cost - mana;

    if (missing < 0)
    {
        missing = 0;
    }

    return missing;
}
```

### 1.

```csharp
ShortBy(3, 8)
```

返回：________

### 2.

```csharp
ShortBy(10, 6)
```

返回：________

### 3.

这里的 parameters 是：

```text
________ and ________
```

### 4.

`missing` 是：

- A. argument
- B. local variable
- C. function
- D. return type

### 16. 本节课总结

本次考试最重要的逻辑：

```text
Function
├── Return Type
├── Function Name
├── Parameters
├── Local Variables
├── Conditions
└── Return Value
```

读函数时建议始终按照下面顺序：

```text
1. 看函数返回类型
2. 看 parameters
3. 代入 arguments
4. 从上往下执行
5. 判断 if / else
6. 遇到函数调用就进入那个函数
7. 找到 return
```

### 17. 课后复习重点

优先复习：

1. Quest 0：`if / else if / else`
2. Quest 1：无参数函数 + function calling function
3. Quest 2：parameters
4. Quest 3：multiple parameters + argument order + output tracing
5. Quest 5：return value + scope + function calls
6. Quest 6：根据需求完成函数
7. Quest 7：把多个相似函数合并成一个带参数的函数
