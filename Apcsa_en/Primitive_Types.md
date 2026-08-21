## 📚Unit 1: Primitive Types

### 📌What is Java?

What do Minecraft, Android phones, and Netflix have in common?

They’re all programmed in Java!

Many of the apps you use in an Android phone or tablet are also written in Java.

Netflix uses Java for some of its software too.

Java is used worldwide to create software that we all use.

### 🖥️  Software

- Visual studio code
- Github
- Chatgpt

### 🗓️  Teaching Arrangement

| Lesson   | Topic                    | Learning Objectives                                   |
| -------- | :----------------------- | ----------------------------------------------------- |
| Lesson 1 | Primitive Types          | 掌握变量定义、字符串、整数、浮点数、布尔值等基础      |
| Lesson 2 | Using Objects            | 对象与引用、构造器调用、形参与实参等                  |
| Lesson 3 | Boolean Expressions & If | 布尔与比较、逻辑运算与短路、优先级与括号、if 语句写法 |
| Lesson 4 | Iteration                | for、while语句                                        |
| Lesson 5 | Writing Classes          | class、public、private、static、overload等            |
| Lesson 6 | Arrays                   | 声明、创建、初始化数组、参数传递、浅/深拷贝           |
| Lesson 7 | ArrayList                | ArrayList<Integer> list 增删改查                      |
| Lesson 8 | 2D Arrays                | 声明/创建/初始化二维数组                              |
| Lesson 9 | Recursion                | 递归、迭代、分治等                                    |

### 📝Demo

```java
public class Main {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
    }
}
```

```java
public class Main {
    public static void main(String[] args) {
        System.out.println("参数个数 = " + args.length);
        for (int i = 0; i < args.length; i++) {
            System.out.println(i + ": " + args[i]);
        }
    }
}
```

###  Compile & Run java program

```java
$ java Main.java
```

---

## 📌Java Programming Language

Java is a **programming language**, which means that we can use Java to tell a computer what to do.

Computers don’t actually speak Java, so we have to **compile** (translate) Java source files into class files.

### Java Source File

Java source files end in:

```text
.java
```

### Java Class File

Compiled Java class files end in:

```text
.class
```

The source file is something humans can read and edit.

The class file is code that a computer can understand and can run.

### Structure of a Java Program

The basic structure of a Java program is:

```java
public class name {
    public static void main(String[] args) {
        statement;
        statement;
        ...
        statement;
    }
}
```

Every executable Java program consists of:

- a **class**, called the driver class,
- that contains a method named `main`,
- that contains the statements (commands) to be executed.

In simple terms:

```text
class → a program

statement → a command to be executed

method → a named group of statements
```

## 📌File Naming

The name of the class has to match up with the name of the file.

For example, if the class is called:

```java
Main
```

then the name of the file is:

```text
Main.java
```

Example:

```java
public class Main {
    public static void main(String[] args) {
        
    }
}
```

File name:

```text
Main.java
```

## 📌Printing

There are two ways to print output on the console:

```java
System.out.println()
```

and

```java
System.out.print()
```

### System.out.println()

`System.out.println()` is the way that you ask Java to print out the value of something followed by a **new line**.

The `ln` means that Java advances to the next line after printing.

Example:

```java
System.out.println("Hello");
System.out.println("World");
```

Output:

```text
Hello
World
```

### System.out.print()

`System.out.print()` without the `ln` will print something **without advancing to the next new line**.

Example:

```java
System.out.print("Hello");
System.out.print("World");
```

Output:

```text
HelloWorld
```

### System.out.println Example

```java
public class Welcome {
    public static void main(String[] args) {
        System.out.println("Hi there!");
        System.out.println("Welcome to APCS A!");
    }
}
```

Output:

```text
Hi There!
Welcome to APCS A!
```

The `System` in:

```java
System.out.println()
```

must be capitalized.

The command line must also end with a semicolon:

```java
;
```

### System.out.print Example

```java
public class SecondClass {
    public static void main(String[] args) {
        System.out.print("Hi there!");
        System.out.println("Welcome to APCS A!");
        System.out.print("We will learn Java!");
    }
}
```

Output:

```text
Hi There!Welcome to APCS A!
We will learn Java!
```

### Question

Why are there two lines of output?

The first statement:

```java
System.out.print("Hi there!");
```

does not move to a new line.

Therefore, the second statement continues printing on the same line:

```java
System.out.println("Welcome to APCS A!");
```

After `println`, Java moves to the next line.

Therefore:

```java
System.out.print("We will learn Java!");
```

appears on the second line.

### 📌Find the Errors

Consider the following Java program:

```java
pooblic class Errors
    public static void main(String args){
        System.out.print("Good morning! ")
        system.out.print("Good afternoon!);
        System.Print "And good evening!";
}
```

### **Corrected Version**

```java
public class Errors {
    public static void main(String[] args) {
        System.out.print("Good morning! ");
        System.out.print("Good afternoon!");
        System.out.print("And good evening!");
    }
}
```

---

## 📌Strings

### String Definition

A **string** is a sequence of characters to be printed.

A string starts and ends with a double quote character:

```text
"
```

The quotes do not appear in the output.

Examples:

```java
"hello"
```

```java
"This is a string. It's very long!"
```

A string enclosed in quotes is called a **string literal**.

## String Restrictions

### Restriction 1: A String May Not Span Multiple Lines

This is not a legal string:

```java
"This is not
a legal String."
```

A normal string literal must remain on one line.

```java
System.out.println("This is not\na legal String.");
```

### Restriction 2: A String May Not Directly Contain a `"` Character

This is not a legal string:

```java
"This is not a "legal" String either."
```

The quotation marks inside the string interfere with the quotation marks that mark the beginning and end of the string.

```java
"This is not a \"legal\" String either."
```

## Comments

### What is a Comment?

A **comment** is a note written in source code by the programmer to describe or clarify the code.

Comments are **not executed** when your program runs.

### Single-Line Comments

Syntax:

```java
// comment text
```

Example:

```java
// This is a one-line comment.
```

Everything after `//` on that line is treated as a comment.

### Multi-Line Comments

Syntax:

```java
/* comment text; may span multiple lines */
```

Example:

```java
/* This is a very long
   multi-line
   comment. */
```

Multi-line comments begin with:

```java
/*
```

and end with:

```java
*/
```

### Where to Place Comments

Comments can be placed:

- at the top of each file — a **comment header**
- at the start of every method
- to explain complex pieces of code

### Why Comments Are Useful

Comments are useful for:

1. Understanding larger, more complex programs.
2. Helping multiple programmers work together.
3. Helping programmers understand each other's code.

### Comments Example

```java
/* Suzy Student, CS 101, Fall 2019
   This program prints lyrics about ... something. */
public class BaWitDaBa {
    public static void main(String[] args) {
        
        // first verse
        System.out.println("Bawitdaba");
        System.out.println("da bang a dang diggy diggy");
        System.out.println();

        // second verse
        System.out.println("diggy said the boogy");
        System.out.println("said up jump the boogy");
    }
}
```

In this example:

```java
/* Suzy Student, CS 101, Fall 2019
   This program prints lyrics about ... something. */
```

is a multi-line comment used as a comment header.

The following comments:

```java
// first verse
```

and

```java
// second verse
```

describe different sections of the program.

### Indent Nicely!

Consider the following code:

```java
public class Welcome{ public static void main(String[]
args){ System.out.println("Hi there!"
);System.out.println("Welcome to APCS A!");}}
```

The code above will compile and run correctly.

Java ignores whitespace.

However, the code is very hard to read.

Therefore, you should make an effort to **indent nicely**.

## Properly Indented Version

```java
public class Welcome {
    public static void main(String[] args) {
        System.out.println("Hi there!");
        System.out.println("Welcome to APCS A!");
    }
}
```

Proper indentation makes the structure of the program much easier to understand.

***

## Lab 1

Use vscode and write a program that has the following outputs.

You must use **exactly 5 different print statements**.

You may use:

```java
System.out.println()
```

and/or:

```java
System.out.print()
```

### Required Output

```text
I am Sam. Sam I am. I do not like them, Sam-I-am.
I do not like green eggs and ham.
```

### Requirement

Use exactly:

```text
5 print statements
```

The statements may be any combination of:

```java
System.out.print()
```

and:

```java
System.out.println()
```

---

## 📌Variables and Datatypes

### Data Types

A **type** is:

- a set of values, such as integers and floating-point numbers
- a set of operations, such as:

```text
+  -  *  /
```

Data types can be categorized as either:

- **Primitive types**
- **Reference types**

The primitive data types used in this course define the set of operations for:

- numbers
- Boolean values (`true` or `false`)

Reference variables, or object variables, hold a **reference (or address)** to an object of a class.

More about reference variables will be introduced later.

## Variables

A variable can be thought of like the Memory Store / Memory Recall buttons on a calculator**.

Variables must be declared before they are used, just like methods.

## Primitive Types

The primitive types on the APCSA exam are:

## int

`int` stores integers, or whole numbers.

Examples:

```java
3
-76
20393
```

## double

`double` stores floating-point numbers, or decimal numbers.

Examples:

```java
6.3
-0.9
60293.93032
```

## boolean

`boolean` stores Boolean values.

The only Boolean values are:

```java
true
false
```

## Receipt Example

Consider the following code:

```java
public class Receipt {
    public static void main(String[] args) {
        // Calculate total owed, assuming 8% tax / 15% tip
        System.out.println("Subtotal:");
        System.out.println(38 + 40 + 30);

        System.out.println("Tax:");
        System.out.println((38 + 40 + 30) * .08);

        System.out.println("Tip:");
        System.out.println((38 + 40 + 30) * .15);

        System.out.println("Total:");
        System.out.println(
            38 + 40 + 30 +
            (38 + 40 + 30) * .08 +
            (38 + 40 + 30) * .15
        );
    }
}
```

## What's Bad About This Code?

There are two main problems:

1. The subtotal expression is repeated many times.:

```java
38 + 40 + 30
```

2. There are many `println` statements.

We will use **variables** to solve these problems.

```java
public class Receipt {
    public static void main(String[] args) {
        // Calculate total owed, assuming 8% tax / 15% tip

        int subtotal = 38 + 40 + 30;

        double tax = subtotal * 0.08;
        double tip = subtotal * 0.15;

        double total = subtotal + tax + tip;

        System.out.println("Subtotal: " + subtotal);
        System.out.println("Tax: " + tax);
        System.out.println("Tip: " + tip);
        System.out.println("Total: " + total);
    }
}
```

## Variables

A **variable** is a piece of the computer's memory that:

- is given a name
- is given a type
- can store a value

A variable can be compared to:

- preset stations on a car stereo
- speed dial on a cell phone

## Steps for Using a Variable

There are three basic steps:

1. **Declare it**
   - State its name and type.

2. **Initialize it**
   - Store a value into it.

3. **Use it**
   - Print it or use it as part of an expression.

## Declaration

A **variable declaration** sets aside memory for storing a value.

Variables must be declared before they can be used.

## Syntax

```java
type name;
```

The variable name is an **identifier**.

Examples:

```java
int x;
```

```java
double myGPA;
```

These declarations create variables named:

```text
x
myGPA
```

## Assignment

An **assignment** stores a value into a variable.

The value can be an expression.

If an expression is used, the variable stores the **result of the expression**.

## Syntax

```java
name = expression;
```

Example:

```java
int x;
x = 3;
```

The variable `x` now stores:

```text
3
```

Another example:

```java
double myGPA;
myGPA = 1.0 + 2.25;
```

The expression:

```java
1.0 + 2.25
```

is evaluated first.

Therefore:

```text
myGPA = 3.25
```

## Using Variables

Once a variable has been given a value, it can be used in expressions.

Example:

```java
int x;
x = 3;
System.out.println("x is " + x);
```

Output:

```text
x is 3
```

The variable can also be used in mathematical expressions:

```java
System.out.println(5 * x - 1);
```

Since:

```text
x = 3
```

the result is:

```text
14
```

## Reassigning Variables

You can assign a value to the same variable more than once.

Example:

```java
int x;
x = 3;
System.out.println(x + " here");
```

Output:

```text
3 here
```

Then:

```java
x = 4 + 7;
System.out.println("now x is " + x);
```

Output:

```text
now x is 11
```

The value stored in `x` changes from:

```text
3
```

to:

```text
11
```

## String Concatenation

When a string is combined with a number using `+`, Java performs **string concatenation**.

```text
string + number = concatenated string
```

Example:

```java
int x = 3;

System.out.println("x is " + x);
```

Output:

```text
x is 3
```

More about string concatenation will be introduced later.

---





# Declaration and Initialization

A variable can be **declared and initialized in one statement**.

## Syntax

```java
type name = value;
```

Example:

```java
double myGPA = 3.95;
```

Now:

```text
myGPA = 3.95
```

Another example:

```java
int x = (12 - 3) * 2;
```

The expression is evaluated first:

```text
(12 - 3) * 2
= 9 * 2
= 18
```

Therefore:

```text
x = 18
```

---

# Assignment and Algebra

Assignment uses:

```java
=
```

However, assignment is **not an algebraic equation**.

In Java:

```java
=
```

means:

> Store the value on the right in the variable on the left.

The expression on the right side is evaluated first.

Then its result is stored in the variable on the left.

---

## Example

```java
int x = 3;

x = x + 2;
```

In mathematics:

```text
x = x + 2
```

would have no solution.

But in Java, it is not an equation.

Java evaluates the right side first:

```text
x + 2
```

Since:

```text
x = 3
```

we get:

```text
3 + 2 = 5
```

Then Java stores `5` in `x`.

Therefore:

```text
x = 5
```

---

# Increasing a Variable

The statement:

```java
x = x + 2;
```

increases the value stored in variable `x` by two.

For example:

```java
int x = 3;

x = x + 2;
```

After the assignment:

```text
x = 5
```

---

# Multiple Variables

Multiple variables of the same type can be declared and initialized at the same time.

## Declaration Syntax

```java
type name1, name2, name3;
```

Example:

```java
int x, y, z;
```

This declares three integer variables:

- `x`
- `y`
- `z`

---

## Declaration and Initialization Syntax

```java
type name1 = value1, name2 = value2, name3 = value3;
```

Example:

```java
int a = 1, b = 2, c = 3;
```

This declares and initializes three integers:

```text
a = 1
b = 2
c = 3
```

---

# Assignment and Types

A variable can only store a value of its own type.

For example:

```java
int x = 2.5;
```

This causes an error:

```text
ERROR: incompatible types
```

because `2.5` is a floating-point value and `x` is an `int`.

---

# Storing int Values in double Variables

An `int` value can be stored in a `double` variable.

Java converts the integer into the equivalent real number.

Example:

```java
double myGPA = 4;
```

The stored value becomes:

```text
4.0
```

Therefore:

```text
myGPA = 4.0
```

---

# Compiler Errors

## 1. Order Matters

Assignment must have the variable on the left.

Incorrect:

```java
int x;

7 = x;
```

This causes an error.

Correct:

```java
int x;

x = 7;
```

---

## 2. A Variable Must Have a Value Before It Is Used

Incorrect:

```java
int x;

System.out.println(x);
```

This causes an error because:

```text
x has no value
```

---

## 3. You Cannot Declare the Same Variable Twice

Incorrect:

```java
int x;
int x;
```

This causes an error because `x` already exists.

Another incorrect example:

```java
int x = 3;
int x = 5;
```

Again, this causes an error because `x` has already been declared.

If you want to change its value, use assignment instead:

```java
int x = 3;

x = 5;
```

---

# Printing a Variable's Value

Use `+` to print a string and a variable's value on the same line.

Example:

```java
double grade = (95.1 + 71.9 + 82.6) / 3.0;

System.out.println("Your grade was " + grade);
```

Output:

```text
Your grade was 83.2
```

Another example:

```java
int students = 11 + 17 + 4 + 19 + 14;

System.out.println(
    "There are " + students +
    " students in the course."
);
```

Output:

```text
There are 65 students in the course.
```

---

# Receipt Question

Improve the receipt program using variables.

Original program:

```java
public class Receipt {
    public static void main(String[] args) {
        // Calculate total owed, assuming 8% tax / 15% tip

        System.out.println("Subtotal:");
        System.out.println(38 + 40 + 30);

        System.out.println("Tax:");
        System.out.println((38 + 40 + 30) * .08);

        System.out.println("Tip:");
        System.out.println((38 + 40 + 30) * .15);

        System.out.println("Total:");
        System.out.println(
            38 + 40 + 30 +
            (38 + 40 + 30) * .15 +
            (38 + 40 + 30) * .08
        );
    }
}
```

---

# Receipt Answer

The program can be improved by storing important values in variables.

```java
public class Receipt {
    public static void main(String[] args) {
        // Calculate total owed, assuming 8% tax / 15% tip

        int subtotal = 38 + 40 + 30;

        double tax = subtotal * .08;

        double tip = subtotal * .15;

        double total = subtotal + tax + tip;

        System.out.println("Subtotal: " + subtotal);

        System.out.println("Tax: " + tax);

        System.out.println("Tip: " + tip);

        System.out.println("Total: " + total);
    }
}
```

---

# Type boolean

A `boolean` is a logical type whose values are:

```java
true
false
```

Example:

```java
int age = 22;

boolean minor = (age < 21);

boolean lovesAPCS = true;

System.out.println(minor);

System.out.println(lovesAPCS);
```

Output:

```text
false
true
```

Explanation:

```java
age < 21
```

is false because:

```text
age = 22
```

Therefore:

```java
minor = false
```

Meanwhile:

```java
boolean lovesAPCS = true;
```

directly assigns the value `true`.

---

# final

The keyword:

```java
final
```

can be used in front of a variable declaration to make the variable a **constant that cannot be changed**.

Constants are traditionally written using uppercase letters.

Example:

```java
public class TestFinal {
    public static void main(String[] args) {

        final double PI = 3.14;

        System.out.println(PI);

        PI = 4.2;
    }
}
```

The following statement causes an error:

```java
PI = 4.2;
```

because `PI` was declared using:

```java
final
```

and therefore cannot be changed.

---

# Naming Variables

The name of a variable should describe the data that it holds.

For example:

```java
score
```

is a useful variable name because it helps explain what the variable stores.

A name like:

```java
x
```

is usually not a good variable name in programming because it gives no clue about what kind of data it stores.

Avoid unnecessarily long variable names such as:

```java
thisIsAReallyLongName
```

especially on the AP exam.

The goal is to make the code easier to understand, not harder.

---

# Variable Naming Convention

In Java and many other programming languages, variable names normally begin with a **lowercase letter**.

If the name contains multiple words, capitalize the first letter of each additional word.

Example:

```java
int numOfLives = 3;
```

This naming style is called:

## camelCase

For example:

```text
numOfLives
playerScore
studentName
totalPrice
```

---

# Why Use camelCase?

Variable names cannot contain spaces.

For example, this is not allowed:

```text
num of lives
```

Instead, Java programmers can write:

```java
numOfLives
```

Capitalizing each additional word makes the variable name easier to read.

---

# Using Underscores

Another option is to use the underscore symbol:

```text
_
```

to separate words.

Example:

```java
int num_of_lives = 3;
```

However, variable names still cannot contain spaces.

---

# Java Is Case Sensitive

Java is **case sensitive**.

Therefore:

```java
playerScore
```

and:

```java
playerscore
```

are considered different identifiers.

Similarly:

```java
myGPA
```

and:

```java
mygpa
```

are different variable names.

---

# Keywords

A **keyword** is an identifier that cannot be used as a variable name because it already has a reserved meaning in Java.

Java keywords listed in the slides include:

```text
abstract
boolean
break
byte
case
catch
char
class
const
continue

default
do
double
else
extends
final
finally
float
for
goto

if
implements
import
instanceof
int
interface
long
native
new
package

private
protected
public
return
short
static
strictfp
super
switch
synchronized

this
throw
throws
transient
try
void
volatile
while
```

For example, you cannot write:

```java
int class = 3;
```

because:

```java
class
```

is already a Java keyword.

Likewise:

```java
int public = 5;
```

is invalid because:

```java
public
```

is reserved by Java.

---

# repl.it Assignments

The following labs are **repl.it assignments**.

Log on to your account to complete them.

They are included in the slides for reference.

---

# Lab 1: Create Variables and Printing

Complete the **Create Variables and Printing** assignment on repl.it.

---

# Lab 2: Create Variables and Printing 2

Complete the **Create Variables and Printing 2** assignment on repl.it.

---

# Lab 3: Create Variables and Printing Them

Complete the **Create Variables and Printing Them** assignment on repl.it.

---

## Arithmetic Operations

### Expressions

An **expression** is a value or operation that computes a value.

Examples:

```java
1 + 4 * 5
```

```java
(7 + 2) * 6 / 3
```

```java
42
```

The simplest expression is a **literal value**.

A complex expression can use:

- operators
- parentheses

---

# Arithmetic Operators

An **operator** combines multiple values or expressions.

| Operator | Meaning                 |
| -------- | ----------------------- |
| `+`      | Addition                |
| `-`      | Subtraction or negation |
| `*`      | Multiplication          |
| `/`      | Division                |
| `%`      | Modulus / remainder     |

As a program runs, its expressions are evaluated.

Example:

```java
1 + 1
```

evaluates to:

```text
2
```

Example:

```java
System.out.println(3 * 4);
```

prints:

```text
12
```

To print the text:

```text
3 * 4
```

instead of evaluating it, place it inside quotation marks:

```java
System.out.println("3 * 4");
```

---

# Integer Division with `/`

When we divide integers, the quotient is also an integer.

Example:

```java
14 / 4
```

The result is:

```text
3
```

not:

```text
3.5
```

More examples:

```java
32 / 5
```

Result:

```text
6
```

```java
84 / 10
```

Result:

```text
8
```

```java
156 / 100
```

Result:

```text
1
```

Dividing an integer by `0` causes an error when the program runs.

This error is called an:

```text
ArithmeticException
```

---

# Integer Remainder with `%`

The `%` operator computes the **remainder from integer division**.

Examples:

```java
14 % 4
```

Result:

```text
2
```

```java
218 % 5
```

Result:

```text
3
```

---

# Applications of the `%` Operator

## Obtain the Last Digit of a Number

```java
230857 % 10
```

Result:

```text
7
```

---

## Obtain the Last Four Digits

```java
658236489 % 10000
```

Result:

```text
6489
```

---

## Determine Whether a Number Is Odd or Even

```java
7 % 2
```

Result:

```text
1
```

```java
42 % 2
```

Result:

```text
0
```

---

# Important `%` Example

What is:

```java
8 % 20
```

The answer is:

```text
8
```

not:

```text
0
```

---

# `%` Example

```java
public static void main(String[] args) {
    System.out.println(45 % 6);
    System.out.println(2 % 2);
    System.out.println(8 % 10);
    System.out.println(11 % 0);
    System.out.println(-21 % 4); // probably not on AP
    System.out.println(21 % -4); // probably not on AP
}
```

Output:

```text
3
0
8
ArithmeticException
-1
1
```

---

# Expressions: Making Change

Find the exact change for:

```text
137 cents
```

using:

- quarters
- dimes
- nickels
- pennies

Use the least number of coins.

---

## Step 1: Quarters

How many quarters?

```java
137 / 25
```

Result:

```text
5 quarters
```

This uses **integer division**.

What's leftover?

```java
137 % 25
```

Result:

```text
12 cents
```

---

## Step 2: Dimes

How many dimes?

```java
12 / 10
```

Result:

```text
1 dime
```

What's leftover?

```java
12 % 10
```

Result:

```text
2 cents
```

---

## Step 3: Nickels

How many nickels?

```java
2 / 5
```

Result:

```text
0 nickels
```

What's leftover?

```java
2 % 5
```

Result:

```text
2 cents
```

---

## Step 4: Pennies

How many pennies?

```java
2 / 1
```

Result:

```text
2 pennies
```

Therefore, 137 cents can be represented using:

```text
5 quarters
1 dime
0 nickels
2 pennies
```

---

# Even or Odd

An important use of the `%` operator is testing for **divisibility**.

For example:

- Is a number even or odd?
- Is a number a multiple of 3?

---

## Testing Whether a Number Is Even

A number is even if it has no remainder when divided by `2`.

```java
if (number % 2 == 0) {
    ...
}
```

---

## Testing Whether a Number Is a Multiple of 3

```java
if (number % 3 == 0) {
    ...
}
```

---

# Precedence

**Precedence** means the order in which operators are evaluated.

Generally, operators at the same precedence level evaluate from **left to right**.

Example:

```java
1 - 2 - 3
```

is evaluated as:

```java
(1 - 2) - 3
```

Result:

```text
-4
```

---

# Operator Precedence

The operators:

```text
* / %
```

have higher precedence than:

```text
+ -
```

Example:

```java
1 + 3 * 4
```

Multiplication happens first:

```text
3 * 4 = 12
```

Then:

```text
1 + 12 = 13
```

Result:

```text
13
```

---

# Precedence Example

Consider:

```java
6 + 8 / 2 * 3
```

First:

```java
8 / 2 = 4
```

Then:

```java
4 * 3 = 12
```

Then:

```java
6 + 12 = 18
```

Therefore:

```text
18
```

---

# Parentheses

Parentheses can force a certain order of evaluation.

Example:

```java
(1 + 3) * 4
```

First:

```java
1 + 3 = 4
```

Then:

```java
4 * 4 = 16
```

Result:

```text
16
```

---

# Spacing and Precedence

Spacing does **not** affect the order of evaluation.

Example:

```java
1+3 * 4-2
```

is evaluated according to operator precedence.

```text
1 + 12 - 2
= 11
```

---

# Precedence Examples

## Example 1

```java
1 * 2 + 3 * 5 % 4
```

Step 1:

```text
1 * 2 = 2
```

So:

```java
2 + 3 * 5 % 4
```

Step 2:

```text
3 * 5 = 15
```

So:

```java
2 + 15 % 4
```

Step 3:

```text
15 % 4 = 3
```

So:

```java
2 + 3
```

Result:

```text
5
```

---

## Example 2

```java
1 + 8 % 3 * 2 - 9
```

Step 1:

```text
8 % 3 = 2
```

So:

```java
1 + 2 * 2 - 9
```

Step 2:

```text
2 * 2 = 4
```

So:

```java
1 + 4 - 9
```

Step 3:

```text
1 + 4 = 5
```

Then:

```text
5 - 9 = -4
```

Result:

```text
-4
```

---

# Integer Division Review

Consider:

```java
15 / 4
```

Since both operands are integers, the result is:

```text
3
```

Consider:

```java
2 / 3
```

The result is:

```text
0
```

---

# Real Numbers — Type `double`

Examples of `double` values:

```java
6.022
-42.0
2.143
```

Placing:

```text
.0
```

or:

```text
.
```

after an integer makes it a `double`.

For example:

```java
42.0
```

is a `double`.

---

# Arithmetic with `double`

The operators:

```text
+ - * / % ()
```

all still work with `double`.

Unlike integer division, division using doubles produces an exact decimal result.

Example:

```java
15.0 / 2.0
```

Result:

```text
7.5
```

Operator precedence remains the same:

```text
()
```

before:

```text
* / %
```

before:

```text
+ -
```

---

# Real Number Example

Consider:

```java
2.0 * 2.4 + 2.25 * 4.0 / 2.0
```

First:

```text
2.0 * 2.4 = 4.8
```

So:

```java
4.8 + 2.25 * 4.0 / 2.0
```

Next:

```text
2.25 * 4.0 = 9.0
```

So:

```java
4.8 + 9.0 / 2.0
```

Next:

```text
9.0 / 2.0 = 4.5
```

So:

```java
4.8 + 4.5
```

Result:

```text
9.3
```

---

# Mixing Types

When an `int` and a `double` are mixed in an operation, the result is a `double`.

Example:

```java
4.2 * 3
```

Result:

```text
12.6
```

The conversion occurs **per operator**, affecting only the operands involved in that operation.

---

# Mixing Types Example 1

Consider:

```java
7 / 3 * 1.2 + 3 / 2
```

First:

```java
7 / 3
```

Since both operands are integers:

```text
7 / 3 = 2
```

So:

```java
2 * 1.2 + 3 / 2
```

Then:

```text
2 * 1.2 = 2.4
```

So:

```java
2.4 + 3 / 2
```

Next:

```java
3 / 2 = 1
```

not:

```text
1.5
```

Therefore:

```text
2.4 + 1 = 3.4
```

Result:

```text
3.4
```

---

# Mixing Types Example 2

Consider:

```java
2.0 + 10 / 3 * 2.5 - 6 / 4
```

First:

```java
10 / 3 = 3
```

So:

```java
2.0 + 3 * 2.5 - 6 / 4
```

Then:

```java
3 * 2.5 = 7.5
```

So:

```java
2.0 + 7.5 - 6 / 4
```

Next:

```java
6 / 4 = 1
```

So:

```java
2.0 + 7.5 - 1
```

Then:

```text
2.0 + 7.5 = 9.5
```

Finally:

```text
9.5 - 1 = 8.5
```

Result:

```text
8.5
```

---

# Type Casting

A **type cast** is a conversion from one type to another.

Type casting can be used to:

1. Promote an `int` into a `double` to get exact division using `/`.
2. Truncate a `double` into an integer.

---

# Type Casting Syntax

```java
(type) expression
```

Examples:

```java
double result = (double) 19 / 5;
```

Result:

```text
3.8
```

Another example:

```java
int result2 = (int) result;
```

Result:

```text
3
```

Another example:

```java
int x = (int) Math.pow(10, 3);
```

Result:

```text
1000
```

---

# More About Type Casting

Type casting has **high precedence**.

It only casts the item immediately next to it.

Consider:

```java
double x = (double) 1 + 1 / 2;
```

The first `1` becomes a `double`, but:

```java
1 / 2
```

still uses integer division.

Therefore:

```text
1 / 2 = 0
```

and:

```text
x = 1.0
```

---

## Example

```java
double y = 1 + (double) 1 / 2;
```

Here:

```java
(double) 1
```

makes the division use a `double`.

Therefore:

```text
1.0 / 2 = 0.5
```

and:

```text
1 + 0.5 = 1.5
```

So:

```text
y = 1.5
```

---

# Casting an Entire Expression

Parentheses can be used to force the evaluation order.

Example:

```java
double average = (double) (a + b + c) / 3;
```

Here, the sum:

```java
a + b + c
```

is calculated first.

Then the entire sum is converted into a `double`.

---

# Another Way to Convert to `double`

A conversion to `double` can also be achieved by multiplying by `1.0`.

Example:

```java
double average = 1.0 * (a + b + c) / 3;
```

---

# Casting Example

```java
public class Test {
    public static void main(String[] args) {
        System.out.println(1 / 3);
        System.out.println(1.0 / 3);
        System.out.println(1 / 3.0);
        System.out.println((double) 1 / 3);
    }
}
```

Output:

```text
0
0.3333333333333333
0.3333333333333333
0.3333333333333333
```

---

# Casting Example 2

```java
public static void main(String[] args) {
    double x = 4 / 3;
    double y = (double) (125 / 10);
    double z = (double) 28 / 5;

    System.out.println(x + " " + y + " " + z);
}
```

Output:

```text
1.0 12.0 5.6
```

---

# Why Does the Casting Example Produce These Values?

## `x`

```java
double x = 4 / 3;
```

Integer division happens first:

```text
4 / 3 = 1
```

Then `1` is stored as:

```text
1.0
```

---

## `y`

```java
double y = (double) (125 / 10);
```

The parentheses are evaluated first:

```text
125 / 10 = 12
```

Then:

```java
(double) 12
```

becomes:

```text
12.0
```

---

## `z`

```java
double z = (double) 28 / 5;
```

`28` is converted into:

```text
28.0
```

before division.

Therefore:

```text
28.0 / 5 = 5.6
```

---

# Round to the Nearest Integer

Casting can be used to round a number to its nearest integer.

---

## Positive Number

```java
double number = 7.0 / 3;
```

To round a positive number to its nearest integer:

```java
int nearestInt = (int) (number + 0.5);
```

---

## Negative Number

```java
double negNumber = -20.0 / 3;
```

To round a negative number to its nearest integer:

```java
int nearestNegInt = (int) (negNumber - 0.5);
```

The values are:

```text
nearestInt = 2
nearestNegInt = -7
```

---

# Increment and Decrement

Increment and decrement operators are shortcuts for increasing or decreasing a variable's value by `1`.

| Shorthand     | Equivalent Longer Version  |
| ------------- | -------------------------- |
| `variable++;` | `variable = variable + 1;` |
| `variable--;` | `variable = variable - 1;` |

---

# Increment Example

```java
int x = 2;

x++;
```

This is equivalent to:

```java
x = x + 1;
```

Therefore:

```text
x = 3
```

---

# Decrement Example

```java
double gpa = 2.5;

gpa--;
```

This is equivalent to:

```java
gpa = gpa - 1;
```

Therefore:

```text
gpa = 1.5
```

---

# Modify-and-Assign

Java provides shortcuts for modifying a variable's value.

| Shorthand            | Equivalent Longer Version      |
| -------------------- | ------------------------------ |
| `variable += value;` | `variable = variable + value;` |
| `variable -= value;` | `variable = variable - value;` |
| `variable *= value;` | `variable = variable * value;` |
| `variable /= value;` | `variable = variable / value;` |
| `variable %= value;` | `variable = variable % value;` |

Examples:

```java
x += 3;
```

Equivalent to:

```java
x = x + 3;
```

---

```java
gpa -= 0.5;
```

Equivalent to:

```java
gpa = gpa - 0.5;
```

---

```java
number *= 2;
```

Equivalent to:

```java
number = number * 2;
```

---

# Code Tracing

What are the values of `x`, `y`, and `z` after tracing through the following code?

```java
int x = 0;
int y = 5;
int z = 1;

x++;
y -= 3;
z = x + z;
x = y * z;
y %= 2;
z--;
```

Answer:

```text
x = 4
y = 0
z = 1
```

---

# Lab 1

For example, if the list is:

```text
{78, 80, 77}
```

The statistics are:

```text
Average = 78.33333333333333

Variance = 1.5555555555555556

Standard deviation = 1.247219128924647
```

---

# Lab 1: Statistics

Create a new repl on **repl.it** and follow the comments below to write a program that computes some statistics.

```java
public class Statistics {
    public static void main(String[] args) {

        // 1. Declare 3 int variables for grades
        //    and initialize them to 3 values

        // 2. Declare an int variable for the sum of the grades

        // 3. Declare a double variable for the average of the grades

        // 4. Write a formula to calculate the sum of the 3 grades

        // 5. Write a formula to calculate the average of the
        //    3 grades from the sum using division and type casting

        // 6. Print out the average

        // 7. Declare a double variable and calculate the variance

        // 8. Declare a double variable to compute the standard deviation

        // 9. Print out the variance and standard deviation
    }
}
```

---

# Lab 2: Exact Change

Use the following template, or something similar, to write a program that gives exact change with the **least number of coins** for a given number of cents.

Use intermediate variables to help your calculation.

```java
public static void main(String[] args) {

    int totalCents = 137;  // 137 can be any number

    ...

    // your code here
}
```

Expected output for:

```java
int totalCents = 137;
```

is:

```text
5 quarters, 1 dimes, 0 nickels, 2 pennies.
```

---

