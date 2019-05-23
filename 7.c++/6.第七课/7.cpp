/*************************************************************************
	> File Name: 7.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 20时49分29秒
 ************************************************************************/

#include<iostream>
#include <string>
using namespace std;
class A{
    private:
    int age;
    public:
    void print() {
        cout << age << endl;
    }
};
class B : public A {};
class C : public A {};
class D : public C, public B {};
//对齐
struct f{
    int a;
    char b;
    double c;
};
int main() {
    D d;
    //d.B::print();
    //d.C::print();
    //cout << sizeof(D) << endl;
    //A *pa = &d;//爷孙没有继承
    C *pc = &d;
    B *pb = &d;
    D *pd = &d;
    void *pbb = pb;
    void *pcc = pc;
    if (pbb == pcc) {
        cout << "point the same" << endl;
    } else {
        cout<< "NO" << endl;
    }
    //cout << "pa : " << pa << endl;
    cout << pd << endl;
    cout << &d << endl;
    cout << pb << endl << pc << endl;
    cout << sizeof(f) << endl;
    return 0;
}

