/*************************************************************************
	> File Name: 3.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 18时27分49秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Parent{
    protected:
        int i;
    public:
    Parent(int v = 0) {
        i = v;
    }
};
class Child : public Parent{
    public:
    Child() :Parent(5){
        cout << "Child()" << endl;
    }
    int getI() {
        return i;
    }
};
class A {
    public:
    A() {
        cout << "A()" << endl;
    }
};
class B : public A {
    public:
    B() {
        cout << "B()" << endl;
    }

};
class C {
    public:
    C() {
        cout << "C()" << endl;
    }
    
};
class D : public C {
    private:
        B b;
    public:
    D() {
        cout << "D()" << endl;
    }

};
//1继承构造顺序
//1先去自动调用
//2再调用子类构造函数
//继承，先双亲再朋友，最后自己 可以递归执行
//析构：与构造顺序相反
/*
int main() {
    Child ch;
    cout << ch.getI() << endl;
    return 0;
}*/

//子类对象构造时需要先初始化父类个属性
//需要调用父类的构造函数
//2，构造函数的执行顺序 先父，后兄弟，在各个
//3，父类构造函数显示调用的时候，必须在子类构造函数的初始化列表里
//4，子类对象销毁时，同样需要调用父类析构函数
//5，先构造的后析构
int main() {
    D d;
    return 0;
}
