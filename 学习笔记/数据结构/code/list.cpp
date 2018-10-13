/*************************************************************************
	> File Name: list.cpp
	> Author: ldc
	> Mail: litesla
	> Created Time: 2018年10月11日 星期四 20时22分20秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;


typedef struct LinkNode{
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct LinkList{
    LinkNode head;
    int length;
}LinkList;

LinkList * init(){
    LinkList *p = (LinkList *)malloc(sizeof(LinkList));
    p->length = 0;
    return p;
}

LinkNode *getNewNode(int value){
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = value;
    p->next = NULL;
    return p;
}
void insert(LinkList *l, int value, int ind){
    LinkNode *p = &(l->head);
    while(ind--){
        p=p->next;
        if(p == NULL) return ;
    }
    LinkNode *new_node = getNewNode(value);
    new_node->next = p->next;
    p->next = new_node;
    l->length++;
    return ;
}

void   erase(LinkList *l, int ind) {
    LinkNode *p = &(l->head);
    while (ind--) {
        p = p->next;
        if(p == NULL) return ;
    }
    if(p->next == NULL) return ;
    LinkNode *q = p->next;
    p->next=p->next->next;
    free(q);
    l->length--;
    return ;
}



void clear(LinkList *l){
    if(l == NULL) return ;
    LinkNode *p = &(l->head), *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(l);
    return ;
}

void output(LinkList *l){
    LinkNode *p = &(l->head);
    while(p != NULL){
        printf("%d->",p->data);
        p=p->next;
    }
    printf("NULL\n");
    return ;
}


int main(){
    srand(time(0));
    LinkList *l = init();
    #define max_op 20 
    int length = 0;
    for(int i = 0; i < max_op; i++){
        int op = rand() %4,value, ind;
        switch(op){
            case 0:
            case 1:
            case 2:{
                ind = rand() % (length +1);
                value = rand() %100;
                printf("insert(%d,%d) to LinkList\n", value,ind);
                insert(l,value,ind);
                output(l);
                length +=1;
            }break;
            case 3:{ 
                if(length == 0) break;
                ind = rand() % (length +1);
                printf("erase(%d) to LinkList\n",ind);
                erase(l,ind);
                output(l);
                length--;
            }break;
        }
    }
    clear(l);
    return 0;
}
