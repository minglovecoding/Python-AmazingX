#include <bits/stdc++.h>
using namespace std;

/*
 PotionFarming (Java → C++)
 --------------------------
 逻辑对应：
 - countleaves() ：统计每个节点子树中的叶子数量
 - countPotions()：根据药水出现分布，计算最大可获得药水数
*/

const int MAXN = 100000 + 5;
vector<int> graph[MAXN];
int numLeaves[MAXN]; // numleaves[cur]：cur 子树中的叶子数

// 统计每个节点子树中叶子数
int countLeaves(int cur, int par) {
    // 叶子节点条件：只有一个邻居且为父节点，或无邻居（孤点）
    if ((graph[cur].size() == 1 && graph[cur][0] == par) || graph[cur].empty()) {
        numLeaves[cur] = 1;
        return 1;
    }

    int sum = 0;
    for (int v : graph[cur]) {
        if (v == par) continue;
        sum += countLeaves(v, cur);
    }
    numLeaves[cur] = sum;
    return sum;
}

// 计算最大可收集药水数
int countPotions(int cur, int par, const vector<int>& modpots) {
    int sum = 0;
    for (int v : graph[cur]) {
        if (v == par) continue;
        sum += countPotions(v, cur, modpots);
    }
    sum += modpots[cur];
    return min(sum, numLeaves[cur]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int s = 0; // root node index = 0
    vector<int> pots(n);
    for (int i = 0; i < n; ++i) {
        cin >> pots[i];
        pots[i]--; // 转换为 0-based
    }

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // Step 1: 统计每个节点的叶子数量
    int leaves = countLeaves(s, -1);

    // Step 2: 统计前 `leaves` 个药水分布（modpots）
    vector<int> modpots(n, 0);
    for (int i = 0; i < leaves; ++i) {
        modpots[pots[i]]++;
    }

    // Step 3: 计算最大药水数
    int ans = countPotions(s, -1, modpots);

    cout << ans << "\n";
    return 0;
}
