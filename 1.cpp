#include<bits/stdc++.h>
using namespace std;
int main()
{
	//1 2 3 4
	vector<int>nums={1,2,3,4};
	//print every element
	for(int i=0;i<4;i++){
		cout<<nums[i]<<" ";
	}
	cout<<endl;
	//for-each语句
	for(int elem:nums){
		cout<<elem<<" ";
	}
	cout<<endl;
	return 0;
}