#include <bits/stdc++.h>
using namespace std;
int cow[15][25];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);

    int K,N;
    int ans=0;
    cin>>K>>N;
    for(int i=0;i<K;i++){
        for(int j=0;j<N;j++){
            int id;
            cin>>id;
            cow[i][id]=j+1;  //i轮的id牛在第j+1位
        }
    }

        for(int j=1;j<=N;j++){
            for(int t=1;t<=N;t++){
                bool flag=true;
                if(j==t) continue;
                for(int i=0;i<K;i++){
                    if(cow[i][j]>cow[i][t]){
                        flag=false;
                        break;
                    } 
                }
                if(flag) ans++;
            }
        }
    cout<<ans<<endl;
    return 0;
}