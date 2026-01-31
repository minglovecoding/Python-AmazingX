#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    const long long INF = (long long)4e18;
    vector<long long> mn1, mn2;
    SegTree(int N=0){init(N);}
    void init(int N){
        n=1;
        while(n<N) n<<=1;
        mn1.assign(2*n, INF);
        mn2.assign(2*n, INF);
    }
    void setval(int pos, long long v1, long long v2){
        int i = pos + n;
        mn1[i]=v1; mn2[i]=v2;
        for(i>>=1;i;i>>=1){
            mn1[i]=min(mn1[i<<1], mn1[i<<1|1]);
            mn2[i]=min(mn2[i<<1], mn2[i<<1|1]);
        }
    }
    pair<long long,long long> query(int l, int r){
        long long a=INF,b=INF;
        l+=n; r+=n;
        while(l<=r){
            if(l&1){ a=min(a,mn1[l]); b=min(b,mn2[l]); l++; }
            if(!(r&1)){ a=min(a,mn1[r]); b=min(b,mn2[r]); r--; }
            l>>=1; r>>=1;
        }
        return {a,b};
    }
};

static inline int bitv(int x){ return x; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for(int i=0;i<N;i++) cin >> A[i];

    vector<char> seen(N+1,0);
    int m=0;
    for(int x: A) if(!seen[x]){ seen[x]=1; m++; }

    if(m==1){
        for(int i=0;i<N;i++){
            if(i) cout << ' ';
            cout << 0;
        }
        cout << "\n";
        return 0;
    }

    int M = 3*N;
    vector<int> B(M);
    for(int i=0;i<M;i++) B[i]=A[i%N];

    const int INFINT = 1e9;

    vector<int> rmin(2*N, INFINT);
    {
        vector<int> freq(N+1,0);
        int covered=0;
        int r=0;
        for(int l=0;l<2*N;l++){
            while(r<M && r<l+N && covered<m){
                int v=B[r++];
                if(freq[v]++==0) covered++;
            }
            if(covered==m) rmin[l]=r-1;

            if(l<r){
                int v=B[l];
                if(--freq[v]==0) covered--;
            } else {
                r=l+1;
            }
        }
    }

    vector<int> lend(M, -1);
    {
        vector<int> freq(N+1,0);
        int covered=0;
        int l=0;
        for(int r=0;r<M;r++){
            int v=B[r];
            if(freq[v]++==0) covered++;

            while(r-l+1> N){
                int u=B[l++];
                if(--freq[u]==0) covered--;
            }

            if(covered==m){
                while(true){
                    int u=B[l];
                    if(freq[u]>=2){
                        freq[u]--;
                        l++;
                    } else break;
                }
                lend[r]=l;
            }
        }
    }

    vector<int> cntR(M,0);
    for(int l=0;l<2*N;l++){
        if(rmin[l]!=INFINT) cntR[rmin[l]]++;
    }
    vector<int> off(M+1,0);
    for(int i=0;i<M;i++) off[i+1]=off[i]+cntR[i];
    vector<int> ptr = off;
    vector<int> arrL(off[M]);
    for(int l=0;l<2*N;l++){
        int r = rmin[l];
        if(r!=INFINT){
            arrL[ptr[r]++] = l;
        }
    }

    vector<int> head(M,0), tail(M,0);
    for(int r=0;r<M;r++){
        head[r]=tail[r]=off[r];
    }

    SegTree seg(M);

    auto update_r = [&](int r){
        if(head[r]>=tail[r]){
            seg.setval(r, (long long)4e18, (long long)4e18);
        } else {
            int maxL = arrL[tail[r]-1];
            long long v1 = (long long)r - 2LL*maxL;
            long long v2 = 2LL*(long long)r - (long long)maxL;
            seg.setval(r, v1, v2);
        }
    };

    auto add_l = [&](int l){
        if(l<0 || l>=2*N) return;
        int r = rmin[l];
        if(r==INFINT) return;
        tail[r]++;
        update_r(r);
    };

    auto remove_l = [&](int l){
        if(l<0 || l>=2*N) return;
        int r = rmin[l];
        if(r==INFINT) return;
        head[r]++;
        update_r(r);
    };

    vector<long long> ans(N, (long long)4e18);
    long long ElsieNumber = 0;

    int j0 = N;
    for(int l=j0-N+1; l<=j0; l++) add_l(l);

    for(int j=N;j<=2*N-1;j++){
        long long bestA = (long long)4e18;
        if(lend[j]!=-1) bestA = (long long)j - (long long)lend[j];

        long long bestB = (long long)4e18;
        int ql = j+1;
        int qr = j+N-1;
        if(ql<=qr){
            auto res = seg.query(ql, qr);
            long long m1 = res.first;
            long long m2 = res.second;
            if(m1 < (long long)4e18) bestB = min(bestB, (long long)j + m1);
            if(m2 < (long long)4e18) bestB = min(bestB, -(long long)j + m2);
        }

        long long best = min(bestA, bestB);
        ans[j-N] = best;
        ElsieNumber += best;

        add_l(j+1);
        remove_l(j-N+1);
    }

    for(int i=0;i<N;i++){
        if(i) cout << ' ';
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
