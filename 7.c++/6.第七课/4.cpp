/*************************************************************************
	> File Name: 4.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 19时02分29秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class A{
    public:
    int i;
    A(int v = 0) {
        i = v;
    }
    int add() {
        return i + 1;
    }
    int add(int a, int b, int c){
        return i + a + b + c;
    }
    int getI() {
        cout << "A::i = " << i << endl;
        return i;
    }
    void say() {
        cout << "hello i'm a" << endl;
    }
};
class B : public A{
    public:
    int i;
    B(int v) : A(0) {
        i = v;
    }
    int add(int a) {
        return i + a;
    }/*
    int add(int a, int b) {
        return a + b + i;
    }
    int getI() {
        cout << "B::i = " << i << endl;
        return i;
    }*/
    void say(){
        cout << "hello i'm b" << endl;

    }
};
//编译中编译器值根据指针的类型去判断，编译中判断成父类的函数是最安全的
void how_to_say(A *p) {
    p->say();
    return;
}

//父子同名冲突
//子类与父类定义相同名字属性和方法
//g++ 优先使用子类的属性和方法，将父类属性隐藏，如果想使用
//1.父子同名冲突，可以通过作用域分辨符号
//2父子间可以定义相同名字的属性和方法
//3子类和父类中同名方法不构成重载关系和方法
//4,子类中定义父类中的同名函数
//5，使用作用域分辨符，访问同名成员和方法
int main() {
    A a;
    B b(3);
    //cout << b.i << endl;
    cout << b.A::add() << endl;
    cout << b.A::add(1,2,3) << endl;
    cout << b.getI() << endl;
    /*
    b.A::i = 10;
    cout << b.A::i << endl;//通过作用域分辨符使用父类还是子类
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    */
    how_to_say(&a);
    how_to_say(&b);
    return 0;
}
//1子类对象是特殊的父类
//子类对象必须初始化父类对象
//父类对象指针可以指向子类对象
//父类对象引用子类对象



