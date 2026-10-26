#include<bits/stdc++.h>
using namespace std;
int case1[4]={0,1,0,0};
int case2[4]={0,0,1,0};
int case3[4]={0,0,0,1};
//int score1,score2,score3;
int main(){
    freopen("shell.in", "r", stdin);
    freopen("shell.out", "w", stdout);
    int a, b, g, N, score1=0, score2=0, score3=0;
    cin>>N;
    for(int i=1; i<=N; i++){
        cin>>a>>b>>g;
        swap(case1[a],case1[b]);
        if(case1[g]==1){
            score1++;   
        }
        swap(case2[a],case2[b]);
        if(case2[g]==1){
            score2++;   
        }
        swap(case3[a],case3[b]);
        if(case3[g]==1){
            score3++;   
        }
    }
    cout<<max(score1,max(score2,score3))<<endl;
    return 0;
}