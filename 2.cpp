#include <bits/stdc++.h>
using namespace std;

long long cnt_diff(long long N) {
    int digits = to_string(N).size();
    long long ans = 0;
    for (int digit = 1; digit <= digits; ++digit) {
        // upper = min(N, int('5' + '0'*(digit-1)) - 1)
        long long upper = 0;
        {
            string s = "5" + string(digit - 1, '0'); // "5", "50", "500", ...
            long long bound = stoll(s) - 1;          // 4, 49, 499, ...
            upper = min(N, bound);
        }
        // lower = int('4' * digit)  -> "4", "44", "444", ...
        long long lower = stoll(string(digit, '4'));
        if (upper > lower) ans += (upper - lower);  // max(upper - lower, 0)
        // 注意：与原 Python 一样，不包含 lower 本身
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long N;
        cin >> N;
        cout << cnt_diff(N) << '\n';
    }
    return 0;
}
//std::stoll 是 C++ <string> 里的函数，用来把字符串转换成 long long 整数