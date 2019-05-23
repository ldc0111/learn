/*************************************************************************
	> File Name: exception5.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 15时21分49秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class base {};
class expection : public base{
    private:
        int i;
        string info;
    public:
    exception(int v1, string &s1) {
        i = v1;
        info = s1;
    }
    void what() {
        cout << "exception id is " << i << endl;
        cout << "exception information is " << info << endl;
    }
}
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
    }catch(int) {
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
    }catch(exception &c){
        cout << "exception information is exception" << endl;
    }catch(base b){
        cout << "exception information is base" << endl; 
    } catch(...){
        cout << "other exception" << endl;
    }
    cout << "done" << endl;
    return 0;
}

