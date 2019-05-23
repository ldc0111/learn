#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stack{
    int *data;
    int top_index,max_size;
}Stack;

Stack * init(int size){
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * size);
    s->top_index = -1;
    s->max_size = size;
    return s;
}

void push(Stack *s, int value){
    if(s->top_index >= s->max_size - 1){
        return ;
    }
    s->top_index += 1;
    s->data[s->top_index] = value;
    return ;
}

int top(Stack *s) {
    if(s->top_index < 0) return -1;
    return s->data[s->top_index];
}
void pop(Stack *s){
    if(s->top_index  < 0) return ;
    s->top_index -= 1;
    return ;
}

int empty(Stack *s){
    return s->top_index < 0;
}


int main(){
    int n, iter = 1, flag = 1;
    scanf("%d", &n);
    Stack *s = init(n);
    
    for(int i = 0; i < n; i++){
        int temp = 0;
        scanf("%d", &temp);
        if(empty(s)|| top(s) < temp){
           while(iter <= temp){
              //printf("(iter = %d) (temp=%d) ", iter, temp);
               push(s, iter);
               iter++;
           }
            pop(s);
        }else if(top(s) > temp){
                flag = 0;
        }else {
            pop(s);
        }
    }
    if(flag){
        printf("YES\n");
    }else {
        printf("NO\n");
    }
}