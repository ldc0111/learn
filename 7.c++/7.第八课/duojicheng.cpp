/*************************************************************************
	> File Name: duojicheng.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 14时53分01秒
 ************************************************************************/

#include<iostream>
using namespace std;


class A{
    public:
    virtual void funca() {
        cout << "BaseA:: funca" << endl;
    }
};
class B{
    public:
    virtual void funcb() {
        cout << "BaseB:: funcB" << endl;
    }
};

class Derived:public A, public B{

};


int main() {
    cout << sizeof(Derived) << endl;
    Derived d;
    A *p1 = &d;
    B *p2 = &d;
    p1->funca();//ｂａｓｅａ
    p2->funcb();//ｂａｓｅｂ
    B *pb = (B *)p1;
    pb->funcb();//ｂａｓｅａ
    B *pd = dynamic_cast<B*>(p1);
    pd->funcb();//ｂａｓｅｂ

    return 0;
}
