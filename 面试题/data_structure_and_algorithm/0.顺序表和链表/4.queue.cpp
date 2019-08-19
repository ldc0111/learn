/*************************************************************************
	> File Name: 4.queue.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月15日 星期四 23时45分17秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Queue{
    int *data;
    int head,tail,length;
}Queue;


Queue *init(int n){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->length = n;
    q->data = (int *)malloc(sizeof(int) * n);
    q->head = 0;
    q->tail = -1;
    return q;
}

int push(Queue *q,int value){
    if (q->tail + 1 == q->length) return 0;
    q->tail += 1;
    q->data[q->tail] = value;
    return 1;
}

int empty(Queue *q) {
    return q->head > q->tail;
}

void pop(Queue *q) {
    if (empty(q)) return ;
    q->head += 1;
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
    printf("Queue = [");
    for (int i = q->head;i <= q->tail; i++) {
        printf (" %d", q->data[i]);
        i == q->tail || printf(",");
    }
    printf("]\n");
}

int main() {
    #define MAX_OP 20 
    srand(time(0));
    Queue * q = init((MAX_OP));
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


