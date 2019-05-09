#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char data;
    struct Node *lchild, *rchild;
}Node;
/*
Node* init(Node * node,char data){
    Node * node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchlid = NULL;
    return node;
}*/
void preorder(Node *node){
    if (node == NULL) {
        return ;
    }
    printf("%c",node->data);
    preorder(node->lchild);
    preorder(node->rchild);
}
void ppreorder(Node *node){
    if(node == NULL){
        return ;
    }
    printf("%c", node->data);
    if(node->lchild != NULL || node->rchild != NULL){
        printf("(");
        ppreorder(node->lchild);
        node->rchild != NULL && printf(",");
        ppreorder(node->rchild);
        printf(")");
    }
}
int main(){
    Node root[1000];
    char ch;
    int i = 0;
    do{
        scanf("%c", &ch);
        if (ch >= 'A' && ch <= 'Z') {
            root[i].data = ch;
            root[i].lchild = NULL;
            root[i].rchild = NULL;
            i++;
        }
    }while(ch != '$');
    //printf("%c", root[1].data);
    for (int j = 0; 2*j + 2 <= i; j++) {
        root[j].lchild = &root[j * 2 + 1];
        if(j * 2 + 2 == i){
            continue;
        }else{
            root[j].rchild = &root[j * 2 + 2];
        }
    }
    //preorder(&root[0]);
    //printf("\n");
    if(i > 0){
        ppreorder(&root[0]);
        printf("\n");
    }
    return ;
}