#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int *data, int left, int right) {
    if(left > right) {
        return ;
    }
    int pivot = data[left],low = left,high = right;
    while(low < high){
        while(low < high && data[high] >= pivot) {
            high--;
        }
        data[low] = data[high];
        while (low < high && data[low] <= pivot) {
            low++;
        }
        data[high] = data[low];
    }
    data[low] = pivot;
    quick_sort(data,left,low - 1);
    quick_sort(data,low + 1,right);
    return ;
}

void select_sort(int *data, int length) {
    int temp;
    for(int i = 0; i < length - 1; i++){
        temp = i;
        for(int j = i + 1; j < length; j++){
            if (data[temp] > data[j]) {
               temp = j; 
            }
        }
        if (i != temp) {
            printf("%d %d\n",i,temp);
            swap(&data[i],&data[temp]);
        }
    }
}

void print(int *data, int length) {
    for (int i = 0; i < length; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", data[i]);
    }
    printf("\n");
}

int main() {
    int m, n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    scanf("%d", &m);
    if (m == 1) {
        select_sort(a, n);
    } else if (m == 2) {
        quick_sort(a, 0, n - 1);
    }
    print(a, n);
    return 0;
}