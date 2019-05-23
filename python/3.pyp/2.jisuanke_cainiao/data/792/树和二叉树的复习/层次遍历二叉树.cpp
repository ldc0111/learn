#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 100000

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
}Node;

Node *init(int data){
    Node * node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}
Node* build(char str[], int l, int r){
    if(l > r) return NULL;
    Node *node = init(str[l]);
    int pos = -1,temp_prior = 0,prior = INF - 1;
    for(int i = l; i <= r; i++){
        int cur_prior = INF;
        switch(str[i]){
            case '(': temp_prior += 100; break;
            case ')': temp_prior -= 100; break;
            case ',': cur_prior = temp_prior +  1; break;
        }
        if(cur_prior <= prior){
            prior = cur_prior;
            pos = i;
        }
    }
    if(pos == -1){
        //if(l < r){
            //printf("%c %d %d|",str[l],l,r);
            node->lchild = build(str,l + 2,r - 1);
        //}
        return node;
    }else {
        node->lchild = build(str,l + 2,pos - 1);
        node->rchild = build(str,pos + 1,r - 1);
    }
    return node;
}

void preorder(Node *node){
    if(node == NULL) return ;
    printf("%c",node->data);
    preorder(node->lchild);
    preorder(node->rchild);
}
typedef struct queue{
    Node * q;
    int head,tail,count,length;
}Queue;

Queue *initq(int length){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->q=(Node *)malloc(sizeof(Node) * length);
    q->head = 0;
    q->tail = -1;
    q->length = length;
    q->count = 0;
    return q;
}

void push(Queue *q, Node val){
    if(q->count >= q->length) return ;
    q->tail = (q->tail + 1) % q->length;
    q->q[q->tail] = val;
     q->count++;
    return ;
}

Node top(Queue *q){
    return q->q[q->head];
}
void pop(Queue *q){
    q->head = (q->head + 1) % q->length;
    q->count--;
}

int empty(Queue * q){
    return q->count <= 0;
}

void bfs(Node *node){
    Queue *q = initq(100);
    if(node == NULL) return ;
    push(q,*node);
    while(!empty(q)){
        Node temp = top(q);
        pop(q);
        printf("%c",temp.data);
        if(temp.lchild != NULL) push(q,*temp.lchild);
        if(temp.rchild != NULL) push(q,*temp.rchild);
        if(!empty(q)) printf(" ");
    }
}

int main(){
    char str[1000];
    scanf("%[^\n]s",str);
    Node * root = NULL;
    root = build(str,0,strlen(str) - 1);
    //preorder(root);
    //printf("\n");
    bfs(root);
    printf("\n");
    return 0;
}