/*************************************************************************
	> File Name: 2.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月01日 星期二 18时37分00秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;


class Test{
    private:
    int i;
    int j;
    public:
    int a;
    int getI() {
        return i;
    }
    int getJ() {
        return j;
    }
    int getA() {
        return a;
    }
    void setI(int value){
        i = value;
        return ;
    }
};


int main() {
    Test t;
    Test *t1 = new Test;
    t.a = 5;
    t1->a = 10;
    t.setI(100);
    cout << t.getI() << endl;
    cout << t.a << " " << t1->a << endl;
    delete t1;
    return 0;
}

