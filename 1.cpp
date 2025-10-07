#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; ++i) cin >> nums[i];

    vector<int> left(N + 1, 0), right(N + 1, 0);
    long long ans = 0;
    int distinct_left = 0;

    // 统计每个值总出现次数（放到 right）
    for (int i = 0; i < N; ++i) right[nums[i]]++;

    for (int i = 0; i < N; ++i) {
        int v = nums[i];
        if (right[v] == 2) {
            // 在倒数第二次出现的位置结算
            ans += (long long)distinct_left - (left[v] > 0 ? 1 : 0);
        }
        right[v] -= 1;
        distinct_left += (left[v] == 0 ? 1 : 0);
        left[v] += 1;
    }

    cout << ans << '\n';
    return 0;
}
