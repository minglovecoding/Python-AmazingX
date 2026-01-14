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
//mat.length、mat[0].length
int [][] seatinginfo={{"America","Bob"},{"Jake","rose"}};

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
      for(int row=0;row<mat.length;row++){
        for(int col=0;col<mat[row].length;col++)
            System.out.print(mat[row][col]+" ");
        System.out.println();
      }
    }
  }
```

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
public int sum(int[][] a){
   int sum=0;
   for(int[] row:a){
       for(int value:row)
           sum+=value;
   }
   return sum;
}
```

2D Arrays of Obejects

```
for(Point[] row: pointMatrix){
   for(Point pt:row)
     pt.setX(1);
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

    // 题8：blur（上下左右+自己平均，边界只算存在的）
    public static int[][] blur(int[][] pixels) {
        int rows = pixels.length;
        int cols = pixels[0].length;
        int[][] out = new int[rows][cols];

        int[] dr = {0, -1, 1, 0, 0};
        int[] dc = {0, 0, 0, -1, 1};

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int sum = 0, count = 0;
                for (int k = 0; k < 5; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                        sum += pixels[nr][nc];
                        count++;
                    }
                }
                out[r][c] = sum / count;
            }
        }
        return out;
    }

    // 题9：只能向右或向下，判断是否有路径（0可走，1墙）
    public static boolean hasPath(int[][] maze) {
        int rows = maze.length;
        int cols = maze[0].length;
        if (maze[0][0] == 1 || maze[rows - 1][cols - 1] == 1) return false;

        boolean[][] dp = new boolean[rows][cols];
        dp[0][0] = true;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (maze[r][c] == 1) continue;
                if (r == 0 && c == 0) continue;
                boolean fromUp = (r > 0) && dp[r - 1][c];
                boolean fromLeft = (c > 0) && dp[r][c - 1];
                dp[r][c] = fromUp || fromLeft;
            }
        }
        return dp[rows - 1][cols - 1];
    }

    // 可选：简单测试入口（不需要可删）
    public static void main(String[] args) {
        int[][] grid = {
                {1, 2, 3},
                {4, 5, 6}
        };
        System.out.println(sumAll(grid));        // 21
        System.out.println(countEvens(grid));    // 3
        System.out.println(Arrays.toString(rowMaxes(grid))); // [3, 6]

        int[][] m = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };
        System.out.println(mainDiagSum(m));  // 15
        System.out.println(antiDiagSum(m));  // 15

        int[][] avg = neighborAverages(m);
        System.out.println(Arrays.deepToString(avg)); // [[3, 4], [6, 7]]

        String[][] seats = {
                {"Amy", "", "Bob"},
                {"", "Cody", ""}
        };
        System.out.println(containsName(seats, "Cody")); // true

        int[][] blurred = blur(m);
        System.out.println(Arrays.deepToString(blurred));

        int[][] maze = {
                {0, 0, 1},
                {1, 0, 0},
                {1, 1, 0}
        };
        System.out.println(hasPath(maze)); // true
    }
}
```
