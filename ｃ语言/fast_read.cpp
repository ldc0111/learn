/*************************************************************************
	> File Name: fast_read.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年09月18日 星期二 19时51分33秒
 ************************************************************************/

#include<iostream>
#include <cstdio>
using namespace std;

char ss[1<<17], *A = ss, *B = ss;
inline char gc(){
    return A == B && (B = (A = ss) + fread(ss, 1,1 << 17,stdin), A == B) ? -1: *A++;
}
template<typename T> inline void sdf(T &x){
    char c;
    T y = 1;
    while (c = gc(), (c < 48 || c > 57) && c != -1) {
        if (c == '-') y = -1;
        printf("2");
    }
    x =c ^ 48;
    while(c = gc(), (c <= 57 && c >= 48)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
    }
    x *= y;
}

int main(){
    int a;
    for(int i = 0; i < 1000000; i++){
        sdf(a);
        //printf("1");
        printf("%d\n", a);
    }

    return 0;
}
