#include <bits/stdc++.h>
using namespace std;

int n;
int path[10];
bool used[10];

void dfs(int depth) {
    // depth 表示当前正在填第几个位置
    if (depth == n) {
        for (int i = 0; i < n; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            path[depth] = i;
            used[i] = true;

            dfs(depth + 1);

            used[i] = false;
        }
    }
}

int main() {
    cin >> n;

    dfs(0);

    return 0;
}