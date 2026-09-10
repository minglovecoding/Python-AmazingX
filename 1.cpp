//1.把x、y坐标离散化为1到N
//2.先对y轴枚举区间（1-1、1-2...1-N;2-2、2-3、2-N;...N-N）
//3.记录每个区间最上方和最下方的元素的x轴x1、x2（且x1<x2），并计算x1本身及左边元素的个数num1，和x2本身及右边元素num2，num1乘以num2即为该区间所有子集个数。
//4.用前缀和方式优化找num1和num2的时间
//5.累加不同区间的子集个数，最后再加空集即为所有子集个数。
#include<bits/stdc++.h>
using namespace std;
const int Nmax=2505;
int cow[Nmax][Nmax];
vector<pair<int,int>>cowMap;
int areaCow(int x1,int y1,int x2,int y2){
    return cow[x2+1][y2+1]-cow[x2+1][y1]-cow[x1][y2+1]+cow[x1][y1];
}
int main(){
    int N;
    int x,y;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>x>>y;
        cowMap.push_back(make_pair(x,y));
    }
    //1.把x、y坐标离散化为1到N
    sort(cowMap.begin(),cowMap.end());
    for(int i=0;i<N;i++){
        cowMap[i].first=i+1;
    }
    sort(cowMap.begin(),cowMap.end(),[](const pair<int,int>&a,const pair<int,int>&b){return a.second<b.second;});
    for(int i=0;i<N;i++){
        cowMap[i].second=i+1;
    }
    //4.用前缀和方式优化找num1和num2的时间
    for(auto mapp:cowMap){
        cow[mapp.first][mapp.second]=1;
    }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cow[i][j]+=cow[i-1][j]+cow[i][j-1]-cow[i-1][j-1];
        }
    }
    //3.记录每个区间最上方和最下方的元素的x轴x1、x2（且x1<x2）
    //并计算x1本身及左边元素的个数num1，和x2本身及右边元素num2，num1乘以num2即为该区间所有子集个数。
    long long ans=0;
    for(int i=0;i<N;i++){
        for(int j=i;j<N;j++){
            int x1=min(cowMap[i].first,cowMap[j].first)-1;
            int x2=max(cowMap[i].first,cowMap[j].first)-1;
            int num1=areaCow(0,i,x1,j);
            int num2=areaCow(x2,i,N-1,j);
            ans+=1LL*num1*num2;
        }
    }
    //5.累加不同区间的子集个数，最后再加空集即为所有子集个数。
    cout<<ans+1<<endl;
    return 0;
}

