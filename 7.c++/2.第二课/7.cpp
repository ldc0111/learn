/*************************************************************************
	> File Name: 7.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月27日 星期四 20时36分40秒
 ************************************************************************/

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;


namespace my_lib {
    int add(int x, int y = 3) {
        return x + y;
    }
    int add() {
        return 100;
    }
    string add(string &s1, string &s2) {
        return s1 + s2;
    }
}
using namespace my_lib;
int (*p1)(int ,int);
int (*p2)();

int main() {
    string s1 = "ldc", s2 = "haizie";
    p1 = add;
    p2 = add;
    int c = (*p1)(1,2);
    int d = (*p2)();

    return 0;
}



