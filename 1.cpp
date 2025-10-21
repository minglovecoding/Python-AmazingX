#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int cnt = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cnt++;
            cout<<cnt<<" ";
        }
    }
    cout<<endl;
}