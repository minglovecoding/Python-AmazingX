## 📚Inheritance

> 理解父类、子类及继承关系, 设计和编写继承关系已明确排除在考试范围外。

1) 继承基础概念

```java
class A {
  public A(int n) { }
}
class B extends A {
  public B() {
    super(5); // 必须
  }
}
//B 是 A 的子类（subclass），A 是父类（superclass）。
//子类 **继承** 父类的 `public` / `protected` 成员（字段和方法），但不继承父类的构造器。
```

例子：

- “Car is-a Vehicle” 合理（Car extends Vehicle）
- “Wheel is-a Car” 不合理（更像 has-a）

2) 修饰符

- `public`：可以公开访问。
- `private`：只能在**当前类内部**访问；子类继承后也不能直接访问父类的 `private` 内容。
- `protected`：同包 + 子类可访问。

3. 子类构造

```java
class A {
  public A(int n) {}
}
class B extends A {
  public B() {
    super(5); // 必须
  }
}
//子类构造器第一行若不写 super(...)，Java 会默认调用无参的super()
//如果父类只有有参构造器，子类必须显式写super(参数...)
//super(...) 必须是子类构造器的第一条语句
```

4. @Override和overloading

```java
class Animal {
  public String speak() {
    return "some sound";
  }
}

class Dog extends Animal {
  @Override
  public String speak() {      // 重写：方法名+参数列表相同
    return "woof";
  }
}

public class Main {
  public static void main(String[] args) {
    Animal a1 = new Animal();
    Animal a2 = new Dog();     // 父类引用指向子类对象（多态）

    System.out.println(a1.speak()); // some sound
    System.out.println(a2.speak()); // woof（运行时执行 Dog 的重写版本）
  }
}
//@Override是重写父类方法
```

```java
class A {
  public void print(int x) {
    System.out.println("A " + x);
  }
}

class B extends A {
  public void print(double x) {
    System.out.println("B " + x);
  }
}

public class Main {
  public static void main(String[] args) {
    A obj = new B();
    obj.print(5.0); 
  }
}
//overloading是相同的函数名，不同的函数参数
```

```java
class Message {
  public String format() {
    return "[MSG]";
  }
}

class ErrorMessage extends Message {
  @Override
  public String format() {
    return super.format() + "[ERROR]";  // 复用父类逻辑
  }
}

public class Main {
  public static void main(String[] args) {
    Message m = new ErrorMessage();
    System.out.println(m.format()); // [MSG][ERROR]
  }
}
//super.format()是调用父类的函数
```

5.多态(Polymorphism)

```java
//同一个“父类类型”的引用，指向不同“子类对象”时，调用同一个方法名，会因为对象真实类型不同而表现出不同的行为。
class Animal {
  public String speak() { return "Animal"; }
}

class Dog extends Animal {
  @Override
  public String speak() { return "woof"; }
}

class Cat extends Animal {
  @Override
  public String speak() { return "meow"; }
}

public class Main {
  public static void main(String[] args) {
    Animal[] arr = { new Dog(), new Cat(), new Animal() };

    for (Animal a : arr) {
      System.out.println(a.speak());
    }
  }
}
```

6. ##### Casting和instanceof

```java
public class Main {
    static class A {
        public void f() { System.out.println("A f"); }
    }
    static class B extends A {
        @Override
        public void f() { System.out.println("B f"); }
        public void g() { System.out.println("B g"); }
    }

    public static void main(String[] args) {
        A x = new B();
        x.f();      // 输出: B f
        // x.g();   // 编译错误：A 类型没有 g
    }
}
```

```java
A x = new B();
B y = (B) x;  // OK
y.g();        // 现在可以调用 g
```

```java
A x = new A();
B y = (B) x;  // 编译能过，但运行会 ClassCastException
```

```java
if (x instanceof B) {
  B y = (B) x;
  y.g();
}
//规避错误
```

##### 7. `super.method()`：在重写中复用父类逻辑

```java
//子类重写方法后，仍可以在里面调用父类版本：`super.f()`。
class A {
  public void f() { System.out.println("A"); }
}
class B extends A {
  @Override
  public void f() {
    super.f();                 // 先做父类的
    System.out.println("B");   // 再加自己的
  }
}
new B().f();
// 输出：A 然后 B
```

8. toString和 equals

```java
//System.out.println(obj) 会自动调用 obj.toString()。
class Point {
  private int x, y;
  public Point(int x, int y) { this.x = x; this.y = y; }
  @Override
  public String toString() { return "(" + x + "," + y + ")"; }
}
System.out.println(new Point(2, 3)); // (2,3)
```

```java
//默认 equals 等同于 ==（引用相等）。
class Point {
  private int x, y;
  public Point(int x, int y) { this.x = x; this.y = y; }

  @Override
  public boolean equals(Object o) {
    if (!(o instanceof Point)) return false;
    Point p = (Point) o;
    return x == p.x && y == p.y;
  }
}

Point a = new Point(1,2);
Point b = new Point(1,2);
System.out.println(a.equals(b)); // true（内容相等）

```

9. 字段隐藏

```java
//字段看“引用类型”，方法看“对象类型”。
class A {
  public int x = 1;
  public int getX() { return x; }
}
class B extends A {
  public int x = 2;            // 隐藏父类字段
  @Override
  public int getX() { return x; } // 重写方法
}

A obj = new B();
System.out.println(obj.x);     // 1（字段看引用类型 A）
System.out.println(obj.getX()); // 2（方法看对象类型 B）

```

***

### 🎯 题 1：最基础的动态绑定

```java
class A {
  public String f() { return "A"; }
}
class B extends A {
  @Override
  public String f() { return "B"; }
}
public class Main {
  public static void main(String[] args) {
    A x = new B();
    System.out.println(x.f());
  }
}
```

问题：能否编译？若能，输出是什么？

### 🎯 题 2：引用类型限制“能调用什么”

```java
class A {
  public void m() { System.out.print("A"); }
}
class B extends A {
  @Override
  public void m() { System.out.print("B"); }
  public void n() { System.out.print("N"); }
}
public class Main {
  public static void main(String[] args) {
    A x = new B();
    x.n();
  }
}
```

问题：能否编译？如果不能，原因是什么（用一句话）？

### 题 3：向下转型（downcast）

```java
class A {
  public void m() { System.out.print("A"); }
}
class B extends A {
  @Override
  public void m() { System.out.print("B"); }
  public void n() { System.out.print("N"); }
}
public class Main {
  public static void main(String[] args) {
    A x = new B();
    ((B) x).n();
    x.m();
  }
}
```

问题：能否编译？若能，输出是什么（不换行）？

### 🎯 题 4：不安全转型（运行时错误）

```java
class A {
  public void m() { System.out.print("A"); }
}
class B extends A {
  @Override
  public void m() { System.out.print("B"); }
  public void n() { System.out.print("N"); }
}
class B extends A { }
public class Main {
  public static void main(String[] args) {
    A x = new A();
    B y = (B) x;
    System.out.println("ok");
  }
}
```

问题：能否编译？运行时会发生什么？（输出/异常类型）

### 🎯 题 5：构造器链 `super(...)`

```java
class A {
  public A() { System.out.print("A0 "); }
  public A(int n) { System.out.print("A" + n + " "); }
}
class B extends A {
  public B() {
    super(3);
    System.out.print("B0 ");
  }
}
public class Main {
  public static void main(String[] args) {
    new B();
  }
}
```

问题：能否编译？若能，输出是什么？

### 🎯 题 6：父类没有无参构造器

```java
class A {
  public A(int n) { System.out.print("A "); }
}
class B extends A {
  public B() {
    //super(10)
    System.out.print("B ");
  }
}
public class Main {
  public static void main(String[] args) {
    new B();
  }
}
```

问题：能否编译？如果不能，最直接原因是什么？

### 🎯 题 7：重载 vs 重写（混合）

```java
class A {
  public void f(int x) { System.out.print("A1 "); }
}
class B extends A {
  public void f(double x) { System.out.print("B2 "); } // 注意参数
}
public class Main {
  public static void main(String[] args) {
    A x = new B();
    x.f(5);
  }
}
```

问题：能否编译？若能，输出是什么？这题体现的是 overriding 还是 overloading？

### 🎯 题 8：`super.method()` 的输出顺序

```java
class A {
  public void m() { System.out.print("A "); }
}
class B extends A {
  @Override
  public void m() {
    super.m();
    System.out.print("B ");
  }
}
public class Main {
  public static void main(String[] args) {
    A x = new B();
    x.m();
  }
}
```

问题：输出是什么（不换行）？

### 🎯 题 9：`Object` 与 `toString()`（多态输出常考）

```java
class A {
  public String toString() { return "A"; }
}
class B extends A {
  @Override
  public String toString() { return "B"; }
}
public class Main {
  public static void main(String[] args) {
    A x = new B();
    System.out.println(x);
  }
}
```

问题：输出是什么？

### 🎯 题 10：字段隐藏（field hiding）陷阱题（AP 偶尔出现）

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
public class Main {
  public static void main(String[] args) {
    A obj = new B();
    System.out.print(obj.x + " ");
    System.out.print(obj.getX());
  }
}
```

问题：能否编译？若能，输出是什么？

## 📚Interface

```java
public interface Shape {
    double getArea();
    int compareTo(Shape other);
}
```

```java
public class Circle implements Shape {

    private double radius;

    public Circle(double r) {
        radius = r;
    }

    public double getArea() {
        return Math.PI * radius * radius;
    }

    public int compareTo(Shape other) {
        if (this.getArea() > other.getArea())
            return 1;
        else if (this.getArea() < other.getArea())
            return -1;
        else
            return 0;
    }
}
```

```java
Shape s = new Circle(5);
System.out.println(s.getArea());
//Shape s = new Shape(); // ❌ 错误
```

