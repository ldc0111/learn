#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int a[3][3] = {0}, suma = 0;
    int b[2][2] = {0}, sumb = 0;
    int *p = &a[0][0];
    for(int i = 0; i < 9; i++){
        scanf("%d", (p + i));
    }
    p = &b[0][0];
    for(int i = 0; i < 4; i++){
        scanf("%d", (p + i));
    }
    
    suma = a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[0][2] * a[1][0] * a[2][1] -
           a[0][2] * a[1][1] * a[2][0] - a[0][0] * a[1][2] * a[2][1] - a[0][1] * a[1][0] * a[2][2];
    sumb = b[0][0] * b[1][1] - 
           b[0][1] * b[1][0];
    printf("%d\n", suma > sumb ? suma : sumb);
    return 0;
}