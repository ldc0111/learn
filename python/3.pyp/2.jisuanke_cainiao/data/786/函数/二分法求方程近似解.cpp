#include <stdio.h>
#include <math.h>
#define EPSILON 1e-7

double bisection(int p, int q, double (*func)(int, int, double));
double f(int p, int q, double x);
int main() {
    int p;
    int q;
    scanf("%d%d", &p, &q);
    printf("%.4f\n", bisection(p, q, f));
    return 0;
}

double bisection(int p, int q, double (*func)(int, int, double)) {
    double head = -20,tail = 20;
    while (fabs(head - tail) > EPSILON) {
        double mid = (head + tail) / 2;
        double sum = func(p,q,mid);
        if(fabs(sum - 0) < EPSILON) return mid;
        else if(sum > 0)  p > 0 ? (tail = mid) : (head = mid);
        else  p > 0 ? (head = mid) : (tail = mid);
    }
    return head;
}

double f(int p, int q, double x) {
    return p * x + q;
}