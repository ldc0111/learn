/*************************************************************************
	> File Name: 2.List.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年08月11日 星期日 23时32分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct LinkNode{
    int data;
    struct LinkNode *next;
}*Linklist, LinkNode;

LinkNode *getNewNode(int val) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    p->data = val;
    p->next = NULL;
}


LinkNode *insert(Linklist l, int val,int ind){
    LinkNode ret, *p = &ret;
    ret.next = l;
    while(ind--) {
        p = p->next;
        if (p == NULL) return l;
    }
    LinkNode *new_node = getNewNode(val);
    new_node->next = p->next;
    p->next = new_node;
    return ret.next;
}


LinkNode* erase(Linklist l, int ind) {
    LinkNode ret, *p = &ret;
    ret.next = l;
    while(ind--) {
        p = p->next;
        if (p == NULL) return l;    
    }
    if (p->next == NULL) return l;
    LinkNode *q = p->next;
    p->next = p->next->next;
    free(q);
    return ret.next;
}

LinkNode * linkflip(Linklist l) {
    if (l == NULL) return l;
    LinkNode *pre = NULL,*cur = l,*tem = NULL;
    while(cur!= NULL){
        tem = cur;
        cur = cur->next;
        tem->next = pre;
        pre = tem;
    }
    return pre;
}
LinkNode * linkflip2(LinkNode *node) {
    if (node == NULL || node->next == NULL) return node;
    LinkNode *ne = node->next;
    LinkNode * he = linkflip2(ne);
    node->next = NULL;
    ne->next = node;
    return he;
}

void clear(Linklist head){
    if (head == NULL) return ;
    LinkNode *p = head, *q;
    while(p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
    return ;
}


void output(Linklist l) {
    LinkNode *p = l;
    printf("[");
    while(p != NULL) {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("]\n");
    return ;
}

int main() {
    Linklist l = NULL;
    int length = 0;
    #define MAX_OP 30
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value,ind;
        switch(op){
            case 0:
            case 1:
            case 2:{
                ind = rand() % (length + 1);
                int val = rand() % 1000;
                printf("insert(%d,%d) to LinkList\n",value,ind);
                l = insert(l,val,ind);
                output(l);
                length += 1;
            }break;
            case 3:{
                if (length == 0) break;
                ind = rand() % length;
                printf("erase(%d)to Linklist\n",ind);
                l = erase(l,ind);
                output(l); 
                length -= 1;
                
            }break;
        }
    }
    output(l);
    l = linkflip(l);
    l = linkflip2(l);
    output(l);
    clear(l);
    return 0;
}
