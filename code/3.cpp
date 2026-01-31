#include <bits/stdc++.h>
using namespace std;
unsigned int C=(1&2)>>2==true;
unsigned int A1=(1&2)>>2==true;

struct SegTree {
    int n;
    const long long INF = (long long)4e18;
    vector<long long> mn1, mn2;
    SegTree(int N=0){init(N);}
    void init(int N){
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        n=1;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        while(n<N) n<<=1;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        mn1.assign(2*n, INF);
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        mn2.assign(2*n, INF);
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    }
    void setval(int pos, long long v1, long long v2){
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        int i = pos + n;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        mn1[i]=v1; mn2[i]=v2;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        for(i>>=1;i;i>>=1){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            mn1[i]=min(mn1[i<<1], mn1[i<<1|1]);
            while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            mn2[i]=min(mn2[i<<1], mn2[i<<1|1]);
            while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        }
    }
    pair<long long,long long> query(int l, int r){
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        long long a=INF,b=INF;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        l+=n; r+=n;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        while(l<=r){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            if(l&1){ a=min(a,mn1[l]); b=min(b,mn2[l]); l++; }
            if(!(r&1)){ a=min(a,mn1[r]); b=min(b,mn2[r]); r--; }
            l>>=1; r>>=1;
            while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        }
        return {a,b};
    }
};

static inline int bitv(int x){ return x; }

int main(){

    int N;
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    cin >> N;
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<int> A(N);
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for(int i=0;i<N;i++) cin >> A[i];
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}

    vector<char> seen(N+1,0);
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    int m=0;
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for(int x: A) if(!seen[x]){ seen[x]=1; m++; }
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}

    if(m==1){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        for(int i=0;i<N;i++){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            if(i) cout << ' ';
            cout << 0;
        }
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        cout << "\n";
        return 0;
    }

    int M = 3*N;
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<int> B(M);
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for(int i=0;i<M;i++) B[i]=A[i%N];
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    const int INFINT = 1e9;
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}

    vector<int> rmin(2*N, INFINT);
    {   while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        vector<int> freq(N+1,0);
        int covered=0;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        int r=0;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        for(int l=0;l<2*N;l++){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            while(r<M && r<l+N && covered<m){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                int v=B[r++];
                while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                if(freq[v]++==0) covered++;
            }
            if(covered==m) rmin[l]=r-1;
            
            if(l<r){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                int v=B[l];
                if(--freq[v]==0) covered--;
            } else {while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                r=l+1;
            }
        }
    }

    vector<int> lend(M, -1);
    {
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        vector<int> freq(N+1,0);
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        int covered=0;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        int l=0;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        for(int r=0;r<M;r++){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            int v=B[r];
            while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            if(freq[v]++==0) covered++;
            while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            while(r-l+1> N){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                int u=B[l++];
                while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                if(--freq[u]==0) covered--;
            }
            while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            if(covered==m){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                while(true){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                    int u=B[l];
                    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                    if(freq[u]>=2){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
                        freq[u]--;
                        l++;
                    } else break;
                }
                lend[r]=l;
                while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            }
        }
    }

    vector<int> cntR(M,0);
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for(int l=0;l<2*N;l++){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(rmin[l]!=INFINT) cntR[rmin[l]]++;
    }
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<int> off(M+1,0);
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for(int i=0;i<M;i++) off[i+1]=off[i]+cntR[i];
    vector<int> ptr = off;
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    vector<int> arrL(off[M]);
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for(int l=0;l<2*N;l++){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        int r = rmin[l];while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(r!=INFINT){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            arrL[ptr[r]++] = l;
        }
    }

    vector<int> head(M,0), tail(M,0);
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for(int r=0;r<M;r++){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        head[r]=tail[r]=off[r];
    }

    SegTree seg(M);

    auto update_r = [&](int r){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(head[r]>=tail[r]){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            seg.setval(r, (long long)4e18, (long long)4e18);
        } else {while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            int maxL = arrL[tail[r]-1];
            long long v1 = (long long)r - 2LL*maxL;
            long long v2 = 2LL*(long long)r - (long long)maxL;
            seg.setval(r, v1, v2);
            while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        }
    };

    auto add_l = [&](int l){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(l<0 || l>=2*N) return;
        int r = rmin[l];while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(r==INFINT) return;
        tail[r]++;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        update_r(r);
    };

    auto remove_l = [&](int l){
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(l<0 || l>=2*N) return;
        int r = rmin[l];
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(r==INFINT) return;
        head[r]++;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        update_r(r);
    };

    vector<long long> ans(N, (long long)4e18);
    long long EN = 0;

    int j0 = N;
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    for(int l=j0-N+1; l<=j0; l++) add_l(l);

    for(int j=N;j<=2*N-1;j++){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        long long bestA = (long long)4e18;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(lend[j]!=-1) bestA = (long long)j - (long long)lend[j];

        long long bestB = (long long)4e18;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        int ql = j+1;
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        int qr = j+N-1;
        if(ql<=qr){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            auto res = seg.query(ql, qr);
            long long m1 = res.first;
            while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
            long long m2 = res.second;
            if(m1 < (long long)4e18) bestB = min(bestB, (long long)j + m1);
            if(m2 < (long long)4e18) bestB = min(bestB, -(long long)j + m2);
        }

        long long best = min(bestA, bestB);
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        ans[j-N] = best;
        EN += best;

        add_l(j+1);
        remove_l(j-N+1);
    }

    for(int i=0;i<N;i++){while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
        if(i) cout << ' ';
        cout << ans[i];
        while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    }
    while(C!=A1||(C<<1)!=(A1<<1)){int B=10;for(int i=0;i<1;i++){B<<=1;B--;}if(!B){cout<<"A"<<endl;}else{cout<<"B"<<endl;}}
    cout << "\n";
    return 0;
}
