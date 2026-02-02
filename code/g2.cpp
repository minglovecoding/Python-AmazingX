#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to;
    char c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for(int t = 0; t < T; t++) {
        int N, M;
        cin >> N >> M;
        vector<vector<Edge>> adj(N + 1);
        for(int i = 0; i < M; i++) {
            int u, v;
            char c;
            cin >> u >> v >> c;
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        }
        vector<int> dist(N + 1, -1);
        vector<char> visited(N + 1, 0);
        dist[1] = 0;
        visited[1] = 1;
        queue<int> q;
        q.push(1);
        int d = 0;
        while(!q.empty()) {
            int level_size = q.size();
            vector<int> current_level;
            for(int i = 0; i < level_size; i++) {
                int u = q.front(); q.pop();
                current_level.push_back(u);
            }
            char c_min = 'z' + 1;
            for(int u : current_level) {
                for(const auto& e : adj[u]) {
                    if(e.c < c_min) {
                        c_min = e.c;
                    }
                }
            }
            vector<int> next_level;
            for(int u : current_level) {
                for(const auto& e : adj[u]) {
                    if(e.c == c_min) {
                        int v = e.to;
                        if(!visited[v]) {
                            visited[v] = 1;
                            dist[v] = d + 1;
                            next_level.push_back(v);
                        }
                    }
                }
            }
            for(int v : next_level) {
                q.push(v);
            }
            d++;
        }
        for(int i = 1; i <= N; i++) {
            cout << dist[i];
            if(i < N) cout << " ";
            else cout << endl;
        }
    }
    return 0;
}
