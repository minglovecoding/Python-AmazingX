USACO 2019 January Bronze Problem 1 — [Shell Game](https://usaco.org/index.php?page=viewproblem2&cpid=891&lang=zh)

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n), g(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> g[i];
    }
    int ans = 0;
    // 枚举石头最初所在的位置
    for (int start = 1; start <= 3; start++) {
        int pos = start;
        int score = 0;
        // 模拟每一轮交换
        for (int i = 0; i < n; i++) {
            if (pos == a[i]) {
                pos = b[i];
            } else if (pos == b[i]) {
                pos = a[i];
            }
            // 判断是否猜中
            if (pos == g[i]) {
                score++;
            }
        }
        ans = max(ans, score);
    }
    cout << ans << "\n";
    return 0;
}
```

