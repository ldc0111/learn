/*************************************************************************
	> File Name: 5.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月27日 星期四 19时38分08秒
 ************************************************************************/

#include<iostream>
using namespace std;
//函数的站位参数，只有类型没有形参
void f(int, int) {
    cout << "hello" << endl;
}


void g(int = 0, int  = 1, int = 2) {
    cout << "hello1" << endl;
}
int main() {
    f(1, 2);
    g();
    return 0;
}
