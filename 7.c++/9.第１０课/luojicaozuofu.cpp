/*************************************************************************
	> File Name: luojicaozuofu.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月21日 星期一 19时16分00秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <string>
using namespace std;

int func(int i) {
    cout << "func: i = " << i << endl;
    return i;
}

class Test{
    private:
        int i;
    public:
    Test(int v = 0) : i(v){

    }
    int geti() const {
        return i;
    }
};
bool operator&&(const Test &obj1, const Test &obj2) {
    return ((obj1.geti()) && (obj2.geti()));
}

bool operator||(const Test &obj1, const Test &obj2) {
    return ((obj1.geti()) || (obj2.geti()));
}
Test gunc(Test obj) {
    cout << "Test :: ojb.i = " << obj.geti() <<  endl;
    return obj;
}
//问题来源，函数的重载是函数的调用
//表象(参数１|| 参数２) 实际 operator||(参数１，参数２)
//无法满足最短路原则一个调用另一个不调用



int main() {
    //最短路原则
    if (func(0) && func(1)) {
        cout << "true" << endl;
    }
    if (func(1) || func(0)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    cout << "Test operator:" << endl;
    Test t1(1),t2(0);
    if (gunc(t1) && gunc(t2)) {//operator&&(gunc(t1), gunc(t2));函数是值传递
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    if (gunc(t1) || gunc(t2)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    return 0;
}
