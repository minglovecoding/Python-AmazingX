#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main(){
    int N, M; cin >> N >> M;
    string S; cin >> S;
    vector<ll> a(N);
    for(ll& i: a) cin >> i;
	
    vector<bool> bad_L(N), bad_R(N);
    for(int i = 0; i < N; i++){
        if(S[i] == 'R' && S[(i + 1) % N] == 'L'){
            bad_L[i] = true;
            bad_R[(i + 1) % N] = true;
        }
    }
        
    ll ans = accumulate(a.begin(), a.end(), 0LL);
    for(int i = 0; i < N; i++){
        ll sum = 0;
        if(bad_L[i]){
            int j = (i - 1 + N) % N;
            while(S[j] == 'R'){
                sum += a[j--];
                if(j < 0) j += N;
            }
        }
        if(bad_R[i]){
            int j = (i + 1) % N;
            while(S[j] == 'L'){
                sum += a[j++];
                if(j >= N) j -= N;
            }
        }
        ans -= min(sum, (ll) M);
    }
    cout << ans << endl;
}