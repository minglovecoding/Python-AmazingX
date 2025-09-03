#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<long long> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        vector<long long> pre(N + 1, 0), suf(N + 2, 0);

        for (int i = 1; i <= N; i++) {
            pre[i] = pre[i - 1] + A[i - 1];
        }
        for (int i = N; i >= 1; i--) {
            suf[i] = suf[i + 1] + A[i - 1];
        }

        long long Elsie = 0;
        for (int i = 0; i < N / 2; i++) { // 0 ~ N//2 - 1
            Elsie = max(Elsie, pre[i] + suf[N + 1 - (N / 2 - 1 - i)]);
        }

        cout << pre[N] - Elsie << " " << Elsie << "\n";
    }

    return 0;
}
