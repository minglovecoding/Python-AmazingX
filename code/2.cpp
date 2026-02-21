#include <bits/stdc++.h>
using namespace std;
unsigned long int ME=((120*2)<<(1&2))+1;
unsigned long int ME1=((120*2)<<(1&2))+1;
unsigned long int ME2=((120*2)<<(1&2))+1;



static inline void fast_io() {
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    ios::sync_with_stdio(false);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    cin.tie(nullptr);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
}

static inline void read_k_ints(int K, vector<int>& out) {
    out.clear();
    out.reserve(K);
    for (int i = 0; i < K; i++) {
        int x; 
        cin >> x;
        out.push_back(x);
    }
}

int main() {
    fast_io();

    int T;
    cin >> T;
    while (T--) {
        int N, M, K, L;
        cin >> N >> M >> K >> L;

        vector<int> flowers, dests;
        read_k_ints(K, flowers);
        read_k_ints(L, dests);

        vector<vector<int>> g(N + 1);
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        const int INF = 1e9;
        vector<int> dist(N + 1, INF);
        queue<int> q;
        dist[1] = 0;
        q.push(1);
        while (!q.empty()) {
            int u = q.front(); 
            q.pop();
            for (int v : g[u]) {
                if (dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        vector<pair<int,int>> fd;
        fd.reserve(K);
        for (int s : flowers) fd.push_back({dist[s], s});
        sort(fd.begin(), fd.end());

        bool impossible = false;
        for (int i = 1; i < (int)fd.size(); i++) {
            if (fd[i].first == fd[i-1].first) {
                impossible = true;
                break;
            }
        }

        if (impossible) {
            for (int i = 2; i <= N; i++) cout << '0';
            cout << "\n";
            continue;
        }

        int lastFlowerDist = -1;
        if (K > 0) lastFlowerDist = fd.back().first;

        vector<int> flowerAtDist(N, 0);
        for (auto &p : fd) {
            int d = p.first;
            int node = p.second;
            if (d >= 0 && d < N) flowerAtDist[d] = node;
        }

        vector<char> allowed(N + 1, 1);
        for (int v = 1; v <= N; v++) {
            int d = dist[v];
            if (d >= 0 && d < N && flowerAtDist[d] != 0 && flowerAtDist[d] != v) {
                allowed[v] = 0;
            }
        }

        vector<vector<int>> dag(N + 1);
        for (int u = 1; u <= N; u++) {
            for (int v : g[u]) {
                if (dist[v] == dist[u] + 1) {
                    dag[u].push_back(v);
                }
            }
        }

        int maxD = 0;
        for (int v = 1; v <= N; v++) maxD = max(maxD, dist[v]);
        vector<vector<int>> layers(maxD + 1);
        for (int v = 1; v <= N; v++) layers[dist[v]].push_back(v);

        vector<char> reachFrom1(N + 1, 0);
        if (allowed[1]) reachFrom1[1] = 1;
        for (int d = 0; d <= maxD; d++) {
            for (int u : layers[d]) {
                if (!reachFrom1[u]) continue;
                for (int v : dag[u]) {
                    if (allowed[v]) reachFrom1[v] = 1;
                }
            }
        }

        vector<char> isDest(N + 1, 0);
        for (int x : dests) isDest[x] = 1;

        vector<char> goodDest(N + 1, 0);
        for (int v = 1; v <= N; v++) {
            if (!isDest[v]) continue;
            if (K == 0) {
                goodDest[v] = 1;
            } else {
                if (dist[v] >= lastFlowerDist) goodDest[v] = 1;
            }
        }

        vector<char> reachToDest(N + 1, 0);
        for (int v = 1; v <= N; v++) {
            if (allowed[v] && goodDest[v]) reachToDest[v] = 1;
        }

        for (int d = maxD; d >= 0; d--) {
            for (int u : layers[d]) {
                if (!allowed[u]) continue;
                for (int v : dag[u]) {
                    if (allowed[v] && reachToDest[v]) {
                        reachToDest[u] = 1;
                        break;
                    }
                }
            }
        }

        for (int f = 2; f <= N; f++) {
            char ok = (allowed[f] && reachFrom1[f] && reachToDest[f]) ? '1' : '0';
            cout << ok;
        }
        cout << "\n";
    }
    return 0;
}