## APCSA 第二轮复习 07：ArrayList、查找与排序

## 📚 1. 复习目标

本章要从“会调用方法”提升到“能预测集合变化、解释边界、写出满足契约的算法”。

| 学习目标 | 学生需要说清的问题 |
| --- | --- |
| 集合操作 | 插入、替换、删除后，size 和索引分别如何变化？ |
| 安全遍历 | 删除后下一次应该检查哪个位置？ |
| 查找 | 输入是否必须有序？找不到返回什么？重复值返回哪个位置？ |
| 排序 | 一轮结束后哪一部分已经满足什么性质？ |
| 算法分析 | 数的是比较、交换、移动，还是总运行成本？ |

## 2. 核心知识与易错点

### 2.1 ArrayList 与数组的关系

ArrayList 使用可扩展的数组存储元素。它的元素个数可以变；底层容量 capacity 与元素个数 size 不是同一个概念。

```java
import java.util.ArrayList;

ArrayList<Integer> numbers = new ArrayList<Integer>();
ArrayList<String> names = new ArrayList<>();
```

- 泛型类型参数必须是引用类型：`Integer`、`Double`、`String`、自定义类等。
- `ArrayList<int>` 不能编译。包装类不只用于集合，集合也不只可以存包装类。
- `numbers.add(7)` 会将 int 自动装箱；`int x = numbers.get(0)` 会自动拆箱。
- ArrayList 变量同样保存引用；`b = a` 不会复制集合。
- `new ArrayList<Integer>(10)` 预留容量，但 size 仍为 0，不能立刻 `get(0)`。这是 Java 扩展辨析，不要求依赖容量构造器完成本章 FRQ。

| 对比 | 数组 | ArrayList |
| --- | --- | --- |
| 个数 | `a.length` | `list.size()` |
| 读取 | `a[i]` | `list.get(i)` |
| 替换 | `a[i] = x` | `list.set(i, x)` |
| 插入/删除 | 自己维护有效长度和移动 | `add` / `remove` |
| 创建后长度 | 数组对象长度固定 | 元素个数可以变化 |

### 2.2 六个核心操作：边界、返回值、size

以下是本章使用的方法契约摘要；完整签名见文末官方文档。

| 调用 | 合法索引 | 结果与返回值 | size 变化 |
| --- | --- | --- | --- |
| `size()` | — | 返回元素个数 | 0 |
| `get(i)` | `0 <= i < size` | 返回位置 i 的元素 | 0 |
| `set(i, x)` | `0 <= i < size` | 替换位置 i，返回旧元素 | 0 |
| `add(x)` | — | 追加到末尾，返回 true | +1 |
| `add(i, x)` | `0 <= i <= size` | 插入位置 i；无返回值 | +1 |
| `remove(i)` | `0 <= i < size` | 删除位置 i，返回被删除的元素 | -1 |

最重要的边界区别：**`add(size, x)` 合法；`get(size)`、`set(size, x)`、`remove(size)` 都越界。** `set` 不能代替向空表中添加第一个元素。

示例：从 `[A, B, C]` 开始。

| 调用 | 返回值 | 调用后的表 |
| --- | --- | --- |
| `list.add(1, "X")` | 无 | `[A, X, B, C]` |
| `list.set(2, "Y")` | `"B"` | `[A, X, Y, C]` |
| `list.remove(0)` | `"A"` | `[X, Y, C]` |

### 2.3 remove 的重载：Java 扩展辨析

AP Java Quick Reference 列出了按索引删除的 `remove(int index)`。原稿还介绍了 Java 的按值删除重载；此处保留，但相关题会明确给出规则。

```java
// 假设 a 当前为 [1, 2, 1]
a.remove(1);                    // 按索引删除：变成 [1, 1]，返回 Integer 2
a.remove(Integer.valueOf(1));    // 按值删除第一个 1：变成 [1]，返回 boolean true
```

不要把 int 参数的 `remove(1)` 理解成“删除数值 1”。按值删除只删第一个匹配项，不是删除全部。

### 2.4 遍历与修改：连续命中是必测反例

错误写法：

```java
for (int i = 0; i < list.size(); i++) {
    if (list.get(i) < 0) {
        list.remove(i);
    }
}
```

追踪输入 `[-2, -3, 4]`：

| 检查前 i | 删除前 | 执行 | 执行后 |
| --- | --- | --- | --- |
| 0 | `[-2, -3, 4]` | 删除 -2 | `[-3, 4]` |
| 1 | `[-3, 4]` | 检查 4，不删 | `[-3, 4]` |

`-3` 左移到索引 0，却被下一次 `i++` 跳过。两个可靠模板：

```java
// 模板 A：倒序删除，未检查的左侧索引不受影响
for (int i = list.size() - 1; i >= 0; i--) {
    if (list.get(i) < 0) {
        list.remove(i);
    }
}

// 模板 B：正序 while，删除后继续检查同一位置
int i = 0;
while (i < list.size()) {
    if (list.get(i) < 0) {
        list.remove(i);
    } else {
        i++;
    }
}
```

增强 for 适合读取、统计、向另一个集合添加元素。遍历当前集合时不要用它对当前集合增删元素；这可能导致 ConcurrentModificationException，也不能把“某次没报错”当作安全证明。

```java
for (Integer x : list) {
    x = x + 1; // 只改变局部变量 x，不会替换 list 中的 Integer
}
// 真正替换每个值：
for (int j = 0; j < list.size(); j++) {
    list.set(j, list.get(j) + 1);
}
```

补充：如果元素是可变对象，调用 `x.setScore(...)` 可能修改集合中那个对象；这与重新给 x 赋值不同。

### 2.5 线性查找：不要求有序

```java
public static int linearSearch(ArrayList<Integer> list, int target) {
    for (int i = 0; i < list.size(); i++) {
        if (list.get(i) == target) {
            return i;
        }
    }
    return -1;
}
```

这里 target 是 int，所以 `list.get(i) == target` 发生拆箱，比较数值。不要推广成“两边都是 Integer 也应该用 ==”；两个包装类引用之间比较内容可用 `equals`，String 内容同样用 `equals`。

本方法返回**第一个**匹配位置；空表或未找到返回 -1。原稿的 int[] 线性查找逻辑也正确；迁移到 ArrayList 时，把 length、下标访问分别改成 size()、get(i)。

### 2.6 二分查找：先写前置条件，再写边界

以下实现要求元素**按非递减顺序排列**。若有重复值，它返回某个匹配位置，不保证最左或最右。

```java
public static int binarySearch(ArrayList<Integer> list, int target) {
    int left = 0;
    int right = list.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (list.get(mid) == target) {
            return mid;
        } else if (list.get(mid) > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}
```

循环不变式：如果目标存在且尚未找到，它仍在闭区间 `[left, right]` 内。比较后排除 mid，所以下一次用 mid ± 1。`left <= right` 保证剩下一个候选时仍检查；空表一开始 right = -1，直接返回 -1。

追踪 `[2, 5, 8, 12, 16, 23, 38]` 查找 23：

| 轮次 | left | right | mid | 读取的值 | 下一步 |
| --- | --- | --- | --- | --- | --- |
| 1 | 0 | 6 | 3 | 12 | left = 4 |
| 2 | 4 | 6 | 5 | 23 | 返回 5 |

原稿只在找到时输出；改成返回索引的方法后，找到、未找到、空表都有明确行为。若为了单次查找先排序，总成本还需要包括排序，不能只说 O(log n)；排序也可能改变原始索引。

### 2.7 选择排序：每轮固定一个最小值

```java
public static void selectionSort(int[] nums) {
    for (int i = 0; i < nums.length - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < nums.length; j++) {
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        int temp = nums[i];
        nums[i] = nums[minIndex];
        nums[minIndex] = temp;
    }
}
```

内层循环完成后再交换。比较的是 `nums[j]` 与“当前最小候选”`nums[minIndex]`，不是始终与 nums[i] 比较。

输入 `[8, 6, 3, 9, 2]`：

| 完成的外层轮次 | 数组状态 | 已固定的前缀 |
| --- | --- | --- |
| i = 0 | `[2, 6, 3, 9, 8]` | `[2]` |
| i = 1 | `[2, 3, 6, 9, 8]` | `[2, 3]` |
| i = 2 | `[2, 3, 6, 9, 8]` | `[2, 3, 6]` |
| i = 3 | `[2, 3, 6, 8, 9]` | `[2, 3, 6, 8]` |

循环不变式：每轮开始前，索引小于 i 的位置已经放好了全局最小的 i 个元素。注意这比“左侧有序”更强。

当 n >= 1，元素大小比较次数固定为 `(n-1)+(n-2)+...+1 = n(n-1)/2`。本代码执行 n-1 次交换代码块，但可能与自己交换；“真正交换两个不同索引的次数”可能更少。空数组没有比较或交换。

### 2.8 插入排序：左侧有序，但位置尚未全局固定

优先掌握基于 set 的右移实现：

```java
public static void insertionSort(ArrayList<Integer> list) {
    for (int i = 1; i < list.size(); i++) {
        int current = list.get(i);
        int j = i - 1;
        while (j >= 0 && list.get(j) > current) {
            list.set(j + 1, list.get(j));
            j--;
        }
        list.set(j + 1, current);
    }
}
```

短路求值很重要：必须先确认 j >= 0，才可以 get(j)。不能随意调换 && 两侧。

输入 `[8, 6, 3, 9, 2]`：

| 完成的外层轮次 | 列表状态 |
| --- | --- |
| i = 1 | `[6, 8, 3, 9, 2]` |
| i = 2 | `[3, 6, 8, 9, 2]` |
| i = 3 | `[3, 6, 8, 9, 2]` |
| i = 4 | `[2, 3, 6, 8, 9]` |

不变式：每轮开始前 `[0, i-1]` 有序；后来的较小值仍可能插到最前面。严格 `>` 使相等值不跨越已有相等值；这是稳定插入的关键。

原稿的 remove/add 版本在本章条件下也能正确排序：

```java
public static void insertionSortRemoveAdd(ArrayList<Integer> list) {
    for (int i = 1; i < list.size(); i++) {
        int current = list.remove(i);
        int index = i - 1;
        while (index >= 0 && current < list.get(index)) {
            index--;
        }
        list.add(index + 1, current);
    }
}
```

每轮临时删除后必定重新插入，轮次结束时长度不变，因此 i 可以继续增加。**即使输入有序，反复 remove/add 仍移动后缀元素，总移动成本可达 Θ(n²)**；不能因为查找插入点的比较较少，就套用 set 版本的最好情况 Θ(n)。

### 2.9 复杂度：区分输入情况与渐近记号

O 是渐近上界，Ω 是渐近下界，Θ 是紧确阶。**O 不等于“最坏情况”，Ω 也不等于“最好情况”**；可以分别讨论最好、最坏情况下的 O、Ω、Θ。

本表采用常见 ArrayList 随机访问、移动元素的成本模型，n 为元素数；讨论辅助空间时不包含输入。

| 算法/操作 | 最好情况 | 最坏情况 | 辅助空间 |
| --- | --- | --- | --- |
| get / set / size | Θ(1) | Θ(1) | Θ(1) |
| 末尾 add | 摊还 Θ(1)，单次通常常数成本 | 扩容的单次可为 Θ(n) | 可能扩容；不等同于算法临时变量空间 |
| 指定位置插入/删除 | 末尾可为 Θ(1)，不计扩容 | 移动后缀 Θ(n) | 无需另建结果集合 |
| 线性查找 | Θ(1)，立即找到 | Θ(n)，找到末尾或未找到 | Θ(1) |
| 迭代二分查找 | Θ(1)，中点即目标 | Θ(log n)，n >= 2 | Θ(1) |
| 上面的选择排序 | Θ(n²) | Θ(n²) | Θ(1) |
| set 版本插入排序 | Θ(n)，已经有序 | Θ(n²)，如严格逆序 | Θ(1) |
| remove/add 版本插入排序 | Θ(n²)，即使已经有序 | Θ(n²) | Θ(1) 个临时变量，不另建结果表 |

倒序删除解决漏删，但不保证线性时间；多次删除仍可能反复搬移保留元素，最坏 Θ(n²)。嵌套循环也不自动等于平方：必须数实际执行次数。

复杂度记号用于理解增长与比较实现，不代替 AP 题中要求的精确操作计数。排序稳定性、摊还成本和 remove(Object) 作为扩展辨析；本章不把原稿扩展为归并排序或递归专题。

## 🎯 3. MCQ 训练（原创）

每题只有一个正确选项。代码片段均处于合法上下文，并已导入 ArrayList；除特别说明外，list 不含 null。题中 `[a, b]` 表示按顺序含 a、b 的列表。

### MCQ 1：泛型类型

哪一个声明不能编译？

A. `ArrayList<Integer> a = new ArrayList<Integer>();`  
B. `ArrayList<String> a = new ArrayList<>();`  
C. `ArrayList<int> a = new ArrayList<int>();`  
D. `ArrayList<Double> a = new ArrayList<Double>();`

### MCQ 2：add 与 set

```java
ArrayList<String> a = new ArrayList<String>();
a.add("A"); a.add("B"); a.add("C");
a.add(1, "X");
String old = a.set(2, "Y");
System.out.println(old + " " + a);
```

A. `X [A, Y, B, C]`  
B. `B [A, X, Y, C]`  
C. `B [A, X, Y]`  
D. `Y [A, X, B, C]`

### MCQ 3：末尾边界

一个 ArrayList<Integer> a 的 size 为 3。下面哪条语句可以正常执行？

A. `a.get(3);`  
B. `a.set(3, 8);`  
C. `a.remove(3);`  
D. `a.add(3, 8);`

### MCQ 4：按位置删除

开始时 a 为 `[4, 1, 4, 2]`。

```java
int x = a.remove(1);
System.out.println(x + " " + a);
```

A. `1 [4, 4, 2]`  
B. `4 [1, 4, 2]`  
C. `1 [4, 2]`  
D. `true [4, 4, 2]`

### MCQ 5：remove 重载（扩展）

已知 `remove(Object obj)` 删除第一个相等对象并返回是否删到；`Integer.valueOf(v)` 返回表示 v 的 Integer。开始时 a 为 `[1, 2, 1]`。

```java
boolean removed = a.remove(Integer.valueOf(1));
System.out.println(removed + " " + a);
```

A. `true [1, 1]`  
B. `1 [2, 1]`  
C. `true [2, 1]`  
D. `true [2]`

### MCQ 6：正序删除的遗漏

开始时 a 为 `[-2, -3, 4, -5]`。

```java
for (int i = 0; i < a.size(); i++) {
    if (a.get(i) < 0) {
        a.remove(i);
    }
}
System.out.println(a);
```

A. `[4]`  
B. `[-3, 4]`  
C. `[-2, 4]`  
D. 抛出 IndexOutOfBoundsException

### MCQ 7：倒序删除

开始时 a 为 `[2, 4, 5, 6]`。

```java
for (int i = a.size() - 1; i >= 0; i--) {
    if (a.get(i) % 2 == 0) a.remove(i);
}
System.out.println(a);
```

A. `[2, 5]`  
B. `[4, 6]`  
C. `[]`  
D. `[5]`

### MCQ 8：增强 for 与赋值

开始时 a 为 `[2, 3]`。

```java
for (Integer x : a) {
    x = x * 2;
}
System.out.println(a);
```

A. `[2, 3]`  
B. `[4, 6]`  
C. `[2, 3, 4, 6]`  
D. 编译错误

### MCQ 9：共享引用

开始时 a 为 `[3, 4]`。

```java
ArrayList<Integer> b = a;
b.set(0, 9);
b = new ArrayList<Integer>();
b.add(7);
System.out.println(a + " " + b);
```

A. `[3, 4] [7]`  
B. `[7] [7]`  
C. `[9, 4] [7]`  
D. `[9, 4] [9, 4, 7]`

### MCQ 10：线性查找的契约

对 `[7, 3, 7, 1]` 调用 2.5 中的 linearSearch，target 为 7，返回值是什么？

A. 2  
B. 0  
C. -1  
D. 必须先排序，否则结果未定义

### MCQ 11：二分查找追踪

对 `[2, 5, 8, 12, 16, 23, 38]` 调用 2.6 中的 binarySearch，target 为 16。依次检查的 mid 是什么？

A. 3、4  
B. 3、5、6  
C. 3、2、4  
D. 3、5、4

### MCQ 12：二分查找的边界错误

将 2.6 的 `while (left <= right)` 改为 `while (left < right)`，其余不变。以下哪组输入会导致“目标存在却返回 -1”？

A. list 为 `[4]`，target 为 4  
B. list 为 `[4, 9]`，target 为 4  
C. list 为 `[]`，target 为 4  
D. list 为 `[2, 4, 9]`，target 为 4

### MCQ 13：选择排序逐轮状态

对 `[8, 6, 3, 9, 2]` 执行 2.7 的选择排序。完成 i = 1 这一轮后，数组是什么？

A. `[3, 6, 8, 9, 2]`  
B. `[2, 6, 3, 9, 8]`  
C. `[2, 3, 6, 9, 8]`  
D. `[2, 3, 6, 8, 9]`

### MCQ 14：选择排序精确比较次数

对长度为 6 的数组执行 2.7 的选择排序，表达式 `nums[j] < nums[minIndex]` 一共计算多少次？

A. 5  
B. 15  
C. 21  
D. 取决于输入是否有序

### MCQ 15：插入排序逐轮状态

对 `[8, 6, 3, 9, 2]` 执行 2.8 的 set 版本。完成 i = 2 这一轮后，列表是什么？

A. `[2, 3, 6, 9, 8]`  
B. `[6, 8, 3, 9, 2]`  
C. `[3, 6, 9, 8, 2]`  
D. `[3, 6, 8, 9, 2]`

### MCQ 16：短路求值

在 2.8 的 set 版本中，把 while 条件改成 `list.get(j) > current && j >= 0`。哪组输入会在第一轮外层循环中发生越界？

A. `[5, 2]`  
B. `[2, 5]`  
C. `[5, 5]`  
D. `[]`

### MCQ 17：插入排序的真实成本

假设列表已按升序排列，长度 n 很大，get/set 成本为常数，插入/删除按移动的元素数计成本。关于 2.8 两个版本，哪项正确？

A. 两个版本总成本都是 Θ(n)  
B. set 版本 Θ(n²)，remove/add 版本 Θ(n)  
C. set 版本 Θ(n)，remove/add 版本 Θ(n²)  
D. 两个版本都只运行一次外层循环

### MCQ 18：有序插入的位置

设 a 非递减有序。要把 value 插到“所有已有相等元素之后”，应如何填空？

```java
int i = 0;
while (i < a.size() && /* condition */) {
    i++;
}
a.add(i, value);
```

A. `a.get(i) < value`  
B. `a.get(i) <= value`  
C. `a.get(i) > value`  
D. `a.get(i) == value`

## ✍️ 4. FRQ 训练（原创）

每题 9 分用于课堂反馈。不得调用 Collections.sort、Arrays.sort、removeIf 或 Stream API；应使用本章循环与核心方法。以下方法均为 public static，已导入 ArrayList。

### FRQ 1：ListCleaner（安全删除与建立新表）

**(a)** 完成方法：

```java
public static int removeOutside(ArrayList<Integer> values, int lower, int upper)
```

前置条件 lower <= upper。原地删除所有小于 lower 或大于 upper 的元素，保持保留元素顺序，并返回删除个数。等于端点的值保留；空表返回 0。

示例：`[3, -1, -2, 5, 8, 5]`，范围 `[0, 5]` → 原表变为 `[3, 5, 5]`，返回 3。

**(b)** 完成方法：

```java
public static ArrayList<Integer> copyAtLeast(ArrayList<Integer> values, int threshold)
```

返回一个新的 ArrayList，包含所有 >= threshold 的元素，保持顺序和重复次数；原表不变。即使没有符合项，也返回新建空表。

示例：`[3, 1, 3, 5]`，threshold = 3 → 新表 `[3, 3, 5]`。

自测：空表、连续两个应删项、全删、全保留、恰好等于上下界、返回表与原表是否同一引用。

### FRQ 2：SearchTools（查找与重复值）

**(a)** `public static int firstIndex(ArrayList<String> words, String target)`

返回第一个与 target 内容相同的字符串索引；未找到或空表返回 -1。列表无须有序，必须比较字符串内容，不能用 ==。不得修改 words。

**(b)** `public static int binaryIndex(ArrayList<Integer> values, int target)`

前置条件：values 非递减有序。使用迭代二分查找返回某个匹配索引；未找到或空表返回 -1。不要求最左匹配，不得修改 values。

示例：`[2, 4, 4, 9]` 查找 4，可返回 1 或 2；查找 3 必须返回 -1。

自测：目标在首位、末位、单元素、夹在两值之间但不存在、全部相等、空表。

### FRQ 3：SortedRoster（有序插入与合并）

**(a)** `public static int insertAfterEquals(ArrayList<Integer> values, int value)`

前置条件：values 非递减有序。原地插入 value，放在所有已有相等元素之后，返回插入后的索引。若无相等元素，放在正常升序位置。空表插到 0。

示例：`[2, 4, 4, 7]` 插入 4 → `[2, 4, 4, 4, 7]`，返回 3。

**(b)** `public static ArrayList<Integer> mergeSorted(ArrayList<Integer> a, ArrayList<Integer> b)`

前置条件：a、b 分别非递减有序。用双指针合并为新的有序表，保留所有重复元素；两原表均不变。相等时先取 a 中的值。要求总时间 O(a.size() + b.size())，按末尾 add 的摊还成本分析；不能先拼接再排序。

示例：`[1, 4, 4]` 和 `[2, 4, 6]` → `[1, 2, 4, 4, 4, 6]`。两表为空时返回新的空表。

### FRQ 4：SortPractice（排序与操作计数）

**(a)** `public static int selectionSortCount(int[] nums)`

原地升序选择排序，结构与 2.7 相同。每次计算元素大小关系 `nums[j] < nums[minIndex]` 时计数一次，返回该次数。不要统计循环条件、赋值或交换。数组长度最多 1000；空数组返回 0。

示例：`[5, 1, 4, 2]` → `[1, 2, 4, 5]`，返回 6。

**(b)** `public static void insertionSort(ArrayList<Integer> list)`

用保存 current、右移较大元素、放回 current 的方法原地升序排序。只允许 get/set/size，不允许 add/remove 或另建集合；空表、单元素、重复值均应正确。

书面解释：为什么只把条件从 `>` 改成 `>=` 仍能按数值排序，却失去本实现对相等元素原始先后次序的保持？可以把相同数值标记为 4a、4b 追踪。

## 🏛️ 5. 官方真题迁移

以下为已公开的历年 FRQ，适合本章课后训练。**表中是中文任务摘要和训练建议，不是原文重印；正式题目、前置条件和官方评分以链接为准。** 历年试卷的题号与考试结构不用于推断当前考纲；当前课程参考 2025 年秋生效的 CED。

| 真题 | 与本章的联系 | 建议安排 |
| --- | --- | --- |
| [2023 Q3 WeatherData](https://apcentral.collegeboard.org/media/pdf/ap23-frq-comp-sci-a.pdf#page=11)，PDF 第 11—13 页 | (a) 删除范围外温度并保序；(b) 找最长连续高温段 | FRQ 1 后做(a)；再练(b)的连续段状态 |
| [2024 Q3 WordChecker](https://apcentral.collegeboard.org/media/pdf/ap24-frq-comp-sci-a.pdf#page=10)，PDF 第 10—12 页 | (a) 相邻字符串包含关系；(b) 按前缀筛选并构造新列表 | FRQ 2 后综合 String 与 ArrayList |

**WeatherData 读题检查**：范围端点保留；热浪指至少两天连续高于 threshold，题目保证至少存在一段。不要把本章原创题对空表的规则移植到真题。

**WordChecker 读题检查**：后一个词是否包含前一个词，方向不能反；createList 匹配的是前缀，不能用“任意位置出现”代替；原列表保持不变，返回表保序。建议用 indexOf 与 substring 练习。

官方评分：

- [2023 Scoring Guidelines](https://apcentral.collegeboard.org/media/pdf/ap23-sg-computer-science-a.pdf)
- [2024 Scoring Guidelines](https://apcentral.collegeboard.org/media/pdf/ap24-sg-computer-science-a.pdf)

建议流程：先读原题和前置条件 → 独立写方法 → 手推边界 → 按官方评分点订正。排序和二分查找的逐轮追踪在本稿用原创 MCQ 训练，不将原创题标为历年真题。

---

## ✅ 6. MCQ 答案与解析（作答后查看）

| 题号 | 答案 | 核心判断 |
| --- | --- | --- |
| 1 | C | 泛型不能直接用 int |
| 2 | B | 插入使 B 移到索引 2；set 返回 B |
| 3 | D | 插入允许 index == size |
| 4 | A | int 参数 1 表示索引；返回被删值 1 |
| 5 | C | Integer 对象参数触发按值删除，只删首个匹配 |
| 6 | B | 删除 -2 后漏过左移的 -3，随后删除 -5 |
| 7 | D | 倒序完整删除偶数，只留 5 |
| 8 | A | 重新给局部变量 x 赋值不替换表元素 |
| 9 | C | set 修改共享表，随后 b 另指新表 |
| 10 | B | 顺序扫描第一次遇到 7 就返回 0 |
| 11 | D | 检查值依次为 12、23、16 |
| 12 | A | left == right == 0 时循环一次也不执行 |
| 13 | C | 两轮固定最小的 2、3 |
| 14 | B | 5 + 4 + 3 + 2 + 1 = 15 |
| 15 | D | 插入 3 后左侧为 3、6、8，2 仍在末尾 |
| 16 | A | 5 被右移后 j = -1，下次先 get(-1) 越界 |
| 17 | C | remove/add 的后缀移动不能忽略 |
| 18 | B | 越过所有 <= value 的元素，再插入 |

订正时至少写一句原因，不能只改选项：

- 6、7：画“删除前索引 → 左移后索引”，解释为什么一份漏删、一份完整。
- 11、12：列 left/right/mid，而不只凭最终排序结果猜。
- 13、15：区分“已固定的全局最小前缀”与“暂时有序的前缀”。
- 14、17：明确计算对象；元素比较次数与元素移动次数是不同指标。
- 18：若改成 `<`，仍有序，但会插在已有相等元素之前，不满足题目契约。

## FRQ 参考实现

以下完整类可分别保存为对应类名的 .java 文件编译。无 main 方法，因为这里实现的是题目要求的方法；运行测试需另写驱动程序调用。只写方法体的课堂作答无须补 import 或 main。

### FRQ 1 参考实现

```java
import java.util.ArrayList;

public class ListCleaner {
    public static int removeOutside(ArrayList<Integer> values, int lower, int upper) {
        int removed = 0;
        for (int i = values.size() - 1; i >= 0; i--) {
            int value = values.get(i);
            if (value < lower || value > upper) {
                values.remove(i);
                removed++;
            }
        }
        return removed;
    }

    public static ArrayList<Integer> copyAtLeast(ArrayList<Integer> values, int threshold) {
        ArrayList<Integer> result = new ArrayList<Integer>();
        for (int value : values) {
            if (value >= threshold) {
                result.add(value);
            }
        }
        return result;
    }
}
```

正确的正序 while 删除也应得分。复杂度：(a) 最坏 O(n²)，(b) 时间 O(n)、结果空间 O(k)，k 为符合项数量。

### FRQ 2 参考实现

```java
import java.util.ArrayList;

public class SearchTools {
    public static int firstIndex(ArrayList<String> words, String target) {
        for (int i = 0; i < words.size(); i++) {
            if (words.get(i).equals(target)) {
                return i;
            }
        }
        return -1;
    }

    public static int binaryIndex(ArrayList<Integer> values, int target) {
        int left = 0;
        int right = values.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int value = values.get(mid);
            if (value == target) {
                return mid;
            } else if (value > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
}
```

能正确实现“最左匹配”的二分变体也符合“某个匹配”要求。时间：(a) 最坏 O(n)，(b) 最坏 O(log n)；辅助空间均 O(1)。

### FRQ 3 参考实现

```java
import java.util.ArrayList;

public class SortedRoster {
    public static int insertAfterEquals(ArrayList<Integer> values, int value) {
        int i = 0;
        while (i < values.size() && values.get(i) <= value) {
            i++;
        }
        values.add(i, value);
        return i;
    }

    public static ArrayList<Integer> mergeSorted(ArrayList<Integer> a, ArrayList<Integer> b) {
        ArrayList<Integer> result = new ArrayList<Integer>();
        int i = 0;
        int j = 0;
        while (i < a.size() && j < b.size()) {
            if (a.get(i) <= b.get(j)) {
                result.add(a.get(i));
                i++;
            } else {
                result.add(b.get(j));
                j++;
            }
        }
        while (i < a.size()) {
            result.add(a.get(i));
            i++;
        }
        while (j < b.size()) {
            result.add(b.get(j));
            j++;
        }
        return result;
    }
}
```

(a) 时间 O(n)，原地插入；(b) 时间 O(n+m)、结果空间 O(n+m)。这是双指针合并练习，不要求掌握归并排序。

### FRQ 4 参考实现

```java
import java.util.ArrayList;

public class SortPractice {
    public static int selectionSortCount(int[] nums) {
        int comparisons = 0;
        for (int i = 0; i < nums.length - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < nums.length; j++) {
                comparisons++;
                if (nums[j] < nums[minIndex]) {
                    minIndex = j;
                }
            }
            int temp = nums[i];
            nums[i] = nums[minIndex];
            nums[minIndex] = temp;
        }
        return comparisons;
    }

    public static void insertionSort(ArrayList<Integer> list) {
        for (int i = 1; i < list.size(); i++) {
            int current = list.get(i);
            int j = i - 1;
            while (j >= 0 && list.get(j) > current) {
                list.set(j + 1, list.get(j));
                j--;
            }
            list.set(j + 1, current);
        }
    }
}
```

书面解释参考：输入 `[4a, 4b]`，用 `>` 时 4a 不右移，顺序保留。改成 `>=` 时，插入 4b 会把 4a 右移，得到 `[4b, 4a]`；数值仍有序，但相等元素顺序变化。标记仅用于理解，不是 Integer 的附加字段。

选择排序时间 O(n²)；set 插入排序最好 O(n)、最坏 O(n²)，辅助空间均 O(1)。
