#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR 0
#define OK 1

typedef struct Stack {
    int *elements;
    int top_index,max_size;
} Stack;

void init(Stack *s,int element) {
    s->elements = (int *)malloc(sizeof(int) * element);
    s->top_index = -1;
    s->max_size = element;
}

int push(Stack *s, int element) {
    if (s->top_index >= s->max_size - 1) {
        return ERROR;
    }
    s->top_index++;
    s->elements[s->top_index] = element;
    return OK;
}

int pop(Stack *s) {
    if(s->top_index < 0){
        return ERROR;
    }
    s->top_index--;
    return OK;
}

int top(Stack *s) {
    return s->elements[s->top_index];
}

int empty(Stack *s) {
    return s->top_index  < 0;
}

int precede(char a,char b) {
    if((a == '*' && (b == '-' || b == '+'))
      ||(a == '/' && (b == '-'||b == '+'))) {
        return OK;
    } else {
        return 0;
    }
}
int operate(char a,int  b, int c) {
    if (a == '+') {
        return b+c;
    } else if (a == '*') { 
        return b * c;
    } else if (a == '-') {
        return c - b;
    } else {
        return c/b;
    } 
}
void calc(Stack *numbers, Stack *operators) {
    int a = top(numbers);
    pop(numbers);
    int b = top(numbers);
    pop(numbers);
    push(numbers,operate(top(operators),a,b));
    pop(operators);
}

void clear(Stack *s) {
    free(s->elements);
    free(s);
}

int main() {
    int n;
    scanf("%d", &n);
    Stack *numbers = (Stack *)malloc(sizeof(Stack));
    init(numbers,n);
    Stack *operators = (Stack *)malloc(sizeof(Stack));
    init(operators, n);
    char *buffer = (char *)malloc(sizeof(char) * (n + 1));
    scanf("%s", buffer);
    int i = 0;
    while(i < n){
        if (isdigit(buffer[i])) {
            push(numbers, buffer[i] - '0');
            i++;
        } else{
            if(empty(operators) || precede(buffer[i], top(operators))){
                push(operators, buffer[i]);
                i++;
            }else{
                calc(numbers,operators);
            }
        }
    }
    while(!empty(operators)){
        calc(numbers,operators);
    }
    printf("%d\n", top(numbers));
    return 0;
}