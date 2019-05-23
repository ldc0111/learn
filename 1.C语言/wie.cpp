/*************************************************************************
	> File Name: wie.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月13日 星期四 18时29分42秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
using namespace std;


int main(){
    //1,2,3int a;
    char str[100];
    //2,FILE *fp = fopen("/dev/null","w");
    //1,2,3scanf("%d", &a);
    //1,printf(" %d", printf("%d", a));
    //2,fprintf(stdout,"%d", fprintf(fp, "%d",a));
    //3,printf("%d\n", sprintf(str,"%d",a));
    for(int i = 0,j = 0; i <= 20; i++){
        j += sprintf(str + j,"%d",i);
    }
    printf("%s",str);
    return 0;
}
