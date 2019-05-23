/*************************************************************************
	> File Name: p1981.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月21日 星期日 16时02分45秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define INF 100000

long long  calc(char *str,int l,int r){
    int pos = -1,temp_piror = 0,piror = INF - 1;
    for(int i = l; i <= r; i++) {
        int cur_piror = INF;
        switch(str[i]) {
            case '(': temp_piror += 100; break;
            case ')': temp_piror -= 100; break;
            case '+': cur_piror = temp_piror + 1; break;
            case '-': cur_piror = temp_piror + 1; break;
            case '*': cur_piror = temp_piror + 2; break;
            case '/': cur_piror = temp_piror + 2; break;
        }
        if(cur_piror < piror){
            piror = cur_piror;
            pos = i;
        }
    }
    //printf("%c\n",str[pos]);
    if(pos == -1){
        long long  num = 0;
        for(int i = l; i <= r; i++){
            if(str[i] < '0' || str[i] > '9') continue;
            num = num * 10 + (str[i] - '0'); 
        }
        return num % 10000;
    }else{
        long long  a = calc(str,l,pos - 1);
        long long  b = calc(str,pos + 1,r);
        switch(str[pos]){
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
    }
    return 0;
}

int main(){
    char str[1200000];
    scanf("%[^\n]s",str);
    //printf("%s\n", str);
    printf("%ld\n", calc(str, 0, strlen(str))%10000);
    return 0;
}

