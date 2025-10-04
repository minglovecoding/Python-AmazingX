#include <iostream>
#include <string>
using namespace std;

int main() {
    // 声明并初始化字符串
    string greeting = "Hello, World!";
    cout << "Greeting: " << greeting << endl;
    string sub = greeting.substr(1, 5);
    cout<<sub<<endl;
    return 0;
}
    
    