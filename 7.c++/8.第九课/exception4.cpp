/*************************************************************************
> File Name: exception4.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2019年01月18日 星期五 15时09分47秒
************************************************************************/

#include <iostream>
#include <string>
using namespace std;
void func1(int i) {
    if (i < 10) {
        throw -1;
    } else if (i < 20) {
        throw -2;
    } else if (i < 30) {
        throw -3;
    }
    return ;
}
void myfunc(int i) {
    try{
        func1(i);
    }catch(int i) {
        switch(i) {
            case -1:{
                throw "run erro";
            }break;
            case -2:{
                throw "parameter erro";
            }break;
            case -3:{
                throw "segment fault";
            }break;
        }
    }
}
int main() {
    int i = 0;
    cin >> i;
    try {
        myfunc(i);
    }catch(const char *s){
        cout << "exception information is " << s << endl;
    }
    cout << "done" << endl;
    return 0;
}


