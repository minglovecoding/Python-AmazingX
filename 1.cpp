#include <bits/stdc++.h>
using namespace std;

int cv(char c) { // 'W','G','B' -> 0,1,2
    if (c == 'W') return 0;
    if (c == 'G') return 1;
    return 2; // 'B'
}

void solve_case() {
    int N, A, B;
    if (!(cin >> N >> A >> B)) return;

    vector<vector<int>> map3(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;               // 长度为 N 的 W/G/B 字符串
        for (int j = 0; j < N; ++j)
            map3[i][j] = cv(s[j]);
    }

    vector<vector<int>> map1(N, vector<int>(N, 0));

    // 第一轮：处理 'B'（值 2）
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (map3[i][j] == 2) {
                map1[i][j] = 1;
                if (i < B || j < A) {            // 越界
                    cout << -1 << '\n';
                    return;
                }
                if (map3[i - B][j - A] == 0) {   // 对应位置是 'W'
                    cout << -1 << '\n';
                    return;
                }
                map1[i - B][j - A] = 1;
            }
        }
    }

    // 第二轮：处理 'G'（值 1）
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (map3[i][j] == 1) {
                if (map1[i][j] == 1) continue;
                if (i < B || j < A) {            // 放自己
                    map1[i][j] = 1;
                    continue;
                }
                if (map1[i - B][j - A] == 1) continue;
                map1[i][j] = 1;
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            ans += map1[i][j];

    cout << ans << '\n';
}

int main() {
    int T; 
    cin>>T;
    while (T--) solve_case();
    return 0;
}
//vector<vector<int>>二维数组
//把字符转换成数字存储
//分解问题，找出解题点