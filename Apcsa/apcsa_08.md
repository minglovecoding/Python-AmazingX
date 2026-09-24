## 📚2D Arrays

多维数组可以看成是数组的数组，比如二维数组就是一个特殊的一维数组，其每一个元素都是一个一维数组，例如：

```java
String[][] str = new String[3][4];
```

### 二维数组的动态初始化

1. 直接为每一维分配空间，例如：

```java
int[][] matrix = new int[2][3];
int [][] mat={{1,2,3},{1,2},{3,4,5}};
//mat[0]={1,2,3}
//mat[1]={1,2}
//mat[2]={3,4,5}
//row: mat.length、column: mat[0].length
String [][] seatinginfo={{"America","Bob"},{"Jake","rose"}};
```

```java
import java.util.*;
public class Main{
    public static void main(String args[]){
        int[][] mat={{1,2,3},{4,5,6},{7,8,9}};
        for(int i=0;i<mat.length;i++){
            for(int j=0;j<mat[0].length;j++){
                System.out.print(mat[i][j]+" ");
            }
            System.out.println();
        }
    }
}
```

2. 从最高维开始，分别为每一维分配空间，例如：

```java
String[][] s = new String[2][];
s[0] = new String[2];
s[1] = new String[3]; 
s[0][0] = new String("Good");
s[0][1] = new String("Luck");
s[1][0] = new String("to");
s[1][1] = new String("you");
s[1][2] = new String("!");
```

遍历2D数组

```java
import java.util.*;
public class Main{
    public static void main(String[] agrs){
      int [][] mat={{1,2,3},{1,2},{3,4,5}};
      for(int[] row:mat){
        for(int element:row)
            System.out.print(element+" ");
        System.out.println();
      }
    }
  }
```

***

Row-major to Column-major order

```java
import java.util.*;
public class Main{
    public static void main(String[] agrs){
      int [][] mat={{1,2,3},{1,2},{3,4,5}};
      for(int col=0;col<mat[0].length;col++){
        for(int row=0;row<mat.length;row++)
            System.out.print(mat[row][col]+" ");
        System.out.println();
      }
    }
  }
```

Returns the sum of a 2D array

```java
public static int sum(int[][] a){
   int sum=0;
   for(int[] row:a){
       for(int value:row)
           sum+=value;
   }
   return sum;
}
```

2D Arrays of Objects

```java
for(Student[] row: st){
   for(Student p:row)
     p.getname();
```

Case: 遍历每个学生的姓名

***

[P1554](https://www.luogu.com.cn/problem/P1554)

```java
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        long l = in.nextLong();
        long r = in.nextLong();
        long[] cnt = new long[10];
        for (long i = l; i <= r; i++) {
            String s = Long.toString(i);
            for (int j = 0; j < s.length(); j++) {
                cnt[s.charAt(j) - '0']++;
            }
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 10; i++) {
            if (i > 0) sb.append(' ');
            sb.append(cnt[i]);
        }
        sb.append(' ');
        System.out.print(sb.toString());
    }
}
```

```java
import java.util.*;

public class Main {

    // 题1：所有元素求和
    public static int sumAll(int[][] grid) {
        int sum = 0;
        for (int r = 0; r < grid.length; r++) {
            for (int c = 0; c < grid[r].length; c++) {
                sum += grid[r][c];
            }
        }
        return sum;
    }

    // 题2：统计偶数
    public static int countEvens(int[][] grid) {
        int cnt = 0;
        for (int[] row : grid) {
            for (int v : row) {
                if (v % 2 == 0) cnt++;
            }
        }
        return cnt;
    }

    // 题3：每行最大值
    public static int[] rowMaxes(int[][] grid) {
        int[] ans = new int[grid.length];
        for (int r = 0; r < grid.length; r++) {
            int mx = grid[r][0]; 
            for (int c = 1; c < grid[r].length; c++) {
                mx = Math.max(mx, grid[r][c]);
            }
            ans[r] = mx;
        }
        return ans;
    }

    // 题4-1：主对角线和
    public static int mainDiagSum(int[][] m) {
        int n = m.length; // 方阵
        int sum = 0;
        for (int i = 0; i < n; i++) sum += m[i][i];
        return sum;
    }

    // 题4-2：副对角线和
    public static int antiDiagSum(int[][] m) {
        int n = m.length;
        int sum = 0;
        for (int i = 0; i < n; i++) sum += m[i][n - 1 - i];
        return sum;
    }

    // 题5：交换两行（O(1) 交换引用）
    public static void swapRows(int[][] grid, int r1, int r2) {
        int[] tmp = grid[r1];
        grid[r1] = grid[r2];
        grid[r2] = tmp;
    }

    // 题6：2x2 相邻平均
    public static int[][] neighborAverages(int[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        int[][] avg = new int[rows - 1][cols - 1];

        for (int r = 0; r < rows - 1; r++) {
            for (int c = 0; c < cols - 1; c++) {
                int sum = grid[r][c] + grid[r + 1][c] + grid[r][c + 1] + grid[r + 1][c + 1];
                avg[r][c] = sum / 4;
            }
        }
        return avg;
    }

    // 题7：查找姓名
    public static boolean containsName(String[][] seats, String name) {
        for (int r = 0; r < seats.length; r++) {
            for (int c = 0; c < seats[r].length; c++) {
                if (seats[r][c] != null && seats[r][c].equals(name)) return true;
            }
        }
        return false;
    }

    // 题8：编写 countHorizontalPairs，统计每行中左右相邻且相等的元素对数。
    // 例如 {{2, 2, 2}, {3, 4, 4}} 返回 3：第一行有两对，第二行有一对
    
    // Homework：编写 hasAdjacentSeats：0 表示空座位，1 表示已占用。
    //如果某一行存在两个左右相邻的空座位，返回 true；否则返回 false。
    public static boolean hasAdjacentSeats(int[][] seats){
    
    }
```
