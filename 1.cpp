#include <iostream>
#include <cmath>
#include <numbers>
using namespace std;
int main() {
	//int a=10;
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int b[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	for(int i=0;i<10;i++){
		cout<<a[i]<<" ";
	}
    cout<<endl;

    for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
    return 0;
}