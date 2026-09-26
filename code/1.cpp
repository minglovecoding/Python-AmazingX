#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int age;
    double score;
};

int main() {
    Student s;

    s.name = "Tom";
    s.age = 18;
    s.score = 92.5;

    cout << s.name << endl;
    cout << s.age << endl;
    cout << s.score << endl;

    return 0;
}

//结构体
//Person
//name、sex、age、height、weight、nationality、degree。
//struct 3 persons。