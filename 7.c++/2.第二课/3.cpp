    /*************************************************************************
	> File Name: 3.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年12月27日 星期四 18时38分06秒
 ************************************************************************/

#include<iostream>
using namespace std;

/*
 历程一：1
int main() {
    int a = 1, b = 2;
    (a > b ? a : b) = 2;// c++ 中返回一个变量的引用
    cout << a << " " << b << endl;
    return 0;
}*/
/*
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap1(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
//youge cuo wu
int& f() {
    int a = 100;
    int &b = a;
    return b;
}




int main() {
    int a = 1, b = 2;
    swap(a, b);
    cout << a << " " << b << endl;
    swap(a, b);
    cout << a << " " << b << endl;

    int c = 1;
    c = f();
    cout << c << endl;
    return 0;
}*/


int main() {
    int a = 1;
    int &b = a;
    //引用相当于一个变量的别名，只可以指向这个变量不能指向别的变量
    int c = 4;
    cout << a << " " << b << endl;
    b = 2; 
    cout << a << " " << b << endl;
    b = c;
    cout << a << " " << b << endl;
    b++;
    cout << a << " " << b << " " << c << endl;
    return 0;
}
