#include<bits/stdc++.h>
using namespace std;
const int Mmax=20;
const int Nmax=1e5+5;
int Q[Nmax];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>Q[i];
    }

    return 0;
}
// 1. 输入并统计每支乐队的人数 count[j]

// 2. 建立前缀和 prefix[j][i]

// 3. 计算每个 mask 已经安排的总人数 length[mask]

// 4. 初始化 dp[0] = 0，其余为 INF

// 5. 枚举 mask 和尚未安排的乐队 j

// 6. 计算乐队 j 对应的目标区间 [left, right]

// 7. 用前缀和计算 correct，完成转移

// 8. 输出 dp[(1 << M) - 1]