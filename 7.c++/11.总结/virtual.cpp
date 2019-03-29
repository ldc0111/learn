/*************************************************************************
	> File Name: virtual.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年03月28日 星期四 19时26分27秒
 ************************************************************************/

#include <iostream>
using namespace std;

class A{
    public:
    A() { x = 1; }

    protected:
    int x;
};

class B: virtual public A{
    public:
    void adj1() {
        x = 2;
    }
    void cout1() {
        cout << x << endl;
    }
};


class C:virtual public  A{
    public:
    void adj2() {
        x = 3;
    }
    void cout2() {
        cout << x << endl;
    }
};

class D: public B,public C{
};
int main() {
    D d;
    d.adj1();
    d.adj2();
    d.cout1();
    d.cout2();

    return 0;
}
