/*************************************************************************
	> File Name: pli.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月13日 星期日 15时18分53秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

int expand(char *str, int i, int j,int n) {
    while (i >= 0 && j < n && str[i] == str[j]) {
        char c = str[j + 1];
        str[j + 1] = 0;
        printf("%s\n", str + i);
        str[j + 1] = c;
        i--, j++;
    }
}


int main() {
    char str[1000];
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; i  < len; i++) {
        printf("%c\n",str[i]);
        expand(str,i - 1, i + 1,len);
        expand(str,i, i + 1, len);
    }
    return 0;
}
