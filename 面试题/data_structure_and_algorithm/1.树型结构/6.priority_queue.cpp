/*************************************************************************
> File Name: 6.priority_queue.cpp
> Author: 
> Mail: 
> Created Time: 2019年08月19日 星期一 23时52分10秒
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a,b) {\
    __typeof(a) _t = a; a = b; b = _t;\
}

void heap_sort(int *arr, int n) {
    int *p = arr - 1;
    for (int i = 2; i <= n; i++) {
        int ind = i;
        while (ind > 1) {
            if (p[ind] <= p[ind >> 1]) break;
            swap(p[ind], p[ind >> 1]);
            ind >>= 1;
        }
    }
    for (int i = n; i > 1; i--) {
        swap(p[i],p[1]);
        int ind = 1;
        while ((ind << 1) <= i - 1) {
            int temp = ind;
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= i - 1 && p[temp] < p[ind << 1 | 1]) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap(p[temp], p[ind]);
            ind = temp;
        }
    }
    return ;
}


void heap_sort2(int *arr, int n) {
    int *p = arr - 1;
    for (int ind = n >> 1; ind > 1; ind--) {
        while ((ind << 1) <= n) {
            int temp = ind;
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= n && p[temp] < p[ind << 1 | 1]) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap(p[temp], p[ind]);
            ind = temp;
        }
    }
    for (int i = n; i > 1; i--) {
        swap(p[i], p[1]);
        int ind = 1;
        while ((ind << 1) <= i - 1) {
            int temp = ind;
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= i - 1 && p[temp] < p[ind << 1 | 1]) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap(p[temp], p[ind]);
            ind = temp;

        }

    }
    return ;
}

void output(int *num, int n) {
    printf ("Are = [");
    for (int i = 0; i < n; i++) {
        printf ("%d ", num[i]);
        i != (n - 1) && printf(",");
    }
    printf("]\n");
    return ;
}

int main() {
    #define MAX_OP 20
    srand(time(0));
    int arr[MAX_OP];
    for (int i = 0; i < MAX_OP; i++) arr[i] = rand() % 100;
    heap_sort2(arr, MAX_OP);
    output(arr,MAX_OP);


    return 0;
}
