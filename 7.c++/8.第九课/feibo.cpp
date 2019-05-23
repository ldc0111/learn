/*************************************************************************
	> File Name: feibo.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 20时14分37秒
 ************************************************************************/

#include<iostream>
using namespace std;
class Fib{
    private:
        int a0;
        int a1;
    public:
        Fib() {
            a0  = 0;
            a1 = 1;
        }
    Fib (int n) {
        a0 = 0;
        a1 = 1;
        for (int i = 2; i <= n; i++) {
            int t = a1;
            a1 = a0 + a1;
            a0 = t;
        }
    }
        int operator()() {
            //每次调用的时候，用这个函数
            int ret = a1;
            a1 = a1 + a0;
            a0 = ret;
            return ret;
        }
    int operator() (int n) {
        //返回第ｎ项的值
        a0 = 0;
        a1 = 1;
        int ret = a1;
        for (int i = 1; i <= n; i++) {
            ret = a1;
            a1 = a0 + a1;
            a0 = ret;
        }
        return ret;
    }
};


int main() {
    Fib fib;
    for (int i = 0; i < 10; i++) {
        cout << fib() << endl;//fib.operator()
    }
    cout << fib(10) << endl;
    Fib fib1(10);
    for (int i = 0; i < 10; i++) {
        cout << fib1() << endl;
    }
    return 0;
}
