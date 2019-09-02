/*************************************************************************
	> File Name: ac.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月01日 星期日 11时34分56秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26
#define BEGIN_LETTER 'a'

typedef struct Node{
    int flag;
    struct Node *next[BASE],*fail;
}Node;


typedef struct Queue{
    Node **data;
    int head,tail,size;
}Queue;

Queue *init_queue(int n) {
    Queue *q = (Queue *)calloc(sizeof(Queue),1);
    q->data = (Node **)calloc(sizeof(Node *),n);
    q->size = n;
    return q;
}

Node *front(Queue *q) {
    return q->data[q->head];
}


int empty(Queue *q) {
    return q->head == q->tail;
}

void clear_queue(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void push(Queue *q, Node *node) {
    q->data[q->tail++] = node;
    return ;
}

void pop(Queue * q) {
    if (empty(q)) return ;
    q->head++;
}


Node *getNewNode(){
    Node *p = (Node *)calloc(sizeof(Node),1);
    return p;
}

int insert(Node *root, const char *str) {
    Node *p = root;
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) p->next[ind] = getNewNode(),cnt++;
        p = p->next[ind];
    }
    p->flag = 1;
    return cnt;
}


void build_ac(Node *root,int n) {
    Queue *q = init_queue(n + 10);
    root->fail = NULL;
    push(q,root);
    while (!empty(q)) {
        Node *now_node = front(q);
        pop(q);
        for (int i = 0; i < BASE; i++) {
            if (now_node->next[i] == NULL) continue;
            Node *p = now_node->fail;
            while(p && p->next[i] == NULL) p = p->fail;
            if (p == NULL) now_node->next[i]->fail = root;
            else now_node->next[i]->fail == p->next[i];
            push(q,now_node->next[i]);
        }
    }
    return ;
}


int match(Node *root,const char *str) {
    Node *p = root;
    int cnt = 0;
    for (int i = 0;str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        while (p && p->next[ind] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else p = p->next[ind];
        Node *q = p;
        while (q) {
            cnt += q->flag;
            q = q->fail;
        }
    }

    return cnt;
}





void clear(Node *node){
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}




int main() {
    Node *root = getNewNode();
    int op,cnt = 0,n;
    char str[1000];
    scanf("%d", &n);
    for (int i = 0; i < n; i++ ) {
        scanf("%s",str);
        cnt += insert(root,str);
    }
    //build ac
    build_ac(root, cnt);
    scanf("%s",str);
    //match ac 
    printf("match word cnt : %d\n", match(root,str));

    return 0;
}
