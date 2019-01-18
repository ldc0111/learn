/*************************************************************************
	> File Name: add.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 09时06分29秒
 ************************************************************************/

#include<iostream>
using namespace std;

void add(int a, int b) {
    cout << "add(int):" <<a + b << endl;
}
template<typename T>
void add(T a, T b) {
    cout << "template:" << a + b << endl;
}
/*
void add(double a, double b) {
    cout << "add(double)" <<a + b << endl;
}*/
void add(int a){
    cout << "add(int a)" << endl;
}

void add(...){
    cout << "add(...)" << endl;
}


//函数调用优先级，普通函数，模板函数，变参函数
int main() {
    add(4,6);
    add<int>(4,6);
    add(3.4, 23.5);
    add(3);
    return 0;
}
