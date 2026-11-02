#include <iostream>

int main()
{
    int a = 3;
    int b = 5;
    
    // 按值来捕获
    auto func1 = [a]() { std::cout << a << std::endl; };
    func1();

    // 按值来捕获
    auto func2 = [=]() { std::cout << a << " " << b << std::endl; };
    func2();

    // 按引用来捕获
    auto func3 = [&a]() { std::cout << a << std::endl; };
    func3();

    // 按引用来捕获
    auto func4 = [&]() { std::cout << a << " " << b << std::endl; };
    func4();
}