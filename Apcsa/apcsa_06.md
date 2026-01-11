## 📚 Arrays

Java语言使用new操作符来创建数组，语法如下：

```java
arrayRefVar = new dataType[arraySize];
```

```java
import java.util.Scanner;
public class Main{
    public static void main(String[] agrs){
        int size=3;
        double[] li=new double[size];
        Scanner sc=new Scanner(System.in);
        li[0]=sc.nextDouble();
        li[1]=sc.nextDouble();
        li[2]=sc.nextDouble();
        double average=0;
        for(int i=0;i<size;i++){
            average+=li[i];
        }
        average/=size;
    //index between 0 and size-1
    /*
    int i=0;
    while(i<size){
       average+=mylist[i];
       i++;
    }
    */
    System.out.println("Average is "+average);
    //Arrays.toString(average)
  }
}
```

### For-Each 循环

```java
public class Main{
   pulic static void main(String[] args){
      double[] mylist={1.0,2.0,3.0,3.1};
      for(double value:mylist){
         System.out.println(value);
      }
   }
}
```

### **数组作为函数的参数**

```java
import java.util.*;

public class Main{
    public static void main(String[] agrs){
        double[] li={1.0,2.0,3.0};
        printArray(li);
    }
    public static void printArray(double[] array) {
    for (int i = 0; i < array.length; i++) {
        System.out.print(array[i] + " ");
    }
    System.out.print("\n");
  }
}
```

### **返回数组**

```java
import java.util.*;

public class Main{
    public static void printArray(double[] array) {
    for (int i = 0; i < array.length; i++) {
        System.out.print(array[i] + " ");
    }
    System.out.print("\n");
    }
    public static double[] reverse(double[] array){
        double[] result=new double[array.length];
        for(int i=0,j=array.length-1;i<array.length;i++,j--){
            result[i]=array[j];
        }
        return result;
    }
    public static void main(String[] agrs){
        double[] li={1.0,2.0,3.0};
        printArray(li);
        printArray(reverse(li));
    }
  }
```

### 多维数组

```java
int[][] a = new int[2][3];
```

***

**Case 1:**

1. 返回最大数

```java
public class Main{
   pulic static void main(String[] args){
      double[] mylist={1.0,2.0,3.0,3.1};
      int largest=mylist[0];
      for(double value:mylist){
          if(value>largest){
            largest=value;
          }
      }
      System.out.println(value);
   }
  return 0;
}
```

2. 判断所有的数是否有偶数

```java
public class Main{
  public static void main(String[] args){
    for(int i=0;i<array.length;i++){
        if(array[i]%2!=0){
          return false;
        } 
    }
    return true;
  }
}
```

3. reverse数组

```java
import java.util.*;
public class Main{
  public static void main(String[] args){
    int[] numbers={1,2,3,4,5,6};
    reverse(numbers);
    System.out.println(Arrays.toString(numbers));
  }
  public static void reverse(int[] x){
    for(int i=0;i<x.length/2;i++){
      int temp=x[i];
      x[i]=x[x.length-1-i];
      x[x.length-1-i]=temp;
    }
  }
}
```

***

[P1428](https://www.luogu.com.cn/problem/P1428)

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] cnt = new int[11];   // 0..10
        int[] ans = new int[n];

        for (int i = 0; i < n; i++) {
            int a = sc.nextInt();
            int s = 0;
            for (int v = 0; v < a; v++) s += cnt[v];
            ans[i] = s;
            cnt[a]++;
        }

        for (int i = 0; i < n; i++) {
            if (i > 0) System.out.print(" ");
            System.out.print(ans[i]);
        }
    }
}

```

[P5727](https://www.luogu.com.cn/problem/P5727)

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long n = sc.nextLong();

        ArrayList<Long> seq = new ArrayList<Long>();
        while (true) {
            seq.add(n);
            if (n == 1) break;
            if (n % 2 == 1) n = n * 3 + 1;
            else n /= 2;
        }

        for (int i = seq.size() - 1; i >= 0; i--) {
            if (i != seq.size() - 1) System.out.print(" ");
            System.out.print(seq.get(i));
        }
    }
}

```

[P5728](https://www.luogu.com.cn/problem/P5728)

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] c = new int[n],m = new int[n], e = new int[n];
        int sum = new int[n];

        for (int i = 0; i < n; i++) {
            c[i] = sc.nextInt();
            m[i] = sc.nextInt();
            e[i] = sc.nextInt();
            sum[i] = c[i] + m[i] + e[i];
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (Math.abs(c[i] - c[j]) <= 5 &&
                    Math.abs(m[i] - m[j]) <= 5 &&
                    Math.abs(e[i] - e[j]) <= 5 &&
                    Math.abs(sum[i] - sum[j]) <= 10) {
                    ans++;
                }
            }
        }
        System.out.println(ans);
    }
}

```