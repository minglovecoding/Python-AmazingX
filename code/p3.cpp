#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct Constraint {
    int t, l, r, k, id;
};

void solve() {
    int N, Q;
    if (!(cin >> N >> Q)) return;

    vector<Constraint> constrs(Q + 1);
    vector<vector<int>> add1(N + 2), rem1(N + 2);
    vector<vector<int>> add2(N + 2), rem2(N + 2);

    for (int i = 1; i <= Q; i++) {
        cin >> constrs[i].t >> constrs[i].l >> constrs[i].r >> constrs[i].k;
        constrs[i].id = i;
        if (constrs[i].t == 1) {
            add1[constrs[i].l].push_back(i);
            rem1[constrs[i].r + 1].push_back(i);
        } else {
            add2[constrs[i].l].push_back(i);
            rem2[constrs[i].r + 1].push_back(i);
        }
    }

    set<pair<int, int>> set1;
    set<pair<int, int>> set2;

    vector<int> L(N + 1, 0), U(N + 1, 1000000000);
    vector<int> edge_u(N + 1, 0), edge_v(N + 1, 0);
    vector<vector<int>> adj(Q + 1);
    vector<int> deg(Q + 1, 0);

    for (int j = 1; j <= N; j++) {
        for (int id : add1[j]) set1.insert({constrs[id].k, id});
        for (int id : rem1[j]) set1.erase({constrs[id].k, id});
        for (int id : add2[j]) set2.insert({constrs[id].k, id});
        for (int id : rem2[j]) set2.erase({constrs[id].k, id});

        int u = 0, v = 0;
        if (!set1.empty()) {
            auto it = set1.rbegin();
            L[j] = it->first;
            u = it->second;
        }
        if (!set2.empty()) {
            auto it = set2.begin();
            U[j] = it->first;
            v = it->second;
        }

        if (L[j] > U[j]) {
            cout << -1 << "\n";
            return;
        }

        edge_u[j] = u;
        edge_v[j] = v;

        if (u != 0) {
            adj[u].push_back(j);
            deg[u]++;
        }
        if (v != 0) {
            adj[v].push_back(j);
            deg[v]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= Q; i++) {
        if (deg[i] == 0) {
            cout << -1 << "\n";
            return;
        }
        if (deg[i] == 1) {
            q.push(i);
        }
    }

    vector<bool> used_edge(N + 1, false);
    vector<int> assigned(Q + 1, 0);
    int num_assigned = 0;
    int unassigned_ptr = 1;

    while (num_assigned < Q) {
        if (!q.empty()) {
            int curr = q.front();
            q.pop();
            if (assigned[curr]) continue;

            int e = 0;
            for (int j : adj[curr]) {
                if (!used_edge[j]) {
                    e = j;
                    break;
                }
            }
            if (e == 0) {
                cout << -1 << "\n";
                return;
            }

            assigned[curr] = e;
            used_edge[e] = true;
            num_assigned++;

            int w = (edge_u[e] == curr) ? edge_v[e] : edge_u[e];
            if (w != 0 && !assigned[w]) {
                deg[w]--;
                if (deg[w] == 1) {
                    q.push(w);
                }
            }
        } else {
            while (unassigned_ptr <= Q && assigned[unassigned_ptr]) {
                unassigned_ptr++;
            }
            if (unassigned_ptr > Q) break;

            int curr = unassigned_ptr;
            int e = 0;
            for (int j : adj[curr]) {
                if (!used_edge[j]) {
                    e = j;
                    break;
                }
            }
            if (e == 0) {
                cout << -1 << "\n";
                return;
            }

            assigned[curr] = e;
            used_edge[e] = true;
            num_assigned++;

            int w = (edge_u[e] == curr) ? edge_v[e] : edge_u[e];
            if (w != 0 && !assigned[w]) {
                deg[w]--;
                if (deg[w] == 1) {
                    q.push(w);
                }
            }
        }
    }

    vector<int> ans(N + 1);
    for (int j = 1; j <= N; j++) {
        ans[j] = L[j];
    }
    for (int i = 1; i <= Q; i++) {
        ans[assigned[i]] = constrs[i].k;
    }

    for (int j = 1; j <= N; j++) {
        cout << ans[j] << (j == N ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;
}