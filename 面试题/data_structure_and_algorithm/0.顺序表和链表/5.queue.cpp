/*************************************************************************
	> File Name: 4.queue.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月15日 星期四 24时00分17秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Queue{
    int *data;
    int head,tail,length,cnt;
}Queue;


Queue *init(int n){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->length = n;
    q->data = (int *)malloc(sizeof(int) * n);
    q->head = 0;
    q->cnt = 0;
    q->tail = -1;
    return q;
}

int push(Queue *q,int value){
    if (q->cnt == q->length) return 0;
    q->tail += 1;
    if(q->tail >= q->length) q->tail -= q->length;
    q->data[q->tail] = value;
    q->cnt += 1;
    return 1;
}

int empty(Queue *q) {
    return !(q->cnt);
}

void pop(Queue *q) {
    if (empty(q)) return ;
    q->head += 1;
    if (q->head >= q->length) q->head -= q->length;
    q->cnt -= 1;
    return ;
}

int front(Queue *q) {
    if (empty(q)) return 0;
    return q->data[q->head];
}


void clear(Queue *q){
    if (q == NULL) return ;
    free(q->data);
    free(q);
}


void output(Queue *q) {
    printf("cnt = %d,Queue = [",q->cnt);
    for (int i = 0;i < q->cnt; i++) {
        int ind = (q->head + i) % q->length;
        printf (" %d", q->data[ind]);
        i + 1 == q->cnt || printf(",");
    }
    printf("]\n");
}

int main() {
    #define MAX_OP 20 
    srand(time(0));
    Queue * q = init(MAX_OP / 2);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2:{
                push(q,value);
                printf ("push : ");
                output(q);

            }break;
            case 3:{
                pop(q);
                printf ("pop : ");
                output(q);

            }break;
        }
    }
    clear(q);
    return 0;
}


