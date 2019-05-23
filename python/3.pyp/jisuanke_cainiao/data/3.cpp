#include <stdio.h>
#include <math.h>
int main() {
    double a,b;
    scanf("%lf%lf",&a, &b);
    printf("%.2lf\n%.2lf",sqrt(a*a + b*b) + a + b, a * b / 2);

    return 0;
}