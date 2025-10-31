#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<long long> c(N), t(N);
    for (int i = 0; i < N; i++) cin >> c[i];
    for (int i = 0; i < N; i++) cin >> t[i];

    vector<long long> deadline(N);
    for (int i = 0; i < N; i++) {
        deadline[i] = c[i] - t[i];  // 关键时间差
    }

    sort(deadline.begin(), deadline.end());

    while (Q--) {
        long long V, S;
        cin >> V >> S;

        // upper_bound 返回第一个 > S 的位置
        int pos = upper_bound(deadline.begin(), deadline.end(), S) - deadline.begin();
        long long count = N - pos;  // 满足条件的数量

        if (count >= V) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
