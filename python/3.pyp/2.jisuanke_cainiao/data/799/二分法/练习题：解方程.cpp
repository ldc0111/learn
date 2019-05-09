#include <stdio.h>
#include <math.h>
#define eps 1e-6
double f(double x) {
    return x * x * x * x + 5 * x * x * x + 6 * x * x + 7 * x + 4;
}

double solve_equation(double y) {
    if(y < f(0) || y > f(100)) return -1;
	double l = 0, r = 100, mid, sum;
    while (fabs(r - l) > eps) {
        mid = (r + l) / 2;
        sum = f(mid);
        if (fabs(sum - y) < eps) return mid;
        if (sum > y) r = mid;
        else l = mid;
    }
    return l;
}
int main() {
	double y;
	scanf("%lf", &y);
	printf("%.10f\n", solve_equation(y));
}