## 📚 Arraylist

`ArrayList` 本质上是一个**可变长度的数组（dynamic array）**

### 1) ArrayList 能装什么

- `ArrayList<E>` 是**泛型容器**，`E` 可以是：

  - 任意引用类型：`String`、自定义类 `Person`、`Integer`、`Double` 等

- E需要用包装类：`Integer / Double / Character`

  不能直接用基本类型：`int / double / char`

  - 例：`ArrayList<Integer> a = new ArrayList<>();`

### 2) 核心方法

- `add(E obj)`：末尾添加
- `add(int index, E obj)`：指定位置插入
- `get(int index)`：取元素
- `set(int index, E obj)`：替换并返回旧值
- `remove(int index)`：按下标删除并返回被删元素
- `remove(Object obj)`：按元素值删除（删第一个匹配，返回 boolean）
- `size()`：元素个数
- `toString()`：打印（例如 `[a, b, c]`）

### 3) 需要掌握的 3 种遍历方式

##### A. 下标 for

```java
for (int i = 0; i < list.size(); i++) {
    // list.get(i)
}
```

##### B. 增强 for（for-each）

```java
for (String s : list) {
    // s
}
```

##### C. 倒序删除

当你要在遍历时删除元素，常用：

```java
for (int i = list.size() - 1; i >= 0; i--) {
    if (true) list.remove(i);
}
//a.remove(1);               删下标 index=1 的元素
//a.remove(Integer.valueOf(1));  删值为 1 的元素
```

Case1 

```java
import java.util.*;
public class Main{
    public static void main(String[] agrs){
        ArrayList<String>names=new ArrayList<String>();
        names.add("hello");
        names.add("world");
        System.out.println(names);
        System.out.println(names.size());
        System.out.println(names.toString());
        System.out.println(names.get(1));
    }
  }
```

Case2: 寻找目标数组的index值

```java
public int sequentialSearch(int[] array, int target) {
    for (int i = 0; i < array.length; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    // target not in array
    return -1;
}
```

Case3: 用二分查找实现case2

```java
import java.util.*;
public class Main{
    public static void main(String args[]){
        ArrayList<Integer>a=new ArrayList<Integer>();
        a.add(1);
        a.add(2);
        a.add(3);
        a.add(4);
        a.add(5);
        System.out.println(a.toString());
        int target=5;
        int left=0,right=a.size()-1;
        while(left<=right){
            int mid=(left+right)/2;
            if(a.get(mid)==target){
                System.out.println("target's index is "+mid);
                return;
            }
            else if(a.get(mid)>target){
                right=mid-1;
            }
            else{
                left=mid+1;
            }
        }
    }
}
```

### 4）Sorting algorithm

Selection sort：从数组里依次选择第i小的数并进行交换。

```java
public static void selectionSort(int arr[]) {
    for (int i = 0; i < arr.length - 1; i++) {
        // find smallest from i to end of array
        int min_idx = i;
        for (int j = i + 1; j < arr.length; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // swap minimum with element at index i
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

```

Insection sort: 把数组/列表分成“左边已排序”和“右边未排序”，每次从右边拿一个元素，插入到左边的正确位置。

```java
public void insertionSort(ArrayList<Integer> list) {
    for (int i = 1; i < list.size(); i++) {
        int current = list.remove(i);   // removes & returns element at i
        int index = i - 1;

        while (index >= 0 && current < list.get(index)) {
            index--;
        }

        list.add(index + 1, current);
    }
}

```

### 5）时间复杂度与空间复杂度

- **输入规模 n**：问题输入的大小（数组长度、图的点/边数、字符串长度等）。
- **时间复杂度**：随 n 增大，算法运行步数/时间如何增长；用 **大 O 记号**描述上界，如 O(n log n)`。
- **空间复杂度**：随 n 增大，算法额外占用的内存如何增长（通常指**辅助空间**，不含输入本身）。

##### 常见记号（从理想到保守）

- **Θ(f(n))**：紧确阶（上界=下界）。
- **O(f(n))**：上界（最坏或上限）。
- **Ω(f(n))**：下界（最好或下限）。
  实际写作中，多用 **O** 表示“渐近上界”。

### 常见量级（从快到慢，大致）

```java
O(1) < O(log n) < O(n) < O(n log n) < O(n^2) < O(n^3) < O(2^n) < O(n!)
```
