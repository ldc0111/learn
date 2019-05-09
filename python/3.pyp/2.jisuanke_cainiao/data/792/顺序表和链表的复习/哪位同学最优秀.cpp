#include <stdio.h>
#include <stdlib.h>
typedef struct LinkedNode{
    int data;
    struct LinkedNode *next;
}LinkedNode;

typedef struct LinkedList{
    int length;
    LinkedNode head;
}LinkedList;

LinkedList *init(int n){
    LinkedList *p = (LinkedList *)malloc(sizeof(LinkedList));
    p->length = n;
    p->head.next = NULL;
    LinkedNode *current_node=  &(p->head);
    for (int i = 1; i <= n; i++) {
        LinkedNode * new_node = (LinkedNode *)malloc(sizeof(LinkedNode));
        new_node->data = i;
        new_node->next = NULL;
        current_node->next = new_node;
        current_node = new_node;
    }
    return p;
}
void delete_node(LinkedList *l,int ind){
    if(ind < 0 || ind > l->length){
        return ;
    }
    LinkedNode *p = &(l->head);
    while(ind--){
        p=p->next;
    }
    LinkedNode *q = p->next;
    p->next = p->next->next;
    free(q);
    l->length--;
    return ;
}
void output1(LinkedList *l){
    int ind = l->length/2;
    LinkedNode *q = l->head.next;
    while(ind--){
        q=q->next;
    }
    printf("%d\n",q->data);
}

void output(LinkedList *l){
    LinkedNode *q = l->head.next;
    while(q){
        printf("%d ", q->data);
        q = q->next;
    }
}
int main(){
    int n,m;
    scanf("%d%d", &n,&m);
    LinkedList *l = init(n);
    for(int i = 0; i < m; i++){
        int temp;
        scanf("%d",&temp);
        delete_node(l,temp - 1);
    }
    //printf("%d\n", l->length);
    //output(l);
    output1(l);
    return 0;
}