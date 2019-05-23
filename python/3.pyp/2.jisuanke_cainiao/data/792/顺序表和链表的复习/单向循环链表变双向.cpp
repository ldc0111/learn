#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode{
    int data;
    struct LinkedNode *prior,*next;
}LinkedNode;

typedef struct LinkedList{
    int length;
    LinkedNode head;
}LinkedList;
LinkedList* init(){
    LinkedList *p = (LinkedList *)malloc(sizeof(LinkedList));
    p->length = 0;
    p->head.next = 0;
    return p;
}

LinkedNode* getNode(int value){
    LinkedNode *p = (LinkedNode *)malloc(sizeof(LinkedNode));
    p->data  = value;
    p->prior = NULL;
    p->next = NULL;
    return p;
}

void insert(LinkedList *l,int ind,int value){
    if(ind < 0 || ind > l->length) return ;
    LinkedNode *new_node = getNode(value);
    if(l->length == 0){
        l->head.next = new_node;
        new_node->next = new_node;
        new_node->prior = new_node;
        l->length++;
        return ;
    }
    LinkedNode *p = &(l->head);
    while(ind--){
        p=p->next;
    }
    new_node->next = p->next;
    p->next = new_node;
    new_node->next->prior = new_node;
    new_node->prior = p;
    l->length++;
    return ;
    
}
void output(LinkedList *l,int value){
    if(l->length  == 0) return;
    LinkedNode *p = l->head.next,*temp;
    while(p->data != value) p=p->next;
    temp = p;
    while(p->prior != temp){
        printf("%d ", p->data);
        p = p->prior;
    }
    printf("%d\n",p->data);
}

int main(){
    int n,temp;
    LinkedList *l = init();
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &temp);
        insert(l,i,temp);
    }
    //printf("%d")
    scanf("%d", &temp);
    output(l,temp);
    return 0;
}