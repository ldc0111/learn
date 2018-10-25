/*************************************************************************
	> File Name: queue.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月21日 星期日 18时14分27秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

typedef struct Queue{
    int *data;
    int head,tail,length, cnt;
}Queue;

Queue *init(int n){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->length = n;
    q->data = (int *)malloc(sizeof(int) * n);
    q->head = 0;q->tail = -1;
    q->cnt = 0;
}

int push(Queue *q, int value){
    if(q->cnt == q->length) return 0;
    q->tail += 1;
    q->tail %= q->length;
    q->cnt +=1;
    q->data[q->tail] = value;
    return 1;
}

int empty(Queue *q){
    return q->cnt == 0;
}

void pop(Queue *q){
    if(empty(q)) return ;
    q->head += 1;
    if(q->head >= q->length) q->head -= q->length;
    q->cnt -= 1;
    return ;
}

int front(Queue *q){
    if(empty(q)) return 0;
    return q->data[q->head];
}
void clear(Queue * q){
    if(q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}
void output(Queue *q) {
    printf("Queue = [");
    for(int i = 0; i < q->cnt; i++) {
        int ind = (q->head + i) % q->length;
        printf(" %d", q->data[ind]);
        i + 1 == q->cnt || printf(",");
    }
    printf(" ]\n");
}


int main(){
    #define MAX_OP 20 
    srand(time(0));
    Queue *q = init(MAX_OP);
    for(int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4,value = rand() %4;
        switch(op) {
            case 0:
            case 1:
            case 2:
                  push(q,value);
                  printf("push :%d from queue\n",value);
            break;
            case 3:
            printf("pop  from queue\n");
            pop(q);
            output(q);
            break;
        }
    }
    return 0;
}
