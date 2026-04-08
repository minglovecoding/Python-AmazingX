## 📌 2026考点变化

删除：继承（Inheritance）不再考 ❌

## ✅ 新增：文件处理

- 读取文本文件（file reading）
- 基本数据处理

## 📊 选择题

- 题目数：**40 → 42题**
- 选项数：**5个 → 4个**

## 🔄 考点内容

1. 基础语法 + 控制结构
2. 类与对象
3. 数组 / ArrayList
4. 数据处理（含文件）

***

## 📚 文件处理

### ⭐ 1️⃣ 用 Scanner 读取文件

```java
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("data.txt");
        Scanner sc = new Scanner(file);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            System.out.println(line);
        }

        sc.close();
    }
}
```

考试考点：

- File 对象创建
- Scanner 读取文件（不是键盘）

### ⭐ 2️⃣ hasNext() / hasNextLine()

### 逐 token 读取

```java
while (sc.hasNext()) {
    String s = sc.next();
}
```

### 逐行读取（更重要）

```java
while (sc.hasNextLine()) {
    String line = sc.nextLine();
}
```

> AP 更偏向 **line processing**

### ⭐ 3️⃣ 文件数据处理

常考形式：

- 统计
- 搜索
- 累加
- 平均值
- 条件筛选

例如：

```java
int sum = 0;
while (sc.hasNextInt()) {
    sum += sc.nextInt();
}
```

### ⭐ 4️⃣ 把文件数据存入 ArrayList

```java
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("data.txt");
        Scanner sc = new Scanner(file);

        ArrayList<String> list = new ArrayList<>();

        while (sc.hasNextLine()) {
            list.add(sc.nextLine());
        }

        sc.close();

        // 示例：打印所有内容
        for (String s : list) {
            System.out.println(s);
        }
    }
}
```

### ⭐ 5️⃣、字符串解析

因为文件读入的是 String：

必须会：

### ⭐ split()

```
String[] parts = line.split(" ");
```

### ⭐ parseInt()

```
int x = Integer.parseInt(parts[0]);
```

文件 → 字符串 → 数字

## Case：

```java
Tom 90
Jack 80
Amy 100
```

```java
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("data.txt");
        Scanner sc = new Scanner(file);

        while (sc.hasNextLine()) {
            String line = sc.nextLine();

            String[] parts = line.split(" ");

            String name = parts[0];
            int score = Integer.parseInt(parts[1]);

            System.out.println(name + " : " + score);
        }

        sc.close();
    }
}
```

✅ 如果要计算平均分

```java
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("data.txt");
        Scanner sc = new Scanner(file);

        int sum = 0;
        int count = 0;

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split(" ");

            int score = Integer.parseInt(parts[1]);

            sum += score;
            count++;
        }

        double avg = (double) sum / count;
        System.out.println(avg);
        sc.close();
    }
}
```

### ✅ 如果要存入 ArrayList

```java
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("data.txt");
        Scanner sc = new Scanner(file);

        ArrayList<Integer> scores = new ArrayList<>();

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            String[] parts = line.split(" ");

            int score = Integer.parseInt(parts[1]);
            scores.add(score);
        }

        sc.close();

        // 计算平均
        int sum = 0;
        for (int s : scores) {
            sum += s;
        }

        if (scores.size() > 0) {
            double avg = (double) sum / scores.size();
            System.out.println("Average: " + avg);
        } else {
            System.out.println("No data");
        }
    }
}
```

### ✅ 如果一行有多个数字

例如：

```
10 20 30 40
```

写法：

```java
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {

        File file = new File("data.txt");
        Scanner sc = new Scanner(file);

        int totalSum = 0;

        while (sc.hasNextLine()) {
            String line = sc.nextLine();

            String[] parts = line.split(" ");

            for (int i = 0; i < parts.length; i++) {
                int num = Integer.parseInt(parts[i]);
                totalSum += num;
            }
        }

        sc.close();

        System.out.println("Total Sum: " + totalSum);
    }
}
```

***

