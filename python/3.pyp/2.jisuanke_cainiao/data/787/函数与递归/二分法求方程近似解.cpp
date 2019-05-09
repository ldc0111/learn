#include <cstdio>
#include <cmath>
#define EPSILON 1e-7

double bisection(int p, int q, double (*func)(int, int, double));
double f(int p, int q, double x);
int main() {
    int p;
    int q;
    scanf("%d %d", &p, &q);
    printf("%.4lf\n", bisection(p, q, f));
    return 0;
}

double bisection(int p, int q, double (*func)(int, int, double)) {
    double head = -20, tail = 20;
    while (tail - head > EPSILON) {
        double mid = (*func)(p, q, (head + tail) / 2);
        if((p > 0 && mid < 0)||(p < 0 && mid > 0)) {
            head = (head + tail) / 2;
        } else {
            tail = (head + tail) / 2;
        }
    }
    return head;
}

double f(int p, int q, double x) {
    return p * x + q;
}