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

```java
// 引入 ArrayList 和 Iterator 类
import java.util.ArrayList;
import java.util.Iterator;

public class Main{
    public static void main(String[] args) {

        // 创建集合
        ArrayList<String> sites = new ArrayList<String>();
        sites.add("Google");
        sites.add("Runoob");
        sites.add("Taobao");
        sites.add("Zhihu");

        // 获取迭代器
        Iterator<String> it = sites.iterator();

        // 输出集合中的第一个元素
        System.out.println(it.next());
    }
}
```

##### 循环集合元素

让迭代器 it 逐个返回集合中所有元素最简单的方法是使用 while 循环：

```java
// 引入 ArrayList 和 Iterator 类
import java.util.ArrayList;
import java.util.Iterator;

public class RunoobTest {
    public static void main(String[] args) {

        // 创建集合
        ArrayList<String> sites = new ArrayList<String>();
        sites.add("Google");
        sites.add("Runoob");
        sites.add("Taobao");
        sites.add("Zhihu");

        // 获取迭代器
        Iterator<String> it = sites.iterator();

        // 输出集合中的所有元素
        while(it.hasNext()) {
            System.out.println(it.next());
        }
    }
}
```

**删除元素**

```java
// 引入 ArrayList 和 Iterator 类
import java.util.ArrayList;
import java.util.Iterator;

public class RunoobTest {
    public static void main(String[] args) {
        ArrayList<Integer> numbers = new ArrayList<Integer>();
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

