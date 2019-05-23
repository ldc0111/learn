/*************************************************************************
	> File Name: 3.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年03月05日 星期二 18时53分40秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;
/*
class type {
    public:
    type(int x = 0) :x(x){}
    private:
    int x;
    protected:
};

int main() {
    type *x = new type(0);
    delete x;
    return 0;
}*/

/*
class Test{
    public:
    const int a;
    Test() : a(0) {}
    int getA() {
        return a;
    }
};

int main() {
    Test t;
    cout << t.getA() << endl;
    int *p = const_cast<int *>(&t.a);
    *p = 10;
    cout << t.getA() << endl;
    return 0;
}*/

/*
class Test{
    private:
    int mi;
    public:
    const int a;
    Test () : a(0){
        mi = 0;
    }
    int getA() const {
        return a;
    }
    int getMi() const {
        cout << "const :" << endl;
        return mi;
    }
    int getMi() {
        cout << "no-const:" << endl;
        mi = 100;
        return mi;
    }
};
*/
/*
int main() {
    Test t;
    const Test t1;
    cout << t.getMi() << endl;
    cout << t1.getMi() << endl;
    return 0;
}*/
/*

int main() {
    Test tp;
    const Test tq;
    const Test &t1 = tp;
    const Test &t2 = tq;
    Test &t3 = tp;
    Test &t4 = tq;
    return 0;
}*/

/*
class Test{
    private:
    int i,j,k,*p;
    public:
    Test(int v1 = 0,int v2 = 0, int v3 = 0) {
        i = v1;
        j = v2;
        p = new int;
        *p = v3;
    }
    Test(const Test &obj) {
        i = obj.i;
        j = obj.j;
        p = new int;
        *p = *obj.p;
    }
    int* getP() {
        return p;
    }
    int getI() {
        return i;
    }
    int  getJ() {
        return j;
    }
    void free() {
        delete p;
    }
    Test &operator=(const Test &obj) {
        cout << "123" << endl;
        if (&obj == this) return *this;
        i = obj.i;
        j = obj.j;
        p = new int;
        *p = *obj.p;
        return *this;
    }
};

int main() {
    Test t1;
    Test t2;
    cout << t1.getI() << " " << t1.getJ() << endl;
    cout << t2.getI() << " " << t2.getJ() << endl;
    cout << t1.getP() << " " << t2.getP() << endl;
    return 0;
}*/
/*
class Test{
    public:
    Test(){
        cout << "Test hello" << endl;
    }
    ~Test(){
        cout << "Test baibai" << endl;
    }
};

void f(){
    Test c;
}

int main() {
    f();
    return 0;
}
*/
class Test{
    public:
    Test *get() {
        return this;
    }
    
};
class test{
    public:
    test(int i = 0) : i(0){}
    void fun(){
        return ;
    }
    protected:
    int i;
    friend void get(test &t);
};

void get(test &t) {
    cout << t.i << endl;
    return ;
}
int main() {
    Test t1, t2;
    cout << t1.get() << endl;
    cout << t2.get() << endl;
    cout << sizeof(test) << endl;
    test t;
    get(t);
    void (test::*p)();
    p = &test::fun;
    return 0;
}



