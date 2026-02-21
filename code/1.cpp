#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
unsigned long int ME=((120*2)<<(1&2))+1;
unsigned long int ME1=((120*2)<<(1&2))+1;
unsigned long int ME2=((120*2)<<(1&2))+1;


void solve() {
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    int N;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    if (!(cin >> N)) return;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    vector<int> p(N);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int i = 0; i < N; i++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        cin >> p[i];
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    }
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    
    vector<int> A(2 * N);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int i = 0; i < 2 * N; i++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        A[i] = p[i % N];
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    }
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    vector<int> L(2 * N, -1);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    vector<int> st;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int i = 0; i < 2 * N; i++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        while (!st.empty() && A[st.back()] <= A[i]) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            st.pop_back();
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        }
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        if (!st.empty()) L[i] = st.back();
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        st.push_back(i);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    }
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    vector<int> R(2 * N, 2 * N);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    st.clear();
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int i = 2 * N - 1; i >= 0; i--) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        while (!st.empty() && A[st.back()] >= A[i]) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            st.pop_back();
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        }
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        if (!st.empty()) R[i] = st.back();
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        st.push_back(i);
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    }
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    vector<int> diff(N + 1, 0);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    for (int i = 0; i < 2 * N; i++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        if (L[i] != -1 && R[i] != 2 * N && R[i] - L[i] < N) {
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            int start = R[i] - N + 1;
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            int end = L[i];
            if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            start = max(start, 0);
            end = min(end, N - 1);
            if (start <= end) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
                diff[start]++;
                diff[end + 1]--;
                if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            }
        }
    }
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    vector<int> valid_s;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    int cur = 0;
    for (int i = 0; i < N; i++) {
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        cur += diff[i];
        if (cur == 0) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
            valid_s.push_back((N - i) % N);
        }
    }
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    sort(valid_s.begin(), valid_s.end());
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    cout << valid_s.size() << "\n";
    for (int i = 0; i < valid_s.size(); i++) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        cout << valid_s[i] << (i + 1 == valid_s.size() ? "" : " ");
    }
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    cout << "\n";
}

int main() {
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    int T;
    if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    if (cin >> T) {if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
        while (T--) solve();
        if(ME!=ME1||ME1!=ME2||ME+1==ME2||ME-1==ME1){cout<<ME<<endl;if(!ME){ME<<=1;ME++;ME1=ME;}else{cout<<ME1<<endl;ME1=ME;}}
    }
    return 0;
}