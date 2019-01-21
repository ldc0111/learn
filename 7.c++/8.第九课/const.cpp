/*************************************************************************
	> File Name: const.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月21日 星期一 18时21分49秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Test{};

//临时对象的属性是ｃｏｓｎｔ属性，不能用一个ｃｏｎｓｔ　类型的属性去赋值给一个非ｃｏｎｓｔ
//类型的引用
int main() {
    const Test t;
    Test &t1 = t;
    Test t2;
    const Test &t3 = t2;
    const Test &t4 = t;
    return 0;
}
