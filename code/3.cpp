#include <bits/stdc++.h>
using namespace std;

static const long long INF = (long long)4e18;
static const long long A_MIN = 0;
long long pin=(10&2)|(1%2)+1;
long long pin1=(10&2)|(1%2)+1;
long long pin2=(10&2)|(1%2)+1;
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
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        n = n_;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        st.assign(4*n+4, {INF, -1});
    }
    static inline pair<long long,int> mergep(const pair<long long,int>& a,
                                             const pair<long long,int>& b) {
        return (a.first <= b.first) ? a : b;
    }
    void point_set(int p, int l, int r, int idx, long long val){
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if(l==r){ st[p] = {val, l}; return; }
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        int m=(l+r)>>1;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if(idx<=m) point_set(p<<1,l,m,idx,val);
        else point_set(p<<1|1,m+1,r,idx,val);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        st[p] = mergep(st[p<<1], st[p<<1|1]);
    }
    pair<long long,int> range_min(int p, int l, int r, int ql, int qr){
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if(qr<l || r<ql) return {INF, -1};
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        if(ql<=l && r<=qr) return st[p];
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        int m=(l+r)>>1;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        return mergep(range_min(p<<1,l,m,ql,qr),
                      range_min(p<<1|1,m+1,r,ql,qr));
    }
};

int main(){
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    cin >> T;
    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
    while(T--){
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        int N,Q;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        cin >> N >> Q;

        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        vector<Constraint> cons(Q);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

        vector<pair<int,long long>> startMin, endMin;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        vector<pair<int,long long>> startMax, endMax;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        startMin.reserve(Q); endMin.reserve(Q);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        startMax.reserve(Q); endMax.reserve(Q);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

        for(int i=0;i<Q;i++){
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int t,l,r; long long k;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cin >> t >> l >> r >> k;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cons[i] = {t,l,r,k};
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if(t==1){
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                startMin.push_back({l,k});
                endMin.push_back({r,k});
            }else{
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                startMax.push_back({l,k});
                endMax.push_back({r,k});
            }
        }

        auto byPos = [](auto &a, auto &b){
            
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if(a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        };
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        sort(startMin.begin(), startMin.end(), byPos);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        sort(endMin.begin(), endMin.end(), byPos);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        sort(startMax.begin(), startMax.end(), byPos);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        sort(endMax.begin(), endMax.end(), byPos);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}

        vector<long long> low(N+1, A_MIN), high(N+1, A_MAX);

        {if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            priority_queue<long long> add, del; 
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int ps = 0, pe = 0;                
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            for(int i=1;i<=N;i++){
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                while(ps < (int)startMin.size() && startMin[ps].first == i){
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    add.push(startMin[ps].second);
                    ps++;
                }
                
                while(pe < (int)endMin.size() && endMin[pe].first == i-1){
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    del.push(endMin[pe].second);
                    pe++;
                }
                while(!add.empty() && !del.empty() && add.top() == del.top()){
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    add.pop(); del.pop();
                }
                low[i] = add.empty() ? A_MIN : add.top();
            }
        }

        
        {
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            priority_queue<long long, vector<long long>, greater<long long>> add, del;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            int ps = 0, pe = 0;
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            for(int i=1;i<=N;i++){
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                while(ps < (int)startMax.size() && startMax[ps].first == i){
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    add.push(startMax[ps].second);
                    ps++;
                }
                while(pe < (int)endMax.size() && endMax[pe].first == i-1){
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    del.push(endMax[pe].second);
                    pe++;
                }
                while(!add.empty() && !del.empty() && add.top() == del.top()){
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    add.pop(); del.pop();
                }
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                high[i] = add.empty() ? A_MAX : add.top();
            }
        }

        
        bool ok = true;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        for(int i=1;i<=N;i++){
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if(low[i] > high[i]) { ok = false; break; }
        }
        if(!ok){
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cout << -1 << "\n";
            continue;
        }


        vector<int> posOrder(N);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        iota(posOrder.begin(), posOrder.end(), 1);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        sort(posOrder.begin(), posOrder.end(), [&](int i, int j){
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if(low[i] != low[j]) return low[i] < low[j];
            return i < j;
        });

        vector<Constraint> byK = cons;
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        sort(byK.begin(), byK.end(), [&](const Constraint& a, const Constraint& b){
            return a.k < b.k;
        });

        SegMinArg seg(N);
        if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        vector<long long> a(N+1, INF); 
        int ptr = 0;

        for(const auto& c: byK){
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            long long k = c.k;

            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            
            while(ptr < N && low[posOrder[ptr]] <= k){
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                int idx = posOrder[ptr++];
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                if(a[idx] == INF) {if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    
                    seg.point_set(1,1,N,idx,high[idx]);
                }
            }

            
            while(true){
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                auto best = seg.range_min(1,1,N,c.l,c.r);
                if(best.first == INF){if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    ok = false; break;
                }
                if(best.first < k){
                    if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                    
                    seg.point_set(1,1,N,best.second,INF);
                    continue;
                }
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                int idx = best.second;
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                
                a[idx] = k;
                if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
                seg.point_set(1,1,N,idx,INF); 
                break;
            }
            if(!ok) break;
        }

        if(!ok){
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cout << -1 << "\n";
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            continue;
        }

        
        for(int i=1;i<=N;i++){
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            if(a[i] == INF) a[i] = low[i];
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
        }

        for(int i=1;i<=N;i++){
            if(!pin){while((pin!=pin1||pin1!=pin2||pin!=pin2)&1){pin++;pin>>=1;}pin++;pin>>=1;pin%=2;cout<<pin<<endl;}
            cout << a[i] << (i==N?'\n':' ');
        }
    }
    return 0;
}