/*************************************************************************
	> File Name: jicheng.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 10时23分23秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

class A {
    protected:
        int i,j;
    public:
    A(){}
    A(int v1,int v2) {
        i = v1;
        j = v2;
    }
    //增加了一个８字节的虚函数表指针
    //虚函数表里存储了一个ｐｒｉｎ的地址
        virtual void print() {
            cout << "A hollo" << endl;
        }
};

class B : public A{
    private:
    int k;//因为有一个指针所以按照８字节对齐原则对齐所以是２４
    public:
        B(int v1,int v2, int v3) : A(v1, v2) {
            k = v3;
        }
        void show() {
            cout << "i = " << i << endl;
            cout << "j = " << j << endl;
            cout << "k = " << k << endl;
        }
};
//c++多态实现原理
//ｖｉｒｔｕａｌ　对象大小改变
//里面加入了一个虚函数指针

typedef struct C{
    void *ptr;
    int a,b,c;

}C;
//如果不加指针的化是１０００　２，３
//加了指针就变成了
//在类声明的时候编译器会自动生成一个虚函数表
//虚函数存的是一个成员函数的地址的数据结构
//虚函数表是由编译器自动生成和维护的　对外隐藏
//被virtual修饰的虚函数会悲哀放入虚函数表中
//存在虚函数时每个对象会有一个指针指向虚函数表，并且这个指针在虚函数头部
//当运行到那的时候ｐ会找到虚函数表，找到那个函数
//如果不是会直接取寻找成员函数
//

int main() {
    //cout << sizeof(A) << endl;//１６
    //cout << sizeof(B) << endl;//２4
    B b(1,2,3);
    C *p = reinterpret_cast<C*>(&b);
    b.show();
    p->a = 10;
    p->b = 100;
    p->c = 1000;
    b.show();
    return 0;
}
