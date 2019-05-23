#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node, *LinkedList;

LinkedList insert(LinkedList head, Node *node, int index) {
    if (head == NULL) {
       if(index != 0) {
           return NULL;
       } 
        head = node;
        return head;
    }
    if(index == 0){
        node->next = head;
        head = node;
        return head;
    }
    Node *current_node = head;
    int count = 0;
    while(current_node->next != NULL && count < index - 1){
        current_node = current_node->next;
        count++;
    }
    if(count == index - 1){
        node->next = current_node->next;
        current_node->next = node;

    }
    return head;
}

void output(LinkedList head) {
    if(head == NULL){
        return ;
    }
    Node *current_node = head;
    while(current_node->next){
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
    printf("%d\n", current_node->data);
}

void clear(LinkedList head) {
    Node * current_node = head;
    while(current_node != NULL){
        Node * delete_node = current_node;
        current_node = current_node->next;
        free(delete_node);
    }
}

int main() {
    LinkedList linkedlist = NULL;
    int n,a,b,c = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d",&a,&b);
        Node * node = (Node *)malloc(sizeof(Node));
        node->data = b;
        node->next = NULL;
        if(a <= c){
            linkedlist = insert(linkedlist,node,a);    
            printf("success\n");
            c++;
        } else {
              printf("failed\n");          
        }
    }
    output(linkedlist);
    clear(linkedlist);
    return 0;
}