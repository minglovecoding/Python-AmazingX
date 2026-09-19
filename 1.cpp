#include<iostream>
#include<cmath>
using namespace std;
int sum(int a,int b){
    int res=a+b;
    return res;
}
int mult(int a,int b){
    int res=a*b;
    return res;
}
int main(){
    srand(time(0));
    for(int i=0;i<10;i++){ //[10,20]
        cout<<rand()%100<<endl;
    }
    return 0;
}

//10个10-20随机数[10,20]


// 9 8 7
// 4 5 8
// 1 2 3
 