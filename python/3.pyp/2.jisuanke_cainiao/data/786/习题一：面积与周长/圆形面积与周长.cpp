#include <stdio.h>
#define PI 3.14159
int main() {
    double r;
    scanf("%lf", &r);
    printf("%.3f\n%.3f\n",PI * 2 * r,PI * r * r);
    return 0;
}