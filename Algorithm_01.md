## 📚 时间复杂度与空间复杂度

- **输入规模 n**：问题输入的大小（数组长度、图的点/边数、字符串长度等）。
- **时间复杂度**：随 n 增大，算法运行步数/时间如何增长；用 **大 O 记号**描述上界，如 O(n log n)`。
- **空间复杂度**：随 n 增大，算法额外占用的内存如何增长（通常指**辅助空间**，不含输入本身）。

### 常见记号（从理想到保守）

- **Θ(f(n))**：紧确阶（上界=下界）。
- **O(f(n))**：上界（最坏或上限）。
- **Ω(f(n))**：下界（最好或下限）。
   实际写作中，多用 **O** 表示“渐近上界”。

### 常见量级（从快到慢，大致）

```
O(1) < O(log n) < O(n) < O(n log n) < O(n^2) < O(n^3) < O(2^n) < O(n!)
```

### 快速判断时间复杂度

- **顺序循环**：`for(i=0;i<n;i++)` → `O(n)`
- **嵌套循环**：外 `n` × 内 `n` → `O(n^2)`；外 `n` × 内 `log n` → `O(n log n)`
- **二分/折半**：每次砍一半 → `O(log n)`（如二分查找）
- **分治（T(n)=a T(n/b)+O(n^d)）**：用主定理
  - 归并排序：`T(n)=2T(n/2)+O(n)` → `O(n log n)`
- **递归深度**：深度 × 每层成本。斐波那契朴素递归 `O(2^n)`。

### 空间复杂度要点

- **原地算法**：额外空间 `O(1)`（如原地交换、双指针）。
- **递归**：调用栈算空间。深度 `d`，每层常数 → `O(d)`。
- **数据结构**：使用的额外结构（队列、栈、哈希表、树）大小一般与元素数成正比 → `O(n)`。

#### case1: 单循环扫描

**任务**：数组求和
 **时间**：O(n)（扫一遍） **空间**：O(1)

```c++
int sum = 0; 1
for (int x : arr) sum += x; 
```

#### case2:双重循环

**任务**：所有二元对(i, j)的统计
 **时间**：O(n^2) **空间**：O(1)

```c++
int cnt = 0; 1
for (int i = 0; i < n; i++) 
  for (int j = 0; j < n; j++)
    cnt++;
```

> 若是“上三角”`for (int j=i+1; j<n; j++)`，次数约 n(n-1)/2，仍记 **O(n^2)**。

#### case:3 二分查找

**任务**：有序数组中找目标
 **时间**：O(log n)（每次砍一半） **空间**：O(1)（迭代）

```c++
int l=0, r=n-1;
while (l<=r) {
  int m = (l+r)/2;
  if (a[m]==target) return m;
  if (a[m]<target) l=m+1; else r=m-1;
}
```

### 📌 枚举算法

  枚举算法是一种通过遍历所有可能的解来解决问题的策略，也被称为穷举算法。 其核心思想是列出问题的所有可能答案，然后逐一验证哪些答案符合题目要求，通常使用循环和判断语句来实现。

例一：百钱买白鸡
1，问题描述：
公鸡每只5元，母鸡每只3元，三只小鸡1元，用100元买100只鸡，问公鸡、母鸡、小鸡各多少只？
2，算法分析：
利用枚举法解决该问题，以三种鸡的个数为枚举对象,分别设为mj,gj和xj，用三种鸡的总数（mj+gj+xj=100）和买鸡钱的总数（1/3*xj+mj*3+gj*5=100）作为判定条件，穷举各种鸡的个数。

```c++
#include<iostream>
using namespace std;
int main()
{
	int mj=0, gj=0, xj=0;                  //定义变量分别表示母鸡、公鸡、小鸡并初始化
	for (gj = 0; gj <= 20; gj++)		   //公鸡最多可买20个
	{
		for (mj = 0; mj <= 33; mj++)	   //母鸡最多可买33个
		{
			xj = 100 - gj - mj;			   // 三种鸡的总数是100只
			if (xj % 3 == 0 && 5 * gj + 3 * mj + xj / 3 == 100)    // 总花费为100元。
		    cout<<gj<<" "<<mj<<" "<<xj<<endl;
		}
	}
	return 0;
}
```

### 📌 暴力算法

**把所有可能的解或足够多的候选解逐一尝试并检验**，从而找到可行解或最优解的方法。核心思想是“全面搜索”。

#### 两数之和

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (a[i] + a[j] == target) {
                cout << i << " " << j << "\n";  // 0-based 下标
                return 0;
            }

    cout << -1 << "\n"; // 没找到
    return 0;
}
```

### P2241 统计方形（数据加强版）

#### 题目描述

有一个 *n*×*m* 方格的棋盘，求其方格包含多少正方形、长方形（不包含正方形）。

#### 输入格式

一行，两个正整数 *n*,*m*（*n*,*m*（*n*≤5000,*m*≤5000））。

#### 输出格式

一行，两个正整数，分别表示方格包含多少正方形、长方形（不包含正方形）。

#### 输入输出样例 #1

#### 输入 #1

```
2 3
```

#### 输出 #1

```
8 10
```

```c++
#include<iostream>
using namespace std;
long long n,m,rec,sqr;
int main() {
    cin>>n>>m;
    for(int i=0; i<n; i++)//循环，从n-0到n-(n-1)
        for(int j=0; j<m; j++) {//循环，从m-0到m-(m-1)
            if(i==j) sqr+=(n-i)*(m-j);//如果i==j，说明是正方形
            else rec+=(n-i)*(m-j);//如果不等说明是矩形
        }
    cout<<sqr<<" "<<rec<<endl;//输出
    return 0;
}

```

### 📌 **贪心算法（Greedy Algorithm）**

一类在求解过程中\**每一步都做当前看来最优（“最贪”）的选择**，希望由一连串局部最优最终导向**全局最优**的算法策略。

[P3817 小A的糖果](https://www.luogu.com.cn/problem/P3817)

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long sum=0//计数器,n,x;
	cin>>n>>x;//输入
	long long a[n+1];
	cin>>a[1];//处理第一个单独超限。
	if(a[1]>x)
		{
		sum+=a[1]-x;//增加吃的量
		a[1]=x;//a[i]>=x,要吃的最少，即是a[i]=x;
		}
	for(int i=2;i<=n;i++)
		{
		cin>>a[i];//输入
		if(a[i]+a[i-1]>x)//照例处理
			{
			sum+=a[i]+a[i-1]-x;
			a[i]=x-a[i-1];
			}
		}
	cout<<sum;//输出
	return 0;//养成好习惯
} 
```

#### case2： 排队接水

[P4995 跳跳 ](https://www.luogu.com.cn/problem/P4995)

```c++
#include <bits/stdc++.h>
using namespace std;
long long n,h[500],ans,point=1;
int main(){
   cin >> n;
   for(int i=1;i<=n;i++)cin >> h[i];
   sort(h,h+n+1);//排升序
   int l=0,r=n;//初始化两个游标
   while(r>l){ //如果游标相等或者左边的游标更小那就退出
       ans+=pow(h[r]-h[l],2);//计算跳一次后增加消耗的体力值
       l++;
       ans+=pow(h[l]-h[r],2);
       r--;//循环一次之后发现，回到了原来的样子，不过问题规模缩小了，要考虑的n少了两个
   }
   cout << ans;
   return 0;
}
```

### 📌  **递推与递归**

**递推（iteration / bottom-up）**：从**初始已知**出发，**按顺序推到目标**。常用循环与数组保存中间结果。

**递归（recursion / top-down）**：把问题**拆成更小的同类问题**，函数**自我调用**，直到命中**基例**。可配合**记忆化**避免重复子问题。

**Case1**：上台阶一次可以走 **1** 或 **2** 步，问走到第 `n` 级有多少种走法 `f[n]`。
 递推关系：

- 初始：`f[0]=1`（不走也算一种方式），`f[1]=1`，`f[2]=2`
- 递推：`f[n]=f[n-1]+f[n-2]`（最后一步走 1 步或 2 步）

#### 最简写法（O(n)，空间 O(1)）

```c++
#include <bits/stdc++.h>
using namespace std;

long long ways(int n) {
    if (n <= 1) return 1;      // f[0]=1, f[1]=1
    long long a = 1, b = 1;    // a=f[i-2], b=f[i-1]
    for (int i = 2; i <= n; ++i) {
        long long c = a + b;   // f[i] = f[i-1] + f[i-2]
        a = b; b = c;
    }
    return b;
}

int main() {
    int n; 
    cin >> n;
    cout << ways(n) << "\n";
    return 0;
}
```

**说明**：这就是一个自底向上的**递推**：从已知的 `f[0], f[1]` 开始，按公式顺序推到 `f[n]`。
 **复杂度**：时间 O(n)，空间 O(1)。

### Case2：阶乘 factorial（基例清晰）

定义：`n! = n * (n-1)!`，且 `0! = 1`

```c++
#include <bits/stdc++.h>
using namespace std;

long long fact(int n){
    if (n == 0) return 1;          // 基例（最小子问题）
    return 1LL * n * fact(n - 1);  // 递归：把问题缩小为 n-1
}

int main(){
    int n; cin >> n;
    cout << fact(n) << "\n";
}
```

小推演：`fact(3) = 3 * fact(2) = 3 * 2 * fact(1) = 3 * 2 * 1 * fact(0) = 6`

 [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)

```c++
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int n,len=1,f[5003][5003];//f[k][i]--第k阶台阶所对应的走法数 
void hp(int k)//高精度加法，k来存阶数 
{    
    int i;
    for(i=1;i<=len;i++)
     f[k][i]=f[k-1][i]+f[k-2][i];//套用公式 
    for(i=1;i<=len;i++)             //进位 
     if(f[k][i]>=10)
     {
         f[k][i+1]+=f[k][i]/10;
         f[k][i]=f[k][i]%10;
         if(f[k][len+1])len++;
    }
}
int main()
{
    int i;
    scanf("%d",&n);
    f[1][1]=1; f[2][1]=2;         //初始化 
    for(i=3;i<=n;i++)              //从3开始避免越界 
     hp(i);                         
    for(i=len;i>=1;i--)             //逆序输出 
     printf("%d",f[n][i]);
    return 0;
}

```

