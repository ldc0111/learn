/*************************************************************************
	> File Name: 1.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年11月01日 星期四 15时03分53秒
 ************************************************************************/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

char ss[1<<17], *A = ss, *B = ss;
inline char gc() {
    return A == B && (B = (A = ss) + fread(ss, 1, 1 << 17, stdin), A == B) ? -1 : *A++;
}

template<typename T> inline void sdf(T &x) {
    char c;
    T y = 1;
    while (c = gc(), (c < 48 || c > 57) && c != -1) {
        if (c == '-') y = -1;
    }
    x = c ^ 48;
    while (c = gc(), (c <= 57 && c >= 48)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
    }
    x *= y;
}

int main() {
    for (int i = 48; i <= 57; i++) {
        printf("%d ^ 48 = %d\n", i, i ^ 48);
    }
    int n, a;
    //sdf(n);
    for (int i = 0; i < 11; i++) {
        sdf(a);
        printf("%d ",a);
    }
    return 0;
}
