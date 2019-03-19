/*************************************************************************
	> File Name: struct.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年03月16日 星期六 22时23分41秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*
class A{
    public:
    int a;
};

struct B : A{

};

int main() {
    B b;
    b.a = 0;
    return 0;
}*/

struct X{
    X() = delete;
    X(const X&) = delete;
    X(int){}
};

struct Y{
    X x;
    Y() = delete;
    Y(const Y&) = delete;
};


int main() {

    return 0;
}
