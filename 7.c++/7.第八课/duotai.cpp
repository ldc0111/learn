/*************************************************************************
	> File Name: duotai.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 09时29分51秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <string>
using namespace std;

class Parent{
    public:
    virtual void say() {
        cout << "I'm Parent" << endl;
    }
};
class Child :public Parent{
    public:
    virtual void say() {
        cout << "I'm Child" << endl;
    }
};
void how_to_say(Parent *p) {
    p->say();
}
//首先　多态是根据实际对象　去判断调用重写函数
//父类指针，父类对象　调用父类对象函数
//　　　　　子类对象　调用子类对象函数
//
//ｃ＋＋　中支持多态的关键字　ｖａｉｔｕａｌ　多态继承
//　　　　　　　　　　　　　　　　　　　　　　虚函数
//
//虚函数——》纯虚函数——》抽象类——》接口
//多态意义：在程序中表现出动态的特性
//　　　　　在子类中重写父类中同名函数，必须声明正虚函数否则没有意义
//　　　　　多态是面向对象的基础
//静态联编：程序在编译期间就知道调用那个函数，函数重载
//动态联编：程序在运行时候才知道调用那些函数　函数重写


int main() {
    Parent p;
    Child c;
    how_to_say(&p);
    how_to_say(&c);
    return 0;
}
