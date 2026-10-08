//wrong：
//1.草地只能属于Nhoj或John，列每块草的可选区间，为该位置到Nhoj左右牛最短距离的（x-d，x+d）。
//2.将草地美味值从大到小进行排序
//3.定义滑动窗口为所有区间的最左端和最右端，尝试放John牛，选择累加美味值最大的区间位置放置。
//4.考虑位置不一定是整数的情况，比如某区间在（4，5），4.5也是一种选择，所以遍历时以0.5为步递增。
//5.每次放置时消掉对应包含区间，放置n次后，输出总美味值。
//case：Nhoj_pos:0、10，草地位置（美味值）：1（6） 4（10） 6（10） 9（6）。

//right：
//1.用 Nhoj 的牛把数轴分 M+1段，各段独立处理。
//2.对每个内部区间，求一头牛的最大收益 best，以及全部草地收益 sum；两头牛一定可以获得整段草地。
//3.将该段贡献写成两个增量：best、sum-best。
//4.最左、最右的区间只需一头牛就能全部获得。
//5.将所有增量从大到小排序，累加前 N 个。

#include <bits/stdc++.h>
using namespace std;
const int grassMax=10^9+5;
const int Kmax=2*10^5+5;
const int Mmax=2*10^5+5;
const int Nmax=2*10^5+5;
int taste[grassMax];
int main(){
    int k,m,n;
    cin>>k>>m>>n;
    for(int i=0;i<k;i++){
        int pos,value;
        cin>>pos>>value;
        taste[pos]=value;
    }
    vector<int>Nhoj;
    for(int i=0;i<m;i++){
        int cowN;
        cin>>cowN;
        Nhoj.push_back(cowN);
    }
    //


    
    return 0;
}