/*************************************************************************
> File Name: nibolan.cpp
> Author: ldc
> Mail: litesla
> Created Time: 2019年01月13日 星期日 14时15分38秒
************************************************************************/

#include<iostream>
using namespace std;

int getNUM(char *str, int *ret) {
    int i = 0, num = 0;
    while (str[i] <= '9' && str[i] >= '0') {
        num = num * 10 + str[i] - '0';
        i++;
    }
    *ret = num;
    return i;
}



int getTerm(char *str, int *ret) {
    int i = 0,temp;
    printf("%s\n", str);
    if (str[i] == 0) return 0;
    i += getNUM(str + i, ret);
    if (str[i] == 0) return i;
    while (str[i]) {
        switch(str[i]) {
            case '*': {
                i += getTerm(str + i + 1, &temp) + 1;//1是本层的×号算坐标少算了一个
                *ret *= temp;
            }break;
            case '/': {
                i += getTerm(str + i + 1, &temp) + 1;
                *ret /= temp;
            }break;
            default:return i;
        }
    }
    return i;
}

int calc(char *str) {
    int i = 0,a,b;
    char op;
    if (str[i] == 0) return 0;
    i += getTerm(str + i, &a);
    if (str[i] == 0) return a;
    while (str[i]) {
        op = str[i];
        i += getTerm(str + i + 1, &b);
        switch(op){
            case '+': a += b;break;
            case '-': a -= b;break;
        }
    }
    return a;
}


int main() {
    char str[10000];
    scanf("%s",str);
    printf("%d\n",calc(str));
    return 0;
}
