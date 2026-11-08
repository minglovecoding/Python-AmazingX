#include <bits/stdc++.h>
using namespace std; 
 
void solve(){
    int n, k;
    cin >> n >> k;
 
    vector<int> A(n);
    for (int &i : A)
        cin >> i;
    
    auto check1 = [&](int l, int r){
        for (int i = l + 1; i <= r; i++)
            if (A[i] != A[i - 1])
                return false;
        return true;
    };
    auto check2 = [&](int l, int r){
        vector<pair<int, int>> blk;
 
        for (int i = l; i <= r; i++){
            if (blk.size() and A[i] == A[i - 1])
                blk.back().second++;
            else
                blk.push_back({A[i], 1});
        }
        if (blk.size() <= 2 or blk.size() % 2 == 0){
            for (int i = 0; i + 2 < blk.size(); i++)
                if (blk[i] != blk[i + 2])
                    return false;
            return true;
        }
        return false;
    };
    auto check3 = [&](int l, int r){
        for (int blkLen = 1; blkLen <= r - l + 1; blkLen++){
            if ((r - l + 1) % blkLen)
                continue;
 
            bool ok = true;
 
            for (int i = l; i + blkLen <= r; i++)
                ok &= (A[i] == A[i + blkLen]);
            
            if (!ok)
                continue;
            
            // Check the prefix
            for (int i = l; i < l + blkLen; i++)
                if ((check1(l, i) and check2(i + 1, l + blkLen - 1)) or (check2(l, i) and check1(i + 1, l + blkLen - 1)))
                    return true;
        }
        return false;
    };
 
    if (k == 1)
        cout<<(check1(0, n - 1) ? "YES" : "NO")<<"\n";
    else if (k == 2)
        cout<<(check2(0, n - 1) ? "YES" : "NO")<<"\n";
    else
        cout<<(check3(0, n - 1) ? "YES" : "NO")<<"\n";
}
 
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); 
    int tc; 
    cin >> tc;
 
    while (tc--) 
        solve();
}