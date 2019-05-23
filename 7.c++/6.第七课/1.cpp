/*************************************************************************
	> File Name: 1.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 18时06分10秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Parent{
    private :
        int a;
    public:
        int b;
        void set(int v1, int v2, int v3) {
            a = v1;
            b = v2;
            c = v3;
        }
    protected:
        int c;
};
class Child1 : public Parent{
    public:
        void print() {
            cout << "a = " << a << endl;
            cout << "b = " << b << endl;
            cout << "c = " << c << endl;
        }
};
class Child2 : private Parent{
    public:
        void print() {
            cout << "a = " << a << endl;
            cout << "b = " << b << endl;
            cout << "c = " << c << endl;
        }
    
};
class Child3 : protected Parent{
    public:
        void print() {
            cout << "a = " << a << endl;
            cout << "b = " << b << endl;
            cout << "c = " << c << endl;
        }
    
};


int main() {
    Child2 c;
    c.b = 100;
    return 0;
}

