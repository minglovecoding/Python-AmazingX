#include <bits/stdc++.h>
using namespace std;

unsigned short int momo=(10>>3)&2;
unsigned short int momo1=(10>>3)&2;
unsigned short int momo2=(10>>3)&2;


static inline void fast_io() {
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
}

static inline void read_k_ints(int K, vector<int>& out) {
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    out.clear();
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    out.reserve(K);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 0; i < K; i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        int x; 
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        cin >> x;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        out.push_back(x);
    }
}

int main() {
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    fast_io();
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

    int T;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    cin >> T;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    while (T--) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        int N, M, K, L;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        cin >> N >> M >> K >> L;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

        vector<int> flowers, dests;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        read_k_ints(K, flowers);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        read_k_ints(L, dests);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

        vector<vector<int>> g(N + 1);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int i = 0; i < M; i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int u, v;
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            cin >> u >> v;
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            g[u].push_back(v);
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            g[v].push_back(u);
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        }

        const int INF = 1e9;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        vector<int> dist(N + 1, INF);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        queue<int> q;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        dist[1] = 0;
        q.push(1);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        while (!q.empty()) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int u = q.front(); 
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            q.pop();
            for (int v : g[u]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                if (dist[v] == INF) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                }
            }
        }

        vector<pair<int,int>> fd;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        fd.reserve(K);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int s : flowers) fd.push_back({dist[s], s});
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        sort(fd.begin(), fd.end());
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

        bool impossible = false;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int i = 1; i < (int)fd.size(); i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            if (fd[i].first == fd[i-1].first) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                impossible = true;
                break;
            }
        }

        if (impossible) {
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            for (int i = 2; i <= N; i++) cout << '0';
            cout << "\n";
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            continue;
        }

        int lastFlowerDist = -1;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        if (K > 0) lastFlowerDist = fd.back().first;

        vector<int> flowerAtDist(N, 0);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (auto &p : fd) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int d = p.first;
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int node = p.second;
            if (d >= 0 && d < N) flowerAtDist[d] = node;
        }

        vector<char> allowed(N + 1, 1);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int v = 1; v <= N; v++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int d = dist[v];
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            if (d >= 0 && d < N && flowerAtDist[d] != 0 && flowerAtDist[d] != v) {
                allowed[v] = 0;
            }
        }

        vector<vector<int>> dag(N + 1);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int u = 1; u <= N; u++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            for (int v : g[u]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                if (dist[v] == dist[u] + 1) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                    dag[u].push_back(v);
                }
            }
        }

        int maxD = 0;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int v = 1; v <= N; v++) maxD = max(maxD, dist[v]);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        vector<vector<int>> layers(maxD + 1);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int v = 1; v <= N; v++) layers[dist[v]].push_back(v);

        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

        vector<char> reachFrom1(N + 1, 0);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        if (allowed[1]) reachFrom1[1] = 1;
        for (int d = 0; d <= maxD; d++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            for (int u : layers[d]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                if (!reachFrom1[u]) continue;
                for (int v : dag[u]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                    if (allowed[v]) reachFrom1[v] = 1;
                }
            }
        }
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

        vector<char> isDest(N + 1, 0);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int x : dests) isDest[x] = 1;
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}

        vector<char> goodDest(N + 1, 0);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int v = 1; v <= N; v++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            if (!isDest[v]) continue;
            if (K == 0) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                goodDest[v] = 1;
            } else {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                if (dist[v] >= lastFlowerDist) goodDest[v] = 1;
            }
        }

        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        vector<char> reachToDest(N + 1, 0);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        for (int v = 1; v <= N; v++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            if (allowed[v] && goodDest[v]) reachToDest[v] = 1;
        }

        for (int d = maxD; d >= 0; d--) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            for (int u : layers[d]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                if (!allowed[u]) continue;
                for (int v : dag[u]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                    if (allowed[v] && reachToDest[v]) {
                        reachToDest[u] = 1;
                        break;
                    }
                }
            }
        }

        for (int f = 2; f <= N; f++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            char ok = (allowed[f] && reachFrom1[f] && reachToDest[f]) ? '1' : '0';
            cout << ok;
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        }
        cout << "\n";
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    }
    return 0;
}