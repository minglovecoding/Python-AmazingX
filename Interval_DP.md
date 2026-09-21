### 区间 DP 

### 🧩 定义：

> 对于一段区间 `[l, r]`，你要求某种最优值（或可行性），
> 并且可以通过划分子区间 `[l, k]` 和 `[k+1, r]` 来合并子问题。

因此它的状态表示通常是：
$$
dp[l][r] = \text{区间 [l,r] 的最优结果}
$$

### 转移通式：

$$
dp[l][r] = \min_{k \in [l,r-1]} \{ dp[l][k] + dp[k+1][r] + \text{cost}(l, r, k) \}
$$

- `dp[l][k]`：左半段的最优代价
- `dp[k+1][r]`：右半段的最优代价
- `cost(l, r, k)`：合并 `[l,k]` 与 `[k+1,r]` 所需的额外代价（如两堆石头合并）

### 计算顺序：

必须保证子区间已计算完再计算大区间
 → 按「区间长度」递增遍历：

```c++
for (int len = 2; len <= n; len++)
  for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1;
      dp[l][r] = INF;
      for (int k = l; k < r; k++)
          dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r] + cost(l,r,k));
  }
```

经典模版，时间复杂度：**O(n³)**。

### 石子合并示例

有 `n` 堆石子排成一行，第 `i` 堆有 `a[i]` 个。每次你可以合并相邻两堆石子，代价是它们的石子总数。
 合并后这两堆变成一堆。
 问：把所有石子合并成一堆的最小总代价。

### 思路分析

我们要求「区间 `[l, r]` 合并成一堆的最小代价」。

### 状态定义：

$$
dp[l][r] = \text{合并 [l,r] 区间成一堆的最小代价}
$$

### 状态转移：

考虑最后一次合并前，区间 `[l,r]` 被分成两部分 `[l,k]` 和 `[k+1,r]`：
$$
dp[l][r] = \min_{l \le k < r} \big( dp[l][k] + dp[k+1][r] + \text{sum}(l,r) \big)
$$
其中：
$$
\text{sum}(l,r) = \sum_{i=l}^r a[i] = \text{前缀和差：} pre[r] - pre[l-1]
$$

### 初始化：

单个石堆不需要合并：
$$
dp[i][i] = 0
$$

### 实现细节

- 预处理前缀和 `pre[i]`；
- 按区间长度 `len` 从小到大枚举；
- 三重循环（O(n³)）计算最小代价。

### 💻 完整代码（C++）

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 1), pre(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));

    for (int len = 2; len <= n; len++) {     // 区间长度
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = LLONG_MAX;
            for (int k = l; k < r; k++) {
                long long cost = dp[l][k] + dp[k + 1][r] + pre[r] - pre[l - 1];
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    }
    cout << dp[1][n] << "\n";
    return 0;
}
```

### 典型例题

| 问题                 | 状态定义               | cost(l,r,k)      | 说明                   |
| -------------------- | ---------------------- | ---------------- | ---------------------- |
| **石子合并**         | 合并 [l,r] 的最小代价  | 区间和           | 每次合并代价为区间总和 |
| **矩阵连乘**         | 计算矩阵链乘法最少次数 | p[l-1]*p[k]*p[r] | 括号化顺序             |
| **括号匹配**         | 最少删除/修改次数      | 特殊规则         | 子区间是否能配对       |
| **凸多边形三角剖分** | 最小三角形权和         | w(l,k,r)         | 多边形 DP 模型         |

```c++
//P1880
#include<bits/stdc++.h>
using namespace std;   
int num[305];  
int dp1[305][305],dp2[305][305];
int pre[305];  
int main()  
{   
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>num[i];
        num[i+n]=num[i];
    }
    for(int i=1;i<=2*n;i++){
        pre[i]=pre[i-1]+num[i];
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=2*n;l++){
            int r=l+len-1;
            dp1[l][r]=1e9;
            dp2[l][r]=0;
            for(int k=l;k<r;k++){
                int cost1=dp1[l][k]+dp1[k+1][r]+pre[r]-pre[l-1];
                int cost2=dp2[l][k]+dp2[k+1][r]+pre[r]-pre[l-1];
                dp1[l][r]=min(dp1[l][r],cost1);
                dp2[l][r]=max(dp2[l][r],cost2);
            }
        }
    }
    int ans1=1e9;
    int ans2=0;

    for(int i=1;i<=n;i++){
        ans1=min(ans1,dp1[i][i+n-1]);
        ans2=max(ans2,dp2[i][i+n-1]);
    }

    cout<<ans1<<"\n"<<ans2<<"\n";
    return 0;  
}
```

> USACO 2021 February Contest, Gold- **Modern Art 3**
