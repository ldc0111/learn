/*************************************************************************
	> File Name: 4.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月27日 星期四 19时22分14秒
 ************************************************************************/

#include<iostream>
using namespace std;
/*
int add(int a = 0, int b = 0) {
    return a + b;
}

int main() {
    cout << add() << endl;
    cout << add(1) << endl;
    cout << add(1, 2) << endl;
    return 0;
}*/
//int add(int a = 4, int b = 5);
int add(int a, int b);

int add2(int a = 1,int b){
    return a + b;
}

int main() {
    //cout << add() << endl;
    cout << add(1,2) << endl;
    //报错，说明他是按顺序赋值的
    cout << add2(1) << endl;
    return 0;
}

//函数参数在函数声明的时候给他就行了，实现的时候不用给，会报错
int add(int a = 4, int b = 5) {
    return a + b;
}

