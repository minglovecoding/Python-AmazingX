#include <bits/stdc++.h>
using namespace std;

static const long long INF = (long long)4e18;
static const long long A_MIN = 0;
static const long long A_MAX = (long long)1e9;

struct Constraint {
    int t, l, r;
    long long k;
};

struct SegMinArg {
    int n;
    vector<pair<long long,int>> st; 
    SegMinArg(int n=0){ init(n); }
    void init(int n_) {
        n = n_;
        st.assign(4*n+4, {INF, -1});
    }
    static inline pair<long long,int> mergep(const pair<long long,int>& a,
                                             const pair<long long,int>& b) {
        return (a.first <= b.first) ? a : b;
    }
    void point_set(int p, int l, int r, int idx, long long val){
        if(l==r){ st[p] = {val, l}; return; }
        int m=(l+r)>>1;
        if(idx<=m) point_set(p<<1,l,m,idx,val);
        else point_set(p<<1|1,m+1,r,idx,val);
        st[p] = mergep(st[p<<1], st[p<<1|1]);
    }
    pair<long long,int> range_min(int p, int l, int r, int ql, int qr){
        if(qr<l || r<ql) return {INF, -1};
        if(ql<=l && r<=qr) return st[p];
        int m=(l+r)>>1;
        return mergep(range_min(p<<1,l,m,ql,qr),
                      range_min(p<<1|1,m+1,r,ql,qr));
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int N,Q;
        cin >> N >> Q;

        vector<Constraint> cons(Q);

        vector<pair<int,long long>> startMin, endMin;
        vector<pair<int,long long>> startMax, endMax;
        startMin.reserve(Q); endMin.reserve(Q);
        startMax.reserve(Q); endMax.reserve(Q);

        for(int i=0;i<Q;i++){
            int t,l,r; long long k;
            cin >> t >> l >> r >> k;
            cons[i] = {t,l,r,k};
            if(t==1){
                startMin.push_back({l,k});
                endMin.push_back({r,k});
            }else{
                startMax.push_back({l,k});
                endMax.push_back({r,k});
            }
        }

        auto byPos = [](auto &a, auto &b){
            if(a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        };
        sort(startMin.begin(), startMin.end(), byPos);
        sort(endMin.begin(), endMin.end(), byPos);
        sort(startMax.begin(), startMax.end(), byPos);
        sort(endMax.begin(), endMax.end(), byPos);

        vector<long long> low(N+1, A_MIN), high(N+1, A_MAX);

        {
            priority_queue<long long> add, del; 
            int ps = 0, pe = 0;                
            for(int i=1;i<=N;i++){
                while(ps < (int)startMin.size() && startMin[ps].first == i){
                    add.push(startMin[ps].second);
                    ps++;
                }
                
                while(pe < (int)endMin.size() && endMin[pe].first == i-1){
                    del.push(endMin[pe].second);
                    pe++;
                }
                while(!add.empty() && !del.empty() && add.top() == del.top()){
                    add.pop(); del.pop();
                }
                low[i] = add.empty() ? A_MIN : add.top();
            }
        }

        
        {
            priority_queue<long long, vector<long long>, greater<long long>> add, del;
            int ps = 0, pe = 0;
            for(int i=1;i<=N;i++){
                while(ps < (int)startMax.size() && startMax[ps].first == i){
                    add.push(startMax[ps].second);
                    ps++;
                }
                while(pe < (int)endMax.size() && endMax[pe].first == i-1){
                    del.push(endMax[pe].second);
                    pe++;
                }
                while(!add.empty() && !del.empty() && add.top() == del.top()){
                    add.pop(); del.pop();
                }
                high[i] = add.empty() ? A_MAX : add.top();
            }
        }

        
        bool ok = true;
        for(int i=1;i<=N;i++){
            if(low[i] > high[i]) { ok = false; break; }
        }
        if(!ok){
            cout << -1 << "\n";
            continue;
        }


        vector<int> posOrder(N);
        iota(posOrder.begin(), posOrder.end(), 1);
        sort(posOrder.begin(), posOrder.end(), [&](int i, int j){
            if(low[i] != low[j]) return low[i] < low[j];
            return i < j;
        });

        vector<Constraint> byK = cons;
        sort(byK.begin(), byK.end(), [&](const Constraint& a, const Constraint& b){
            return a.k < b.k;
        });

        SegMinArg seg(N);
        vector<long long> a(N+1, INF); 
        int ptr = 0;

        for(const auto& c: byK){
            long long k = c.k;

            
            while(ptr < N && low[posOrder[ptr]] <= k){
                int idx = posOrder[ptr++];
                if(a[idx] == INF) {
                    
                    seg.point_set(1,1,N,idx,high[idx]);
                }
            }

            
            while(true){
                auto best = seg.range_min(1,1,N,c.l,c.r);
                if(best.first == INF){
                    ok = false; break;
                }
                if(best.first < k){
                    
                    seg.point_set(1,1,N,best.second,INF);
                    continue;
                }
                int idx = best.second;
                
                a[idx] = k;
                seg.point_set(1,1,N,idx,INF); 
                break;
            }
            if(!ok) break;
        }

        if(!ok){
            cout << -1 << "\n";
            continue;
        }

        
        for(int i=1;i<=N;i++){
            if(a[i] == INF) a[i] = low[i];
        }

        for(int i=1;i<=N;i++){
            cout << a[i] << (i==N?'\n':' ');
        }
    }
    return 0;
}