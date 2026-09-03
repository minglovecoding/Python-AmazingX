## 📚Unit 2: Using Objects


#### Class

A class in programming defines a new abstract data type. A class is the formal implementation, or blueprint, of the attributes and behaviors of an object.

When you create objects or instances of a class in coding, you create new variables or objects of that class data type.

```java
public class Dog {
    private String breed;
    private int size;
    private String colour;
    private int age;
    void eat() {
    }
    void run() {
    }
    void sleep(){
    }
    void name(){
    }
}
```

```java
public class Main {
    public static void main(String[] args) {
        Dog dog1 = new Dog();
        dog1.eat();
        dog1.run();
        dog1.sleep();
    }
}
```

Objects

class: A program entity that represents a template for a new type of objects.

object or instance: An entity that combines attributes(data) and behavior(methods). object-oriented programming (OOP): Programs that perform their behavior as interactions between objects. Java is object-oriented.

The Car class is a template for creating Car objects.


#### Classes and objects

Example: The Ipod class provides the template or blueprint for the attributes(data) and behavior(methods) of an ipod object.

Its attributes or data can include the current song, current volume and battery life.

Its behavior or methods can include change song, change volume, turn on/off, etc...

Two different Ipod objects can have different attributes/data. However, their template share the same implementation/code.


#### Blueprint analogy

iPod blueprint

attributes:
- current song
- volume
- battery life

behavior:
- power on/off
- change station/song
- change volume
- choose random song


#### More Examples

Suppose you are writing an arcade game. What are some useful classes and their corresponding objects?

Example: The Character Class represents characters in the game. Attributes/Data: String name, int numberOfLives, boolean isAlien. Behavior/Methods: shoot(), runLeft(), runRight(), jump().

Objects:

```java
Character player1, player2; //declaring objects of type Character
Character enemy1, enemy2;
```


#### More Examples

Your game might have more than one classes.

Classes: Character, Boss, MysteryBox, Obstacle.

Objects:

```java
Boss level1, level2;
MysteryBox yellow; // give player 3 extra lives
MysteryBox red; // give player 100 coins
Obstacle wall; //immovable
Obstacle poison; // kills player
```


#### Sprite

Sprite's attributes can include many properties: the image(.png or .jpg) of the sprite, the width and height of the image, and position on the screen given by center_x and center_y instance variables.

To keep things simple, for now, we focus on just two attributes: center_x and center_y.

center_x

origin (0,0)

center_y

(center_x, center_y)


#### Class Diagram

The image below represents a class diagram of the Sprite class. The class diagram allows us to preview the contents of the class.

| Sprite                                               |
| ---------------------------------------------------- |
| public Sprite(double x, double y)                    |
| double center_x<br>double center_y<br>...            |
| public void display()<br>public void update()<br>... |

constructor: method that inititalizes the attributes.

attributes:data or properties of a class(variables)

methods: behaviors of the class.


#### Constructor

The constructor of a class is a method that allows us to initialize the attributes(variables) of an object when it is first created.

Constructors always have the same name as the class and are used with the keyword new.

An object variable is created using the keyword new followed by a call to a constructor.

| Sprite                                               |
| ---------------------------------------------------- |
| public Sprite(double x, double y)                    |
| double center_x<br>double center_y<br>...            |
| public void display()<br>public void update()<br>... |

signature: name of constructor and its parameter list.


#### Constructor

arguments or parameters: data that methods need to do its job.

Consider the line of code used to create a Sprite object called player:

```java
Sprite player = new Sprite(30.0,50.0);
```

The actual parameters (30.0, 50.0) is passed to the formal parameters (double x, double y) of the constructors. The actual parameters passed to a constructor must be compatible with the types identified in the formal parameter list.

In code not shown here, the variables x and y are then used to initialize the attributes center_x and center_y.

| Sprite                                    |
| ----------------------------------------- |
| public Sprite(double x, double y)         |
| double center_x<br>double center_y<br>... |
| ...                                       |


#### Multiple Objects

We can create multiple objects using the constructor.

```java
public class ConstructorExample
{
public static void main(String[] args){
Sprite player1 = new Sprite(30, 50);
Sprite player2 = new Sprite(10, 40);
}
}
```

Note that in this example, player1 and player2 are two different objects or instances of the same class, each with its own copy of instance variables and methods.

We can access the attributes of an object by using the dot notation as shown in the next example.


#### Accessing attributes

We can access the attributes of an object by using the dot notation.

```java
public class ConstructorExample{
public static void main(String[] args){
Sprite player1 = new Sprite(30, 50);
Sprite player2 = new Sprite(10, 40);
System.out.println(player1.center_x) // 30.0
System.out.println(player1.center_y) // 50.0
System.out.println(player2.center_x) // 10.0
System.out.println(player2.center_y) // 40.0
}
}
```


#### modifying attributes

We can modify the attributes of an object by using the dot notation.

```java
public class ConstructorExample{
public static void main(String[] args){
Sprite player1 = new Sprite(30, 50);
Sprite player2 = new Sprite(10, 40);
System.out.println(player1.center_x) // 30.0
System.out.println(player1.center_y) // 50.0
System.out.println(player2.center_x) // 10.0
System.out.println(player2.center_y) // 40.0
player1.center_x = 100;
System.out.println(player1.center_x) // 100.0
}
}
```


#### Overloaded constructors

Constructors are said to be overloaded when there are multiple constructors with the same name but a different signature.

Note on the right, the Sprite class has two constructors: one that has no parameter and one that has parameters.

Usually, the constructor that has no parameter (sometimes called the default constructor) initializes the object to some default values, for example, zeroes.

| Sprite                                               |
| ---------------------------------------------------- |
| public Sprite()<br>public Sprite(double x, double y) |
| double center_x<br>double center_y<br>...            |
| ...                                                  |


#### overloaded constructors

We can call different constructors to initialize our objects. Assume the default constructor initializes center_x and center_y to be at the origin.

```java
public class ConstructorExample{
public static void main(String[] args){
Sprite player1 = new Sprite();
Sprite player2 = new Sprite(10, 40);
System.out.println(player1.center_x) // 0.0
System.out.println(player1.center_y) // 0.0
System.out.println(player2.center_x) // 10.0
System.out.println(player2.center_y) // 40.0
}
}
```


#### Primitive vs Reference Type

The memory associated with a variable of a primitive type(int, double, boolean) holds an actual primitive value.

```java
int x = 3; // x is a variable of a primitive type
// the memory associated with x actually holds the value 3

int y = x; // y copies the value of x
// y is a different variable in memory
// which also hold the value 3
```

Here we have two different integers in memory both of which has the value 3.

| x    | 3    |
| ---- | ---- |

| y    | 3    |
| ---- | ---- |


#### Primitive vs. Reference Type

While the memory associated with a variable of a reference type holds an object reference value. This value is the memory address of the referenced object.

```java
Sprite x = new Sprite(100, 200);
// x is a variable of a reference type
// the value of x is actually an address in memory of this
// Sprite object not the actual object itself.
Sprite y = x; // copies the address of x
```

Note that this is similar to the previous slide example. But in this case, both x and y stores the same address in memory therefore both refer to the same object.


#### More Examples

```java
// x, y and isPrime are variables of primitive type(Unit 1).
int x = 3;
double y = 2.5;
boolean isPrime = false;

// player1, player2 are variables of a reference type

Sprite player1 = new Sprite(100, 200);
Sprite player2 = new Sprite();
```


#### Null

The keyword null is a special value used to indicate that a reference is not associated with any object. Accessing an instance variable of a null reference will result in a NullPointerException.

```java
// player1 points to the address or location in memory for the
// Sprite object
Sprite player1 = new Sprite(100, 200);
Sprite player2 = null; // player2 is initialized to null since it is not
// yet associated with any object.
System.out.println(player2.center_x) // NullPointerException
Sprite player3;
System.out.println(player3.center_x) // error! Player3 is not
//  initialized(not a NullPointerException)
```


#### Example Implementation

Although we will write the Sprite class later in Unit 5. It is instructive to see the implementation of this very simple class to understand the structure of a class. Note that there are two .java files. The main method is in Main.java(sometimes call the driver class) and the Sprite object class is in Sprite.java.

declaring the instance variables

Main.java

Sprite.java

```java
public class Sprite{
double center_x;
double center_y;
public Sprite(){
center_x = 0;
center_y = 0;
}
public Sprite(double x, double y){
center_x = x;
center_y = y;
}
}
```

```java
public class Main{
public static void main(String[] args){
Sprite player1 = new Sprite();
Sprite player2 = new Sprite(10, 40);
}
}
```

overloaded constructors

creating the objects by calling one of the constructors

initializing the instance variables


---

### User Input with Scanner


#### Optional Topic: User Input with Scanner


#### Input and System.in

interactive program: Reads input from the console.

While the program runs, it asks the user to type input. The input typed by the user is stored in variables in the code.

```java
Can be tricky; users are unpredictable and misbehave.
```

But interactive programs have more interesting behavior.

Scanner: An object that can read input from many sources.

Communicates with System.in (the opposite of System.out) Can also read from files, web sites, databases, ...


#### Scanner syntax

The Scanner class is found in the java.util package.

```java
import java.util.*;   // so you can use Scanner
```

Constructing a Scanner object to read console input:

```java
Scanner name = new Scanner(System.in);
```

Example:

```java
Scanner console = new Scanner(System.in);
```


#### Scanner methods

Each method waits until the user presses Enter. The value typed by the user is returned.

```java
System.out.print("How old are you? ");  // prompt
int age = console.nextInt();
System.out.println("You typed " + age);
```

prompt: A message telling the user what input to type.

| Method       | Description                               |
| ------------ | ----------------------------------------- |
| nextInt()    | reads an int from the user and returns it |
| nextDouble() | reads a double from the user              |
| next()       | reads a one-word String from the user     |
| nextLine()   | reads a one-line String from the user     |


#### Scanner example

```java
import java.util.*;   // so that I can use Scanner

public class UserInputExample {
public static void main(String[] args) {
  Scanner console = new Scanner(System.in);
  System.out.print("How old are you? ");
  int age = console.nextInt();
  int years = 65 - age;
  System.out.println(years + " years to retirement!");
  }
}
```

Console (user input underlined):

```java
How old are you?
36 years until retirement!
```

| age  | 29   |
| ---- | ---- |

| years | 36   |
| ----- | ---- |

```java
29
```


#### Input tokens

token: A unit of user input, as read by the Scanner. Tokens are separated by whitespace (spaces, tabs, new lines). How many tokens appear on the following line of input?

```java
23  John Smith   42.0  "Hello world"  $2.50  "  19"
```

When a token is not the type you ask for, it crashes.

```java
System.out.print("What is your age? ");
int age = console.nextInt();
```

Output:

```java
What is your age? Timmy
java.util.InputMismatchException
at java.util.Scanner.next(Unknown Source)
at java.util.Scanner.nextInt(Unknown Source)
...
```


#### Scanner example 2

```java
import java.util.*;   // so that I can use Scanner

public class ScannerMultiply {
public static void main(String[] args) {
Scanner console = new Scanner(System.in);

System.out.print("Please type two numbers: ");
  int num1 = console.nextInt();
  int num2 = console.nextInt();
  int product = num1 * num2;
  System.out.println("The product is " + product);
  }
}
```

Valid Outputs (user input underlined):

```java
Please type two numbers: 8 6
```

The product is 48

```java
// 2 tokens separated by space
```

```java
Please type two numbers: 8
6
```

The product is 48

```java
// 2 tokens separated by new
// line
```


#### Strings as user input

Strings as user input

Scanner's next method reads a word of input as a String.

```java
Scanner console = new Scanner(System.in);
System.out.print("What is your name? ");
String name = console.next();
System.out.println("Your name is " + name);
```

Output:

```java
What is your name? Chelsey
Your name is Chelsey.
```

The nextLine method reads a line of input as a String.

```java
System.out.print("What is your address? ");
String address = console.nextLine();
System.out.println("Your address is " + address);
```

Output:

```java
What is your address? 123 Fake st.
Your address is 123 Fake st.
```


---

### Methods


#### Modularity

modularity: Writing code in smaller, more manageable components or modules. Then combining the modules into a cohesive system.

Modularity with methods. Break complex code into smaller tasks and organize it using methods.

Methods define the behaviors or functions for objects.

An object's behavior refers to what the object can do (or what can be done to it). A method is simply a named group of statements.


#### static vs non-static

Variables and methods can be classified as static or nonstatic(instance).

Non-static or instance: Part of an object, rather than shared by the class. Non-static methods are called using the dot operator along with the object variable name.

```java
static: Part of a class, rather than part of an object. Not copied into each object; shared by all objects of that class. Static methods are called using the dot operator along with the class name unless they are defined in the enclosing class.
```

We will further clarify this distinction in Unit 5 when we learn to write our own classes.


#### Static Method Inside Driver Class

The driver class is the class with the main method. Note that the main method is the begin point of a run of any program. The driver class can contain other static methods. You can call a static method from another method in the same enclosing class directly without referencing the name or object of the class.

```java
public class MyClass{
public static void main(String[] args){
  method2();
  method1();
}
public static void method1(){
  System.out.println("running method1");
}
public static void method2(){
  System.out.println("running method2");
 }
}
```

MyClass.java

Output: running method2 running method1


#### Static Method Inside Driver Class

The order of the methods in the driver class does not matter and does not affect the run or output of the program. The program below has the exact same output as the program from the previous slide. The main method is always the starting point of the run of any program.

```java
public class MyClass{
public static void method1(){
  System.out.println("running method1");
}
public static void main(String[] args){
  method2();
  method1();
}
public static void method2(){
  System.out.println("running method2");
 }
}
```

MyClass.java

Output: running method2 running method1


#### Control flow

Control flow

When a method is called, the program's execution... "jumps" into that method, executing its statements, then "jumps" back to the point where the method was called. What is the output?

```java
public class MethodsExample {
public static void main(String[] args) {
message1();

message2();


}

...
}
```

Output: This is message1. This is message2. This is message1. Done with message2.


#### Methods

Non-static or instance methods belong to individual objects. They are usually implemented inside of an object class rather than the driver class.

Methods in an object class are non-static by default unless explicitly labeled "static".

Non-static methods are called through objects of the class.


#### Non-static Method Call

Output: Begins here. method1 method2 Ends here.

A program's run begins and ends at the main method.

non-static(instance) methods

MyClass.java

MyProgram.java

```java
public class MyProgram{
  public static void main(String[] args){
    System.out.println("Begins here.");
    MyClass c = new MyClass();
    c.method1();
    c.method2();
    System.out.println("Ends here.");
  }
}
```

```java
public class MyClass{
...
public void method1(){
System.out.println("method1");
}
public void method2(){
System.out.println("method2");
}
}
```

non-static method is called through the name of an object using the dot notation


#### Method Signature

A method signature for a method consists of the method name and the ordered, possibly empty, list of parameter types.

```java
public void name(parameters){
statements;
}
```

Examples:

```java
public void method1(){
...
}

public void method2(int x, double y){
...
}
```

The parameters in the method header are formal parameters.

void: no value is returned when method ends.

no parameters


#### Static Example

When calling a method with parameters, values provided in the parameter list need to correspond to the order and type in the method signature.

```java
public class MyProgram{
public static void main(String[] args){
mystery1(3, 4); // error, incompatible types!
mystery1(); // missing actual parameters
mystery1(3); // missing actual parameters
mystery1(3, true); // correct
mystery2(3.2, 3.0); // error, incompatible types!
double a = 2.5;
int b = 5;
mystery2(double a, int b); // error, no type in actual parameters
mystery2(a, b); // correct

}
public static void mystery1(int x, boolean y){
...
}
public static void mystery2(double x, int z){
...
}
}
```


#### Non-static Example

When calling a method with parameters, values provided in the parameter list need to correspond to the order and type in the method signature.

MyProgram.java

```java
public class MyProgram{
public static void main(String[] args){
MyClass c = new MyClass();
c.method1(); // correct!
c.method2(); // error! Missing actual parameters
c.method2(3.5, 4.1); // error! Wrong types
c.method2(2, 3.1); // correct!
c.method2(3, 4); // correct, 4 is casted to a double 4.0
}
}
```

MyClass.java

```java
public class MyClass{
...
public void method1(){
...
}
public void method2(int x, double y){
...
}
}
```


#### Static Vs Non-static Method Calling

MyClass.java

```java
public class MyClass{
public static void main(String[] args){
System.out.println(SomeClass.method1());
SomeClass a = new SomeClass();
System.out.println(a.method2());
System.out.println(a.method1());
System.out.println(SomeClass.method2());

}
}

public class SomeClass{
public SomeClass(){...}
public static int method1() // static method
{...}
public int method2() // non-static or instance method
{...}}
```

call static method through name of class

call non-static method through name of an object

This works also but not considered "best practice"

This is an error!

SomeClass.java

Note that method1 and method2 both belong to a different class than the driver class where they are being called.


#### Method Returns

Methods in Java can have return types. Such non-void methods return values back that can be used by the program. A method can use the keyword "return" to return a value.

```java
public type methodName(type var1,..., type var2){
...
}
```

Examples:

```java
public int method1(){
...
}

public double method2(int x){
...
}
```

Note: Method parameters are its inputs and method returns are its outputs.

```java
return types
```


#### Return

```java
return: To send out a value as the result of a method.
```

The opposite of a parameter: Parameters send information in from the caller to the method. Return values send information out from a method to its caller. A call to the method can be used as part of an expression.


#### Return

Non-void methods return a value that is the same type as the return type in the signature.

To use the return value when calling a non-void method, it must be stored in a variable or used as part of an expression.

Procedural abstraction allows a programmer to use a method by knowing what the method does even if they do not know how the method was written.

For example, the Math library, part of the java.lang package contains many useful mathematical methods. We may not know how these methods were implemented but we can still use them.


#### Common error: Not storing

Many students forget to store the result of a method call.

```java
public static void main(String[] args) {
Math.abs(-4); // error! Returned value not stored nor used
// (not a compiler/syntax error)
// corrected
int result = Math.abs(-4);
System.out.println(result); // 4

System.out.println("the square root of 4 is " + Math.sqrt(4));
// the square root of 4 is 2.0
}
```

returned value is concatenated with a string


#### NullPointerException

Using a null reference to call a method or access an instance variable causes a NullPointerException to be thrown.

```java
public static void main(String[] args) {

Sprite a = null; //currently the variable a references no object
a.display(); // NullPointerException, can't call method on
// a reference to nothing!
System.out.println(a.center_x); // NullPointerException
}
```


#### Void Methods

Void methods do not have return values. Once the execution of the method completes, the flow of control returns to the point immediately following where the method was called.

```java
public void methodName(type var1,..., type var2){
...
}
```

Examples:

```java
public void method1(){
...
}

public void method2(int x){
...
}
```

void


#### Void Methods

Void methods do not have return values and are therefore not called as part of an expression.

```java
public class MyClass{
public static void main(String[] args){
int a = 3 + printX(5); //error! Does not return!
int b = 5 * twiceX(3); // correct, b = 30
printX(5); // correct
// Output: The input x is 5
}
public static void printX(int x){
System.out.println("The input x is" + x);
}
public static int twiceX(int x){
return 2 * x;
}
}
```


#### Overloaded Methods

Methods are said to be overloaded when there are multiple methods with the same name but a different signature.

```java
public class MyClass{
public static void main(String[] args){
double a = add(1, 2) + add(1.8, 5.2) + add(1, 2, 3);
System.out.println(a); // 16.0
}
public static int add(int x, int y){
return x + y;
}
public static double add(double x, double y){
return x + y;
}
public static int add(int x, int y, int z){
return x + y + z;
}
}
```

Three methods named "add".


#### Value Semantics

Parameters are passed using call by value or value semantics. Call by value initializes the formal parameters with copies of the actual parameters. When primitive variables (int, double,boolean) and String(the only object class that does this) are passed as parameters, their values are copied. Modifying the parameter will not affect the variable passed in.

```java
public class MyClass{
public static void main(String[] args){
int x = 23;
strange(x);
System.out.println("2. x = " + x);
}
public static void strange(int x){
x = x + 1;
System.out.println("1. x = " + x);
}
```

Note: The value of x in main did not change.

The x variable in main is different than the x variable in strange.

Output:

```java
1. x = 24
2. x = 23
```


#### Value semantics

Value semantics: methods cannot change the values of primitive types(int, boolean, float) and String.

```java
public class MyClass{
public static void main(String[] args){
int x = 5;
doubleMyNumber(x);
System.out.println("My number is" + x); //My number is 5
}
public static void doubleMyNumber(int x){
x = x * 2;
}
}
```

Note: The value of x in main did not change.


#### Find all errors.

```java
public class MyClass{
public static void main(String[] args){
printX();
add();
add(3, 5);
System.out.println(printX()); 					System.out.println("3 + 5 = " + add(3, 5));
int y = 3 + add(4, 6.0);
}
public static void printX(int x){
System.out.println("The input x is" + x);
}
public static int add(int x, int y){
return x + y;
}
}
```


#### Answers

```java
public class MyClass{
public static void main(String[] args){
printX(); // missing actual parameter.
add(); // missing actual parameters.
add(3, 5); // returned value not stored
// but not a syntax error.
System.out.println(printX(5)); // error!
//no returned value!
System.out.println("3 + 5 = " + add(3, 5));//correct!
int y = 3 + add(4, 6.0); // incompatible types!
}
public static void printX(int x){
System.out.println("The input x is" + x);
}
public static int add(int x, int y){
return x + y;
}
}
```


#### Nonstatic vs Static

Let's do one example of a object class to understand when to make a method static vs. non-static.

```java
class Student{
int id;
public Student(int new_id){
id = new_id;
}
public void printMyID(){
System.out.println("My ID is " + id);
}
public static void printWelcomeMessage(){
System.out.println("Welcome all students!");
}
}


}
```

printMyID is a non-static method and belong to individual student objects. E.g. if there are 5 student objects, there are 5 different copies of printMyID, one for each student.


#### Nonstatic vs Static

Let's do one example of a object class to understand when to make a method static vs. non-static.

```java
class Student{
int id;
public Student(int new_id){
id = new_id;
}
public void printMyID(){
System.out.println("My ID is " + id);
}
public static void printWelcomeMessage(){
System.out.println("Welcome all students!");
}
}


}
```

printWelcomeMessage is a static(class) method. It belongs to the class rather than individual objects. If there are 5 student objects, there is only ONE shared printWelcomeMessage.


#### Nonstatic vs Static

Here's how we can use the Student class.

```java
class DriverClass{
public static void main(String[] args){
// create a Student object
Student s1 = new Student(12343);
// call instance or non-static printMyID()
s1.printMyID();
// call static printWelcomeMessage()
Student.printWelcomeMessage();
// this also works but not considered
// "best practice"
s1.printWelcomeMessage();
}
}
```


#### Lab

Write a driver class with the following five static methods.

```java
// given two integers x and y, returns their average.
public static double average(int x, int y)
{...}


// given two points (x1, y1) and (x2,y2), returns
// the slope of the line through them. You may assume
// x1 is not equal to x2.
public static double slope(int x1,int y1,int x2,int y2)
{...}
```

Write your main() method so that your program has an output similar to:

Notice the format of the points on the coordinate plane.


#### Lab 2

Create a new repl. Implement the driver class(Main.java on repl.it) to ask the user to enter two different points(using a Scanner object)on the plane and print out their midpoint and the distance between them.

For (x1, y1) and (x2, y2): Midpoint: ((x1+x2)/2, (y1+y2)/2)


#### Lab 2

Write your program so that it has EXACTLY THE FOLLOWING OUTPUT.

Program Output: (underlined values are user-entered inputs)

Enter x1: 2 Enter y1: -1 Enter x2: 3 Enter y2: 5 The midpoint between (2,-1) and (3,5) is (2.5, 3.0) The distance between (2,-1) and (3,5) is 6.082762530298219


#### Lab 2 Outline

I created a repl for this lab.

Click on the link below to go to the repl. Then "fork" it by either pressing on the "fork it" button or repl.it will fork it for you automatically if you begin editting the program.

Fill in the code as indicated by the comments.


---


#### Strings

string: An object storing a sequence of text characters.

```java
String is not a primitive type. String is an object type.
```

Three ways to initialize a string:

```java
String a = new String("text");
String b = "text";
String c = expression;


Examples:

String a = new String("John Smith");
String b = "John Smith";
String c = "John" + "Smith";
```

The String class is part of the java.lang package. Classes in the java.lang package are available by default.


#### Indexes

Characters of a string are numbered with 0-based indexes:

```java
String a = "J. Smith";
```

First character's index : 0 Last character's index : 1 less than the string's length

| index     | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    |
| --------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| character | J    | .    |      | S    | m    | i    | t    | h    |


#### String concatenation

string concatenation: primitive values can be concatenated with a String object using +. This causes implicit conversion of the values to String objects.

"hello" + 42 is 1 + "abc" + 2 is "abc" + 1 + 2 is 1 + 2 + "abc" is "abc" + 9 * 3 is "1" + 1 is 4 - 1 + "abc" is

Use + to print a string and an expression's value together.

```java
System.out.println("Grade: " + (95.1 + 71.9) / 2);
```

Output: Grade: 83.5

```java
"hello42"
```

```java
"1abc2"
```

```java
"abc12"
```

```java
"3abc"
```

```java
"abc27"
```

```java
"11"
```

```java
"3abc"
```


#### Escape sequences

escape sequence: A special sequence of characters used to represent certain special characters in a string. \n new line character \" quotation mark character \\ backslash character

```java
Example:
System.out.println("\\hello\nhow are \"you\"?\\\\");
```

Output:
- \hello
- how are "you"?\\


#### Questions

What is the output of the following println statements?

```java
System.out.println("\\\\");
System.out.println("'");
System.out.println("\"\"\"");
```

Write a println statement to produce this output:

```java
/ \ // \\ /// \\\
```


#### Answers

Output of each println statement:

```java
\\
'
"""
```

println statement to produce the line of output:

```java
System.out.println("/ \\ // \\\\ /// \\\\\\");
```


#### String methods

| Method name                                          | Description                                                  |
| ---------------------------------------------------- | ------------------------------------------------------------ |
| String(String str)                                   | Constructs a new String object that represents the same sequence of characters as str |
| int length()                                         | Returns number of characters in this string                  |
| substring(index1, index2)<br>or<br>substring(index1) | Returns the characters in this string from index1 (inclusive) to index2 (exclusive);<br>if index2 is omitted, grabs till end of string |
| boolean equals(String other)                         | Returns true if this is equal to other; returns false otherwise |
| int compareTo(String other)                          | Returns a value < 0 if this is less than other; returns zero if this is equal to other; returns a value > 0 if this is greater than other |
| indexOf(str)                                         | Returns index where the start of the given string appears in this string (-1 if not found) |


#### String method examples

```java
// index     0123456789012345678
String s1 = "programming in java";

System.out.println(s1.length());
// 19
System.out.println(s1.indexOf("i")); // 8
System.out.println(s1.indexOf("gram")); // 3
System.out.println(s1.indexOf("hi")); // -1

System.out.println(s1.substring(7, 10)); // "min"
System.out.println(s1.substring(12)); // "in java"
System.out.println(s1.substring(2,3));// "o"
System.out.println(s1.substring(2,2));
// "", empty string

String s2 = s1.substring(10, 17); // "g in ja"
```


#### String method examples

Given the following string:

```java
// index       0123456789012345678901
String book = "Building Java Programs";
```

How would you extract the word "Java" ?

```java
String word = book.substring(9,13);
```

String's equals:

```java
String a = "hello", b = "Hello";
System.out.println(a.equals(b)); // false
System.out.println(a.equals("hello")); // true
```


#### Comparing strings

When the operator == is used with object variables it returns true when the two variables refer to the same object. These variables are called aliases for the same object and object references.

With strings this happens when one string variable is set to another or when strings are set to the same string literal.

```java
String a = "hi"; //String literal
String b = "hi";
System.out.println(a == b); /* true
```

the Java run-time will check if that string literal already exists as an object in memory, and if so reuse it. So a and b will refer to the same string object. */

```java
String c = b;
System.out.println(b == c); //true
```


#### Comparing strings

With String objects, you must use the equals method to test if two strings have the same characters in the same order instead of == which is used for primitive types. If you use the new keyword to create a string it will create a new string object. So, even if we create two string objects with the same characters using the new operator they will not refer to the same object.

```java
String a = new String("hi");
String b = new String("hi");
System.out.println(a == b); //false, not same objects
System.out.println(a.equals(b)); //true, same characters & order
```


#### compareTo

The compareTo method compares strings in dictionary (lexicographical) order: If string1.compareTo(string2) < 0, then string1 precedes string2 in the dictionary. If string1.compareTo(string2) > 0, then string1 follows string2 in the dictionary. If string1.compareTo(string2)==0, then string1 and string2 are identical. (This test is an alternative to string1.equals(string2).)

All you need to know is that all digits precede all capital letters, which precede all lowercase letters. Thus "5" comes before "R", which comes before "a".


#### compareTo

```java
String s1 = "HOT", s2 = "HOTEL", s3 = "dog";
String s4 = "hot";
String s5 = new String("hot");


s1.compareTo(s2) returns a negative number(<0) since s1 < s2.

s4.compareTo(s3) returns a positive number(>0) since s4 > s3.

s4.compareTo(s5) returns 0 since s4 is equal to s5.
```


#### Modifying strings

Methods like substring build and return a new string, rather than modifying the current string.

```java
String is immutable; once created, its value cannot be changed.

String s = "kendrick";
s = "snoop dog";
//"kendrick" is discarded and a new String
// object "snoop dog" is created.

s.substring(0, 5); //returns snoop, not stored
System.out.println(s);
// snoop dog, s is not changed
```


#### Modifying strings

To modify a variable's value, you must reassign it:

```java
String s = "lil bow wow";
s = s.substring(0,3);
System.out.println(s);   // lil
```


#### Value semantics

Value semantics: String is the only object class that follows value semantics. Modifying the parameter will not affect the variable passed in.

```java
public class MyClass{
public static void main(String[] args){
String x = "hi";
changeMe(x);
System.out.println(x); // hi
}
public static void changeMe(String x){
x = "hello";
}
}
```

Note: The value of x in main did not change.


#### Silly Strings

```java
String beans;
String cheese;
String quartet;
String bikini;
String theory;

String school = "Hogwarts: School for Pigs";
String headmaster = "Kevin Bacon";
String teacher = "Brad Pig";
String gf = "Piggy Azalea";

String fav_book = "Hamlet";
String fav_char_star_wars = "Ham Solo";
String fav_char_star_wars_2 = "ChewBacon";
```


#### Lab 2

Create a new repl on repl.it. Implement the driver class(Main.java) to include two methods: printName and pigLatin.

printName: static, void method which takes a String input which represents a full name in the format: first name, a space, middle name, space and last name. The method extracts first, middle and last name and prints them. Use Scanner class to take input.(String full_name = console.nextLine();).

input: "Michael Benjamin Smith"

print output: First: Michael Middle: Benjamin Last: Smith


#### Lab 2: Extracting Substring

pigLatin: static, method which takes a String input and returns the string in Pig Latin:take the first letter and put it at the end of the word and add the letters "ay" to the end. For example:

input: "pig"

returns: "igpay"


---


#### Math And Wrapper Classes


#### Static Methods

The Math class has many useful static methods. The class is part of the java.lang package(group of classes) that is available by default(no need to import to use). To call these, use the syntax:

```java
Math.methodName(parameters);

double answer = Math.sqrt(9.2);
int b = Math.round(5.6755);
```


#### Java's Math class

| Method name                              | Description                                                  |
| ---------------------------------------- | ------------------------------------------------------------ |
| int abs(int x)<br>double abs(double x)   | returns the absolute value of a int or double value (overloaded method) |
| double pow(double base, double exponent) | Returns the value of the first parameter raised to the power of the second parameter |
| double sqrt(double x)                    | Returns the positive square root of a double value           |
| double random()                          | Returns a random double value greater than or equal to 0.0 and less than 1.0 |

| Constant | Description  |
| -------- | ------------ |
| Math.E   | 2.7182818... |
| Math.PI  | 3.1415926... |


#### Calling Math methods

Examples:

```java
double squareRoot = Math.sqrt(121.0);
System.out.println(squareRoot);           // 11.0

int absoluteValue = Math.abs(-50);
System.out.println(absoluteValue);        // 50

System.out.println(Math.min(3, 7) + 2);   // 5
```

The Math methods do not print to the console. Each method produces ("returns") a numeric result. Remember to store, print or use the result in some expression


#### Math questions

Evaluate the following expressions:

```java
Math.abs(-1.23)
Math.pow(3, 2)
Math.pow(10, -2)
Math.sqrt(121.0) - Math.sqrt(256.0)
```


#### Math questions

Write a method withinHalf which takes two double parameters and return true if they are within .5 of each other and false otherwise.

```java
withinHalf(4,5.1) // returns false
withinHalf(3.4,3.9) // returns true
withinHalf(3.9,3.4) // returns true
withinHalf(-1.2,-1.1) // returns true

public static boolean withinHalf(double x, double y)
{
return Math.abs(x - y) <= .5;
}
```


#### Quirks of real numbers

Some Math methods return double or other non-int types.

```java
int x = Math.pow(10, 3);   // ERROR: incompat. types
```

Some double values print poorly (too many digits).

```java
double result = 1.0 / 3.0;
System.out.println(result);    // 0.3333333333333
```

The computer represents doubles in an imprecise way.

```java
System.out.println(0.1 + 0.2);
```

Instead of 0.3, the output is 0.30000000000000004


#### Random Numbers


#### Random numbers

```java
Math.random() produces a number from 0(inclusive) to 1 exclusive.

double x = Math.random(); // 0.0 <= x < 1.0
double x = 3 * Math.random(); // 0.0 <= x < 3.0
double x = Math.random() + 2; // 2.0 <= x < 3.0
double x = 5 * Math.random() + 4; // 4.0 <= x <9.0
```

In general, to produce a random real number in the range [low,high),

```java
double x = (high - low) * Math.random() + low;

Generate a random real value in [7.0,15.0).
double x = 8 * Math.random() + 7;
```


#### Random Integers

How do we generate random integers? Use casting!

```java
int x = (int)(100 * Math.random());
// random integer 0 to 99 inclusive.

int y = (int)(100 * Math.random()) + 4;
// random integer 4 to 103 inclusive.

int z = (int)(2 * Math.random());
// random integer 0 or 1, useful for heads/tails
```


#### More Examples

```java
int x = (int) Math.random() * 5;
// x = 0

int y = (int)(6 * Math.random()) - 10;
// integer from -10 to -5 inclusive.

double z = 3 * Math.random() + 5;
//random double in [5,8)
```


#### Wrapper Classes

A wrapper class takes an existing value of primitive type and "wraps" or "boxes" it in an object, and provides a new set of methods for that type.

It can be used in Java container classes that requires the item to be objects. (Arraylist)


#### Wrapper Classes

The wrapper class allows

The construction of an object from a single value(wrapping or boxing the primitive in a wrapper object. The retrieval of a primitive value(unwrapping or unboxing from a wrapper object.)


#### Wrapper Classes

You will need to know two wrapper classes:

```java
Integer class
Double class
```


#### Wrapper Classes

```java
Integer and Double are wrapper classes...not Rapper Classes.
```

These are Rapper Classes:

```java
public class Tupac{...}
public class Biggie extends Tupac{...}
public class JayZ extends Biggie{...}
public class KendrickLamar extends Biggie{...}
```


#### Integer Class


#### Double Class

The Double class wraps a value of type double in an object.

Here are two useful methods:

Double(double value): Constructs an Double object from an double.

double doubleValue(): Returns the value of this Double as a double


#### Examples

```java
Integer intObj = new Integer(6);//boxes 6 in Integer object
int j = intObj.intValue(); //unboxes 6 from Integer object

Double dObj = new Double(2.5);//boxes 2.5 in Double object
double d = dObj.doubleValue(); //unboxes 2.5 from Double object
```


#### Auto-Boxing and Unboxing

Auto-boxing is the automatic boxing of primitive types in their wrapper classes.

To retrieve the value of an Integer(or Double), the intValue() or doubleValue() method can be called(unboxing).

Auto-unboxing is the automatic conversion of a wrapper class to its corresponding primitive type. This means you don't need to explicitly call the intValue() or doubleValue().


#### Autoboxing and Auto-unboxing

```java
Integer a = new Integer(5);
int x = a.intValue(); // unboxing x = 5
int y = a; // auto-unboxing, easier.

Integer b = new Integer(7); // boxing
Integer c = 7; // auto-boxing
int z = a + x; // auto-unboxing

Double d = new Double(7.5); // boxing
double e = d.doubleValue(); // unboxing
double f = d + 2.0; // auto-unboxing
```
