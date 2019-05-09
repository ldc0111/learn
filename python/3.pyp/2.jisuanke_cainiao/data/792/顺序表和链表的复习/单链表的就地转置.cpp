#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct LinkedNode{
    char data;
    struct LinkedNode *next;
}LinkedNode;
typedef struct LinkedList{
    int length;
    LinkedNode head;
}LinkedList;
LinkedList* init(){
    LinkedList *p = (LinkedList *)malloc(sizeof(LinkedList));
    p->length = 0;
    p->head.next = NULL;
    return p;
}

void insert(LinkedList *l, int ind,char value){
    if(ind < 0 || ind > l->length){
        return ;
    }
    LinkedNode *p = &(l->head);
    while(ind--){
        p=p->next;
    }
    LinkedNode * new_node = (LinkedNode *)malloc(sizeof(LinkedNode));
    new_node->data = value;
    new_node->next = p->next;
    p->next = new_node;
    l->length++;
    return ;
}


void output(LinkedList *l){
    if(l == NULL || l->length <= 0) return ;
    LinkedNode *current_node = l->head.next;
    while(current_node->next){
        printf("%c ", current_node->data);
        current_node=current_node->next;
    }
    printf("%c\n", current_node->data);
}

void reverse(LinkedList *l){
    if(l == NULL || l->length <= 1) return ;
    LinkedNode *current_node = l->head.next->next,*next_node;
    l->head.next->next = NULL;
    //next->node->next = l->head.
    while(current_node!= NULL){
        next_node = current_node->next;
        current_node->next = l->head.next;
        l->head.next = current_node;
        current_node = next_node;
    }
    return ;
}
int main(){
    int n;
    LinkedList *l = init();
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        getchar();
        char temp;
        scanf("%c", &temp);
        insert(l, i,temp);
        //printf("%c", temp);
    }
    //output(l);
    //printf("%d\n",l->length);
    reverse(l);
    output(l);
    return 0;
}