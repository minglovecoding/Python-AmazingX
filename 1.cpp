#include <iostream>
using namespace std;

vector<vector<int>> res;

void dfs(vector<int>& nums, int idx) {
    // 递归到最后一个位置，记录答案
    if (idx == nums.size()) {
        res.push_back(nums);
        return;
    }
    
    // 枚举 idx 位置放谁
    for (int i = idx; i < nums.size(); i++) {
        swap(nums[i], nums[idx]);       // 选择：把 num[i] 放到 idx
        dfs(nums, idx + 1);             // 递归处理下一位
        swap(nums[i], nums[idx]);       // 回溯：换回来
    }
}

int main() {
    vector<int> nums ={1,2,3};
    dfs(nums, 0);

    for (auto &v : res) {
        for (int x : v) cout << x << " ";
        cout << endl;
    }
}
