#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n, num_marked;

void solve() {
    cin >> n >> num_marked;

    vector<int> next_node(n + 1);
    vector<int> in_degree(n + 1);
    vector<vector<int>> prev_nodes(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> next_node[i];
        in_degree[next_node[i]]++;
        prev_nodes[next_node[i]].push_back(i);
    }

    vector<int> dist_from_marked(n + 1, INF);
    vector<bool> is_marked(n + 1);
    queue<int> q;

    for (int i = 0; i < num_marked; i++) {
        int x; cin >> x;
        is_marked[x] = true;
        dist_from_marked[x] = 0;
        q.push(x);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        int v = next_node[u];
        if (dist_from_marked[v] == INF) {
            dist_from_marked[v] = dist_from_marked[u] + 1;
            q.push(v);
        }
    }

    vector<bool> on_cycle(n + 1, true);
    for (int i = 1; i <= n; i++) {
        if (!in_degree[i]) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        on_cycle[u] = false;
        int v = next_node[u];
        if (--in_degree[v] == 0) q.push(v);
    }

    vector<int> cycle_id(n + 1, -1);
    vector<int> cycle_pos(n + 1);
    vector<int> cycle_root(n + 1);
    vector<int> cycle_len;
    int current_cycle_count = 0;

    for (int i = 1; i <= n; i++) {
        if (on_cycle[i] && cycle_id[i] == -1) {
            int u = i, p = 0;
            while (cycle_id[u] == -1) {
                cycle_id[u] = current_cycle_count;
                cycle_pos[u] = p++;
                cycle_root[u] = u;
                u = next_node[u];
            }
            cycle_len.push_back(p);
            current_cycle_count++;
        }
    }

    vector<int> dist_to_cycle(n + 1);
    vector<vector<int>> group_nodes(n + 1);

    for (int i = 1; i <= n; i++) {
        if (on_cycle[i]) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        group_nodes[cycle_root[u]].push_back(u);
        
        for (int v : prev_nodes[u]) {
            if (!on_cycle[v]) {
                cycle_id[v] = cycle_id[u];
                cycle_root[v] = cycle_root[u];
                dist_to_cycle[v] = dist_to_cycle[u] + 1;
                q.push(v);
            }
        }
    }

    vector<vector<bool>> banned_mod(current_cycle_count);
    vector<vector<int>> tree_obstacles(n + 1);

    for (int i = 1; i <= n; i++) {
        if (dist_from_marked[i] == 0 && is_marked[i]) {
            int cid = cycle_id[i];
            int l = cycle_len[cid];

            long long val = (long long)dist_to_cycle[i] - cycle_pos[cycle_root[i]];
            int m = (val % l + l) % l;

            if (banned_mod[cid].empty()) banned_mod[cid].assign(l, false);
            banned_mod[cid][m] = true;

            if (!on_cycle[i]) tree_obstacles[cycle_root[i]].push_back(dist_to_cycle[i]);
        }
    }

    vector<bool> cycle_blocked(current_cycle_count);
    vector<vector<int>> prev_valid_mod(current_cycle_count);

    for (int i = 0; i < current_cycle_count; i++) {
        if (banned_mod[i].empty()) continue;
        cycle_blocked[i] = true;
        for (int j = 0; j < cycle_len[i]; j++) {
            if (!banned_mod[i][j]){
                cycle_blocked[i] = false;
                break;
            }
        }
        if (!cycle_blocked[i]) {
            int l = cycle_len[i];
            prev_valid_mod[i].resize(2 * l);
            int last = -1;
            for (int j = 0; j < 2 * l; j++) {
                int m = j % l;
                if (!banned_mod[i][m]) last = j;
                prev_valid_mod[i][j] = last;
            }
        }
    }

    vector<int> ans(n + 1);
    vector<int> valid_prefix_pos(n + 1);

    for (int r = 1; r <= n; r ++){
        if (!on_cycle[r] || group_nodes[r].empty()) continue;

        int cid = cycle_id[r];
        int l = cycle_len[cid];
        int max_depth = -1;
        
        for (int x : tree_obstacles[r]) max_depth = max(max_depth, x);

        if (max_depth != -1) {
            int last_ok = -1;
            for (int x = 0; x <= max_depth; x++) {
                long long val = (long long)x - cycle_pos[r];
                int m = (val % l + l) % l;
                bool ok = true;
                if (!banned_mod[cid].empty() && banned_mod[cid][m]) ok = false;
                valid_prefix_pos[x] = ok ? x : -1;
            }
            for (int x : tree_obstacles[r]) valid_prefix_pos[x] = -1;
            
            for (int x = 0; x <= max_depth; x++) {
                if (valid_prefix_pos[x] != -1) last_ok = valid_prefix_pos[x];
                valid_prefix_pos[x] = last_ok;
            }
        }

        for (int u : group_nodes[r]) {
            if (is_marked[u]) { ans[u] = -1; continue; }
            if (dist_from_marked[u] == INF) { ans[u] = -2; continue; }
            if (cycle_blocked[cid]) { ans[u] = -1; continue; }

            int limit_step = dist_to_cycle[u] + dist_from_marked[u] - 1;
            int best_reach = -1;

            if (limit_step > max_depth) {
                long long val = (long long)limit_step - cycle_pos[r];
                int m = (val % l + l) % l;
                
                int g = prev_valid_mod[cid][m + l];
                int diff = (m + l) - g;
                int cand = limit_step - diff;
                
                if (cand > max_depth) best_reach = cand;
                else if (max_depth != -1) best_reach = valid_prefix_pos[max_depth];
            } else {
                if (max_depth != -1 && limit_step >= 0) best_reach = valid_prefix_pos[limit_step];
            }

            if (best_reach < dist_to_cycle[u]) ans[u] = -1;
            else ans[u] = best_reach - dist_to_cycle[u];
        }
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}