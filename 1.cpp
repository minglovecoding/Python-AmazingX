#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("shell.in", "r", stdin);
    freopen("shell.out", "w", stdout);
	bool s1[4]={false,true,false,false},s2[4]={false,false,true,false},s3[4]={false,false,false,true};
	int cnt=0,num=0,total=0,a,b,g,n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a>>b>>g;
		swap(s1[a],s1[b]);
		swap(s2[a],s2[b]);
		swap(s3[a],s3[b]);
		if(s1[g]){
			cnt++;
		}if(s2[g]){
			num++;
		}if(s3[g]){
			total++;
		}
	}
	cout<<max(max(cnt,num),total);
	return 0;
}