/*************************************************************************
	> File Name: 3.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月13日 星期日 18时28分02秒
 ************************************************************************/

#include<iostream>
using namespace std;

int atoi(char *str) {
    int i = 0; ret = 0, flag = 1;
    while (str[i] == ' ') ++i;
    if (str[i] =='-')  flag =-1, i++;
    while (str[i] && str[i] <= '9' && str[i] >= '0') {
        ret = ret * 10 + (str[i] - '0');
    }
}


int main() {
    return 0;
}
