/*************************************************************************
	> File Name: 5.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月10日 星期四 20时01分25秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
using namespace std;


class Test{
    private:
        int i;
        int j;
    public:
    Test(int v1 = 0, int v2 = 0) {
        i = v1;
        j = v2;
    }
    int getI(){
        return i;
    }
    int getJ() {
        return j;
    }
    int add(int value) {
        return i + j + value;
    }
    ~Test(){
        return ;
    }
};

class A{
    int a;
    int b;
    char c;
    double d;
    public:
    void print() {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
        cout << "d = " << d << endl;
    }
};
struct B{
    int a;
    int b;
    char c;
    double d;
};
/*
int main() {
    Test t(1,3);
    cout << t.getI() << " "<< t.getJ() << endl;//1  3
    cout << t.add(10) << endl;//14

    return 0;
}*/
/*一个对象是一个特殊的结构体
 * 运行时他被退化成结构体了
 * 成员属性中间可能有空隙
 * 可以通过内存地址直接取访问它
 * 访问权限只对编译器有效
 * 访问权限只在编译期有效，运行期无效
*/
int main() {
    A a1;
    B b1;
    //a1.a = 100;
    a1.print();
    cout << sizeof(a1) << " " << sizeof(b1) << endl;
    //对象在运行的时候被退化成了struct，可以用指针进行修改
    B *p = reinterpret_cast<B*>(&a1);
    p->a = 100;
    p->b = 1000;
    p->c = 'C';
    p->d = 3.2;
    a1.print();
    return 0;
}
