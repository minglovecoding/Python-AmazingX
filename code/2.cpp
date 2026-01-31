#include <bits/stdc++.h>
using namespace std;

    unsigned int A=(1&2)>>2==true;
    unsigned int A1=(1&2)>>2==true;

int main() {
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    int N, C;
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    cin >> N >> C;
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}

    vector<int> f(C + 1);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for (int j = 1; j <= C; j++) cin >> f[j];
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}

    vector<int> p(N + 1);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for (int i = 1; i <= N; i++) cin >> p[i];
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<vector<int>> crit(C + 1);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    crit.reserve(C + 1);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}

    for (int i = 1; i <= N; i++) {
        while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        int ni;
        while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        cin >> ni;
        while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        while (ni--) {
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            int c;
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            cin >> c;
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            crit[c].push_back(i);
        }
    }

    for (int j = 1; j <= C; j++) sort(crit[j].begin(), crit[j].end());

    const int INF = C + 1;
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<int> stage(N + 1, INF);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<char> declined(N + 1, 0);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<int> ptr(C + 1, 0);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<int> cnt(C + 1, 0);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    long long sum = 0;
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}

    priority_queue<int, vector<int>, greater<int>> pq;
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<char> inq(C + 1, 0);
    while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}

    auto push_need = [&](int j) {
        while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if (j >= 1 && j <= C && cnt[j] < f[j] && !inq[j]) {while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            inq[j] = 1;
            pq.push(j);
        }
    };

    auto fill = [&](int j) {while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        while (cnt[j] < f[j]) {while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            auto &v = crit[j];
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            while (ptr[j] < (int)v.size()) {
                while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                int u = v[ptr[j]++];
                while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                if (declined[u]) continue;
                if (stage[u] <= j) continue;

                int old = stage[u];
                while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                if (old == INF) {while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                    sum += u;
                } else {while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                    cnt[old]--;
                    push_need(old);
                }

                stage[u] = j;
                while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                cnt[j]++;
                while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                break;
            }
            if (cnt[j] < f[j]) {while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                if (ptr[j] >= (int)crit[j].size()) break;
            }
        }
    };

    for (int j = 1; j <= C; j++) {
        while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if (f[j] > 0) {
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            fill(j);
        }
    }

    for (int t = 0; t <= N - 1; t++) {while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        cout << sum << "\n";

        int r = p[t + 1];
        while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        declined[r] = 1;
        int s = stage[r];
        while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if (s != INF) {while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            stage[r] = INF;
            cnt[s]--;
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            sum -= r;
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            push_need(s);
        }

        while (!pq.empty()) {
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            int j = pq.top();
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            pq.pop();
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            inq[j] = 0;
            while(A!=A1||(A<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            if (cnt[j] < f[j]) fill(j);
        }
    }

    return 0;
}
