/*************************************************************************
	> File Name: test4.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月16日 星期三 15时18分41秒
 ************************************************************************/

#include<iostream>
using namespace std;

class base{
    protected:
        int a;
    public:
    base(int v1) {
        a = v1;
    }
    int get() {
        return a;
    }
    bool equal(base *p) {
        return (this == p);
    }
};

class interfacel{
    public:
    virtual void add(int i) = 0;
    virtual void sub(int i) = 0;
};

class interface2{
    public:
    virtual void mul(int i) = 0;
    virtual void div(int i) = 0;
};


class Derived : public base, public interfacel, public interface2{
    public:
    Derived(int i) : base(i){

    }
    void add(int i) {
        a += i;
    }
    void sub(int i) {
        a -= i;
    }
    void mul(int i) {
        a *= i;
    }
    void div(int i) {
        if (i != 0){
            a /= i;
        }
    }
};


int main() {
    Derived d(10);
    Derived *p = &d;
    interfacel *p1 = &d;
    interface2 *p2 = &d;
    if (p->equal(dynamic_cast<base *>(p1)) && p->equal(dynamic_cast<base *>(p2))) {
        p->add(10);
        p->sub(5);
        p->mul(10);
        p->div(10);
    }
    cout << p->get() << endl;
    return 0;
}
