/*************************************************************************
	> File Name: ip.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月04日 星期四 10时04分05秒
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

union IP{
    struct{
        unsigned char arr[4];
    }ip;
    unsigned int num;
};

int main(){
    int a,b,c,d;
    IP ip;
    while(scanf("%d.%d.%d.%d",&a, &b, &c, &d) != EOF){
        ip.ip.arr[0] = a;
        ip.ip.arr[1] = b;
        ip.ip.arr[2] = c;
        ip.ip.arr[3] = d;
        printf("%u\n", ip.num);
       // memset(&ip,'\0',sizeof(ip));
    }
    return 0;
}
