/*************************************************************************
	> File Name: 1.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月06日 星期日 20时49分37秒
 ************************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Test{
    private:
    //static int cnt;
    int m;
    public:
    static int cnt;
    static int getCnt() {
        return cnt;
    }
    static int getCnt(Test &t, int v) {
        t.m = v;
        return v;
    }
    Test() {
        cnt++;
    }

    int getM() {
        return this->m;
    }
    Test* getP() {
        return this;
    }
    ~Test() {
        cnt -= 1;
    }
};
int Test::cnt = 0;
//静态成员变量是属于类的，必须在类里进行初始化
//生命周期跟类一样，是整个周期，
//第三可以通过类名直接访问
//第四所有同一个类中所有对象都共享
//直接访问共有的静态成元变量
//静态成员函数不能直接访问类中的成员，因为他没有this指针，不知道是那个对象的
//
//静态成员变量 
//所有对象共享
//静态成员函数访问不了静态成员，
//对象有属性->程序中改变
//方法（函数）需要改变的
//属性是不共享的，方法是共享的，属性是自己的，方法是大家的
//不同的对象是怎么找打自己的方法的？
//每一个成员方法里面都有一个this指针是某一个对象的地址
//静态成员函数里没有this指针，他只知道共有的，除非你告诉我，那个对象的那个属性
int main() {
    /*
    Test t1;
    Test t2;
    Test t3;
    Test t4;
    cout << Test::cnt << endl;
    cout << t1.getCnt() << endl;
    cout << t2.getCnt() << endl;
    cout << t3.getCnt() << endl;
    */
    /*
    cout << Test::getCnt() << endl;
    Test t1;
    cout << Test::getCnt() << endl;
    Test *p = new Test();
    cout << Test::getCnt() << endl;
    delete p;
    cout << Test::getCnt() << endl;
    */
    Test t;
    cout << Test::getCnt(t, 5) << endl;
    printf("&t = %p\n", &t);
    printf("this = %p\n", t.getP());
    cout << t.getM() << endl;
    return 0;
}
