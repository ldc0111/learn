/*************************************************************************
	> File Name: builbtree.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月28日 星期日 18时18分07秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char data; 
    struct Node *lchild,  *rchild;
}Node;
typedef struct Stack{
    Node **data;
    int top,size;
}Stack;

Stack * initStack(char n){
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->size = n;
    s->top = -1;
}

int empty(Stack *s){
    return s== NULL || s->top == -1;
}
void pop(Stack *s){
    if(empty(s)) return ;
    s->top -= 1;
    return ;
}
void push(Stack *s,Node *node){
    if(s->top + 1 == s->size) return ;
    s->data[++(s->top)] = node;
    return ;
}

Node * top(Stack *s){
    if(empty(s)) return NULL;
    return s->data[s->top];
}



void clearStack(Stack *s){
    if(s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}


Node * geyNewNode(int key){
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = key;
    p->lchild = p->rchild = NULL;
    return p;
}
void clearTree(Node *root){
    if(root == NULL) return ;
    clearTree(root->lchild);
    clearTree(root->rchild);
    free(root);
    return ;
}

Node * build(const char *str){
    Node *p = NULL, *root = NULL;
    Stack *s = initStack(100);
    int k = 0;
    while(str[0]){
        switch(str[0]){
            case '(':{
                push(s,p);
                k = 0;
            }break;
                case ')':{
                    pop(s);
                }
            case ',':{
                k = 1;
            }break;
            case ' ': break;
            default:{
                p = geyNewNode(str[0]);
                if(root == NULL) root = p;
                if(empty(s)) break;
                if(k == 0)top(s)->lchild = p;
                else top(s)->rchild = p;
            }break;
        }
        str++;
    }
    return root;
}

void output(Node * root){
    if(root == NULL) return ;
    printf("%c ",root->data);
    output(root->lchild);
    output(root->rchild);
    return ;
}


int main(){
    char str[1000];
    Node *root = NULL;
    while(scanf("%[^\n]s",str) != EOF){
        getchar();
        output(root = build(str));
        printf("\n");
        clearTree(root);
    }

    return 0;
}
