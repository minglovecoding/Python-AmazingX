#include<bits/stdc++.h>
using namespace std;
vector<vector<int>>res;
void dfs(vector<int>& nums,int index){
    if(index==nums.size()){
        res.push_back(nums);
        return;
    }
    //逐个选第index的数
    for(int i=index;i<nums.size();i++){
        swap(nums[i],nums[index]);
        dfs(nums,index+1);
        swap(nums[i],nums[index]);
    }
}
using namespace std;
int main(){
    vector<int>nums={1,2,3,4,5};
    dfs(nums,0);
    for(auto v:res){
        for(int x:v){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    return 0;
}