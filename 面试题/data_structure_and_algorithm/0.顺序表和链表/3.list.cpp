/*************************************************************************
	> File Name: 3.list.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月12日 星期一 00时35分32秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct LinkNode{
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct LinkList{
    LinkNode head;
    int length;
}LinkList;

LinkList * init(){
    return (LinkList *)calloc(sizeof(LinkList),1);
}

LinkNode *getNewNode(int val){
    LinkNode *p = (LinkNode *)calloc(sizeof(LinkNode), 1);
    p->data = val;
    return p;
}

int insert(LinkList *l, int val,int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0;
    LinkNode *p = &(l->head);
    while (ind--) {
        p = p->next;
        if (!p) return 0;
    }
    LinkNode *newNode = getNewNode(val);
    newNode->next = p->next;
    p->next = newNode;
    l->length += 1;

    return 1;
}

int erase(LinkList *l, int ind) {
    if (l == NULL ) return 0;
    if (ind < 0 || ind >= l->length) return 0;//注意这一点好好想想，容易错

    LinkNode *p = &(l->head);
    while (ind--) {
        p = p->next;
        if (!p) return 0;
    }
    LinkNode *deleteNode = p->next;
    p->next = p->next->next;
    free(deleteNode);
    l->length -= 1;
    return 1;
}


void clear(LinkList * l){
    if(l == NULL) return ;
    LinkNode *p = l->head.next, *q;
    while(p){
        q = p;
        p = q->next;
        free(q);
    }
    free(l);
    return ;
}


void output(LinkList *l){
    printf("[");
    LinkNode *p = l->head.next;
    while(p){
        printf(" %d",p->data);
        p = p->next;
    }
    printf("]\n");
    return ;
}

int main() {
    LinkList *l = init();
    #define MAX_OP 30
    
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 3,val = 0,ind = 0;
        printf("[%d, op = %d]\n", i, op);
        switch(op){
            case 0:
            case 1:{
                val = rand() % 100;
                ind = rand() % (l->length + 2) - 1;
                printf("insert(%d,%d) = %d to LinkList.\n",val,ind,insert(l ,val, ind));
                output(l);

            }break;
            case 2:{
                ind = rand() % (l->length + 2) - 1;
                printf("%d\n",ind);
                printf("erase(%d) = %d to LinkList.\n",ind ,erase(l,ind));
                output(l);
            }break;
        }
    }
    clear(l);
    return 0;
}
