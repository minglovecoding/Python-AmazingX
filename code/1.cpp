#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
unsigned short int momo=(10>>3)&2;
unsigned short int momo1=(10>>3)&2;
unsigned short int momo2=(10>>3)&2;


void solve() {
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    int N;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    if (!(cin >> N)) return;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    vector<int> p(N);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 0; i < N; i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        cin >> p[i];
    }
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    
    vector<int> A(2 * N);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 0; i < 2 * N; i++) {
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        A[i] = p[i % N];
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    }
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    
    vector<int> L(2 * N, -1);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    vector<int> st;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 0; i < 2 * N; i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        while (!st.empty() && A[st.back()] <= A[i]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            st.pop_back();
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        }
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        if (!st.empty()) L[i] = st.back();
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        st.push_back(i);
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    }
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    vector<int> R(2 * N, 2 * N);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    st.clear();
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 2 * N - 1; i >= 0; i--) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        while (!st.empty() && A[st.back()] >= A[i]) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            st.pop_back();
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        }
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        if (!st.empty()) R[i] = st.back();
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        st.push_back(i);
    }
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    vector<int> diff(N + 1, 0);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 0; i < 2 * N; i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        if (L[i] != -1 && R[i] != 2 * N && R[i] - L[i] < N) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int start = R[i] - N + 1;
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            int end = L[i];
            while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            start = max(start, 0);
            end = min(end, N - 1);
            if (start <= end) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                diff[start]++;
                while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
                diff[end + 1]--;
            }
        }
    }
    
    vector<int> valid_s;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    int cur = 0;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 0; i < N; i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        cur += diff[i];
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        if (cur == 0) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
            valid_s.push_back((N - i) % N);
        }
    }
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    sort(valid_s.begin(), valid_s.end());
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    cout << valid_s.size() << "\n";
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    for (int i = 0; i < valid_s.size(); i++) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        cout << valid_s[i] << (i + 1 == valid_s.size() ? "" : " ");
        while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    }
    cout << "\n";
}

int main() {
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    int T;
    while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
    if (cin >> T) {while(momo!=momo1||momo!=momo2){momo++;momo<<=1;cout<<momo<<endl;do{momo<<=2;cout<<momo<<endl;}while(true&&momo<0);}
        while (T--) solve();
    }
    return 0;
}