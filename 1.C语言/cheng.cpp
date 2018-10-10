/*************************************************************************
	> File Name: cheng.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月18日 星期二 18时30分52秒
 ************************************************************************/

#include<iostream>
using namespace std;



int main(){
    int n;

    cin >> n;

    (n == 0) && cout << "FOOLISH" << endl;
    (n < 60 && n > 0) && cout << "FALL" << endl;
    (n >= 60 && n < 75) && cout << "MEDIUM" << endl;
    (n >= 75 && n <= 100) && cout << "GOOD" << endl; 

    return 0;
}
