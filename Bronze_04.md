### 🧩 什么是 `struct`？

`struct`（结构体）是一种 **自定义的数据类型**，可以把多个不同类型的数据组合在一起，打包成一个整体使用。

有点像是把 **姓名 + 年龄 + 成绩** 装进同一个盒子，这个盒子就是结构体。

### 📝 基本语法

```c++
struct Person {
    string name;
    int age;
    double score;
};
```

它定义了一个叫 `Person` 的结构体类型，里面包含三个成员。

### 🔥 如何使用？

#### 1. 创建变量

```c++
Person p1;
```

#### 2. 给成员赋值

```c++
p1.name = "Alice";
p1.age = 18;
p1.score = 95.5;
```

#### 3. 打印输出

```c++
cout << p1.name << " " << p1.age << " " << p1.score << endl;
```

### 📦 定义时顺便初始化

```c++
Person p2 = {"Bob", 20, 88.0};
```

### 📌 结构体也能嵌套

```c++
struct Student {
    string name;
    int age;
    struct Score {
        int math;
        int english;
    } score;
};

Student s = {"Tom", 17, {90, 85}};
cout << s.score.math << endl; // 输出 90
```

### ⭐ 结构体数组

```c++
Person people[3] = {
    {"Tom", 17, 89.5},
    {"Jerry", 18, 92.0},
    {"Mike", 19, 85.0}
};
```