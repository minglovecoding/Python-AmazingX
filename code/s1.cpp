#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using i64 = long long;

// 一条有向边：从当前点 u 走到 to，并且这条边对应“哪一头牛”的编号 id
struct Edge {
    int to, id;
};

int C;

void solve() {
    int n;
    if (!(cin >> n)) return;

    string sl, sr;
    cin >> sl >> sr;

    /*
      核心建模（非常重要）：
      设 b[i] ∈ {0,1} 表示牛 i 的真实阵营：
        b[i]=0 => John (说真话)
        b[i]=1 => Nhoj (说假话)

      输入给的是“牛 i 声称左/右邻居属于谁(J/N)”，但考虑真假话后可转成 XOR 关系：
        b[i] XOR b[right(i)] = r[i]
        b[left(i)] XOR b[i] = l[i]

      其中 l[i], r[i] ∈ {0,1} 被解释为：
        0: 我和邻居同阵营
        1: 我和邻居不同阵营

      而且在环上相邻拼接时必须满足：
        r[p_k] == l[p_{k+1}]
      （上一头牛的 r 必须等于下一头牛的 l）
      这就变成一个只有两个点(0/1)的有向多重图：
        每头牛 i 是一条边： l[i] -> r[i]
      找到使用每条边一次的“欧拉回路”，其边序就是环上牛的顺序。
    */

    vector<int> l(n), r(n);
    vector<int> in(2, 0), out(2, 0);

    // adj[0], adj[1] 分别存从点 0/1 出发的边（多重边）
    vector<Edge> adj[2];

    int cnt_r1 = 0; // 统计所有 r[i]=1 的数量（用于全局偶性检查）

    for (int i = 0; i < n; ++i) {
        // 把字符转成 0/1（注意：这里用 'N' 映射为 1）
        // l[i]=1 表示“牛 i 声称左邻居是 Nhoj”，等价于 XOR 差分里 l[i]=1（不同阵营）
        // r[i]=1 同理
        l[i] = (sl[i] == 'N');
        r[i] = (sr[i] == 'N');

        // 每头牛 i 对应一条边：l[i] -> r[i]，边 id = i+1（牛编号从 1 开始）
        adj[l[i]].push_back({r[i], i + 1});

        // 维护入度/出度（欧拉回路必要条件：每个点 in=out）
        out[l[i]]++;
        in[r[i]]++;

        if (r[i]) cnt_r1++;
    }

    /*
      可行性必要条件 1：欧拉回路要求每个点 in=out
      可行性必要条件 2：绕环一圈必须回到起点：
         b1 XOR b2 = r[p1]
         b2 XOR b3 = r[p2]
         ...
         bN XOR b1 = r[pN]
       XOR 全部得到 r[p1] XOR ... XOR r[pN] = 0
       => 1 的个数必须为偶数
       注意：环上的顺序只是重排，所以“所有 r[i] 的 XOR”不变，直接要求 cnt_r1 偶数即可。
    */
    if (in[0] != out[0] || in[1] != out[1] || cnt_r1 % 2 != 0) {
        cout << "NO\n";
        return;
    }

    /*
      现在在 2 点图上找欧拉回路（Hierholzer 算法）：
      - stack 记录当前走到的点序列
      - path_ids 记录走过的边 id（与 stack 同步推进）
      - 当走到一个点没有出边可走时，回退，把最后一条边加入答案
      最终得到的 ans 是“欧拉回路的边序（反向）”，最后 reverse。
    */

    // 从哪个点开始都可以；若 1 点有边则从 1 开始，否则从 0
    int start_node = adj[1].empty() ? 0 : 1;

    vector<int> ans;              // 记录欧拉回路边序（最终会变成环上牛的顺序）
    vector<int> stack = {start_node}; // 走点的栈
    vector<int> path_ids;         // 走边的栈（每次沿边深入就 push 边 id）

    while (!stack.empty()) {
        int u = stack.back();
        if (!adj[u].empty()) {
            // 还有边可走：取出一条 u->to 的边，沿着它走
            Edge e = adj[u].back();
            adj[u].pop_back();

            stack.push_back(e.to);
            path_ids.push_back(e.id);
        } else {
            // 没边可走：回退
            stack.pop_back();

            // 回退时把“刚刚完成的那条边”加入答案（Hierholzer 的标准写法）
            if (!path_ids.empty()) {
                ans.push_back(path_ids.back());
                path_ids.pop_back();
            }
        }
    }

    // 必须用掉所有 n 条边，否则说明图不是一个连通的欧拉回路结构（边分散在多个部分）
    if (ans.size() != (size_t)n) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    if (C == 1) {
        // Hierholzer 得到的是反序边序，翻转后就是从 p1 到 pN 的顺序
        reverse(ans.begin(), ans.end());

        // 输出环上顺序：p1..pN（这里每条边 id 就是牛编号）
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";

        /*
          构造阵营字符串 b（对应环上顺序 p=ans）：
          令 current_state = b[p1]，我们可以任意取 0（John）作为起点。
          然后利用关系：
            b[p_{k+1}] = b[p_k] XOR r[p_k]
          依次推下去得到整圈的 b。
          由于我们前面保证了所有 r 的 XOR 为 0，所以走完一圈会回到起点，合法闭环。
        */
        string res = "";
        int current_state = 0; // 0->J, 1->N

        for (int i = 0; i < n; ++i) {
            res += (current_state == 0 ? 'J' : 'N');

            // 下一头牛的阵营 = 当前阵营 XOR 当前牛的 r 值
            // 注意 r 数组是按牛编号 i 存的，所以要用 ans[i]-1 来索引
            current_state ^= r[ans[i] - 1];
        }

        cout << res << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (cin >> T >> C) {
        while (T--) solve();
    }
    return 0;
}
