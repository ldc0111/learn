/*************************************************************************
	> File Name: 6.stack.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月16日 星期五 00时20分19秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Stack{
    int *data;
    int top,size;
}Stack;

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->top = -1;
    s->size = n;
    return s;
}

int empty(Stack *s) {
    return s->top == -1;
}

int top(Stack *s) {
    if (empty(s)) return 0;
    return s->data[s->top];
}

int push(Stack *s, int value){
    if (s->top + 1 == s->size) return 0;
    s->top += 1;
    s->data[s->top] = value;
    return 1;
}

int pop(Stack *s) {
    if (empty(s)) return 0;
    s->top -= 1;
}


void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

void output(Stack *s) {
    printf("Stack = [");
    for (int i = s->top; i >= 0; i--) {
        printf(" %d",s->data[i]);
        i && printf(",");
    }
    printf("]\n");
}
int main() {
    srand(time(0));
    #define MAX_OP 20 
    Stack *s = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4,value = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2:{
                push(s,value);
                printf("push %d to Stack\n", top(s));
                output(s); 
            }break;
            case 3:{
                pop(s);
                printf("pop %d to Stack\n",top(s));
                output(s);

            }break;
        }
    }
    return 0;
}
