/*************************************************************************
	> File Name: liangge.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2019年01月13日 星期日 15时35分50秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
using namespace std;

typedef struct Data{
    int val,pos;
} Data;

typedef struct hashteble{
    Data *data;
    int *flag;
    int n;
}hashteble;

hashteble* init(int n) {
    hashteble *h = (hashteble *)malloc(sizeof(hashteble));
    h->data = (Data *)calloc(n, sizeof(Data));
    h->flag = (int *)calloc(n, sizeof(int));
    h->n = n;
    return h;

}
int hashfunc(hashteble * h, int val) {
    return val % h->n;
}

void insert(hashteble *h, int val, int ind) {
    int hash = hashfunc(h,val);
    int temp = 1;
    while (h->flag[hash]) {
        hash += (temp++);
        hash %= h->n;
    }
    h->data[hash].val = val;
    h->data[hash].pos = ind;
    h->flag[hash] = 1;
    return ;
}

int query(hashteble *h, int val) {
    int hash = hashfunc(h,val);
    int time = 1;
    while (h->flag[hash] && h->data[hash].val != val){
        hash += (time++);
        hash %= h->n;
    }
    if(h->flag[hash] && h->data[hash].val == val){
        return h->data[hash].pos;
    }
    return -1;
}

void clear(hashteble *h) {
    free(h->data);
    free(h->flag);
    free(h);
}

#define maxn 500
int arr[maxn + 5] = {0};

int main() {
    int n,target;
    scanf("%d", &n);
    hashteble *h = init(3 * n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", arr + i);
    }
    scanf("%d", &target);
    for (int i = 1; i <= n ;i++) {
        int pos;
        if((pos = query(h, target - arr[i])) == -1) {
            insert(h, arr[i], i);
            continue;
        }
        printf("%d %d\n", pos, i);
        break;
    }
    clear(h);
    return 0;
}
