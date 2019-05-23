/*************************************************************************
	> File Name: 2.p1981.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月21日 星期日 16时41分41秒
 ************************************************************************/

#include<iostream>
#include <string.h>
#include <cstdio>
using namespace std;
#define maxn 1200000
#define mod_num 10000
char str[maxn];
int calc(char *str){
    int len = strlen(str);
    for(int i = 0; str[i]; i++) str[i]=(str[i]== '+' ? 0 : str[i]);
    int total = 0;
    for(int j = 0; j < len; j += strlen(str + j) + 1) {
        int num = 0, p = 1;
        for(int i  = j; str[i]; i++){
            switch(str[i]){
                case '*': p*=num; p %= mod_num; num = 0; break;
                default : num = num * 10 + str[i] - '0';
            }
        }
        p *= num; p %= mod_num;
        total +=p;
        total %= mod_num;
    }
    return total;
}


int main(){
    scanf("%s", str);
    printf("%d\n", calc(str));
    return 0;
}
