/*************************************************************************
	> File Name: revTest.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月08日 星期二 18时17分35秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

class Test{
    private:
        int i;
    public:
        Test(int v) {
            cout << "Test(int v)" << endl;
            i = v;
        }
        Test() { 
            int i = 0;
            //这里会产生一个临时对象,生命周期只有一行
            cout << "Test()" << endl;
            Test(100);
        }
        void printI(){
            cout << "i = " << i << endl;
        }
        Test(const Test &t) {
            i = t.i;//？
            cout << "Tesst(const Test &t): i = " << i << endl;
        }
};

void func1(Test t) {
    return;
}
Test func2(){
    Test t(100);
    return t;
}

//-fno-elide-constructors
int main() {
    //默认有返回值优化，减少一次ｃｏｐｙ函数调用
    //原因：会加快速度
    //Test t = Test(100);//t = 100
    //t.printI();
    //func1(t);
    //Test t1 = func2();//　t = 100;
    //t1.printI();
    Test t3[3] = {1, 2, 3};
    return 0;
}
