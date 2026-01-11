#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

struct Edge {
    int to;
    ll z;
};

int N, M;
vector<ll> L, R;
vector<vector<Edge>> adj;
vector<int> node_type; 
vector<ll> node_const; 
vector<int> component_nodes;

bool possible;
bool root_fixed;
ll root_val;

void dfs(int u, int t, ll c) {
    node_type[u] = t;
    node_const[u] = c;
    component_nodes.push_back(u);

    for (auto& e : adj[u]) {
        int v = e.to;
        ll z = e.z;
        
        int target_t = -t;
        ll target_c = z - c;

        if (node_type[v] == 0) {
            dfs(v, target_t, target_c);
            if (!possible) return;
        } else {
            if (node_type[v] == target_t) {
                if (node_const[v] != target_c) {
                    possible = false;
                    return;
                }
            } else {
                ll diff;
                if (node_type[v] == 1) {
                    diff = target_c - node_const[v];
                } else {
                    diff = node_const[v] - target_c;
                }

                if (abs(diff) % 2 != 0) {
                    possible = false; 
                    return;
                }
                
                ll calculated_root = diff / 2;
                
                if (root_fixed && root_val != calculated_root) {
                    possible = false; 
                    return;
                }
                
                root_fixed = true;
                root_val = calculated_root;
            }
        }
    }
}

void solve() {
    if (!(cin >> N >> M)) return;
    
    L.assign(N + 1, 0);
    R.assign(N + 1, 0);
    for (int i = 1; i <= N; ++i) cin >> L[i];
    for (int i = 1; i <= N; ++i) cin >> R[i];

    adj.assign(N + 1, vector<Edge>());
    for (int i = 0; i < M; ++i) {
        int u, v;
        ll z;
        cin >> u >> v >> z;
        adj[u].push_back({v, z});
        adj[v].push_back({u, z});
    }

    node_type.assign(N + 1, 0);
    node_const.assign(N + 1, 0);
    possible = true;
    
    ll total_generating = 0;

    for (int i = 1; i <= N; ++i) {
        if (node_type[i] == 0) {
            component_nodes.clear();
            root_fixed = false;
            
            dfs(i, 1, 0);

            if (!possible) {
                cout << -1 << endl;
                return;
            }

            if (root_fixed) {
                for (int u : component_nodes) {
                    ll val = (ll)node_type[u] * root_val + node_const[u];
                    if (val >= L[u] && val <= R[u]) {
                        total_generating++;
                    }
                }
            } else {
                vector<pair<ll, int>> events;
                
                for (int u : component_nodes) {
                    ll low, high;
                    
                    if (node_type[u] == 1) {
                        low = L[u] - node_const[u];
                        high = R[u] - node_const[u];
                    } else {
                        low = node_const[u] - R[u];
                        high = node_const[u] - L[u];
                    }

                    if (low <= high) {
                        events.push_back({low, 1});
                        events.push_back({high + 1, -1});
                    }
                }
                
                sort(events.begin(), events.end());
                
                ll current_overlap = 0;
                ll max_overlap = 0;
                
                for (auto& ev : events) {
                    current_overlap += ev.second;
                    if (current_overlap > max_overlap) {
                        max_overlap = current_overlap;
                    }
                }
                total_generating += max_overlap;
            }
        }
    }

    cout << total_generating << endl;
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