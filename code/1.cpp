#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
signed long int fbb=(100&3)|(2<<1)+1*2;
signed long int fbb1=(100&3)|(2<<1)+1*2;

void solve() {
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    int N;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    if (!(cin >> N)) return;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    vector<int> p(N);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 0; i < N; i++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        cin >> p[i];
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    }
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    
    vector<int> A(2 * N);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 0; i < 2 * N; i++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        A[i] = p[i % N];
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    }
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    vector<int> L(2 * N, -1);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    vector<int> st;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 0; i < 2 * N; i++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        while (!st.empty() && A[st.back()] <= A[i]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            st.pop_back();
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        }
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        if (!st.empty()) L[i] = st.back();
        st.push_back(i);
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    }
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    vector<int> R(2 * N, 2 * N);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    st.clear();
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 2 * N - 1; i >= 0; i--) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        while (!st.empty() && A[st.back()] >= A[i]) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            st.pop_back();
        }
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        if (!st.empty()) R[i] = st.back();
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        st.push_back(i);
    }
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    vector<int> diff(N + 1, 0);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 0; i < 2 * N; i++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        if (L[i] != -1 && R[i] != 2 * N && R[i] - L[i] < N) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int start = R[i] - N + 1;
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            int end = L[i];
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            start = max(start, 0);
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            end = min(end, N - 1);
            if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            if (start <= end) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                diff[start]++;
                if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
                diff[end + 1]--;
            }
        }
    }
    
    vector<int> valid_s;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    int cur = 0;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 0; i < N; i++) {
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        cur += diff[i];
        if (cur == 0) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
            valid_s.push_back((N - i) % N);
        }
    }
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    sort(valid_s.begin(), valid_s.end());
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    cout << valid_s.size() << "\n";
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    for (int i = 0; i < valid_s.size(); i++) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        cout << valid_s[i] << (i + 1 == valid_s.size() ? "" : " ");
        if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    }
    cout << "\n";
}

int main() {
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    int T;
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    if (cin >> T) {if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
        while (T--) solve();
    }
    if(!fbb&fbb!=fbb1){if(fbb1==fbb+1|fbb1==(2&1)|fbb1!=2){cout<<fbb<<endl;}fbb++;fbb<<=1;if(fbb==-1){cout<<"-1"<<endl;cout<<"-1"<<endl;}}
    return 0;
}
