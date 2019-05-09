#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Queue{
    char **data;
    int head,tail,length,count;
}Queue;

Queue* init(int size){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data=(char **)malloc(sizeof(char *) * size);
    q->head = 0;
    q->tail = -1;
    q->length = size;
    q->count = 0;
    return q;
}
void push(Queue *q, char *str){
    if(q->count > q->length){
        return 0;
    }
    q->tail += 1;
    q->data[q->tail] = str;
    q->count++;
    return ;
}
int empty(Queue *q){
    return q->count == 0;
}
char * top(Queue * q){
    return q->data[q->head];
}
void pop(Queue *q){
    q->head += 1;
    q->count -= 1;
    return ;
}


int main(){
    Queue *wei = init(10);
    Queue *yi = init(10);
    Queue *bo = init(10);
    for (int i = 0; i < 10; i++) {
        int op;
        scanf("%d", &op);
        char *str = (char *)malloc(sizeof(char) * 12);
        scanf("%s", str);
        if(op == 0) {
            push(wei,str);
        } else if ( op == 1) { 
            push(yi,str);
        } else {
            push(bo,str);
        }
    }
    for(int i = 0; i < 10; i++){
        if(!empty(wei)){
            printf("%s ",top(wei));
            pop(wei);
        }else{
            printf("0 ");
        }
        if(!empty(yi)){
            printf("%s ",top(yi));
            pop(yi);
        }else{
            printf("0 ");
        }
        
        if(!empty(bo)){
            printf("%s\n",top(bo));
            pop(bo);
        }else{
            printf("0\n");
        }
    }
    return 0;
}