## 📚 Java iterator

##### Iterator

Java迭代器（Iterator）是一种用于遍历集合（如列表、集合和映射等）的接口。

迭代器接口定义了几个方法，最常用的是以下三个：

- **next()** - 返回迭代器的下一个元素，并将迭代器的指针移到下一个位置。
- **hasNext()** - 用于判断集合中是否还有下一个元素可以访问。
- **remove()** - 从集合中删除迭代器最后访问的元素（可选操作）。

Iterator 类位于 java.util 包中，使用前需要引入它，语法格式如下：

```java
import java.util.Iterator; // 引入 Iterator 类
```

获取一个迭代器可用iterator()方法：

##### 循环集合元素

让迭代器 it 逐个返回集合中所有元素最简单的方法是使用 while 循环：

```java
// 引入 ArrayList 和 Iterator 类
import java.util.ArrayList;
import java.util.Iterator;

public class Main {
    public static void main(String[] args) {

        // 创建集合
        ArrayList<String> sites = new ArrayList<String>();
        sites.add("Google");
        sites.add("Runoob");
        sites.add("Taobao");
        sites.add("Zhihu");

        // 1.获取迭代器
        Iterator<String> it = sites.iterator();

        // 输出集合中的所有元素
        while(it.hasNext()) {
            System.out.println(it.next());
        }
        
        //2.for循环
        for(int i=0;i<sites.size();i++){
          System.out.println(sites.get(i));
        }
    }
}
```

**删除元素**

```java
// 引入 ArrayList 和 Iterator 类
import java.util.ArrayList;
import java.util.Iterator;

public class Main {
    public static void main(String[] args) {
        ArrayList<Integer> numbers = new ArrayList<Integer>();
        //int -> Integer
        //double -> Double
        //boolean -> Boolean
        numbers.add(12);
        numbers.add(8);
        numbers.add(2);
        numbers.add(23);
        Iterator<Integer> it = numbers.iterator();
        while(it.hasNext()) {
            Integer i = it.next();
            if(i < 10) {  
                it.remove();  // 删除小于 10 的元素
            }
        }
        System.out.println(numbers);
    }
}
```

注：在使用迭代器遍历集合时，不能直接修改集合中的元素，而是需要使用迭代器的 remove() 方法来删除当前元素。

***

### While语句

> print sum=1+2+3+...+99+100。

```java
int sum=0;
int number=1;
while(number<=100){
   sum+=number;
   number++;
}
```

> 用while语句提取输入数的每位数字。

```java
Scanner console=new Scanner(System.in);
System.out.print("Enter number:");
int number=console.nextInt();
while(number!=0){
  System.out.println(number%10);
  number/=10;
}
```

> 移去字符串中的空格字符

```java
public static String removeSpaces1(String str){
  while(str.indexOf("")!=-1){
    int indexSpace = str.indexOf("");
    String first= str.substring(0,indexSpace);
    String second= str.substring(indexSpace+1);
    str=first+second;
  }
  return str;
}
```

> 判断一个数是否是回文数

```java
public static boolean isPalindrome(String str){
    int len = str.length();

    for(int i = 0; i < len; i++){
        String current = str.substring(i, i + 1);
        String opposite = str.substring(len - 1 - i, len - i);
        if(!current.equals(opposite))
            return false;
    }
    return true;
}
```

another way

```c++
public static boolean isPalindrome(String str){
    int len = str.length();

    for(int i = 0; i < len/2; i++){
        String current = str.substring(i, i + 1);
        String opposite = str.substring(len - 1 - i, len - i);
        if(!current.equals(opposite))
            return false;
    }
    return true;
}
```

### For语句

**What’s the total number of x++ operations \*in terms of n\*?**

```java
int x = 0;

for(int i = 0; i < n; i++){
    x++;
}

for(int j = 0; j < n; j++){
    x++;
}
```

**What’s the total number of x++ operations?**

```Java
int x = 0;
for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 15; j++)
        x++;
}
```

**What’s the total number of operations in \*terms of n\*?**

```java
for(int i = 0; i < n; i++){
    for(int j = i; j < n; j++)
        x++;
}
```

**Answer:**
 n + (n−1) + (n−2) + … + 2 + 1 = n(n+1)/2 (quadratic)

***

[P5721](https://www.luogu.com.cn/problem/P5721)

````java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        
        int cur = 1; // 当前要输出的数字
        for (int i = 0; i < n; ++i) {
            int len = n - i; // 本行的数字个数
            for (int j = 0; j < len; ++j) {
                System.out.printf("%02d", cur); // 两位数字，不足补0
                cur++;
            }
            if (i != n - 1) {
                System.out.println();
            }
        }
    }
}
````

[P1217](https://www.luogu.com.cn/problem/P1217)

```java
import java.util.Scanner;

public class Main {

    // 判断是否为质数
    static boolean isPrime(int s) {
        if (s < 2) return false;
        for (int i = 2; i * i <= s; i++) {
            if (s % i == 0) return false;
        }
        return true;
    }

    // 判断是否为回文数
    static boolean isPalindrome(int s) {
        int b = 0, t = s;//`t` 保存原始数字 `s`（因为后面要把 `s` 变成 0）
        //`b` 是反转后的数字（初始是 0）
        while (s > 0) {
            b = b * 10 + s % 10;
            s /= 10;
        }
        return t == b;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();

        for (int i = a; i <= b; i++) {
            if ((i & 1) == 1 && isPalindrome(i) && isPrime(i)) {
                System.out.println(i);
            }
        }
    }
}
```

### 🔍 **1）取出 s 的最后一位：**

`s % 10`
 例如 s = 123 → 3

### **2）把这位数字加到 b 的末尾：**

```java
b = b * 10 + (最后一位)
```

例如 b = 0：
 过程如下：

| 循环 | s    | s % 10 | b 新值        | s 新值 |
| ---- | ---- | ------ | ------------- | ------ |
| 1    | 123  | 3      | 0*10+3 = 3    | 12     |
| 2    | 12   | 2      | 3*10+2 = 32   | 1      |
| 3    | 1    | 1      | 32*10+1 = 321 | 0      |

得到 b = 321，就是原数字的反转。

***

[P5718](https://www.luogu.com.cn/problem/P5718)

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int ans = Integer.MAX_VALUE;  // 等价于 C++ 的 INT_MAX

        for (int i = 0; i < n; i++) {
            int x = sc.nextInt();
            ans = Math.min(ans, x);   // 取较小值
        }

        System.out.println(ans);
    }
}
```

### 🎯 **常见考试题型**

##### **1. 遍历数组进行统计**

```java
int count = 0;
for (int i = 0; i < arr.length; i++) {
    if (arr[i] > 10)
        count++;
}
```

##### **2. ArrayList 遍历 + 删除元素**

APCSA 强调：

- **从后往前删** 才不会漏删

```java
for (int i = list.size() - 1; i >= 0; i--) {
    if (list.get(i) < 0)
        list.remove(i);
}
```

##### **3. 字符串遍历**

```java
for (int i = 0; i < s.length(); i++) {
    char c = s.charAt(i);
}
```

##### **4. 找最大/最小 / sum**

```java
int max = arr[0];
for (int x : arr) {
    if (x > max)
        max = x;
}
```

##### **5. 双层循环输出 pattern**

```java
for (int i = 0; i < 5; i++) {
    for (int j = 0; j < i; j++) {
        System.out.print("*");
    }
    System.out.println();
}
```

##### **6. 2D array 遍历**

```java
for (int r = 0; r < grid.length; r++) {
    for (int c = 0; c < grid[0].length; c++) {
        System.out.println(grid[r][c]);
    }
}
```

### ⭐ APCSA 8 个iteration模板

##### 1) 标准 for

```java
for (int i = 0; i < n; i++) {}
```

##### **2) for-each**

```java
for (int x : arr) {}
```

##### **3) 遍历 ArrayList**

```java
for (int i = 0; i < list.size(); i++) {}
```

##### **4) while 循环**

```java
while (condition) {
    // update
}
```

##### **5) 双层 for**

```java
for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
```

##### **6) 过滤统计 count**

```java
int count = 0;
for (int x : arr)
    if (x == target) count++;
```

##### **7) 删除 ArrayList 元素**

```java
for (int i = list.size()-1; i >= 0; i--)
    if (...) list.remove(i);
```

##### **8) 累加 sum**

```java
int sum = 0;
for (int x : arr) sum += x;
```
