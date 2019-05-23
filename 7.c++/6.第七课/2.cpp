/*************************************************************************
	> File Name: 2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 18时19分03秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Parent{
    public:
    Parent() {
        cout << "Parent()" << endl;
    }
};
class Child : public Parent{
    public:
    Child() {
        cout << "Child()" << endl;
    }
};
//1 默认的调用方式
//要求父类的构造函数必须是无参，或者是带默认参数的
int main() {
    Child ch;
}

