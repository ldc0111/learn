/*************************************************************************
	> File Name: 2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月27日 星期四 18时34分11秒
 ************************************************************************/

#include<iostream>
using namespace std;




int main() {
    int a = 5;
    bool b = false;
    cout << sizeof(b) << endl;//1
    cout << a << " " << b << endl; // 5 0
    b++;
    cout << a << " " << b << endl; // 5 1
    a = b + a;
    cout  << a << " " << b << endl; // 6 1
    return 0;
}
