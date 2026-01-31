#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using i64 = long long;

struct Edge {
    int to, id;
};

int C;

void solve() {
    int n;
    if (!(cin >> n)) return;

    string sl, sr;
    cin >> sl >> sr;

    vector<int> l(n), r(n), in(2, 0), out(2, 0);
    vector<Edge> adj[2];
    int cnt_r1 = 0;

    for (int i = 0; i < n; ++i) {
        l[i] = (sl[i] == 'N');
        r[i] = (sr[i] == 'N');
        adj[l[i]].push_back({r[i], i + 1});
        out[l[i]]++;
        in[r[i]]++;
        if (r[i]) cnt_r1++;
    }

    if (in[0] != out[0] || in[1] != out[1] || cnt_r1 % 2 != 0) {
        cout << "NO\n";
        return;
    }

    int start_node = adj[1].empty() ? 0 : 1;
    vector<int> ans, stack = {start_node};
    vector<int> path_ids;

    while (!stack.empty()) {
        int u = stack.back();
        if (!adj[u].empty()) {
            Edge e = adj[u].back();
            adj[u].pop_back();
            stack.push_back(e.to);
            path_ids.push_back(e.id);
        } else {
            stack.pop_back();
            if (!path_ids.empty()) {
                ans.push_back(path_ids.back());
                path_ids.pop_back();
            }
        }
    }

    if (ans.size() != (size_t)n) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    if (C == 1) {
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";

        string res = "";
        int current_state = 0;
        for (int i = 0; i < n; ++i) {
            res += (current_state == 0 ? 'J' : 'N');
            current_state ^= r[ans[i] - 1];
        }
        cout << res << "\n";
    }
}

int main() {


    int T;
    if (cin >> T >> C) {
        while (T--) solve();
    }
    return 0;
}