/*************************************************************************
	> File Name: 5.priority_queue.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月19日 星期一 22时43分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a,b) {\
    __typeof(a) _t = a;\
                a = b;\
                b = _t;\
}

typedef struct priority_queue{
    int *data;
    int size,cnt;
}priority_queue;

priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int) * (n + 1));
    q->cnt = 0;
    q->size = n;
    return q;
}

int empty(priority_queue *q) {
    return q->cnt == 0;
}
int push(priority_queue *q, int value) {
    if (q->cnt == q->size) return 0;
    q->data[++q->cnt] = value;
    int ind = q->cnt;
    while (ind > 1) {
        if (q->data[ind] <=  q->data[ind >> 1]) break;
        swap(q->data[ind],q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}


int pop(priority_queue *q) {
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    int ind = 1;
    while ((ind << 2) < q->cnt) {
        int temp = ind;
        if (q->data[temp] < q->data[ind << 1]) temp = ind << 1;
        if (((ind << 1 | 1) < q->cnt) && q->data[temp] < q->data[(ind << 1 | 1)]) temp = ind << 1 | 1;
        if (temp == ind) break;
        swap(q->data[temp], q->data[ind]);
        ind = temp;
    }
    return 1;
}

int top(priority_queue *q) {
    if (empty(q)) return 0;
    return q->data[1];
}



void clear(priority_queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void output(priority_queue *q) {
    printf ("Queue = [");
    for (int i = 1; i <= q->cnt; i++) {
        printf ("%d ",q->data[i]);
        i == q->cnt || printf(",");
    }
    printf("]\n");
}


int main() {
    #define MAX_OP 20 
    srand(time(0));
    priority_queue *q = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4,value = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2:{
                printf ("insert %d to priority_queue\n", value);
                push(q,value);
            }break;
            case 3:{
                printf("pop %d from priority_queue\n", top(q));
                pop(q);
            }break;
        }
        output(q);
    }


    return 0;
}
