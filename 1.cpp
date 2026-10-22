#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,K;
    cin>>N>>K;

    vector<int>pos(N+1);
    vector<vector<int>>visited(N+1);
    for(int i=1;i<=N;i++){
        pos[i]=i;
        visited[i].push_back(i);
    }
    //计算一轮交换后的结果
    for(int i=0;i<K;i++){
        int a,b;
        cin>>a>>b;
        int cowA=pos[a];
        int cowB=pos[b];
        visited[cowA].push_back(b);
        visited[cowB].push_back(a);
        swap(pos[a],pos[b]);
    }
    //nextCow数组表示牛一轮后所在的位置
    vector<int>nextCow(N+1);
    for(int i=1;i<=N;i++){
        int cow=pos[i];
        nextCow[cow]=i;
    }

    int cycleId=0;  //置换环编号
    vector<bool>usedCow(N+1,false);  //牛有没有被分类
    vector<int>posMark(N+1,0);  //记录pos_i在哪个置换环
    vector<int>ans(N+1);  //输出每头牛经过的位置数

    for(int start=1;start<=N;start++){
        if(usedCow[start]) continue;
        cycleId++;
        vector<int>cycle;
        int current=start;
        while(!usedCow[current]){
            usedCow[current]=true;
            cycle.push_back(current);
            current=nextCow[current];
        }
        int cnt=0;
        for(int cow:cycle){//统计并集
            for(int i:visited[cow]){
                if(posMark[i]!=cycleId){
                    posMark[i]=cycleId;
                    cnt++;
                }
            }
        }
        for(int cow:cycle){
            ans[cow]=cnt;
        }
    }
    for(int cow=1;cow<=N;cow++){
        cout<<ans[cow]<<'\n';
    }
	return 0;
}