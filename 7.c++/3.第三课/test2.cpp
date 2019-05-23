/*************************************************************************
	> File Name: test2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月01日 星期二 19时49分46秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Test{
    private:
    int a;
    public:
    Test() {
        a = 10;
        cout << "Test(): " << a <<  endl;
    }
    Test(int value) {
        a = value;
        cout << "Test(int): " << a << endl;
    }
    Test(int c, int b){
        a = c;
        cout << "Test(int, int)" << endl;
    }
    Test(const Test &obj){
        a = obj.a;
        cout << "Test copy" << endl;
    }
    int getA() {
        return a;
    }
    int* getP() {
        return &a;
    }
};
//如果没有构造函数，系统内部会提供一个无参数的构造函数
//如果你写了一个构造函数，如果写了构造函数就不会给你提供无参数的构造函数了
/*
int main() {
    Test t(1);//1
    Test t2 = 100;//int i = 100
    Test t3;
    int  i = 1;
    return 0;
}*/

/*
int main() {
    //1
    //Test *p = new Test(1);
    //2.对象数组
    Test tt = {1,1};
    //Test t[3];
    *
    for (int i = 0; i < 3; i++) {
        cout << t[i].getA() << endl;
    }
}*/


//浅拷贝，深拷贝，
int main() {
    Test t1(1);
    Test t5 = t1;//初始化
    //Test t5;//拷贝构造函数是，用已经实现的构造函数去初始化一个新的对象
    //t5 = t1;//这个调用的不是拷贝构造函数
    cout << t1.getP() << endl;
    cout << t5.getP() << endl;
    return 0;
}



