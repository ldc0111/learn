/*************************************************************************
	> File Name: fast_read.
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月01日 星期四 14时46分00秒
 ************************************************************************/
#include <iostream>
#include <cstdio>
using std::cin;
using std::cout;
using std::endl;

//读不乱标准输入，可以读取文件


char ss[1 << 17], *A = ss, *B = ss;
inline char gc(){
    return A == B && (B = (A = ss) + fread(ss,1,1 << 17,stdin), A == B) ? -1:*A++;
}
inline void sdf(int &x){
    char c;
    int y = 1;
    while (c = gc(),(c < 48 || c > 57) && c != -1) {
        if (c == '-') y = -1;
        printf("2");
    }
    x = c ^ 48;
    while (c = gc(),(c <= 57 && c >= 48)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
    }
    x *= y;
}



int main(){
    int a;
    for(int i = 0; i < 100; i++){
        sdf(a);
        printf("%d\n", a);
    }

    return 0;
}
