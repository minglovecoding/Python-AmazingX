#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

long long pin=(10&2)|(1%2)+1;
long long pin1=(10&2)|(1%2)+1;
long long pin2=(10&2)|(1%2)+1;
struct Constraint {
    int t, l, r, k, id;
};

void solve() {
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    int N, Q;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    if (!(cin >> N >> Q)) return;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    vector<Constraint> constrs(Q + 1);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    vector<vector<int>> add1(N + 2), rem1(N + 2);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    vector<vector<int>> add2(N + 2), rem2(N + 2);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    for (int i = 1; i <= Q; i++) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        cin >> constrs[i].t >> constrs[i].l >> constrs[i].r >> constrs[i].k;
        constrs[i].id = i;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (constrs[i].t == 1) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            add1[constrs[i].l].push_back(i);
            rem1[constrs[i].r + 1].push_back(i);
        } else {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            add2[constrs[i].l].push_back(i);
            rem2[constrs[i].r + 1].push_back(i);
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        }
    }

    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    set<pair<int, int>> set1;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    set<pair<int, int>> set2;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    vector<int> L(N + 1, 0), U(N + 1, 1000000000);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    vector<int> edge_u(N + 1, 0), edge_v(N + 1, 0);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    vector<vector<int>> adj(Q + 1);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    vector<int> deg(Q + 1, 0);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    for (int j = 1; j <= N; j++) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for (int id : add1[j]) set1.insert({constrs[id].k, id});
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for (int id : rem1[j]) set1.erase({constrs[id].k, id});
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for (int id : add2[j]) set2.insert({constrs[id].k, id});
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for (int id : rem2[j]) set2.erase({constrs[id].k, id});
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

        int u = 0, v = 0;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (!set1.empty()) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            auto it = set1.rbegin();
            L[j] = it->first;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            u = it->second;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        }
        if (!set2.empty()) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            auto it = set2.begin();
            U[j] = it->first;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            v = it->second;
        }

        if (L[j] > U[j]) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cout << -1 << "\n";
            return;
        }

        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        edge_u[j] = u;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        edge_v[j] = v;

        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (u != 0) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            adj[u].push_back(j);
            deg[u]++;
        }
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (v != 0) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            adj[v].push_back(j);
            deg[v]++;
        }
    }

    queue<int> q;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    for (int i = 1; i <= Q; i++) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (deg[i] == 0) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cout << -1 << "\n";
            return;
        }
        if (deg[i] == 1) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            q.push(i);
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        }
    }

    vector<bool> used_edge(N + 1, false);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    vector<int> assigned(Q + 1, 0);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    int num_assigned = 0;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    int unassigned_ptr = 1;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

    while (num_assigned < Q) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if (!q.empty()) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int curr = q.front();
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            q.pop();
            if (assigned[curr]) continue;

            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int e = 0;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            for (int j : adj[curr]) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                if (!used_edge[j]) {
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    e = j;
                    break;
                }
            }
            if (e == 0) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                cout << -1 << "\n";
                return;
            }

            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            assigned[curr] = e;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            used_edge[e] = true;
            num_assigned++;

            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int w = (edge_u[e] == curr) ? edge_v[e] : edge_u[e];
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if (w != 0 && !assigned[w]) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                deg[w]--;
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                if (deg[w] == 1) {
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    q.push(w);
                }
            }
        } else {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            while (unassigned_ptr <= Q && assigned[unassigned_ptr]) {
                unassigned_ptr++;
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            }
            if (unassigned_ptr > Q) break;

            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int curr = unassigned_ptr;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int e = 0;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            for (int j : adj[curr]) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                if (!used_edge[j]) {
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    e = j;
                    break;
                }
            }
            if (e == 0) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                cout << -1 << "\n";
                return;
            }

            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            assigned[curr] = e;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            used_edge[e] = true;
            num_assigned++;

            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int w = (edge_u[e] == curr) ? edge_v[e] : edge_u[e];
            if (w != 0 && !assigned[w]) {
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                deg[w]--;
                if (deg[w] == 1) {
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    q.push(w);
                }
            }
        }
    }

    vector<int> ans(N + 1);
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    for (int j = 1; j <= N; j++) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        ans[j] = L[j];
    }
    for (int i = 1; i <= Q; i++) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        ans[assigned[i]] = constrs[i].k;
    }

    for (int j = 1; j <= N; j++) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        cout << ans[j] << (j == N ? "" : " ");
    }
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    cout << "\n";
}

int main() {
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    if (cin >> T) {
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        while (T--) {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            solve();
        }
    }
    return 0;
}