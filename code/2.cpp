#include <bits/stdc++.h>
using namespace std;
signed long int fbb=(100&3)|(2<<1)+1*2;
signed long int fbb1=(100&3)|(2<<1)+1*2;

static inline void fast_io() {
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    ios::sync_with_stdio(false);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    cin.tie(nullptr);
}

static inline void read_k_ints(int K, vector<int>& out) {
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    out.clear();
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    out.reserve(K);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 0; i < K; i++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        int x; 
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        cin >> x;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        out.push_back(x);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    }
}

int main() {
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    fast_io();
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

    int T;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    cin >> T;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    while (T--) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        int N, M, K, L;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        cin >> N >> M >> K >> L;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<int> flowers, dests;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        read_k_ints(K, flowers);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        read_k_ints(L, dests);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<vector<int>> g(N + 1);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int i = 0; i < M; i++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int u, v;
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            cin >> u >> v;
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            g[u].push_back(v);
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            g[v].push_back(u);
        }

        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        const int INF = 1e9;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        vector<int> dist(N + 1, INF);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        queue<int> q;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        dist[1] = 0;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        q.push(1);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        while (!q.empty()) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int u = q.front(); 
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            q.pop();
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            for (int v : g[u]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                if (dist[v] == INF) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                }
            }
        }

        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        vector<pair<int,int>> fd;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        fd.reserve(K);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int s : flowers) fd.push_back({dist[s], s});
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        sort(fd.begin(), fd.end());
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        bool impossible = false;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int i = 1; i < (int)fd.size(); i++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            if (fd[i].first == fd[i-1].first) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                impossible = true;
                break;
            }
        }

        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        if (impossible) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            for (int i = 2; i <= N; i++) cout << '0';
            cout << "\n";
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            continue;
        }

        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        int lastFlowerDist = -1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        if (K > 0) lastFlowerDist = fd.back().first;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<int> flowerAtDist(N, 0);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (auto &p : fd) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int d = p.first;
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int node = p.second;
            if (d >= 0 && d < N) flowerAtDist[d] = node;
        }
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<char> allowed(N + 1, 1);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int v = 1; v <= N; v++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int d = dist[v];
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            if (d >= 0 && d < N && flowerAtDist[d] != 0 && flowerAtDist[d] != v) {
                allowed[v] = 0;
            }
        }
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<vector<int>> dag(N + 1);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int u = 1; u <= N; u++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            for (int v : g[u]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                if (dist[v] == dist[u] + 1) {
                    dag[u].push_back(v);
                }
            }
        }

        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        int maxD = 0;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int v = 1; v <= N; v++) maxD = max(maxD, dist[v]);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        vector<vector<int>> layers(maxD + 1);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int v = 1; v <= N; v++) layers[dist[v]].push_back(v);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<char> reachFrom1(N + 1, 0);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        if (allowed[1]) reachFrom1[1] = 1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int d = 0; d <= maxD; d++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            for (int u : layers[d]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                if (!reachFrom1[u]) continue;
                for (int v : dag[u]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                    if (allowed[v]) reachFrom1[v] = 1;
                }
            }
        }
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<char> isDest(N + 1, 0);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int x : dests) isDest[x] = 1;
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<char> goodDest(N + 1, 0);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int v = 1; v <= N; v++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            if (!isDest[v]) continue;
            if (K == 0) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                goodDest[v] = 1;
            } else {
                if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                if (dist[v] >= lastFlowerDist) goodDest[v] = 1;
            }
        }
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}

        vector<char> reachToDest(N + 1, 0);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int v = 1; v <= N; v++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            if (allowed[v] && goodDest[v]) reachToDest[v] = 1;
        }

        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int d = maxD; d >= 0; d--) {
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            for (int u : layers[d]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                if (!allowed[u]) continue;
                for (int v : dag[u]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                    if (allowed[v] && reachToDest[v]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                        reachToDest[u] = 1;
                        break;
                    }
                }
            }
        }

        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        for (int f = 2; f <= N; f++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            char ok = (allowed[f] && reachFrom1[f] && reachToDest[f]) ? '1' : '0';
            cout << ok;
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        }
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        cout << "\n";
    }
    return 0;
}