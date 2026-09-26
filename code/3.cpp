#include<bits/stdc++.h>
using namespace std;
const int Nmax=505;
int grid[Nmax][Nmax];
bool valid[Nmax];  //whether >=100
bool hundred[Nmax];  //is there has 100
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>grid[i][j];
        }
    }
    long long sum=0;
    for(int l=0;l<N;l++){
        fill(valid,valid+N,true);
        fill(hundred,hundred+N,false);
        for(int r=l;r<N;r++){
            for(int row=0;row<N;row++){
                 valid[row]&=(grid[row][r]>=100);
                 hundred[row]|=(grid[row][r]==100);
            }
            int start=0;
            int end_100=-1;
            for(int row=0;row<N;row++){
                if(!valid[row]){
                    start=row+1;
                    end_100=-1;
                    continue;
                }
                if(hundred[row]){
                    end_100=row;
                }
                if(end_100!=-1){
                    sum+=end_100-start+1;
                }
            }
        }
    }
    cout<<sum<<endl;
    return 0;
}