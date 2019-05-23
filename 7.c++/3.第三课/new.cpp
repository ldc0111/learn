/*************************************************************************
	> File Name: new.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月01日 星期二 18时09分49秒
 ************************************************************************/

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

namespace my_lib{
    int i = 10;
    namespace my_lib1{
        int i = 100;
    }
}
using namespace my_lib;
using my_lib::my_lib1::i;


int main() {
    /*
     type *name = new type; //申请
     delete name; //收回
     //单个变量初始化
     type *name = new type(100);//申请并赋值
     delete name;
     //申请一堆连续的空间
     type *name = new type[length];//申请连续空间
     delete[] name;

     //new是按字节分配的
     *
    */
    int *p = new int(100);
    cout << *p << endl;
    int *p1 = new int[10];
    for (int i = 0; i < 10; i++) {
        p1[i] = i + 1;
    }
    for (int i = 0; i < 10; i++) {
        cout << i << ":" << p1[i] << endl;
    }
    delete p;
    delete[] p1;
    cout << my_lib::i << endl << my_lib::my_lib1::i << endl;
    return 0;
}
