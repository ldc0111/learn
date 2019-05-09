#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Stack{
    char *data;
    int top_index,size;
}Stack;

Stack* init(int size) {
    Stack *q = (Stack *)malloc(sizeof(Stack));
    q->data = (char * )malloc(sizeof(char) * size);
    q->top_index = -1;
    q->size = size;
    return q;
}
void push(Stack *s, char ch){
    if(s->top_index >= s->size - 1){
        return ;
    }
    s->top_index += 1;
    s->data[s->top_index] = ch;
    return ;
}
void pop(Stack *s){
    s->top_index--;
}

char top(Stack *s){
    return s->data[s->top_index];
}
int empty(Stack *s){
    return s->top_index < 0;
}

int main(){
    int flag = 1;
    char str[30];
    int temp = 0;
    scanf("%[^\n]s", str);
    int len = ((strlen(str) - 1)/2);
    Stack *s = init(len);
    for (int i = 0; i < len; i++) {
        push(s,str[i]);
    }
    if (strlen(str) % 2){
        temp = len;
    } else{
        temp = len + 1;
    }
    for(int i = 0; i < len; i++){
        if(top(s) != str[temp + i]){
            flag = 0;
        }
        pop(s);
    }
    if(flag){
        printf("true\n");
    }else {
        printf("false\n");
    }
    return ;
}