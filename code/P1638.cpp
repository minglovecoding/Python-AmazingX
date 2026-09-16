//双指针+滑动区间
//1.右指针不断向右移动，将画作加入窗口。
//2.当窗口包含全部m位画家后，左指针不断向右移动，并更新最短区间，
//3.当删除某幅画后，不再包含全部画家，停止移动左指针。
//4.继续向右移动右指针，直到right到达N。
#include<bits/stdc++.h>
using namespace std;
const int Nmax=10^6+5;
int paintings[Nmax];
int cnt[2005];
int num=0;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>paintings[i];
    }
    int bestLeft=1;
    int bestRight=n;
    int maxLen=Nmax;
    
    int left=1;
    for(int right=1;right<=n;right++){
        if(cnt[paintings[right]]==0) num++;
        cnt[paintings[right]]++;
        while(num==m){
            int len=right-left+1;
            if(len<maxLen){
                maxLen=len;
                bestLeft=left;
                bestRight=right;
            }
            //left向左移
            cnt[paintings[left]]--;
            if(cnt[paintings[left]]==0) num--;
            left++;
        }
    }
    cout<<bestLeft<<" "<<bestRight<<"\n";
    return 0;
}
/* 滑动窗口模版
for (右指针) {
    加入右端元素;

    while (窗口满足条件) {
        更新答案;
        删除左端元素;
        左指针++;
    }
}
*/