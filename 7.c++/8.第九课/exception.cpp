/*************************************************************************
	> File Name: exception.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月18日 星期五 14时25分42秒
 ************************************************************************/

#include<iostream>
using namespace std;
double div(double a, double b) {
    const double x = 0.00000001;
    double ret = 0.0;
    if (!((b > -x) && (b < x))) {
        ret = a / b;
    } else {
        throw 5;
    }
    return ret;
}


int main() {
    cout << div(1.0, 0.5) << endl;
    cout << div(1.0, 0) << endl;
    /*
    try{
        div(1.0,0.0);
    } catch(int i) {
        cout << "b is zero !" << endl;
        cout << "catch(int i) : i = " << i << endl;
    }*/
    cout << "exception is dealed!" << endl;
    return 0;
}
