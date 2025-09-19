#include <iostream>
#include <string>

int main() {
    // 声明并初始化字符串
    std::string greeting = "Hello, World!";
    std::cout << "Greeting: " << greeting << std::endl;

    // 使用 size() 获取字符串长度
    std::cout << "Length of the greeting: " << greeting.size() << std::endl;

    // 使用 empty() 检查字符串是否为空
    std::cout << "Is the greeting empty? " << (greeting.empty() ? "Yes" : "No") << std::endl;

    // 使用 operator[] 访问特定位置的字符
    std::cout << "Character at position 7: " << greeting[7] << std::endl;

    // 使用 substr() 获取子字符串
    std::string sub = greeting.substr(7, 5);
    std::cout << "Substring from position 7 with length 5: " << sub << std::endl;

    // 使用 find() 查找子字符串
    std::cout << "Position of 'World' in the greeting: " << greeting.find("World") << std::endl;

    // 使用 replace() 替换字符串中的部分内容
    // 替换 'World' 为 'C++'
    std::string modified = greeting;
    std::string::size_type pos = modified.find("World");
    if (pos != std::string::npos) {
        modified.replace(pos, 5, "C++"); // 从位置 pos 开始，替换 5 个字符为 "C++"
    }
    std::cout << "Modified greeting: " << modified << std::endl;

    return 0;
}