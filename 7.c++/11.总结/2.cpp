/*************************************************************************
	> File Name: 2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年03月05日 星期二 18时43分55秒
 ************************************************************************/

#include<iostream>
using namespace std;
void f() {
    cout  << "hello world" << endl;
    return ;
}
void f(int i) {
    cout << "i = " << i << endl;
    return ;
}
void f(int i, int j) {
    cout << "i = " << i << endl;
    cout << "j = " << j << endl;
    return ;
}
void (*ptr1)();
void (*ptr2)(int);
void (*ptr3)(int, int);
int main() {
    ptr1 = f;
    ptr2 = f;
    ptr3 = f;
    cout << (void *)ptr1 << endl;
    cout << (void *)ptr2 << endl;
    cout << (void *)ptr3 << endl;
    return 0;
}
