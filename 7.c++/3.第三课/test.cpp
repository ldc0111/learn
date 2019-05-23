/*************************************************************************
	> File Name: test.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月01日 星期二 19时25分05秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Test{
    private:
    int i,j;
    public:
    int getI() {
        return i;
    }
    int getJ() {
        return j;
    }
};

Test t1;

int main() {
    cout << t1.getI() << " " << t1.getJ() << endl;
    Test t2;
    cout << t2.getI() << " " << t2.getJ() << endl;
    Test *t3 = new Test;
    cout << t3->getI() << " " << t3->getJ() << endl;
    return 0;
}
