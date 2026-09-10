//从字串p入手
//f[i][j][p]=f[i-1][j][p]+g[i][j][p]
//g[i][j][p]=g[i−1][j−1][p]+f[i−1][j−1][p−1]
//f[i][0][0]=1
//f[n][m][k]
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
const int M=205;
const int MOD=1000000007;
int f[N][M][M];
int g[N][M][M];
int main(){
    int n,m,k;
    string A,B;
    cin>>n>>m>>k;
    cin>>A>>B;
    A=" "+A;
    B=" "+B;
    f[0][0][0]=1;
    for (int i = 1; i <= n; i++) {
        // 什么都不选择
        f[i][0][0] = 1;
        for (int j = 1; j <= min(i, m); j++) {
            for (int p = 1; p <= min(j, k); p++) {
                // 情况一：不选择 A[i]
                f[i][j][p] = f[i - 1][j][p];
                // 只有字符相等时，才能选择 A[i]
                if (A[i] == B[j]) {
                    // 情况二：延续当前第 p 个子串
                    g[i][j][p] = g[i - 1][j - 1][p];
                    // 情况三：从 A[i] 开始第 p 个子串
                    g[i][j][p] += f[i - 1][j - 1][p - 1];
                    if (g[i][j][p] >= MOD) {
                        g[i][j][p] -= MOD;
                    }
                    // 总方案 = 不选择 A[i] + 选择 A[i]
                    f[i][j][p] += g[i][j][p];

                    if (f[i][j][p] >= MOD) {
                        f[i][j][p] -= MOD;
                    }
                }
            }
        }
    }
    cout << f[n][m][k] <<endl;
    return 0;
}

/*----------------------------------*/
/*
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
const int MAXM = 205;
int f[2][MAXM][MAXM];
int g[2][MAXM][MAXM];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    string A, B;
    cin >> n >> m >> k;
    cin >> A >> B;
    // 改成从 1 开始编号
    A = " " + A;
    B = " " + B;
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int now = i & 1;
        int pre = now ^ 1;
        //清楚残留数据
        memset(f[now], 0, sizeof(f[now]));
        memset(g[now], 0, sizeof(g[now]));
        f[now][0][0] = 1;
        for (int j = 1; j <= min(i, m); j++) {
            for (int p = 1; p <= min(j, k); p++) {
                // 不选择 A[i]
                f[now][j][p] = f[pre][j][p];
                if (A[i] == B[j]) {
                    // 延续第 p 个子串
                    g[now][j][p] = g[pre][j - 1][p];
                    // 在 A[i] 处新开第 p 个子串
                    g[now][j][p] += f[pre][j - 1][p - 1];
                    if (g[now][j][p] >= MOD) {
                        g[now][j][p] -= MOD;
                    }
                    f[now][j][p] += g[now][j][p];
                    if (f[now][j][p] >= MOD) {
                        f[now][j][p] -= MOD;
                    }
                }
            }
        }
    }
    cout << f[n & 1][m][k] << '\n';
    return 0;
}
*/