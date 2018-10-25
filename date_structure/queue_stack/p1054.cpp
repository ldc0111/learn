/*************************************************************************
	> File Name: p1054.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月21日 星期日 19时45分26秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cmath>
using namespace std;
#define maxn 100000
#define INF 10000000
#define max_mod 1000000000 

long long  poww(long long a,long long b) {
    long long temp = a;
    long long i = 1;
    while(i < b){
        temp = (temp * a) % max_mod;
        i++;
    }
    return temp;
}


long long  calc(char * str, int l, int r, int value){
    long long  pos = -1, temp_prior = 0, prior = INF - 1;
    for(int i = l; i <= r; i++) {
        long long  temp = INF;
        switch(str[i]) {
            case '(': temp_prior += 100; break;
            case ')': temp_prior -= 100; break;
            case '+': temp = temp_prior + 1; break;
            case '-': temp = temp_prior + 1; break;
            case '*': temp = temp_prior + 2; break;
            case '/': temp = temp_prior + 2; break;
            case '^': temp = temp_prior + 3; break;
        }
        if(temp <= prior) {
            prior = temp;
            pos = i;
        }
    }
    //printf("%c\n", str[pos]);
    if(pos == -1){
        long long  num = 0;
        for(int i = l; i <= r; i++){
            if(str[i] == 'a') return value;
            if(str[i] < '0' || str[i] > '9') continue;
            num = num * 10 + str[i] - '0';
        }
        return num;
    }else{
        long long  a = (calc(str,l,pos - 1, value));
        long long  b = (calc(str,pos + 1, r, value));
        //printf("(a = %d) %c (b = %d)\n", a,str[pos],b);
        switch(str[pos]) {
            case '+': return (a + b) % max_mod;
            case '-': return (a - b) % max_mod;
            case '*': return (a * b) % max_mod;
            case '/': return (a / b) % max_mod;
            case '^': return poww(a,b);
        }
    }
    return 0;
}


int main(){
    //printf("%ld",calc("(8-a)^4",0,strlen("(8-a)^4"),4));
    char str[75];
    long long  a[50] = {0};
    long long b[50] = {0};
    srand(time(0));

    int n;
    scanf("%[^\n]s", str);
    getchar();
    //printf("%d\n", calc(str, 0, strlen(str)-1, 780));;

    scanf("%d", &n);
    for (int i = 0; i < 20; i++) {
        a[i] = rand()% 50;

        b[i] = calc(str, 0, strlen(str) - 1, a[i]);
    }

    getchar();
    for(int i = 0; i < n; i++){
        int flag = 1;
        getchar();
        memset(str,0,sizeof(str));
        scanf("%[^\n]s", str);
        
        for(int j = 0; j < 20; j++){
            if(b[j] != calc(str, 0, strlen(str) - 1, a[j])){
                flag = 0;
                //printf("\na[i] =%d b[i] = %d cale : %d\n", a[i],b[i],calc(str,0,strlen(str) -1, a[i]));
                break;
            }
         }
        flag && printf("%c", i+'A');
    }
    printf("\n");
    return 0;
}

