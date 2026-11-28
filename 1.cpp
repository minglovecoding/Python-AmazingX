//1.模拟第一轮的K次交换，记录每头奶牛经过的位置及对应时间。
//2.根据第一轮结束后每头奶牛所在的位置，建立置换图，并进行环分解。
//3.在每个置换环上使用滑动窗口，统计每头奶牛经过的不同位置数量。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
  
    int n, k;
    long long minutes;
    cin >> n >> k >> minutes;
    //1.模拟第一轮交换，记录移动路径
    vector<int> cowAt(n + 1);
    // {位置, 首轮中到达该位置的时间t}；允许重复记录。
    vector<vector<pair<int, int>>> path(n + 1);
    for (int i = 1; i <= n; i++) {
        cowAt[i] = i;
        path[i].push_back({i, 0});
    }
    for (int t = 1; t <= k; t++) {
        int a, b;
        cin >> a >> b;
        path[cowAt[a]].push_back({b, t});
        path[cowAt[b]].push_back({a, t});
        swap(cowAt[a], cowAt[b]);
    }
    //2.建立置换图并进行环分解
    vector<int> to(n + 1);
    for (int pos = 1; pos <= n; pos++) to[cowAt[pos]] = pos;
    vector<bool> used(n + 1, false);
    //使用频率数组统计不同位置
    //当前窗口中的路径记录包含位置 pos 的次数。
    //当前窗口中不同位置的总数
    vector<int> frequency(n + 1, 0), answer(n + 1);
    int distinct = 0;
    auto modify = [&](int node, int timeLimit, int delta) {
        //操作哪一个节点的路径；考虑该路径前多少分钟；1 表示加入，-1 表示删除
        for (auto [pos, time] : path[node]) {
            if (time > timeLimit) break;
            if (delta == 1) {
                if (frequency[pos] == 0) distinct++;
                frequency[pos]++;
            } else {
                frequency[pos]--;
                if (frequency[pos] == 0) distinct--;
            }
        }
    };
    //3.将总时间拆分为完整轮和剩余时间
    long long rounds = minutes / k;
    int remainder = int(minutes % k);
    for (int start = 1; start <= n; start++) {
        if (used[start]) continue;
        vector<int> cycle;
        int u = start;
        while (!used[u]) {
            used[u] = true;
            cycle.push_back(u);
            u = to[u];
        }
        int len = int(cycle.size());
        //情况一：完整轮数大于等于环长
        if (rounds >= len) {
            for (int node : cycle) modify(node, k, 1);
            for (int node : cycle) answer[node] = distinct;
            for (int node : cycle) modify(node, k, -1);
            continue;
        }
        //情况二：完整轮数小于环长
        int full = int(rounds);
        //第一步：初始化完整窗口
        for (int j = 0; j < full; j++) modify(cycle[j], k, 1);
        for (int i = 0; i < len; i++) {
            //第二步：临时加入部分路径
            int next = cycle[(i + full) % len];
            modify(next, remainder, 1);
            answer[cycle[i]] = distinct;
            modify(next, remainder, -1);
            //第三步：移动完整窗口
            if (full > 0) {
                modify(cycle[i], k, -1);
                modify(next, k, 1);
            }
        }
        // 绕环一圈后，完整窗口回到初始位置，清空其贡献。
        for (int j = 0; j < full; j++) modify(cycle[j], k, -1);
    }
    for (int cow = 1; cow <= n; cow++) cout << answer[cow] << '\n';
}
//每条首轮记录只被常数次加入、删除，因此总时间 O(N+K)，空间 O(N+K)。