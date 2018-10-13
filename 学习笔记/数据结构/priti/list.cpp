/*************************************************************************
	> File Name: list.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月11日 星期四 21时21分30秒
 ************************************************************************/

#include<iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

typedef struct LinkNode{
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct LinkList{
    int length;
    struct LinkNode head;
}LinkList;

LinkList * init(){
    LinkList *p = (LinkList *)malloc(sizeof(LinkList));
    p->head.next = NULL;
    p->length = 0;
    return p;
}

LinkNode * getNewNode(int value){
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = value;
    p->next = NULL;
    return p;
}

void insert(LinkList *l,int value,int ind){
    if(l == NULL) return ;
    if(ind < 0 || ind > l->length) return ;
    LinkNode *p = &(l->head);
    while(ind--){
        p=p->next;
    }
    LinkNode *new_node = getNewNode(value);
    new_node->next = p->next;
    p->next = new_node;
    l->length++;
    return ;
}
void erase(LinkList *l,int ind) {
    if(ind < 0 || ind >= l->length) return ;
    LinkNode *p = &(l->head);
    while(ind--){
        p=p->next;
    }
    LinkNode *q = p->next;
    p->next=p->next->next;
    free(q);
    l->length -= 1;
    return ;
}
void clear(LinkList * l){
    if (l == NULL) return ;
    LinkNode *p = l->head.next, *q;
    while(p){
        q = p;
        p = p->next;
        free(q);
    }
    free(l);
    return ;
}

void output(LinkList *l){
    if(l == NULL) return ;
    LinkNode *p = l->head.next;
    printf("[");
    while(p){
        printf(" %d->", p->data);
        p=p->next;
    }
    printf("NULL ]\n");
    return ;

}

int main(){
    srand(time(0));
    LinkList *l = init();
    #define max_op 20 
    for(int i = 0; i < max_op; i++){
        int op = rand()%4,value,ind;
        switch(op){
            case 0:
            case 1:
            case 2:{
                ind = rand() % (l->length + 1);
                value = rand() %100;
                printf("insert(%d, %d) to LinkList\n", value,ind);
                insert(l,value,ind);
                output(l);

            }break;
            case 3:{
                ind = rand() % (l->length + 1);
                printf("erase(%d) to LinkList\n", ind);
                erase(l,ind);
                output(l);
                
            }break;
        }
    }
    clear(l);
    return 0;
}
