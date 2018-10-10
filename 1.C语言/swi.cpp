/*************************************************************************
	> File Name: swi.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月18日 星期二 18时52分32秒
 ************************************************************************/

#include<iostream>
using namespace std;


int main(){
    int n;

    scanf("%d", &n);
    switch (n) {
        case 1:
            printf("one\n");
            break;
        case 2:
            printf("tow\n");
            break;
        case 3:
            printf("three\n");
            break;
        default :
            printf("error\n");
            break;
    }

    return 0;
}
