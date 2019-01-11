/*************************************************************************
	> File Name: xigou.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月06日 星期日 19时49分16秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;
class Value{
    private:
    int i;
    public:
    Value(int v):i(v) {
        cout << "Value()" << i << endl;
    }

};


class Test{
    private:
    Value v1;
    Value v2;
    public:
    Test():v1(1), v2(2){
        cout << "hello" << endl;
    }
    //析构函数，无参数，无返回值，所以不能被重载
    ~Test(){
        cout << "byebye" << endl;
    }
};
//因为c++标准中没有规定全局变量的对象的构造顺序，所以不同的编译器结果不同
//对象构造顺序：先父母，再朋友，在自己
//d
int main() {
    Test t;
    Test *p = new Test;
    delete p;
    return 0;
}
